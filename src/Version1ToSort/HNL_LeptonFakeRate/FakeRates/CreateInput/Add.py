import os 

vMVAB = []
vMVAEC = []
  for(unsigned int imva=0 ; imva < 65 ; imva++){
    double mva_d= -0.4 + double(imva)*0.02;
    std::string mvaS= std::to_string(mva_d);
    vMVAB.push_back("MVAB"+mvaS+"_");
  }
  for(unsigned int imva=0 ; imva < 80 ; imva++){
    double mva_d= -0.7 + imva*0.02;
    std::string mvaS= std::to_string(mva_d);
    vMVAEC.push_back("MVAEC"+mvaS+"_");
  }



  for(auto iMVAB : vMVAB) IDs.push_back(iMVAB+"MVAEC-0.7_ISOB0.15_ISOEC0.15_DXYB1EC1");
  for(auto iMVAEC : vMVAEC) IDs.push_back(iMVAEC+"MVAB-0.4_ISOB0.15_ISOEC0.15_DXYB1EC1");
  IDs.push_back("POGT_ISOB0.15_ISOEC0.15_DXYB1EC1");
  IDs.push_back("POGM_ISOB0.15_ISOEC0.15_DXYB1EC1");


  for(unsigned int i=0; i < IDs.size(); i++){



    TString denom = "Fake_LooseMuMu_Mu_" +IDs[i] +"_MuMu_40_ptcone_eta";
    TString num   = "Fake_TightMuMu_Mu_" +IDs[i] +"_MuMu_40_ptcone_eta";

