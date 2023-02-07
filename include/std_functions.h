#ifndef std_functions_h
#define std_functions_h

#include  "Log.h"


TString GetHostname(){
  char hostbuffer[256];
  int hostname = gethostname(hostbuffer, sizeof(hostbuffer));

  TString s_hostname = TString(hostname);
  return s_hostname;
}

void sMakeDir(const std::string &s)
{

  struct stat buffer;
  if( (stat (s.c_str(), &buffer) == 0)) return;
  gSystem->mkdir(TString(s));

}
void MakeDir(TString a){
  sMakeDir(string(a));
}


bool IsPathExist(const std::string &s)
{

  struct stat buffer;
  return (stat (s.c_str(), &buffer) == 0);
}
#endif
