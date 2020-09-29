void ReadLimitFromTree(TString filename,TString tag){

  TFile *file = new TFile(filename);

  TTree *tree = (TTree *)file->Get("limit");
  
  if(tree){
    double limit;
    tree->SetBranchAddress("limit",&limit);
    tree->GetEntry(0);
    //tree->GetEntry(1);
    //tree->GetEntry(2);
    
    ofstream ofile_tex;
    ofile_tex.open(tag+"_limit.txt");
    ofile_tex.setf(ios::fixed,ios::floatfield);
    ofile_tex.precision(4);
    ofile_tex <<  limit << "\n"<< endl;
    ofile_tex.close();
    
  }
  else{
    
    ofstream ofile_tex;
    ofile_tex.open(tag+"_limit.txt");
    ofile_tex.setf(ios::fixed,ios::floatfield);
    ofile_tex <<  "--" << endl;
    ofile_tex.close();

  }
}
