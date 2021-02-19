import os
import sys
import math
import numpy as np
import time
import os.path
import random


from OMPython import OMCSessionZMQ

time = 1000

print "removing old System (if any) ..."
os.system("rm -f ./System")    # remove previous executable, if any.
print "done!"

counter_ok = 0
counter_fail = 0
counter_tot = 0

for i1 in range (0,10):

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

    omc.sendExpression("loadFile(\"System.mo\")")
    omc.sendExpression("getErrorString()")

    omc.sendExpression("buildModel(System, stopTime="+str(float(time))+")")
    omc.sendExpression("getErrorString()")

#omc.sendExpression('simulate(System, outputFormat="mat", startTime=0, stopTime=100, numberOfIntervals=5)')
#omc.sendExpression("getErrorString()")



    rand_meal_len = random.randint(60,120)
    #rand_meal_len = 5
    rand_meal_period = random.randint(300,480)
    #rand_meal_period = 20
    rand_gamma = random.randint(10,30)
    #gamma = 20

    rand_b= round(random.uniform(0.5841, 0.8282),4)         # original value 0.7328;
    rand_d= round(random.uniform(0.061, 0.1436),4)          # original value 0.1014
    rand_kmax= round(random.uniform(0.0318,0.0869),4)       # original value 0.0426 
    rand_kmin= round(random.uniform(0.0066, 0.01),4)        # original value 0.0076 
    rand_kabs= round(random.uniform(0.0293, 0.1),4)         # original value 0.0542 
    rand_BW=   round(random.uniform(83.0, 104.0),2)         # original value 96


    with open ("parameters.txt", 'wt') as f:                
        f.write("gen.Meal_length="+str(rand_meal_len)+"\n"+"gen.Meal_period="+str(rand_meal_period)+"\n"+"gen.gamma="+str(rand_gamma)+"\n"+"rag.K.b="+str(rand_b)+"\n"+"rag.K.d="+str(rand_d)+"\n"+"rag.K.kmax="+str(rand_kmax)+"\n"+"rag.K.kmin="+str(rand_kmin)+"\n"+"rag.K.kabs="+str(rand_kabs)+"\n"+"rag.K.BW="+str(rand_BW)+"\n")
        f.flush()
        os.fsync(f)
    os.system("./System -s=rungekutta -overrideFile=parameters.txt > log")
    '''
    for i2 in range(0,time):

        delta = omc.sendExpression("val(gen.delta, "+str(float(i2))+", \"System_res.mat\")")
        ra_meal = omc.sendExpression("val(rag.Rameal, "+str(float(i2))+", \"System_res.mat\")")
        glucose = omc.sendExpression("val(pa.G, "+str(float(i2))+", \"System_res.mat\")")
        insulin = omc.sendExpression("val(pa.I, "+str(float(i2))+", \"System_res.mat\")")


        print "\nDelta: ", delta
        print "Ra_meal: ", ra_meal
        print "Glucose: ", glucose
        print "Insulin: ", insulin, "\n"

    print "\nMeal length: ", rand_meal_len
    print "Meal_period: ", rand_meal_period
    print "rand_b: ", rand_b
    print "rand_d: ", rand_d
    print "rand_kmax: ", rand_kmax
    print "rand_kmin: ", rand_kmin
    print "rand_kabs: ", rand_kabs
    print "rand_BW: ", rand_BW, "\n"

    b = omc.sendExpression("val(rag.K.b, 1000, \"System_res.mat\")")
    d = omc.sendExpression("val(rag.K.d, 1000, \"System_res.mat\")")
    kmax = omc.sendExpression("val(rag.K.kmax, 1000, \"System_res.mat\")")
    kmin = omc.sendExpression("val(rag.K.kmin, 1000, \"System_res.mat\")")
    kabs = omc.sendExpression("val(rag.K.kabs, 1000, \"System_res.mat\")")
    BW = omc.sendExpression("val(rag.K.BW, 1000, \"System_res.mat\")")

    print "\nb: ", b
    print "d: ", d
    print "kmax: ", kmax
    print "kmin: ", kmin
    print "kabs: ", kabs
    print "BW: ", BW, "\n"
    '''
    delta = omc.sendExpression("val(gen.delta, "+str(time)+", \"System_res.mat\")")
    ra_meal = omc.sendExpression("val(rag.Rameal, "+str(time)+", \"System_res.mat\")")
    glucose = omc.sendExpression("val(pa.G, "+str(time)+", \"System_res.mat\")")
    insulin = omc.sendExpression("val(pa.I, "+str(time)+", \"System_res.mat\")")


    #print "\nDelta: ", delta
    print "\nSimulation", i1+1
    print "Ra_meal: ", ra_meal
    print "Glucose: ", glucose
    print "Insulin: ", insulin, "\n"

    fail = omc.sendExpression("val(pu.fail, 1000.0, \"System_res.mat\")")

    if fail == True: 
        print("fail")
        counter_fail = counter_fail + 1
    else : 
        print("pass")
        counter_ok = counter_ok + 1
    
counter_tot = counter_ok + counter_fail

print "\nTotal number of tests: ", counter_tot
print "Number of test passed: ", counter_ok
print "Number5 of tests failed: ", counter_fail, "\n"

 
#os.system("libreoffice --calc System_res.csv ./System")
os.system("./clean.sh ./System") 

