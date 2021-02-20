import os
import sys
import math
import numpy as np
import time
import os.path
import random


from OMPython import OMCSessionZMQ

time = 100

print "removing old System (if any) ..."
os.system("rm -f ./System")    # remove previous executable, if any.
print "done!"

counter_ok = 0
counter_fail = 0
counter_tot = 0
step_a = 3.0        # original value 1.0
step_b = 0.001      # original value 0.001

for i0 in range (0, 3):

    print "Patient ", i0, "\n"

    rand_b= round(random.uniform(0.5841, 0.8282),4)         # original value 0.7328
    rand_d= round(random.uniform(0.061, 0.1436),4)          # original value 0.1014
    rand_kmax= round(random.uniform(0.0318,0.0869),4)       # original value 0.0426 
    rand_kmin= round(random.uniform(0.0066, 0.01),4)        # original value 0.0076 
    rand_kabs= round(random.uniform(0.0293, 0.1),4)         # original value 0.0542 
    rand_BW=   round(random.uniform(83.0, 104.0),2)         # original value 96

    #rand_Vg = round(random.uniform(0.73,1.33),2)            # original value 1
    rand_Vi = round(random.uniform(0.039,0.062),3)          #original value 0.041

    rand_meal_len = random.randint(60,120)
    rand_meal_period = random.randint(300,480)
    rand_gamma = random.randint(10,30)
    #gamma = 20


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
        
        #step_a = step_a + 0.1
        #step_b = step_b + 0.005
        sum_g = 0
        min_g, min_i = 100000, 100000
        max_g, max_i = 0, 0

        print "\nSimulation", i1+1
        print "a: ", step_a
        print "b: ", step_b, "\n"

        with open ("parameters.txt", 'wt') as f:                
            f.write("gen.Meal_length="+str(rand_meal_len)+"\n"+"gen.Meal_period="+str(rand_meal_period)+"\n"+"gen.gamma="+str(rand_gamma)+"\n"+"rag.K.b="+str(rand_b)+"\n"+"rag.K.d="+str(rand_d)+"\n"+"rag.K.kmax="+str(rand_kmax)+"\n"+"rag.K.kmin="+str(rand_kmin)+"\n"+"rag.K.kabs="+str(rand_kabs)+"\n"+"rag.K.BW="+str(rand_BW)+"\n"+"pu.a="+str(step_a)+"\n"+"pu.b="+str(step_b)+"\n"+"pa.Vi="+str(rand_Vi))
            f.flush()
            os.fsync(f)
        os.system("./System -s=rungekutta -overrideFile=parameters.txt > log")
        
        for i2 in range(0,time):

            #delta = omc.sendExpression("val(gen.delta, "+str(float(i2))+", \"System_res.mat\")")
            #ra_meal = omc.sendExpression("val(rag.Rameal, "+str(float(i2))+", \"System_res.mat\")")
            glucose = omc.sendExpression("val(pa.G, "+str(float(i2))+", \"System_res.mat\")")
            insulin_out = omc.sendExpression("val(pu.insulin_out, "+str(float(i2))+", \"System_res.mat\")")

            sum_g = sum_g + glucose
            if (glucose > max_g): max_g = glucose
            if (glucose < min_g): min_g = glucose
            if (glucose > max_i): max_i = insulin_out
            if (glucose < min_i): min_i = insulin_out
            #print "\nDelta: ", delta
            #print "Ra_meal: ", ra_meal
            #print "Glucose: ", glucose
            #print "Insulin: ", insulin, "\n"

        '''
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
        

        delta = omc.sendExpression("val(gen.delta, "+str(time)+", \"System_res.mat\")")
        ra_meal = omc.sendExpression("val(rag.Rameal, "+str(time)+", \"System_res.mat\")")
        glucose = omc.sendExpression("val(pa.G, "+str(time)+", \"System_res.mat\")")
        insulin = omc.sendExpression("val(pa.I, "+str(time)+", \"System_res.mat\")")


        #print "\nDelta: ", delta
        print "\nSimulation", i1+1
        print "Ra_meal: ", ra_meal
        print "Glucose: ", glucose
        print "Insulin: ", insulin, "\n"
        '''
        #Vg = omc.sendExpression("val(pa.Vg, "+str(float(time))+", \"System_res.mat\")")
        #Vi = omc.sendExpression("val(pa.Vi, "+str(float(time))+", \"System_res.mat\")")
        
        media = sum_g / time
        print "\nAverage values: "
        print "min glucose: ", min_g
        print "max glucose: ", max_g
        print "min insulin: ", min_i
        print "max insulin: ", max_i
        print "average glucose: ", media

        fail = omc.sendExpression("val(pu.fail,"+str(float(time))+", \"System_res.mat\")")

        if fail == True: 
            print("fail")
            counter_fail = counter_fail + 1
        else : 
            print("pass")
            counter_ok = counter_ok + 1

        print "------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
        
    counter_tot = counter_ok + counter_fail

print "\nTotal number of tests: ", counter_tot
print "Number of test passed: ", counter_ok
print "Number of tests failed: ", counter_fail, "\n"

 
#os.system("libreoffice --calc System_res.csv ./System")
os.system("./clean.sh ./System") 

