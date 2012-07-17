#include "MythConnection.h"
#include "MythRecorder.h"
#include "MythFile.h"
#include "MythSGFile.h"
#include "MythProgramInfo.h"
#include "MythEventHandler.h"
#include "MythTimer.h"
#include "client.h"

using namespace ADDON;


/*   
*								MythConnection
*/

MythConnection::MythConnection():
m_conn_t(new MythPointerThreadSafe<cmyth_conn_t>()),m_server(""),m_port(0)
{  
}


MythConnection::MythConnection(CStdString server,unsigned short port):
m_conn_t(new MythPointerThreadSafe<cmyth_conn_t>),m_server(server),m_port(port)
{
  char *cserver=strdup(server.c_str());
  cmyth_conn_t connection=CMYTH->ConnConnectCtrl(cserver,port,64*1024, 16*1024);
  free(cserver);
  *m_conn_t=(connection);
  
}

std::vector< CStdString > MythConnection::GetStorageGroupFileList_(CStdString sgGetList)
  {
    std::vector< CStdString > retval;
    Lock();
    char **sg;
    CStdString bckHostNme = GetBackendHostname();
    int len = CMYTH->StoragegroupFilelist(*m_conn_t,&sg,sgGetList.Buffer(),bckHostNme.Buffer());
    if(!sg)
      return retval;
    for(int i=0;i<len;i++)
    {
      char *tmp=sg[i];
      CStdString tmpSG(tmp);
      XBMC->Log(LOG_DEBUG,"%s - ############################# - %s",__FUNCTION__,tmpSG.c_str());
      retval.push_back(tmpSG/*.c_str()*/);
    }
    
    CMYTH->RefRelease(sg);
    Unlock();
    return retval;
  }

std::vector< MythSGFile > MythConnection::GetStorageGroupFileList(CStdString storagegroup)
{
    Lock();
    CStdString hostname = GetBackendHostname();
    cmyth_storagegroup_filelist_t filelist=CMYTH->StoragegroupGetFilelist(*m_conn_t,storagegroup.Buffer(),hostname.Buffer());
    int len=CMYTH->StoragegroupFilelistCount(filelist);
    std::vector< MythSGFile >  retval(len);
    for(int i=0;i<len;i++)
    {
      cmyth_storagegroup_file_t file=CMYTH->StoragegroupFilelistGetItem(filelist,i);
      retval.push_back(MythSGFile(file));
    }
    CMYTH->RefRelease(filelist);
    Unlock();
    return retval;
}

MythFile MythConnection::ConnectPath(CStdString filename, CStdString storageGroup)
{
  Lock();
  MythFile retval = MythFile(CMYTH->ConnConnectPath(filename.Buffer(),*m_conn_t,64*1024, 16*1024,storageGroup.Buffer()),*this);
  Unlock();
  return retval;
}

  bool MythConnection::IsConnected()
{
  return *m_conn_t!=0;
}

MythRecorder MythConnection::GetFreeRecorder()
{
  Lock();
  MythRecorder retval = MythRecorder(CMYTH->ConnGetFreeRecorder(*m_conn_t),*this);
  Unlock();
  return retval;
}

MythRecorder MythConnection::GetRecorder(int n)
{
  Lock();
  MythRecorder retval = MythRecorder(CMYTH->ConnGetRecorderFromNum(*m_conn_t,n),*this);
  Unlock();
  return retval;
}

  boost::unordered_map<CStdString, MythProgramInfo>  MythConnection::GetRecordedPrograms()
  {
    Lock();
    boost::unordered_map<CStdString, MythProgramInfo>  retval;
    cmyth_proglist_t proglist=CMYTH->ProglistGetAllRecorded(*m_conn_t);
    int len=CMYTH->ProglistGetCount(proglist);
    for(int i=0;i<len;i++)
    {
      cmyth_proginfo_t cmprog=CMYTH->ProglistGetItem(proglist,i);
      MythProgramInfo prog=CMYTH->ProginfoGetDetail(*m_conn_t,cmprog);
      CStdString path=prog.Path();
      retval.insert(std::pair<CStdString,MythProgramInfo>(path.c_str(),prog));
    }
    CMYTH->RefRelease(proglist);
    Unlock();
    return retval;
  }

  boost::unordered_map<CStdString, MythProgramInfo>  MythConnection::GetPendingPrograms()
   {
    Lock();
    boost::unordered_map<CStdString, MythProgramInfo>  retval;
    cmyth_proglist_t proglist=CMYTH->ProglistGetAllPending(*m_conn_t);
    int len=CMYTH->ProglistGetCount(proglist);
    for(int i=0;i<len;i++)
    {
      MythProgramInfo prog=CMYTH->ProglistGetItem(proglist,i);
      CStdString filename;
      filename.Format("%i_%i",prog.ChannelID(),prog.StartTime());
      retval.insert(std::pair<CStdString,MythProgramInfo>(filename.c_str(),prog));
    }
    CMYTH->RefRelease(proglist);
    Unlock();
    return retval;
  }

  boost::unordered_map<CStdString, MythProgramInfo>  MythConnection::GetScheduledPrograms()
   {
    Lock();
    boost::unordered_map<CStdString, MythProgramInfo>  retval;
    cmyth_proglist_t proglist=CMYTH->ProglistGetAllScheduled(*m_conn_t);
    int len=CMYTH->ProglistGetCount(proglist);
    for(int i=0;i<len;i++)
    {
      cmyth_proginfo_t cmprog=CMYTH->ProglistGetItem(proglist,i);
      MythProgramInfo prog=CMYTH->ProginfoGetDetail(*m_conn_t,cmprog);//Release cmprog????
      CStdString path=prog.Path();
      retval.insert(std::pair<CStdString,MythProgramInfo>(path.c_str(),prog));
    }
    CMYTH->RefRelease(proglist);
    Unlock();
    return retval;
  }

  bool  MythConnection::DeleteRecording(MythProgramInfo &recording)
  {
    Lock();
    bool retval = CMYTH->ProginfoDeleteRecording(*m_conn_t,*recording.m_proginfo_t)==0;
    Unlock();
    return retval;
  }


