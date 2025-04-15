#include "Macros.h"
#include "mylib.h"

// Function declarations
void MakeFRFile(TString year, TString dataset = "MuMu", TString PtType = "Pt");
TString DoubleToString(double d);

void MakeMVA_FR_FileLL_HEM_Cleaned() {
  MakeFRFile("2018", "MuMu", "PtParton");
}

void MakeFRFile(TString year, TString dataset, TString PtType) {
  // Paths to input files
  TString path = TString(std::getenv("FILE_MERGED_PATH")) + "HNL_Lepton_FakeRate/Jan27_HEM/HEMJetFakes__/" + year + "/HNL_Lepton_FakeRate_Data_FakeMuon.root";
  TString mcpath = TString(std::getenv("FILE_MERGED_PATH")) + "HNL_Lepton_FakeRate/Jan27_HEM/HEMJetFakes__/" + year + "/HNL_Lepton_FakeRate_MC.root";

  TFile* fdata = new TFile(path, "READ");
  TFile* fmc = new TFile(mcpath, "READ");


  // Check if files are opened successfully
  if (!fdata || fdata->IsZombie() || !fmc || fmc->IsZombie()) {
    std::cerr << "Error: Unable to open input files!" << std::endl;
    return;
  }
  fdata->ls();

  // Set plotting style
  PlottingSetup();

  // Determine the era and year
  TString era = year;
  if (era.Contains("2016pre")) era = "2016a";
  if (era.Contains("2016post")) era = "2016b";
  TString Year = year;
  if (era.Contains("2016")) Year = "2016";

  TString outfile = "FR_Mu_" + era + "_HNL_ULID_" + PtType + "_v5.root";

  // Output file
  TFile* fout = new TFile(outfile, "RECREATE");
  fout->cd();
  
  // IDs for processing
  std::vector<TString> IDs = {
    "HNL_ULID_2018"
  };

  // Processing IDs
  for (auto ID : IDs) {
    // Adjust ID based on PtType
    if (PtType == "PtParton") ID.ReplaceAll("pt_eta", "ptparton_eta");
    if (PtType == "PtCorr") ID.ReplaceAll("pt_eta", "ptcorr_eta");
    if (PtType == "MotherPt") ID.ReplaceAll("pt_eta", "MJpt_eta");

    TString denom = PtType + "/Fake_" + PtType + "_LooseMuMu_" + ID+"MuMu_AJ40_ptparton_eta";
    TString num = PtType + "/Fake_" + PtType + "_TightMuMu_" + ID+"MuMu_AJ40_ptparton_eta";
    

    // Retrieve histograms
    TH2D* h_pt_num = (TH2D*)fdata->Get(num.Data());
    TH2D* h_pt_denom = (TH2D*)fdata->Get(denom.Data());
    TH2D* h_mcpt_num = (TH2D*)fmc->Get(num.Data());
    TH2D* h_mcpt_denom = (TH2D*)fmc->Get(denom.Data());

    // Check histograms
    if (!h_pt_num || !h_pt_denom || !h_mcpt_num || !h_mcpt_denom) {
      std::cerr << "Error: Missing histograms for ID: " <<num << std::endl;
      continue;
    }

    // Subtract MC from data
    TH2D* eff_rate = (TH2D*)h_pt_num->Clone(("HNL_ULID_" + Year + "_" + ID).Data());
    eff_rate->Add(h_mcpt_num, -1.0);

    TH2D* hratedenom = (TH2D*)h_pt_denom->Clone((ID + "_denom").Data());
    hratedenom->Add(h_mcpt_denom, -1.0);

    // Avoid negative bin contents
    for (int x = 1; x <= eff_rate->GetNbinsX(); ++x) {
      for (int y = 1; y <= eff_rate->GetNbinsY(); ++y) {
	if (eff_rate->GetBinContent(x, y) <= 0) eff_rate->SetBinContent(x, y, 1);
      }
    }

    // Divide histograms
    eff_rate->Divide(eff_rate, hratedenom, 1.0, 1.0, "cl=0.683 b(1,1) mode");

    // Print bin contents
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << ID << std::endl;
    for (int x = 1; x <= eff_rate->GetNbinsX(); ++x) {
      for (int y = 1; y <= eff_rate->GetNbinsY(); ++y) {
	std::cout << "Bin (" << x << ", " << y << "): " << eff_rate->GetBinContent(x, y) << std::endl;
      }
    }
    std::cout << "-----------------------------------------------------" << std::endl;

    // Write to file
    eff_rate->Write();
  }

  // Close files
  fout->Close();
  fdata->Close();
  fmc->Close();
}

TString DoubleToString(double d) {
  std::ostringstream stream;
  stream << std::fixed << std::setprecision(10) << d;
  TString result = TString(stream.str().c_str());
  result.ReplaceAll(".", "p");
  result.ReplaceAll("-", "neg");
  return result;
}
