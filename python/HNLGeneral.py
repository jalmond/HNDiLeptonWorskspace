import os

def GetOutput(_command,tag):
    
    tag=tag.replace('/','_')

    cdir2 = os.getcwd()+"/"
    os.system(_command + " &> "+cdir2+"/log_getoutput"+tag+".txt ")
    arr_commands=[]
    commandlist = open (cdir2+"/log_getoutput"+tag+".txt","r")

    for _line in commandlist:
        _line = _line.strip('\n')
        _line = _line.replace('\t',' ')
        arr_commands.append(_line)
    commandlist.close()

    os.system('rm ' + cdir2+'/log_getoutput'+tag+'.txt')

    return arr_commands
