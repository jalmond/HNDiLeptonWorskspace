import os,ROOT,time
import mylib
import ctypes
import canvas_margin
import tdrstyle
import CMS_lumi, tdrstyle
import math
from array import array


## SampleGroup ##
class SampleGroup:
  def __init__(self, Name, Type, Samples,  Era, Color=0, Style=1, TLatexAlias="", LatexAlias=""):

    self.Name = Name
    self.Type = Type
    self.Samples = Samples
    self.Era = Era
    if "16" in Era:
      self.Year = 2016
    elif Era == "YearCombined":
      print Name + " " + Era
      self.Year =Era
    else:
      self.Year=int(Era)

    self.Color = Color
    self.Style = Style
    self.TLatexAlias = TLatexAlias
    self.LatexAlias = LatexAlias

  def Print(self):
    print ('Sample group name = '+self.Name)
    print (  'Type = '+self.Type)
    print (  'Samples = '),
    print (self.Samples)
    print (  'Year = '+str(self.Year))
    print (  'Era = '+str(self.Era))
    print (  'Color = '+str(self.Color))
    print (  'TLatexAlias = '+str(self.TLatexAlias))
    print (  'LatexAlias = '+str(self.LatexAlias))

## SignalInfo ##
class SignalInfo:
  def __init__(self,  mN):
    self.Process = "SS"
    self.mN = mN
    self.xsec = 1.
    self.kfactor = 1.
    self.xsecScale = 1.
    self.Color = ROOT.kBlack
    self.Style = 3
    self.useOfficial = False

    self.TLatexAlias = "(m_{N}, Process) = (%d, %s) GeV"%(self.mN, self.Process)

  def Print(self):
    print ('( %d, %f, %f)'%( self.mN, self.xsec, self.kfactor))
  def GetTLatexAlias(self):
    if self.xsecScale!=1.:
      self.TLatexAlias = "%d #times (m_{N}) = (%d, %d) GeV"%(self.xsecScale, self.mN)

    return self.TLatexAlias

## Variable ##
class Variable:
  def __init__(self, Name, TLatexAlias, Unit):
    self.Name = Name
    self.TLatexAlias = TLatexAlias
    self.Unit = Unit
  def Print(self):
    print ('(%s, %s, %s)' % (self.Name, self.TLatexAlias, self.Unit))

## Region ##
class Region:
  def __init__(self, Name, PrimaryDataset, PName, UnblindData=True, Logy=-1, TLatexAlias="", CutFlowCaption="Test"):
    self.Name = Name
    self.PrimaryDataset = PrimaryDataset
    self.ParamName = PName
    self.UnblindData = UnblindData
    self.Logy = Logy
    self.TLatexAlias = TLatexAlias
    self.CutFlowCaption = CutFlowCaption

    self.DrawData = True
    self.DrawRatio = True

  def Print(self):
    print ('(%s, %s, UnblindData=%s, Logy=%f, %s)'%(self.Name, self.PrimaryDataset, self.UnblindData, self.Logy, self.TLatexAlias))

## Systematic ##
class Systematic:
  def __init__(self, Name, Direction, Year):
    self.Name = Name
    self.Direction = Direction
    self.Year = Year ## if <0, it's correalted    

  def FullName(self):
    if self.Year>0:
      return 'Run'+str(self.Year)+'_'+self.Name

    else:
      return self.Name
  def Print(self):
    str_Direction = 'Up' if self.Direction>0 else 'Down'
    if self.Direction==0:
      str_Direction = "Central"
    print ('(%s, %s, %d)'%(self.Name, str_Direction, self.Year))

