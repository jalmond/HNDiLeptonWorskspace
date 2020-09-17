import os 
def read_limit_output(limit_dir,tag):

    counter=0
    fulllog=[]
    file_limit_path= str(os.getenv("LIMIT_PATH")) +limit_dir+"/"
    for root, dirs, files in os.walk(file_limit_path):
        for filename in files:
            if "job" in filename:
                if ".log" in filename:
                    counter=counter+1
                    _file = open(file_limit_path+filename,"r")
                    for f in _file:
                        fulllog.append(f)
                    _file.close()
    Found=False
    _card=""
    _Fulllog=[]
    TagFound=False
    for x in fulllog:
        if tag in x:
            TagFound=True
        if "Input datacard" in x:
              _Fulllog.append(x)

        if Found:
            _Fulllog.append(x)
        if "-- Hybrid New -- " in x:
            _Fulllog.append(x)
            Found=True

        if "Done" in x:
            _Fulllog.append(x)

            Found=False
    
    if not TagFound:
        print "@"*30
        print "Incorrect directory as no input found"
        print "@"*30
        exit()
    print "Number of jobs in dir " +  file_limit_path + " is " + str(counter)
    return _Fulllog
