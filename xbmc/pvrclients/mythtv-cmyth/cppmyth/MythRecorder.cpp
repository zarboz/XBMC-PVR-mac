
#include "MythRecorder.h"
#include "MythProgramInfo.h"
#include "MythChannel.h"
#include "client.h"

using namespace ADDON;

/*
*								Myth Recorder
*/


MythRecorder::MythRecorder():
m_recorder_t(new MythPointerThreadSafe<cmyth_recorder_t>()),livechainupdated(new int(0)),m_conn()
{
}

MythRecorder::MythRecorder(cmyth_recorder_t cmyth_recorder,MythConnection conn):
m_recorder_t(new MythPointerThreadSafe<cmyth_recorder_t>()),livechainupdated(new int(0)),m_conn(conn)
{
  *m_recorder_t=cmyth_recorder;
}

bool MythRecorder::SpawnLiveTV(MythChannel &channel)
{
  char* pErr=NULL;
  CStdString channelNum = channel.Number();
  m_conn.Lock();
  //m_recorder_t->Lock();
  //check channel
  *livechainupdated=0;
  *m_recorder_t=(CMYTH->SpawnLiveTv(*m_recorder_t,64*1024, 16*1024,MythRecorder::prog_update_callback,&pErr,channelNum.GetBuffer()));
  int i=20;
  while(*livechainupdated==0&&i--!=0)
  {
    //m_recorder_t->Unlock();
    m_conn.Unlock();
    usleep(100000);
    m_conn.Lock();
    //m_recorder_t->Lock();
  }
  //m_recorder_t->Unlock();
  m_conn.Unlock();
  ASSERT(*m_recorder_t);
  
  if(pErr)
    XBMC->Log(LOG_ERROR,"%s - %s",__FUNCTION__,pErr);
  return pErr==NULL;
}

bool MythRecorder::LiveTVChainUpdate(CStdString chainID)
{
  m_conn.Lock();
  char* buffer=strdup(chainID.c_str());
  //m_recorder_t->Lock();
  bool retval=CMYTH->LivetvChainUpdate(*m_recorder_t,buffer,16*1024)==0;
  if(!retval)
    XBMC->Log(LOG_ERROR,"LiveTVChainUpdate failed on chainID: %s",buffer);
  *livechainupdated=1;
  //m_recorder_t->Unlock();
  free(buffer);
  m_conn.Unlock();
  return retval;
}

void MythRecorder::prog_update_callback(cmyth_proginfo_t prog)
{
  XBMC->Log(LOG_DEBUG,"prog_update_callback");

}


bool MythRecorder::IsNull()
{
  if(m_recorder_t==NULL)
    return true;
  return *m_recorder_t==NULL;
}



bool MythRecorder::IsRecording()
{
  m_conn.Lock();
  //m_recorder_t->Lock();
  bool retval=CMYTH->RecorderIsRecording(*m_recorder_t)==1;
  //m_recorder_t->Unlock();
  m_conn.Unlock();
  return retval;
}

bool MythRecorder::IsTunable(MythChannel &channel)
{
  m_conn.Lock();

  XBMC->Log(LOG_DEBUG,"%s: called for recorder %i, channel %i",__FUNCTION__,ID(),channel.ID());

  cmyth_inputlist_t inputlist=CMYTH->GetFreeInputlist(*m_recorder_t);

  bool ret = false;
  for (int i=0; i < inputlist->input_count; ++i)
  {
    cmyth_input_t input = inputlist->input_list[i];
    if ((int)input->sourceid != channel.SourceID())
    {
      XBMC->Log(LOG_DEBUG,"%s: skip input, source id differs (channel: %i, input: %i)",__FUNCTION__, channel.SourceID(), input->sourceid);
      continue;
    }

    if (input->multiplexid && (int)input->multiplexid != channel.MultiplexID())
    {
      XBMC->Log(LOG_DEBUG,"%s: skip input, multiplex id id differs (channel: %i, input: %i)",__FUNCTION__, channel.MultiplexID(), input->multiplexid);
      continue;
    }

    XBMC->Log(LOG_DEBUG,"%s: using recorder, input is tunable: source id: %i, multiplex id: channel: %i, input: %i)",__FUNCTION__, channel.SourceID(), channel.MultiplexID(), input->multiplexid);

    ret = true;
    break;
  }

  CMYTH->RefRelease(inputlist);
  m_conn.Unlock();

  if (!ret)
  {
    XBMC->Log(LOG_DEBUG,"%s: recorder is not tunable",__FUNCTION__);
  }

  return ret;
}