## Plotter ##
class Plotter:

  def __init__(self):

    self.DoDebug = False
    self.Lxplus_User=''
    self.Lxplus_Dir=''
    self.DataYear = 2016
    self.DataEra = ""
    self.DataDirectory = "2016"

    self.SampleGroups = []
    self.RegionsToDraw = []
    self.VariablesToDraw = []
    self.SignalsToDraw = []

    self.Systematics = []
    self.InputDirectory = ""
    self.Filename_prefix = ""
    self.Filename_suffix = ""
    self.Filename_data_skim = ""
    self.Filename_skim = ""
    self.OutputDirectory = ""
    self.OutputDirectoryLocal = ""

    self.ScaleMC = False

    self.ExtraLines = ""

    self.ErrorFromShape = False
    self.AddErrorLinear = False

    self.NoErrorBand = False

  def PrintBorder(self):
    print ('--------------------------------------------------------------------------')
    
  def PrintSamples(self):
    self.PrintBorder()
    print ('[Plotter.PrintSamples()] Printing samples')
    for s in self.SampleGroups:
      s.Print()
    self.PrintBorder()

  def PrintRegions(self):
    self.PrintBorder()
    print ('[Plotter.PrintRegions()] Printing regions to be drawn')
    for s in self.RegionsToDraw:
      s.Print()
    self.PrintBorder()

  def PrintVariables(self):
    self.PrintBorder()
    print ('[Plotter.PrintVariables()] Printing variables to be drawn')
    for s in self.VariablesToDraw:
      s.Print()
    self.PrintBorder()

  def PrintSystematics(self):
    self.PrintBorder()
    print ('[Plotter.PrintSystematics()] Printing systematics')
    for s in self.Systematics:
      s.Print()
    self.PrintBorder()

  ## Benning related

  def SetBinningFilepath(self, RebinFilepath, XaxisFilepath, YaxisFilepath):
    self.RebinFilepath = RebinFilepath
    self.XaxisFilepath = XaxisFilepath
    self.YaxisFilepath = YaxisFilepath

  def ReadBinningInfo(self, Region):
    ## Rebin
    Rebins = dict()
    
    for line in open(self.RebinFilepath).readlines():
      words = line.split()
      Rebins[words[0]] = int(words[1])
      if self.DoDebug:
        print ("Setting rebin " + str(words[0]) + " " + str(words[1]))



    if len(Rebins) == 0:
      print("No binnings set for " +str(Region) )

    ## xaxis
    XaxisRanges = dict()

    for line in open(self.XaxisFilepath).readlines():
      words = line.split()
      #if Region!=words[0]:
      #  continue
      XaxisRanges[words[0]] = [float(words[1]), float(words[2])]

    if len(XaxisRanges) == 0:
      print("No binnings set for " +str(Region) )

    return Rebins, XaxisRanges
  def Rebin(self, hist, region, var, nRebin):
    
    if var=='NCand_Mass':
      return mylib.RebinNMass(hist, region, self.DataYear)
    else:
      if nRebin>0:
        hist.Rebin(nRebin)
        return hist
      else:
        return hist
  def ZeroDataCheckCut(self,var,xlow,xhigh):
    ## TODO
    return False


  def DoCutFlow(self,Hist_Name):

    nprec = 0
    print ('[Plotter.Cutflow()] ')

    CutFlowDir= os.getenv("HNDILEPTONWORKSPACE_DIR")+'/CutFlow/'
    
    if os.path.exists(CutFlowDir+'/Cutflow.sh'):
      os.system('rm '+CutFlowDir+'/Cutflow.sh')
    
    ROOT.gErrorIgnoreLevel = ROOT.kFatal

    tdrstyle.setTDRStyle()
    ROOT.TH1.AddDirectory(False)


    for Region in self.RegionsToDraw:
      print Region.Name
      Indir = self.InputDirectory
      Outdir = self.OutputDirectoryLocal+'/'+Region.Name+'/'
      if self.ScaleMC:
        Outdir = self.OutputDirectoryLocal+'/ScaleMC/'+Region.Name+'/'
      os.system('mkdir -p '+Outdir)

      print("self.Filename_prefix " + str(self.Filename_prefix))
      #f_Data = ROOT.TFile(Indir+'/'+self.DataDirectory+'/'+self.Filename_prefix+self.Filename_data_skim+'_data_'+Region.PrimaryDataset+self.Filename_suffix+'.root')

      f_Data = ROOT.TFile(Indir+'/'+self.DataDirectory+'/'+self.Filename_prefix+self.Filename_data_skim+'_data_Lepton'+self.Filename_suffix+'.root')
      print (Region.PrimaryDataset + '/'+ Region.ParamName + '/'+ Region.Name+'/'+Hist_Name) #######

      histName = Region.PrimaryDataset + '/'+ Region.ParamName + '/'+ Region.Name+'/'+Hist_Name
      
      Histogram_Name=Region.Name+'/RegionPlots_'+Region.PrimaryDataset+'/' + Region.ParamName+ '/'+Variable.Name


      h_Data = f_Data.Get(Histogram_Name)
      if not h_Data:
        print (Indir+'/'+self.DataDirectory+'/'+self.Filename_prefix+self.Filename_data_skim+'_data_'+Region.PrimaryDataset+self.Filename_suffix+'.root missing ' +Region.PrimaryDataset + '/'+ Region.ParamName + '/'+ Region.Name+'/'+Hist_Name)
        print (Region.PrimaryDataset + '/'+ Region.ParamName + '/'+ Region.Name+'/'+Hist_Name)
        print (Hist_Name+'_'+Region.Name+'.pdf ==> No data, skipped')
        print ('---- ' + Indir+'/'+self.DataDirectory+'/'+self.Filename_prefix+self.Filename_data_skim+'_data_'+Region.PrimaryDataset+self.Filename_suffix+'.root')
        continue
      data_integral=h_Data.Integral()
      data_error  = ctypes.c_double(0.)
      integral = h_Data.IntegralAndError(0,h_Data.GetNbinsX(),data_error,"");

      total_bkg_integral=0.
      total_bkg_staterror=0.
      sys_total_bkg_up=0
      sys_total_bkg_down=0
      
      CFName=Region.PrimaryDataset+"_"+Region.Name
      CutFlowLatexFile = open (CutFlowDir+'/Cutflow_'+CFName+'.tex','w')
      CutFlowLatexFile.write('\\documentclass[10pt]{article}\n')
      CutFlowLatexFile.write('\\usepackage{epsfig,subfigure,setspace,xtab,xcolor,array,colortbl}\n')
      CutFlowLatexFile.write('\providecommand{\\cmsTable}[1]{\\resizebox{\\textwidth}{!}{#1}}\n')
      CutFlowLatexFile.write('\\begin{document}\n')
      CutFlowLatexFile.write('\\input{"'+CutFlowDir+'/Tables/Cutflow_'+self.DataDirectory+'_'+CFName+'Table.txt"}\n')
      CutFlowLatexFile.write('\\end{document}\n')
      CutFlowLatexFile.close()
      caption=Region.CutFlowCaption
      print ("Caption = " + caption)
      CutFlowLatexTableFile = open (CutFlowDir+'/Tables/Cutflow_'+self.DataDirectory+'_'+CFName+'Table.txt','w')
      CutFlowLatexTableFile.write("\\begin{table}[ptb]\n" )
      CutFlowLatexTableFile.write("\\centering\n" )
      CutFlowLatexTableFile.write("\\cmsTable{\n" )
      CutFlowLatexTableFile.write("\\begin{tabular}{lcccc}\n" )
      CutFlowLatexTableFile.write("\\hline\n" )
      CutFlowLatexTableFile.write("\\hline\n" )   
      CutFlowLatexTableFile.write("Source & \\multicolumn{4}{c}{} \\\\ \n" )
      CutFlowLatexTableFile.write("\\hline\n" )   
      
      
      for SampleGroup in self.SampleGroups:

        bkg_integral=0.
        bkg_staterror=0.

        
        for Sample in SampleGroup.Samples:
          if self.DoDebug:
            print ('[DEBUG] Trying to make histogram for Sample = '+Sample)
            
          f_Sample = ROOT.TFile(Indir+'/'+str(SampleGroup.Era)+'/'+self.Filename_prefix+self.Filename_skim+'_'+Sample+self.Filename_suffix+'.root')
          h_Sample = 0
          #if (Syst.Year>0) and (Syst.Year!=SampleGroup.Year):
          #  tmp_dirName = Region.Name
          #  h_Sample = f_Sample.Get(tmp_dirName+'/'+Hist_Name+'_'+tmp_dirName)
          #elif (Syst.Name in ["Lumi", "DYNorm", "NonPromptNorm", "OthersNorm"]):
          #  tmp_dirName = Region.Name
          #  h_Sample = f_Sample.Get(tmp_dirName+'/'+Hist_Name+'_'+tmp_dirName)
          #  ## For all other cases
          #else:
          dirName = Region.Name

          #Histogram_Name=Region.PrimaryDataset + '/'+ Region.ParamName + '/'+ Region.Name+'/'+Hist_Name
          Histogram_Name=Region.Name+'/RegionPlots_'+Region.PrimaryDataset+'/' + Region.ParamName+ '/'+Variable.Name
          print Histogram_Name
          h_Sample = f_Sample.Get(Histogram_Name)

          if not h_Sample:
            continue


          ## Scale
          MCSF, MCSFerr = 1., 0.
          #if self.ScaleMC:
          #  if "DYJets" in Sample:
          MCSF= mylib.GetNormSF(SampleGroup.Year, Sample)
          
          if self.DoDebug:
            print "MCSF = " + str(MCSF)
          if Region.Name == "HNL_HighMassSR1_TwoLepton_CR":
            if "NonPrompt" in Sample:
              if Region.PrimaryDataset == "MuMu":
                MCSF = 0.5
              else:
                MCSF = 1.2
              #else :
              #if Region.PrimaryDataset == "EE":
              #  MCSF = 1.4

          h_Sample.Scale( MCSF )

          stat_error  = ctypes.c_double(0.)
          integral = h_Sample.IntegralAndError(0,h_Sample.GetNbinsX(),stat_error,"");
          bkg_integral += h_Sample.Integral()
          total_bkg_integral += h_Sample.Integral()
          bkg_staterror = math.sqrt(bkg_staterror*bkg_staterror + stat_error.value*stat_error.value)
          total_bkg_staterror = math.sqrt(total_bkg_staterror*total_bkg_staterror + stat_error.value*stat_error.value)
          
        print (Sample + " integral = " + str(bkg_integral))
        bkg_integral=round(bkg_integral,nprec)
        bkg_staterror=round(bkg_staterror,nprec)
        sys_bkg_up =  mylib.GetMCUncertainty(SampleGroup.Name)*bkg_integral
        sys_bkg_down = mylib.GetMCUncertainty(SampleGroup.Name)*bkg_integral
        sys_total_bkg_up = math.sqrt(sys_total_bkg_up*sys_total_bkg_up+sys_bkg_up*sys_bkg_up)
        sys_total_bkg_down = math.sqrt(sys_total_bkg_down*sys_total_bkg_down+sys_bkg_down*sys_bkg_down)
        
        if bkg_integral > 0:
          CutFlowLatexTableFile.write( SampleGroup.LatexAlias + "& " +  str(bkg_integral) + "& $\\pm$ & "  + str(bkg_staterror)  +  "&$^{+"+str(sys_bkg_up)+"}_{-"+str(sys_bkg_down)+"}$ \\\\\n" )

      sys_total_bkg_up   = int(round(sys_total_bkg_up))
      sys_total_bkg_down   = int(round(sys_total_bkg_down))
      total_bkg_integral=   int(round(total_bkg_integral,nprec))
      total_bkg_staterror = int(round(total_bkg_staterror,nprec))

      CutFlowLatexTableFile.write('\\hline\n')

      significance_up = (data_integral - total_bkg_integral) / (math.sqrt(total_bkg_staterror*total_bkg_staterror+sys_total_bkg_up*sys_total_bkg_up + data_error.value*data_error.value ))
      significance_down = (data_integral - total_bkg_integral) / (math.sqrt(total_bkg_staterror*total_bkg_staterror+sys_total_bkg_down*sys_total_bkg_down + data_error.value*data_error.value ))
      significance=significance_up
      if significance_down > significance_up:
        significance=significance_down


      sys_total_bkg_up=int(round(sys_total_bkg_up,nprec))
      sys_total_bkg_down=int(round(sys_total_bkg_down,nprec))
      CutFlowLatexTableFile.write('Total& ' + str(total_bkg_integral)  + "& $\\pm$ & "  + str(total_bkg_staterror)  +  "&$^{+"+str(sys_total_bkg_up)+"}_{-"+str(sys_total_bkg_down)+"}$ \\\\\n" )
      CutFlowLatexTableFile.write('\\hline\n')
      CutFlowLatexTableFile.write('Data& \\multicolumn{4}{c}{$' + str(int(data_integral)) + '$}\\\\ \n')
      CutFlowLatexTableFile.write('\\hline\n')
      significance=round(significance,nprec)
      if significance < 0:
        CutFlowLatexTableFile.write("Significance&  \\multicolumn{4}{c}{$" + str(significance) + "\\sigma$}\\\\ \n")
      else:
        CutFlowLatexTableFile.write("Signifficance&  \\multicolumn{4}{c}{$" + str(significance) + "\\sigma$}\\\\ \n")

      CutFlowLatexTableFile.write('\\hline\n')
      CutFlowLatexTableFile.write('\\hline\n')
      CutFlowLatexTableFile.write('\end{tabular}\n')
      CutFlowLatexTableFile.write('}\n')
      CutFlowLatexTableFile.write("\\caption{"+caption+"}\n")
      CutFlowLatexTableFile.write('\end{table}\n')

      print "#"*50
      print "#"*50
      print ("Starting process for Cutflow:")
      
      print ("Moving to Cutflow dir")
      
      cdir=os.getenv("PWD")

      os.chdir(CutFlowDir)
      #print ('CutFlowDir='+CutFlowDir)
      
      latex_command = "latex " +  CutFlowDir+"/Cutflow_"+CFName+".tex"
      os.system("ls  " + CutFlowDir)
      time.sleep(5)
      dvi_command = "dvipdf "+ CutFlowDir +"/Cutflow_"+CFName+".dvi"
      mv_command = "mv " + CutFlowDir+"/Cutflow_"+CFName+".pdf  " + Outdir

      print ('DoCutFlow: source '+CutFlowDir+"/Cutflow"+CFName+".sh") 
      run_latex = open(CutFlowDir+"/Cutflow"+CFName+".sh","a")
      run_latex.write('cd ' + CutFlowDir+'\n')
      run_latex.write(latex_command + '\n')
      run_latex.write(dvi_command + '\n')
      run_latex.write(mv_command + '\n')
      print '-'*40
      print '-'*40
      print(latex_command)
      print '-'*40
      print(dvi_command)
      print '-'*40
      print(mv_command)
      run_latex.write('rm Cutflow_'+CFName+'.aux\n')
      run_latex.write('rm Cutflow_'+CFName+'.tex\n')
      run_latex.write('rm Cutflow_'+CFName+'.dvi\n')
      
      run_latex.write('cd -')
      run_latex.close()

      cwd= os.getenv("PWD")
      os.chdir(CutFlowDir)
      os.system(latex_command)
      os.system(dvi_command)
      os.system(mv_command)
      #os.system('rm Cutflow'+Region.Name+'.aux\n')                                                                                    
      #os.system('rm Cutflow'+Region.Name+'.tex\n')                                                                                   
      #os.system('rm Cutflow'+Region.Name+'.dvi\n')                                                                                    
      os.chdir(cwd)
            
      print ('Table ==> ' + Outdir + '/Cutflow'+CFName+'.pdf')

      
      if not self.OutputDirectory =="":
        OutdirLXPLUS= self.OutputDirectory +'/'+Region.Name+'/'
        if self.ScaleMC:
          os.system("ssh jalmond@lxplus.cern.ch 'mkdir -p " + self.OutputDirectory +"/ScaleMC/'")
          OutdirLXPLUS= self.OutputDirectory +'/ScaleMC/'+Region.Name+'/'
          
      print( 'scp ' + Outdir + '/Cutflow_'+CFName+'.pdf  '+self.Lxplus_User + '@lxplus.cern.ch:'+OutdirLXPLUS+'/')
      os.system('scp ' + Outdir + '/Cutflow_'+CFName+'.pdf  '+ self.Lxplus_User + '@lxplus.cern.ch:'+OutdirLXPLUS+'/')



  def Draw(self):

    ROOT.gErrorIgnoreLevel = ROOT.kFatal

    tdrstyle.setTDRStyle()
    ROOT.TH1.AddDirectory(False)
    lxplus_dir=[]
    for Region in self.RegionsToDraw:

      print ('## Drawing '+Region.Name)

      ## Read binning data
      Rebins, XaxisRanges = self.ReadBinningInfo(Region.Name)

      ## Input/Output directotry
      Indir = self.InputDirectory
      Outdir = self.OutputDirectoryLocal+'/'+Region.Name+'/'
      if self.ScaleMC:
        Outdir = self.OutputDirectoryLocal+'/ScaleMC/'+Region.Name+'/'

      if not self.OutputDirectory =="":
        OutdirLXPLUS= self.OutputDirectory +'/'+Region.Name+'/'
        os.system("ssh "+self.Lxplus_User + "@lxplus.cern.ch 'mkdir -p " + OutdirLXPLUS + "'")
        if self.ScaleMC:
          os.system("ssh "+self.Lxplus_User + "@lxplus.cern.ch 'mkdir -p " + self.OutputDirectory +"/ScaleMC/'")
          OutdirLXPLUS= self.OutputDirectory +'/ScaleMC/'+Region.Name+'/'
          os.system("ssh "+self.Lxplus_User + "@lxplus.cern.ch 'mkdir -p " + OutdirLXPLUS + "'")


      print ('##   Outputs => '+Outdir)
      
      os.system('mkdir -p '+Outdir)
      if not self.OutputDirectory =="":
        print('scp ' + os.getenv('HTML_DIR') + '/index.php ' + ''+self.Lxplus_User + '@lxplus.cern.ch:'+ OutdirLXPLUS+'/')
        os.system('scp ' + os.getenv('HTML_DIR') + '/index.php ' + ''+self.Lxplus_User + '@lxplus.cern.ch:'+ OutdirLXPLUS+'/')


      ## Data file
      #f_Data = ROOT.TFile(Indir+'/'+self.DataDirectory+'/'+self.Filename_prefix+self.Filename_data_skim+'_data_'+Region.PrimaryDataset+self.Filename_suffix+'.root')
      f_Data = ROOT.TFile(Indir+'/'+self.DataDirectory+'/'+self.Filename_prefix+self.Filename_data_skim+'_data_Lepton'  +self.Filename_suffix+'.root')
      
      if self.DoDebug:
        print ('[DEBUG] Trying to read from data file' + Indir+'/'+self.DataDirectory+'/'+self.Filename_prefix+self.Filename_data_skim+'_data_'+Region.PrimaryDataset+self.Filename_suffix+'.root')


      ## Loop over variables

      for Variable in self.VariablesToDraw:

        ## BinInfo
        nRebin = 1
        
        if  Variable.Name in  Rebins.keys():
          print(Variable.Name + ' rebinning to ' + str(Rebins[Variable.Name]))
          nRebin = Rebins[Variable.Name]

          
        xMin= -999
        xMax=-999

        if  Variable.Name in  XaxisRanges.keys():
          xMin = XaxisRanges[Variable.Name][0]
          xMax = XaxisRanges[Variable.Name][1]
        yMax = -999

        if self.DoDebug:
          print ('[DEBUG] Trying to draw variable = '+Variable.Name)
          print ('[DEBUG] (xMin,xMax) = (%s,%s)'%(xMin,xMax))

        ## xtitle
        xtitle = Variable.TLatexAlias
        if Variable.Name=="NCand_Mass":
          if "Resolved" in Region.Name:
            xtitle = "m_{ljj} (GeV)"
          else:
            xtitle = "m_{lJ} (GeV)"

        ## Save hists
        ## For legend later..
        HistsToDraw = dict()

        ## Get data first
        if self.DoDebug:
          print ('[DEBUG] Trying to get data histogram..')
          print (Region.PrimaryDataset + '/'+ Region.ParamName + '/'+ Region.Name+'/'+Variable.Name)

        Histogram_Name=Region.Name+'/RegionPlots_'+Region.PrimaryDataset+'/' + Region.ParamName+ '/'+Variable.Name

        h_Data = f_Data.Get(Histogram_Name)
        if not h_Data:
          print (Indir+'/'+self.DataDirectory+'/'+self.Filename_prefix+self.Filename_data_skim+'_data_Lepton'+self.Filename_suffix+'.root')
          print (Histogram_Name)
          print (Variable.Name+'_'+Region.Name+'.pdf ==> No data, skipped')
          continue

        ## Make overflow
        print ('[DEBUG] (xMin,xMax) = (%s,%s)'%(xMin,xMax))

        if xMin !=  -999:
          h_Data.GetXaxis().SetRangeUser(xMin,xMax)
        h_Data = mylib.MakeOverflowBin(h_Data)

        ## Rebin
        h_Data = self.Rebin(h_Data, Region.Name, Variable.Name, nRebin)
        ## Copy data axis
        dataAxis = h_Data.GetXaxis()
        nBin = dataAxis.GetNbins()
        xBins = [dataAxis.GetBinLowEdge(1)]
        for ix in range(0,nBin):
          xBins.append( dataAxis.GetBinUpEdge(ix+1) )
        xBins = array("d",xBins)

        ### Att data histogram
        h_Data.SetMarkerStyle(20)
        h_Data.SetMarkerSize(1.2)
        h_Data.SetMarkerColor(ROOT.kBlack)
        h_Data.SetLineColor(ROOT.kBlack)

        if self.DoDebug:
          print ('[DEBUG] data histogram finished')
          print ('Data:')
          for z in range(0,h_Data.GetXaxis().GetNbins()):
            x_l = h_Data.GetXaxis().GetBinLowEdge(z+1)
            x_r = h_Data.GetXaxis().GetBinUpEdge(z+1)
            y = h_Data.GetBinContent(z+1)
            print ('[%f,%f] : %f +- %f'%(x_l,x_r,y,h_Data.GetBinError(z+1)))

        ## Loop over samples
        ## For Legend, save 
        HistsForLegend = []
        AliasForLegend = [] ## Prevent double-counting
        stack_Bkgd = ROOT.THStack("stack_Bkgd", "")
        h_Bkgd = 0
        ## Save systematic
        SystematicUps = dict()
        SystematicDowns = dict()
        ## If we take errors fro shapes
        h_TotalBackgroundFromShape = 0

        ## Loop over systematics
        for Syst in self.Systematics:

          if self.DoDebug:
            print ('[DEBUG] Trying to make histogram for Syst = '),
            Syst.Print()

          h_Bkgd_ForSyst = 0
          paraName = Region.ParamName

          if Syst.Name!="Central":

            if Syst.Direction>0:
              paraName = "Syst_"+Syst.Name+"Up_"+Region.ParamName
            else:
              paraName = "Syst_"+Syst.Name+"Down_"+Region.ParamName

          for SampleGroup in self.SampleGroups:
            Color = SampleGroup.Color
            LegendAdded = False

            for Sample in SampleGroup.Samples:

              if self.DoDebug:
                print ('[DEBUG] Trying to make histogram for Sample = '+Sample)

              f_Sample = ROOT.TFile(Indir+'/'+str(SampleGroup.Era)+'/'+self.Filename_prefix+self.Filename_skim+'_'+Sample+self.Filename_suffix+'.root')
              h_Sample = 0

              ## Uncorrelated sources has Syst.Year = 2016 or 2017 or 2018
              ## For this cases, SampleGroup.Year should be matched
              if (Syst.Year>0) and (Syst.Year!=SampleGroup.Year):
               
                print "self.Filename_prefix = " + self.Filename_prefix
                tmp_paraName = Region.ParamName
                Histogram_Name=Region.Name+'/RegionPlots_'+Region.PrimaryDataset+'/' + Region.ParamName+ '/'+Variable.Name


                h_Sample = f_Sample.Get(Histogram_Name)

              ## 1) Lumi, MC normalizaion
              ## Use central and scale them later
              elif (Syst.Name in ["Lumi"]):
                tmp_paraName = Region.ParamName

                Histogram_Name=Region.Name+'/RegionPlots_'+Region.PrimaryDataset+'/' + Region.ParamName+ '/'+Variable.Name


                h_Sample = f_Sample.Get(Histogram_Name)
              ## For all other cases
              elif (Syst.Name in ["GetMCUncertainty"]):
                tmp_paraName = Region.ParamName

                Histogram_Name=Region.Name+'/RegionPlots_'+Region.PrimaryDataset+'/' + Region.ParamName+ '/'+Variable.Name

                h_Sample = f_Sample.Get(Histogram_Name)
              else:
                
                print "Histogram_Name = " + Histogram_Name
                Histogram_Name=Region.Name+'/RegionPlots_'+Region.PrimaryDataset+'/' + Region.ParamName+ '/'+Variable.Name

                
                h_Sample = f_Sample.Get(Histogram_Name)
                if self.DoDebug:

                  print("Looking in file: "+Indir+'/'+str(SampleGroup.Era)+'/'+self.Filename_prefix+self.Filename_skim+'_'+Sample+self.Filename_suffix+'.root')
                  print(Histogram_Name)

              if not h_Sample:
                print("Looking in file: "+Indir+'/'+str(SampleGroup.Era)+'/'+self.Filename_prefix+self.Filename_skim+'_'+Sample+self.Filename_suffix+'.root')
                print(Histogram_Name)

                print 'No hist : %s %s'%(Syst.Name,Sample)
                continue

              ## Make overflow
              if xMin !=  -999:
                h_Sample.GetXaxis().SetRangeUser(xMin,xMax)
              h_Sample = mylib.MakeOverflowBin(h_Sample)

              h_Sample = self.Rebin(h_Sample, Region.Name, Variable.Name, nRebin)
              h_Sample.SetLineColor(Color)
              h_Sample.SetLineWidth(1)
              h_Sample.SetFillColor(Color)

              ## Scale
              MCSF, MCSFerr = 1., 0.
              if self.ScaleMC:
                ## now, only for DY
                if "DYJets" in Sample:
                  MCSF, MCSFerr = mylib.GetDYNormSF(SampleGroup.Year, Region.Name)
              print Region.Name + " " + Region.PrimaryDataset + " " + Sample

              MCSF= mylib.GetNormSF(SampleGroup.Year, Sample)
              if "_CR" in Region.Name:
                if "NonPrompt" in Sample:
                  if Region.PrimaryDataset == "MuMu":
                    MCSF = 0.5
                  else :
                    if Region.PrimaryDataset == "EE":
                      MCSF = 0.5


              print "MCSF  " +str(MCSF)
              h_Sample.Scale( MCSF )

              ## Manual systematic
              ## 1) [Lumi] Uncorrelated
              if (Syst.Name=="Lumi") and (Syst.Year==SampleGroup.Year):
                lumierr = mylib.LumiError(0)
                for ix in range(0,h_Sample.GetXaxis().GetNbins()):
                  y = h_Sample.GetBinContent(ix+1)
                  y_new = y + y*float(Syst.Direction)*lumierr
                  h_Sample.SetBinContent(ix+1, y_new)
                  
              if (Syst.Name=="GetMCUncertainty") and (Syst.Year==SampleGroup.Year):
                mcerr = mylib.GetMCUncertainty(SampleGroup.Name)
                for ix in range(0,h_Sample.GetXaxis().GetNbins()):
                  y = h_Sample.GetBinContent(ix+1)
                  y_new = y + y*float(Syst.Direction)*mcerr
                  h_Sample.SetBinContent(ix+1, y_new)
                  
                  
                  
              ## AddError option
              AddErrorOption = ''
              if self.AddErrorLinear:
                AddErrorOption = 'L'

              ## If central, add to h_Bkgd
              if Syst.Name=="Central" and Sample=='total_background':
                if not h_TotalBackgroundFromShape:
                  h_TotalBackgroundFromShape = h_Sample.Clone()
                else:
                  h_TotalBackgroundFromShape = mylib.AddHistograms( h_TotalBackgroundFromShape, h_Sample, AddErrorOption )
                HistsToDraw[Sample] = h_Sample.Clone()

              elif Syst.Name=="Central":
                
                
                stack_Bkgd.Add( h_Sample )
                if not h_Bkgd:
                  h_Bkgd = h_Sample.Clone()
                else:
                  h_Bkgd = mylib.AddHistograms( h_Bkgd, h_Sample, AddErrorOption)

                HistsToDraw[Sample] = h_Sample.Clone()
                if (not LegendAdded) and (SampleGroup.TLatexAlias not in AliasForLegend):
                  HistsForLegend.append( [HistsToDraw[Sample],SampleGroup.TLatexAlias] )
                  AliasForLegend.append(SampleGroup.TLatexAlias)
                  LegendAdded = True
              ## else (i.e., systematic), add to h_Bkgd_ForSyst
              else:
                if self.DoDebug:
                  print ("Adding hist to syst " + Syst.Name)
                if not h_Bkgd_ForSyst:
                  h_Bkgd_ForSyst = h_Sample.Clone()
                else:
                  h_Bkgd_ForSyst = mylib.AddHistograms(h_Bkgd_ForSyst, h_Sample, AddErrorOption)

              ## Close file
              f_Sample.Close()

            ##==>End Sample loop
          ##==>End SampleGroup loop

          if Syst.Name!="Central":
            if Syst.Direction>0:
              SystematicUps[Syst.FullName()] = h_Bkgd_ForSyst
            else:
              SystematicDowns[Syst.FullName()] = h_Bkgd_ForSyst

        ##==>End Syst loop
        #print SystematicUps
        #print SystematicDowns

        ## Syst Up/Down . Max/Min
        h_Bkgd_TotErr_Max = h_Bkgd.Clone()
        h_Bkgd_TotErr_Min = h_Bkgd.Clone()
        for SystKey in SystematicUps:
          #print 'SystKey = '+SystKey
          h_Up = SystematicUps[SystKey]
          h_Down = SystematicDowns[SystKey]
          for ix in range(0,h_Bkgd.GetXaxis().GetNbins()):
            x_l = h_Bkgd.GetXaxis().GetBinLowEdge(ix+1)
            x_r = h_Bkgd.GetXaxis().GetBinUpEdge(ix+1)
            y_Central = h_Bkgd.GetBinContent(ix+1)
            y_Up = h_Up.GetBinContent(ix+1)
            y_Down = h_Down.GetBinContent(ix+1)
            ## -.
            y_Max = max( max(y_Central,y_Up), y_Down)
            y_Min = min( min(y_Central,y_Up), y_Down)
            #print '[%d,%d] : %f, (Max,Min) = (%f,%f)'%(x_l,x_r,y_Central,y_Up,y_Down)

            ## Update Max
            err_Max_Current = h_Bkgd_TotErr_Max.GetBinError(ix+1)
            err_Max_ToAdd = y_Max-y_Central
            err_Max_Updated = math.sqrt( err_Max_Current*err_Max_Current + err_Max_ToAdd*err_Max_ToAdd )
            h_Bkgd_TotErr_Max.SetBinError(ix+1, err_Max_Updated)
            ## Update Min
            err_Min_Current = h_Bkgd_TotErr_Min.GetBinError(ix+1)
            err_Min_ToAdd = y_Central-y_Min
            err_Min_Updated = math.sqrt( err_Min_Current*err_Min_Current + err_Min_ToAdd*err_Min_ToAdd )
            h_Bkgd_TotErr_Min.SetBinError(ix+1, err_Min_Updated)
        ##==>End Systematic loop

        ## Blind mode
        if not Region.UnblindData:
          h_Data = h_Bkgd.Clone(h_Data.GetName())
          h_Data.SetMarkerStyle(20)
          h_Data.SetMarkerSize(1.2)
          h_Data.SetMarkerColor(ROOT.kBlack)
          h_Data.SetLineColor(ROOT.kBlack)

        ## hist => gr
        gr_Bkgd_TotErr = mylib.GetAsymmError(h_Bkgd_TotErr_Max,h_Bkgd_TotErr_Min)
        gr_Data = ROOT.TGraphAsymmErrors(h_Data)

        ## Error from shape
        if self.ErrorFromShape:
          if self.DoDebug:
            print ('Total background :')
            for z in range(0,h_TotalBackgroundFromShape.GetXaxis().GetNbins()):
              x_l = h_TotalBackgroundFromShape.GetXaxis().GetBinLowEdge(z+1)
              x_r = h_TotalBackgroundFromShape.GetXaxis().GetBinUpEdge(z+1)
              y = h_TotalBackgroundFromShape.GetBinContent(z+1)
              print ('[%f,%f] : %f +- %f'%(x_l,x_r,y,h_TotalBackgroundFromShape.GetBinError(z+1)))
          gr_Bkgd_TotErr = ROOT.TGraphAsymmErrors(h_TotalBackgroundFromShape)

        err_up_tmp = []
        err_down_tmp = []
        alpha = 1. - 0.6827
        for i in range(0, gr_Data.GetN()):
          N = gr_Data.GetY()[i]

          L = 0.                                          if (N==0.) else (ROOT.Math.gamma_quantile(alpha/2.,N,1.))
          U = ( ROOT.Math.gamma_quantile_c(alpha,N+1,1) ) if (N==0.) else (ROOT.Math.gamma_quantile_c(alpha/2.,N+1.,1.))

          #print '%d - %f + %f'%(N, N-L, U-N)

          if N!=0:
            gr_Data.SetPointEYlow(i, N-L )
            gr_Data.SetPointEYhigh(i, U-N )
            err_down_tmp.append(N-L)
            err_up_tmp.append(U-N)
            if Variable.Name!="NCand_Mass":
              gr_Data.SetPointEXlow(i, 0)
              gr_Data.SetPointEXhigh(i, 0)
          else:
            zerodata_err_low = 0.1
            zerodata_err_high = 1.8

            xlow = gr_Data.GetX()[i]-gr_Data.GetEXlow()[i]
            xhigh = gr_Data.GetX()[i]+gr_Data.GetEXhigh()[i]
            if self.ZeroDataCheckCut(Variable.Name,xlow,xhigh):
              zerodata_err_low = 0.
              zerodata_err_high = 0.

            gr_Data.SetPointEYlow(i, zerodata_err_low)
            gr_Data.SetPointEYhigh(i, zerodata_err_high)
            err_down_tmp.append(zerodata_err_low)
            err_up_tmp.append(zerodata_err_high)
            if Variable.Name!="NCand_Mass":
              gr_Data.SetPointEXlow(i, 0)
              gr_Data.SetPointEXhigh(i, 0)

        ## Legend
        lg = 0
        ## No signal
        if len(self.SignalsToDraw)==0:
          #lg = ROOT.TLegend(0.55, 0.45, 0.92, 0.90)
          lg = ROOT.TLegend(0.6, 0.55, 0.92, 0.90)
        ## With Signal
        else:
          if Region.DrawRatio:
            lg = ROOT.TLegend(0.55, 0.46, 0.92, 0.90)
          else:
            lg = ROOT.TLegend(0.50, 0.56, 0.92, 0.90)
        lg.SetBorderSize(0)
        lg.SetFillStyle(0)

        if not self.NoErrorBand:
          lg.AddEntry(gr_Bkgd_TotErr, "Stat.+syst. uncert.", "f")
        ## dummy graph for legend..
        ## this is because h_Data does not have horizontal error bars,
        ## and gr_data does not have points
        gr_Data_dummy = ROOT.TGraphAsymmErrors(gr_Data)
        gr_Data_dummy.SetMarkerStyle(20)
        gr_Data_dummy.SetMarkerSize(1.2)
        dataLegendGOption="ep"
        if Variable.Name=="NCand_Mass":
          dataLegendGOption="lpe"
        if Region.DrawData:
          if Region.UnblindData:
            lg.AddEntry(gr_Data_dummy, "Data", dataLegendGOption)
          else:
            lg.AddEntry(gr_Data_dummy, "Total background", dataLegendGOption)
        for i_lg in range(0,len(HistsForLegend)):
          h_lg = HistsForLegend[ len(HistsForLegend)-1-i_lg ][0]
          tlatexaliax = HistsForLegend[ len(HistsForLegend)-1-i_lg ][1]
          lg.AddEntry(h_lg,tlatexaliax,"f")

        ## Prepare canvas

        if self.DoDebug:
          print ('[DEBUG] Preparing canvas..')

        c1 = ROOT.TCanvas('c1', '', 800, 800)

        c1_up = ROOT.TPad("c1_up", "", 0, 0.25, 1, 1)
        c1_down = ROOT.TPad("c1_down", "", 0, 0, 1, 0.25)
        if Region.DrawRatio:
          c1, c1_up, c1_down = canvas_margin.canvas_margin(c1, c1_up, c1_down)
          c1.Draw()
          c1_up.Draw()
          c1_down.Draw()

          c1_up.cd()
          if Region.Logy>0:
            c1_up.SetLogy(True)

        else:
          c1_up = ROOT.TPad("c1_up", "", 0, 0, 1, 1)
          c1_up.SetTopMargin( 0.052 )
          c1_up.SetBottomMargin( 0.13 )
          c1_up.SetRightMargin( 0.032 )
          c1_up.SetLeftMargin( 0.15 )
          c1.Draw()
          c1_up.Draw()
          c1_up.cd()

          if Region.Logy>0:
            c1_up.SetLogy(True)

        c1.cd()

        latex_CMSPriliminary = ROOT.TLatex()
        latex_Lumi = ROOT.TLatex()

        latex_CMSPriliminary.SetNDC()
        latex_Lumi.SetNDC()
        latex_CMSPriliminary.SetTextSize(0.035)
        latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}")

        latex_Lumi.SetTextSize(0.035)
        latex_Lumi.SetTextFont(42)
        latex_Lumi.DrawLatex(0.73, 0.96, mylib.TotalLumiByEra(str(self.DataEra))+" fb^{-1} (13 TeV)")

        #### axis histograms

        h_dummy_up = ROOT.TH1D('h_dumy_up', '', nBin, xBins)
        if xMin !=  -999:
          h_dummy_up.GetXaxis().SetRangeUser(xMin, xMax)
        if nRebin>0:
          binsize = h_dummy_up.GetXaxis().GetBinUpEdge(1)-h_dummy_up.GetXaxis().GetBinLowEdge(1)
          str_binsize = '%d'%(binsize)
          if binsize!=int(binsize):
            str_binsize = '%1.2f'%(binsize)
          h_dummy_up.GetYaxis().SetTitle('Events / '+str_binsize+' '+Variable.Unit)
        else:
          h_dummy_up.GetYaxis().SetTitle('Events / bin')
        if Variable.Name=='NCand_Mass':
          h_dummy_up.GetYaxis().SetTitle('Events / bin')

        h_dummy_down = ROOT.TH1D('h_dumy_down', '', nBin, xBins)
        h_dummy_down.GetYaxis().SetRangeUser(0.,2.)


        if (self.ErrorFromShape):
          #if ('DYCR' in Region.Name) and ('PostFit' in self.OutputDirectory):
          if ('DYCR' in Region.Name):
            h_dummy_down.GetYaxis().SetRangeUser(0.70,1.30)
            #h_dummy_down.GetYaxis().SetRangeUser(0.0,2.0)
          else:
            h_dummy_down.GetYaxis().SetRangeUser(0.,2.8)
            #h_dummy_down.GetYaxis().SetRangeUser(0.0,2.0)

        h_dummy_down.SetNdivisions(504,"Y")
        if xMin != -999:
          h_dummy_down.GetXaxis().SetRangeUser(xMin, xMax)
        h_dummy_down.GetXaxis().SetTitle(xtitle)
        h_dummy_down.GetYaxis().SetTitle("#frac{Data}{Sim.}")
        h_dummy_down.SetFillColor(0)
        h_dummy_down.SetMarkerSize(0)
        h_dummy_down.SetMarkerStyle(0)
        h_dummy_down.SetLineColor(ROOT.kWhite)

        if Region.DrawRatio:
          h_dummy_up, h_dummy_down = canvas_margin.hist_axis(h_dummy_up, h_dummy_down)
        else:
          h_dummy_up.SetTitle("")
          h_dummy_up.GetYaxis().SetLabelSize(0.04)
          h_dummy_up.GetYaxis().SetTitleSize(0.054)
          h_dummy_up.GetYaxis().SetTitleOffset(1.30)
          h_dummy_up.GetXaxis().SetLabelSize(0.035)
          h_dummy_up.GetXaxis().SetTitleSize(0.055)
          h_dummy_up.GetXaxis().SetTitle(xtitle)

        ## Get Y maximum
        yMax = max( yMax, mylib.GetMaximum(gr_Data) )
        yMax = max( yMax, mylib.GetMaximum(gr_Bkgd_TotErr) )
        ## Yaxis range
        yMin = 0.
        yMaxScale = 1.2
        if "METPhi" in Variable.Name:
          yMaxScale = 2.

        if Region.Logy>0:
          yMaxScale = 10
          yMin = Region.Logy
        h_dummy_up.GetYaxis().SetRangeUser( yMin, yMaxScale*yMax )

        ## Exception control

        if (Variable.Name=="NCand_Mass"):

          if ("_SR" in Region.Name) and ("EMu" not in Region.Name):
            if ("Resolved" in Region.Name):
              h_dummy_up.GetYaxis().SetRangeUser( 1E-1, yMaxScale*yMax )
            else:
              h_dummy_up.GetYaxis().SetRangeUser( 1, yMaxScale*yMax )
          elif ("_DYCR" in Region.Name):
            if ("Resolved" in Region.Name):
              h_dummy_up.GetYaxis().SetRangeUser( yMin, yMaxScale*yMax )
            else:
              h_dummy_up.GetYaxis().SetRangeUser( yMin, 50*yMax )
          elif ("NoBJet" in Region.Name):
            h_dummy_up.GetYaxis().SetRangeUser( 1E-2, 4*yMax )
            
        if (Variable.Name=="ZCand_Mass" or Variable.Name=="DiJet_Mass") and ("_DYCR" in Region.Name):
          h_dummy_up.GetYaxis().SetRangeUser(10, 2E5)
        if (Variable.Name=="ZCand_Pt" or Variable.Name=="DiJet_Pt") and ("_DYCR" in Region.Name):
          if ("Resolved" in Region.Name):
            h_dummy_up.GetYaxis().SetRangeUser(10, 5E6)
          else:
            h_dummy_up.GetYaxis().SetRangeUser(10, 2E5)
        
        if ("_CR" in Region.Name) :
          h_dummy_up.GetYaxis().SetRangeUser( 1E-1, yMaxScale*yMax )
          if ("_EE" in Region.Name) :
            h_dummy_up.GetYaxis().SetRangeUser( 1E-1, yMaxScale*yMax*3.5 )


        if self.DoDebug:
          print ('[DEBUG] Canvas is ready')

        ## Draw up

        c1_up.cd()

        h_dummy_up.Draw("histsame")
        stack_Bkgd.Draw("histsame")

        gr_Bkgd_TotErr.SetMarkerColor(0)
        gr_Bkgd_TotErr.SetMarkerSize(0)
        gr_Bkgd_TotErr.SetFillStyle(3013)
        gr_Bkgd_TotErr.SetFillColor(ROOT.kBlack)
        gr_Bkgd_TotErr.SetLineColor(0)
        if not self.NoErrorBand:
          gr_Bkgd_TotErr.Draw("sameE2")

        gr_Data.SetLineWidth(2)
        gr_Data.SetMarkerSize(0.)
        gr_Data.SetMarkerColor(ROOT.kBlack)
        gr_Data.SetLineColor(ROOT.kBlack)
        if Region.DrawData:
          h_Data.Draw("phistsame")
          gr_Data.Draw("p0same")

        #### 2020/10/14 For the ARC comments
        #for ix in range(0,h_Data.GetXaxis().GetNbins()):
        #  iBin = ix+1
        #  x_l = h_Data.GetXaxis().GetBinLowEdge(iBin)
        #  x_r = h_Data.GetXaxis().GetBinUpEdge(iBin)
        #  y_Data = h_Data.GetBinContent(iBin)
        #  y_Bkgd = h_Bkgd.GetBinContent(iBin)
        #  ratio = y_Data/y_Bkgd
        #  print '%s\t%d\t%d\t%1.2f\t%1.2f\t%1.2f'%(Region.Name, x_l, x_r, y_Data, y_Bkgd, ratio)

        ## Signal
        h_Sigs = []
        for Sig in self.SignalsToDraw:

          fname_Sig = self.Filename_prefix+'_Type1_SS_M%d'%(Sig.mN)+'.root'
          fpullpath_Sig = Indir+'/'+self.DataDirectory+'/SIGMerged/'+fname_Sig

          f_Sig = ROOT.TFile(fpullpath_Sig)

          Histogram_Name=Region.Name+'/RegionPlots_'+Region.PrimaryDataset+'/' + Region.ParamName+ '/'+Variable.Name

          h_Sig = f_Sig.Get(Histogram_Name)
          if not h_Sig:
            print (fpullpath_Sig)
            print (Histogram_Name)
            continue

          ## Make overflow
          if xMin !=  -999:
            h_Sig.GetXaxis().SetRangeUser(xMin,xMax)
          h_Sig = mylib.MakeOverflowBin(h_Sig)

          ## Rebin
          h_Sig = self.Rebin(h_Sig, Region.Name, Variable.Name, nRebin)

          ## Scale
          #h_Sig.Scale( Sig.xsec * Sig.kfactor * Sig.xsecScale )
          if Region.PrimaryDataset != "EMu":
            print("Scaling xsec by 2. since Signals have E+Mu coupling")
            h_Sig.Scale(2.)
          
          ## Att
          h_Sig.SetLineWidth(3)
          h_Sig.SetLineColor(Sig.Color)
          h_Sig.SetLineStyle(Sig.Style)

          ## Save
          h_Sigs.append(h_Sig)

          ## legend
          lg.AddEntry(h_Sig, Sig.GetTLatexAlias(), 'l')

          ## Draw
          h_Sig.Draw("histsame")

        h_dummy_up.Draw("axissame")

        ## Legend
        lg.Draw()

        ## Draw down
        c1_down.cd()
        h_dummy_down.Draw("histsame")

        ## values must be set later
        h_Data_Ratio = h_Data.Clone('h_Data_Ratio')
        ## BinContent set by divide here, but errors must be set later
        tmp_h_Data_Ratio = h_Data.Clone()
        tmp_h_Data_Ratio.Divide(h_Bkgd)
        gr_Data_Ratio = ROOT.TGraphAsymmErrors(tmp_h_Data_Ratio)
        gr_Data_Ratio.SetName('gr_Data_Ratio')
        gr_Data_Ratio.SetLineWidth(2)
        gr_Data_Ratio.SetMarkerSize(0.)
        gr_Data_Ratio.SetLineColor(ROOT.kBlack)
        ## values must be set later, but BinContent will be simply 1
        gr_Bkgd_Ratio = gr_Bkgd_TotErr.Clone('gr_Bkgd_Ratio')

        for i in range(1,h_Data_Ratio.GetXaxis().GetNbins()+1):

          ## FIXME for zero? how?
          if h_Bkgd.GetBinContent(i)!=0:

            ## ratio point
            ## BinContent = Data/Bkgd
            ## BinError = DataError/Bkgd
            h_Data_Ratio.SetBinContent( i, h_Data_Ratio.GetBinContent(i) / h_Bkgd.GetBinContent(i) )
            h_Data_Ratio.SetBinError ( i, h_Data_Ratio.GetBinError(i) / h_Bkgd.GetBinContent(i) )

            if err_down_tmp[i-1]!=0.:
              gr_Data_Ratio.SetPointEYlow(i-1, err_down_tmp[i-1] / h_Bkgd.GetBinContent(i) )
              gr_Data_Ratio.SetPointEYhigh(i-1, err_up_tmp[i-1] / h_Bkgd.GetBinContent(i))
              if Variable.Name!="NCand_Mass":
                gr_Data_Ratio.SetPointEXlow(i-1, 0)
                gr_Data_Ratio.SetPointEXhigh(i-1, 0)
            else:
              gr_Data_Ratio.SetPointEYlow(i-1, 0)
              gr_Data_Ratio.SetPointEYhigh(i-1, 1.8 / h_Bkgd.GetBinContent(i))
              if Variable.Name!="NCand_Mass":
                gr_Data_Ratio.SetPointEXlow(i-1, 0)
                gr_Data_Ratio.SetPointEXhigh(i-1, 0)

            ## ratio allerr
            ## BinContent = 1
            ## BinError = Bkgd(Stat+Syst)Error/Bkgd

            gr_Bkgd_Ratio.SetPoint(i-1,h_Bkgd.GetXaxis().GetBinCenter(i), 1.)
            gr_Bkgd_Ratio.SetPointEYhigh( i-1, gr_Bkgd_Ratio.GetErrorYhigh(i-1) / h_Bkgd.GetBinContent(i) )
            gr_Bkgd_Ratio.SetPointEYlow( i-1,  gr_Bkgd_Ratio.GetErrorYlow(i-1) / h_Bkgd.GetBinContent(i) )

          elif h_Bkgd.GetBinContent(i)==0. and h_Data_Ratio.GetBinContent(i)==0.:

            h_Data_Ratio.SetBinContent( i, 0 )
            h_Data_Ratio.SetBinError ( i, 0 )
            gr_Data_Ratio.SetPoint(i-1, 0, 0)
            gr_Data_Ratio.SetPointEYlow(i-1, 0)
            gr_Data_Ratio.SetPointEYhigh(i-1, 0)

            gr_Bkgd_Ratio.SetPoint(i-1,h_Bkgd.GetXaxis().GetBinCenter(i), 1.)
            gr_Bkgd_Ratio.SetPointEYhigh( i-1, 0. )
            gr_Bkgd_Ratio.SetPointEYlow( i-1, 0. )

            if Variable.Name!="NCand_Mass":
              gr_Data_Ratio.SetPointEXlow(i-1, 0)
              gr_Data_Ratio.SetPointEXhigh(i-1, 0)

          ## If bkgd <= 0
          else:
            this_max_ratio = 20.0
            this_data = h_Data_Ratio.GetBinContent(i)
            this_data_err = h_Data_Ratio.GetBinError(i)

            h_Data_Ratio.SetBinContent( i, this_max_ratio )
            h_Data_Ratio.SetBinError ( i, this_data_err*this_max_ratio/this_data )

            tmp_x = ctypes.c_double(0.)
            tmp_y = ctypes.c_double(0.)
            #            tmp_x = ROOT.Double(0.)
            #tmp_y = ROOT.Double(0.)
            gr_Data_Ratio.GetPoint(i-1, tmp_x, tmp_y)
            gr_Data_Ratio.SetPoint(i-1, tmp_x, this_max_ratio)
            gr_Data_Ratio.SetPointEYlow(i-1, err_down_tmp[i-1]*this_max_ratio/this_data)
            gr_Data_Ratio.SetPointEYhigh(i-1, err_up_tmp[i-1]*this_max_ratio/this_data)

            gr_Bkgd_Ratio.SetPoint(i-1,h_Bkgd.GetXaxis().GetBinCenter(i), 1.)
            gr_Bkgd_Ratio.SetPointEYhigh( i-1, 0. )
            gr_Bkgd_Ratio.SetPointEYlow( i-1, 0. )

            if Variable.Name!="NCand_Mass":
              gr_Data_Ratio.SetPointEXlow(i-1, 0)
              gr_Data_Ratio.SetPointEXhigh(i-1, 0)
        ##==>End bin loop

        gr_Bkgd_Ratio.SetMarkerColor(0)
        gr_Bkgd_Ratio.SetMarkerSize(0)
        gr_Bkgd_Ratio.SetFillStyle(3013)
        gr_Bkgd_Ratio.SetFillColor(ROOT.kBlack)
        gr_Bkgd_Ratio.SetLineColor(0)
        gr_Bkgd_Ratio.Draw("sameE2")

        h_Data_Ratio.Draw("p9histsame")
        gr_Data_Ratio.Draw("p0same")

        ## y=1 graph
        g1_x = [-9000, 9000]
        g1_y = [1, 1]
        g1 = ROOT.TGraph(2, array("d", g1_x ), array("d", g1_y ))
        g1.Draw("same")

        ## TLatex
        c1.cd()
        channelname = ROOT.TLatex()
        channelname.SetNDC()
        channelname.SetTextSize(0.037)
        channelname.DrawLatex(0.2, 0.88, "#font[42]{"+Region.TLatexAlias+"}")

        ## Extra lines
        exec(self.ExtraLines)

        ## Save
        c1.SaveAs(Outdir+Variable.Name+'_'+Region.PrimaryDataset+'_'+Region.Name+'.pdf')
        c1.SaveAs(Outdir+Variable.Name+'_'+Region.PrimaryDataset+'_'+Region.Name+'.png')
        print (Variable.Name+'_'+Region.Name+'.pdf ==> Saved')

        print(str(self.OutputDirectory))
        if not self.OutputDirectory =="":
          print ('scp ' + Outdir+Variable.Name+'_'+Region.PrimaryDataset+'_'+Region.Name+'.pdf  '+self.Lxplus_User + '@lxplus.cern.ch:'+OutdirLXPLUS+'/')
          os.system('scp ' + Outdir+Variable.Name+'_'+Region.PrimaryDataset+'_'+Region.Name+'.pdf  '+self.Lxplus_User + '@lxplus.cern.ch:'+OutdirLXPLUS+'/')
          os.system('scp ' + Outdir+Variable.Name+'_'+Region.PrimaryDataset+'_'+Region.Name+'.png  '+self.Lxplus_User + '@lxplus.cern.ch:'+OutdirLXPLUS+'/')
          lxplus_dir.append(OutdirLXPLUS)
          

        c1.Close()

      ##==>End Variable loop
      
      if self.DoDebug:
        print ('[DEBUG] All variables are done for this region, closing data TFile')
      f_Data.Close()

    ##==>End Region loop

    print ("List of output dir:")
    for _dir in lxplus_dir:
      htmlname=_dir
      htmlname.replace('/afs/cern.ch/user/j/jalmond/www/','https://jalmond.web.cern.ch/jalmond/')
      print htmlname
    if self.DoDebug:
      print ('[DEBUG] All regions are done.')
