#ifndef list_functions_h
#define list_functions_h
vector<TString> GetFullSignalList(TString AnalyserName){
  
  vector<TString> List;
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M1000_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M100_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M1100_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M1200_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M125_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M1300_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M1500_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M150_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M1700_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M2000_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M200_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M2500_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M250_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M3000_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M300_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M400_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M500_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M600_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M700_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M800_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M85_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M900_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M90_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_DF_M95_private");
  List.push_back("HNL_SignalEfficiency_DYTypeI_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M10000_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M1000_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M1100_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M1200_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M1250_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M1300_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M15000_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M1500_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M1700_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M1750_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M20000_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M2000_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M2500_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M3000_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M5000_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M500_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M600_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M700_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M7500_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M750_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M800_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_DF_M900_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M10000_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M1000_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M1100_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M1200_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M1250_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M1300_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M15000_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M1500_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M1700_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M1750_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M20000_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M2000_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M2500_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M3000_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M5000_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M500_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M600_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M700_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M7500_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M750_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M800_private");
  List.push_back("HNL_SignalEfficiency_SSWWTypeI_SF_M900_private");
  List.push_back("HNL_SignalEfficiency_VBFTypeI_DF_M1000_private");
  List.push_back("HNL_SignalEfficiency_VBFTypeI_DF_M1100_private");
  List.push_back("HNL_SignalEfficiency_VBFTypeI_DF_M1200_private");
  List.push_back("HNL_SignalEfficiency_VBFTypeI_DF_M1300_private");
  List.push_back("HNL_SignalEfficiency_VBFTypeI_DF_M1500_private");
  List.push_back("HNL_SignalEfficiency_VBFTypeI_DF_M1700_private");
  List.push_back("HNL_SignalEfficiency_VBFTypeI_DF_M2000_private");
  List.push_back("HNL_SignalEfficiency_VBFTypeI_DF_M2500_private");
  List.push_back("HNL_SignalEfficiency_VBFTypeI_DF_M3000_private");
  List.push_back("HNL_SignalEfficiency_VBFTypeI_DF_M500_private");
  List.push_back("HNL_SignalEfficiency_VBFTypeI_DF_M600_private");
  List.push_back("HNL_SignalEfficiency_VBFTypeI_DF_M700_private");
  List.push_back("HNL_SignalEfficiency_VBFTypeI_DF_M800_private");
  List.push_back("HNL_SignalEfficiency_VBFTypeI_DF_M900_private");
  List.push_back("HNL_SignalEfficiency_VBFTypeI_private");
  
  return List;
}

#endif