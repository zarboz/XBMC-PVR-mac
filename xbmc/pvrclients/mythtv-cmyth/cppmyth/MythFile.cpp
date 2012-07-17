
#include "MythFile.h"
#include "client.h"


using namespace ADDON;

/*
 *        MythFile
 */


 MythFile::MythFile()
   :m_file_t(new MythPointer<cmyth_file_t>()),m_conn(MythConnection())
 {
 }

  MythFile::MythFile(cmyth_file_t myth_file,MythConnection conn)
    : m_file_t(new MythPointer<cmyth_file_t>()),m_conn(conn)
 {
   *m_file_t=myth_file;
 }
 
void MythFile::UpdateDuration (unsigned long long length )
 {
    m_conn.Lock();
    CMYTH->UpdateFileLength(*m_file_t,length);
    m_conn.Unlock();
  }
  
  bool  MythFile::IsNull()
  {
    if(m_file_t==NULL)
      return true;
    return *m_file_t==NULL;
  }

  int MythFile::Read(void* buffer,long long length)
  {
   m_conn.Lock();
   int bytesRead=CMYTH->FileRead(*m_file_t,static_cast<char*>(buffer),length);
   m_conn.Unlock();
   return bytesRead;
  }

  long long MythFile::Seek(long long offset, int whence)
  {
    m_conn.Lock();
    long long retval = CMYTH->FileSeek(*m_file_t,offset,whence);
    m_conn.Unlock();
    return retval;
  }
  
  unsigned long long MythFile::CurrentPosition()
  {
    m_conn.Lock();
    unsigned long long retval = CMYTH->FilePosition(*m_file_t);
    m_conn.Unlock();
    return retval;
  }
  
  unsigned long long MythFile::Duration()
  {
    m_conn.Lock();
    unsigned long long retval = CMYTH->FileLength(*m_file_t);
    m_conn.Unlock();
    return retval;
  }