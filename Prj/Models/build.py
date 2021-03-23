import os
import sys
import os.path

from OMPython import OMCSessionZMQ

l = len(sys.argv) 


if (l < 4 or l > 4): 
        print sys.argv
        print "Error: 1 option and 2 arguments needed"
        quit(10)

#if (not(sys.argv[1].isdigit()) or not(sys.argv[2].isdigit())) :
        #print "Error: the 2 argument must be numbers"
        #quit(15)

a = float(sys.argv[2]) 
b = float(sys.argv[3]) 

if (sys.argv[1] == "-v"):
    print "ok"    
    rand_b= round(random.uniform(0.5841, 0.8282),4)         # original value 0.7328
    rand_d= round(random.uniform(0.061, 0.1436),4)          # original value 0.1014
    rand_kmax= round(random.uniform(0.0318,0.0869),4)       # original value 0.0426 
    rand_kmin= round(random.uniform(0.0066, 0.01),4)        # original value 0.0076 
    rand_kabs= round(random.uniform(0.0293, 0.1),4)         # original value 0.0542 
    rand_BW= round(random.uniform(83.0, 104.0),2)           # original value 96

    rand_meal_len = random.randint(600,700)
    #rand_meal_period = random.randint(300,480)

    with open ("parameters.txt", 'wt') as f:                
        f.write(
        #"gen.Meal_length="+str(rand_meal_len)+"\n"+
        "gen.Meal_period="+str(rand_meal_period)+"\n"+
        "rag.K.b="+str(rand_b)+"\n"+
        "rag.K.d="+str(rand_d)+"\n"+
        "rag.K.kmax="+str(rand_kmax)+"\n"+
        "rag.K.kmin="+str(rand_kmin)+"\n"+
        "rag.K.kabs="+str(rand_kabs)+"\n"+
        "rag.K.BW="+str(rand_BW)+"\n"
        )
        f.flush()
        os.fsync(f)
else :
    pass

sim_time = 2000

omc = OMCSessionZMQ()
omc.sendExpression("getVersion()")
omc.sendExpression("cd()")

omc.sendExpression("loadFile(\"connectors.mo\")")
omc.sendExpression("getErrorString()")

omc.sendExpression("loadFile(\"fake-patient.mo\")")
omc.sendExpression("getErrorString()")

omc.sendExpression("loadFile(\"mealgen.mo\")")
omc.sendExpression("getErrorString()")

omc.sendExpression("loadFile(\"Pump.mo\")")
omc.sendExpression("getErrorString()")

omc.sendExpression("loadFile(\"rag.mo\")")
omc.sendExpression("getErrorString()")

omc.sendExpression("loadFile(\"monitor_pump.mo\")")
omc.sendExpression("getErrorString()")

omc.sendExpression("loadFile(\"monitor_average.mo\")")
omc.sendExpression("getErrorString()")

omc.sendExpression("loadFile(\"monitor_hipogli.mo\")")
omc.sendExpression("getErrorString()")

omc.sendExpression("loadFile(\"System.mo\")")
omc.sendExpression("getErrorString()")

omc.sendExpression("buildModel(System, stopTime="+str(float(sim_time))+")")
omc.sendExpression("getErrorString()")