MythEventHandler MythConnection::CreateEventHandler()
{
  return MythEventHandler(m_server,m_port);
}

CStdString MythConnection::GetServer()
{
  return m_server;
}

int MythConnection::GetProtocolVersion()
{
  Lock();
  int retval = CMYTH->ConnGetProtocolVersion(*m_conn_t);
  Unlock();
  return retval;
}

bool MythConnection::GetDriveSpace(long long &total,long long &used)
{
  Lock();
  bool retval = CMYTH->ConnGetFreespace(*m_conn_t,&total,&used)==0;
  Unlock();
  return retval;
}

bool MythConnection::UpdateSchedules(int id)
{
  Lock();
  CStdString cmd;
  cmd.Format("RESCHEDULE_RECORDINGS %i",id);
  bool retval = CMYTH->ScheduleRecording(*m_conn_t,cmd.Buffer())>=0;
  Unlock();
  return retval;  
}

MythFile MythConnection::ConnectFile(MythProgramInfo &recording)
{
  Lock();
  MythFile retval = MythFile(CMYTH->ConnConnectFile(*recording.m_proginfo_t,*m_conn_t,64*1024, 16*1024),*this);
  Unlock();
  return retval;
}

bool MythConnection::IsNull()
{
  if(m_conn_t==NULL)
    return true;
  return *m_conn_t==NULL;
}

void MythConnection::Lock()
{
  if(g_bExtraDebug)
    XBMC->Log(LOG_DEBUG,"Lock %i",m_conn_t.get());
  m_conn_t->Lock();
  if(g_bExtraDebug)
    XBMC->Log(LOG_DEBUG,"Lock acquired %i",m_conn_t.get());
}

void MythConnection::Unlock()
{
  if(g_bExtraDebug)
    XBMC->Log(LOG_DEBUG,"Unlock %i",m_conn_t.get());
  m_conn_t->Unlock();
  
}

  CStdString MythConnection::GetSetting(CStdString hostname,CStdString setting)
  {
    CStdString retval;
    Lock();
    char * value = CMYTH->ConnGetSetting(*m_conn_t,hostname.Buffer(),setting.Buffer());
    retval = value;
    CMYTH->RefRelease(value);
    value = NULL;
    Unlock();
    return retval;
  }

  bool MythConnection::SetSetting(CStdString hostname,CStdString setting,CStdString value)
  {
    bool retval = false;
    Lock();
    retval = CMYTH->ConnSetSetting(*m_conn_t,hostname.Buffer(),setting.Buffer(),value.Buffer()) >= 0;
    Unlock();
    return retval;
  }

  CStdString MythConnection::GetHostname()
  {
    CStdString retval;
    Lock();
    char * hostname = CMYTH->ConnGetClientHostname(*m_conn_t);
    retval = hostname;
    CMYTH->RefRelease(hostname);
    hostname = NULL;
    Unlock();
    return retval;
  }

  CStdString MythConnection::GetBackendHostname()
  {
    CStdString retval;
    Lock();
    char * hostname = CMYTH->ConnGetBackendHostname(*m_conn_t);
    retval = hostname;
    CMYTH->RefRelease(hostname);
    hostname = NULL;
    Unlock();
    return retval;
  }


  
/*
Profile = Default
recpriority = 0
maxepisodes = 0
maxnewest = 0
recgroup = Default
dupmethod = 6
dupin = 15
playgroup = Default
storagegroup = Default

Defaults for MythTimer
AutoTranscode / DefaultTranscoder
AutoRunUserJob1
AutoRunUserJob2
AutoRunUserJob3
AutoRunUserJob4
autocommflag => AutoCommercialFlag
AutoExpireDefault
transcoder => DefaultTranscoder?? 

start/endoffset => DefaultStartOffset/DefaultEndOffset

*/

  void MythConnection::DefaultTimer(MythTimer &timer)
  {
    timer.AutoTranscode(atoi(GetSetting("NULL","AutoTranscode").c_str())>0);
    timer.Userjob(1,atoi(GetSetting("NULL","AutoRunUserJob1").c_str())>0);
    timer.Userjob(2,atoi(GetSetting("NULL","AutoRunUserJob2").c_str())>0);
    timer.Userjob(3,atoi(GetSetting("NULL","AutoRunUserJob3").c_str())>0);
    timer.Userjob(4,atoi(GetSetting("NULL","AutoRunUserJob4").c_str())>0);
    timer.AutoCommFlag(atoi(GetSetting("NULL","AutoCommercialFlag").c_str())>0);
    timer.AutoExpire(atoi(GetSetting("NULL","AutoExpireDefault").c_str())>0);
    timer.Transcoder(atoi(GetSetting("NULL","DefaultTranscoder").c_str()));
    timer.StartOffset(atoi(GetSetting("NULL","DefaultStartOffset").c_str()));
    timer.StartOffset(atoi(GetSetting("NULL","DefaultEndOffset").c_str()));
        
  }