bool MythRecorder::CheckChannel(MythChannel &channel)
{
  m_conn.Lock();
  //m_recorder_t->Lock();
  CStdString channelNum=channel.Number();
  bool retval=CMYTH->RecorderCheckChannel(*m_recorder_t,channelNum.GetBuffer())==0;
  //m_recorder_t->Unlock();
  m_conn.Unlock();
  return retval;
}

bool MythRecorder::SetChannel(MythChannel &channel)
{
  
  //m_recorder_t->Lock();
  m_conn.Lock();
  if(!IsRecording())
  {
    XBMC->Log(LOG_ERROR,"%s: Recorder %i is not recording",__FUNCTION__,ID(),channel.Name().c_str());
    //m_recorder_t->Unlock();
    m_conn.Unlock();
    return false;
  }
  CStdString channelNum=channel.Number();
  if(CMYTH->RecorderPause(*m_recorder_t)!=0)
  {
    XBMC->Log(LOG_ERROR,"%s: Failed to pause recorder %i",__FUNCTION__,ID());
    //m_recorder_t->Unlock();
    m_conn.Unlock();
    return false;
  }
  if(!CheckChannel(channel))
  {
    XBMC->Log(LOG_ERROR,"%s: Recorder %i doesn't provide channel %s",__FUNCTION__,ID(),channel.Name().c_str());
    //m_recorder_t->Unlock();
    m_conn.Unlock();
    return false;
  }
  if(CMYTH->RecorderSetChannel(*m_recorder_t,channelNum.GetBuffer())!=0)
  {
    XBMC->Log(LOG_ERROR,"%s: Failed to change recorder %i to channel %s",__FUNCTION__,ID(),channel.Name().c_str());
    //m_recorder_t->Unlock();
    m_conn.Unlock();
    return false;
  }
  if(CMYTH->LivetvChainSwitchLast(*m_recorder_t)!=1)
  {
    XBMC->Log(LOG_ERROR,"%s: Failed to switch chain for recorder %i",__FUNCTION__,ID(),channel.Name().c_str());
    //m_recorder_t->Unlock();
    m_conn.Unlock();
    return false;
  }
  *livechainupdated=0;
  int i=20;
  while(*livechainupdated==0&&i--!=0)
  {
    //m_recorder_t->Unlock();
    m_conn.Unlock();
    usleep(100000);
    //m_recorder_t->Lock();
    m_conn.Lock();
  }

  //m_recorder_t->Unlock();
  m_conn.Unlock();
  for(int i=0;i<20;i++)
  {
    if(!IsRecording())
      usleep(1000);
    else
      break;
  }

  return true;
}

int MythRecorder::ReadLiveTV(void* buffer,long long length)
{
  m_conn.Lock();
  //m_recorder_t->Lock();
  int bytesRead=CMYTH->LivetvRead(*m_recorder_t,static_cast<char*>(buffer),length);
  //m_recorder_t->Unlock();
  m_conn.Unlock();
  return bytesRead;
}

MythProgramInfo MythRecorder::GetCurrentProgram()
{
  m_conn.Lock();
  //m_recorder_t->Lock();
  MythProgramInfo retval=CMYTH->RecorderGetCurProginfo(*m_recorder_t);
  //m_recorder_t->Unlock();
  m_conn.Unlock();
  return retval;
}

long long MythRecorder::LiveTVSeek(long long offset, int whence)
{
  m_conn.Lock();
  //m_recorder_t->Lock();
  long long retval = CMYTH->LivetvSeek(*m_recorder_t,offset,whence);
  //m_recorder_t->Unlock();
  m_conn.Unlock();
  return retval;
}

long long MythRecorder::LiveTVDuration()
{
  m_conn.Lock();
  //m_recorder_t->Lock();
  long long retval = CMYTH->LivetvChainDuration(*m_recorder_t);
  //m_recorder_t->Unlock();
  m_conn.Unlock();
  return retval;
}

int MythRecorder::ID()
{
  m_conn.Lock();
  int retval = CMYTH->RecorderGetRecorderId(*m_recorder_t);
  m_conn.Unlock();
  return retval;
}

 bool  MythRecorder::Stop()
 {
   m_conn.Lock();
   bool retval = CMYTH->RecorderStopLivetv(*m_recorder_t)==0;
   m_conn.Unlock();
   return retval;
 }
