# HNDiLeptonWorskspace
General workspace for dilepton hn analyses

Contains Codes for:

- merging root files in tamsa/macbook for plot/limits
- checking/plotting signal efficiencies 
- making SR/CR plots
- making cards for limits

----------------------------------------------------
 Steps to get limits Cut and Count:
----------------------------------------------------

[1] Merge output from SKAnalyzer \n
- cd $HNDILEPTONWORKSPACE_DIR/OutputTool/$Analyzer \n
- source run.sh
    >>>>>>> Files are merged and sent to $HNDILEPTONWORKSPACE_DIR/OutputTool/MergedFiles/$Analyzer
    >>>>>>> i.e, one for each bkg SSPrompt,CF,FakeMu, OSPrompt

[2] Make cards
--- cd $HNDILEPTONWORKSPACE_DIR/Limits/MakeCards/CutandCount
--- source run.sh $config 
    >>>>>>> $config found in configfiles dir
    >>>>>>> script produces datacards for each SR bin depending on the instructions in $config, options are
    	        >  channels = Combinedchannel,SChannel,TChannel  (as long as signals are ran, combined adds s+t)
		>  flavours = EE,MuMu   (names given in analyzer for channels)    
		>  years    = 2016,2017,2018 
		>  SRs      = SR1,SR2  (names of SR in analyzer)
		>  masses_s = 100,125,200,250,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500 (mass for s-channel)
		>  masses_t = 600,700,800,900,1000,1100,1200,1500  (masses of signal t-channel)
		>  masses_c = 100,125,200,250,300,400,500,600,700,800,900,1000,1100,1200,1500 (masses with combined)
		>  IDMu     = POGTightPFIsoVeryTight  (name of ID in analyzer)
		>  IDEl     = passTightID  ( (name of ID in analyzer))

    >>>>>>> datacards sent to  $HNDILEPTONWORKSPACE_DIR/Limits/DataCardsCutCount/HNtypeI_JA/Year/Channel+SR
    >>>>>>> list of all datacards to run combined in $HNDILEPTONWORKSPACE_DIR/Limits/DataCardsCutCount/HNtypeI_JA/run/
    >>>>>>> signals are scaled to get r param in limit code
    >>>>>>> configure to set systematics
    
    >>>>>>> Also produces txt files and plots for all datacards, sent to lxplus website
    >>>>>>> Txt files sent to $HNDILEPTONWORKSPACE_DIR/Limits/DataCardsCutCount/HNtypeI_JA/Year/Channel+SR
		>  cardname="card_"+year+"_"+flavour + "_" + SR+"_N" + mass + isVBF+"_"+_id+".txt"
		>  txtfile = event_counts_"+year+"_"+SR+"_"+_id+"_"+flavour+"_cutcount.txt"

[3] run combine  on limit card
--- get blind exected limits for each year:
    >>>>> MuMu_SR1 (SS ; 1 ak4 jet; 0 AK8 jets)
    >>>>> MuMu_SR2 (SS ; X ak4 jet; 1+ AK8 jets)
    >>>>> MuMu_SR3 (OS ; 1 ak4 jet; 0 AK8 jets)
    >>>>> MuMu_SR4 (OS ; X ak4 jet; 1+ AK8 jets)
    >>>>> EE_SR1 (SS ; 1 ak4 jet; 0 AK8 jets)
    >>>>> EE_SR2 (SS ; X ak4 jet; 1+ AK8 jets)
    >>>>> EE_SR3 (OS ; 1 ak4 jet; 0 AK8 jets)
    >>>>> EE_SR4 (OS ; X ak4 jet; 1+ AK8 jets)

[4] merge cards for:
    >>>>>>  LL_SR1+SR2     (each year)
    	    > DIR =  Outdir +  + year + "/"+flavour+"_CombinedSR1_SR2/
	    > cardname= "card_"+year + "_"+flavour+"_combined_SR1_SR2_N"+mass+channel_tag+"_"+_id+".txt"
    >>>>>>  LL_SR1+SR2+SR3+SR4  (each year)
    	    > Outdir +  + year + "/"+flavour+"_CombinedSR1_SR2_SR3_SR4/
	    > cardname= "card_"+year + "_"+flavour+"_combined_SR1_SR2_SR3_SR4_N"+mass+channel_tag+"_"+_id+".txt"
    >>>>>   2016-2018 LL_SR1+SR2
    	    > "card_CombinedYears_"+flavour+"_combined_SR1_SR2_N"+mass+channel_tag+"_"+_id+".txt"
    >>>>>   2016-2018 LL_SR1+SR2+SR3+SR4
    	    > "card_CombinedYears_"+flavour+"_combined_SR1_SR2_SR3_SR4_N"+mass+channel_tag+"_"+_id+".txt"


----------------------------------------------------
 Steps to get limits Shape:
----------------------------------------------------
- copy steps [1] from Cut Count

- [2] Making datacards

--- produce root files for input
    >>>>>>> cd /data6/Users/jalmond/2020/HL_SKFlatAnalyzer/HNDiLeptonWorskspace/Limits/MakeShapeInput/
    >>>>>>> source run.sh  (this can be configured as it runs all variables in default)
--- follow steps for Cut and count but navigate to shape working dir.
    >>>>>>> cards and root files sent to $HNDILEPTONWORKSPACE_DIR/Limits/DataCardsShape/HNtypeI_JA/Year/Channel+SR
    	   	 > cardname = card_"+year+"_"+flavour + "_" + SR+"_N" + mass + isVBF+"_" +_id+"_"+_var+".txt"
		 > input_rootfile = "HN"+ mass + "_highmass_Run2Legacy_v4_"+year + "_"+SR + "_"+ flavour + "_"+_id + "_"+_var+".root
    >>>>>>> cards copied to os.getenv("HNDILEPTONWORKSPACE_DIR")+"/"+ str(Outdir)+"/Workspace/"

		 