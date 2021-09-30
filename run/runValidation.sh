python3 python/Draw_Val.py -c 0 -y 2016
bash CutFlow/Cutflow.sh
python3 python/Draw_Val_W.py -c 0 -y 2016
bash CutFlow/Cutflow.sh
python3 python/Draw_Val.py -c 0 -y 2017
bash CutFlow/Cutflow.sh
python3 python/Draw_Val_W.py -c 0 -y 2017
bash CutFlow/Cutflow.sh
python3 python/Draw_Val.py -c 0 -y 2018
bash CutFlow/Cutflow.sh
python3 python/Draw_Val_W.py -c 0 -y 2018
bash CutFlow/Cutflow.sh
rsync -av $PLOT_PATH/$SKANVERSION/HNL_Validation/   jalmond@lxplus:~/www/SNU/WebPlots/HNL/HNL_Validation
