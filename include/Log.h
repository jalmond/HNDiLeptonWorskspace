#ifndef Log_h
#define Log_h



void Message(TString message , bool m_debug){

  if(m_debug) cout << message << endl;
}
void PrintOut(TString mess){
  cout << "%%%%%%%%%%%%%%%%%%%%    " << mess << " %%%%%%%%%%%%%%%%%%%% " << endl;
}

void PrintSetup(TString name, TString era){

  cout << "Setting up code for " << name << " running era "  << era << endl;
}

void PreLogMessage(int n=1){

  for(int i=0; i < n; i++) cout << "------------------------------------------" << endl;
}

#endif
