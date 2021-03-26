import os
import sys
import math
import numpy as np
import time
import os.path
import random

from color import pretty, prettyln

from OMPython import OMCSessionZMQ

#omc = OMCSessionZMQ()

# remove previos executable, if any ...
print '\nremoving old System (if any) ...'
os.system("rm -f ./System")    
print "done!\n"

# setting simulation time an number of patient to test ...
sim_time = 2000
num_of_patient = 100

# setting global variables to count the number of passed test and the average of glucose level between diffrent patients
Global_Average = 0
counter_ok = 0
counter_fail = 0
counter_tot = 0

a =  1040       # original value 1.0
b =  1.95       # original value 0.001

pre_average = 0
enable_sleep = False

start_time = time.time()

for i in range(0, num_of_patient):   # Start simulation for n patients

    # Generating a random patient
    print "\nPatient ", i, "\n"

    fail_test = False

    rand_b= round(random.uniform(0.5841, 0.8282),4)         # original value 0.7328
    rand_d= round(random.uniform(0.061, 0.1436),4)          # original value 0.1014
    rand_kmax= round(random.uniform(0.0318,0.0869),4)       # original value 0.0426 
    rand_kmin= round(random.uniform(0.0066, 0.01),4)        # original value 0.0076 
    rand_kabs= round(random.uniform(0.0293, 0.1),4)         # original value 0.0542 
    rand_BW= round(random.uniform(83.0, 104.0),2)           # original value 96

    #rand_meal_len = random.randint(590,650)
    #rand_meal_period = random.randint(2300,2450)

    get_sim_time = time.time()
    
    # Building Model for specific patient 
    
    omc = OMCSessionZMQ()
    omc.sendExpression("getVersion()")
    omc.sendExpression("cd()")

    omc.sendExpression("loadFile(\"connectors.mo\")")
    omc.sendExpression("getErrorString()")

    omc.sendExpression("loadFile(\"fake_patient.mo\")")
    omc.sendExpression("getErrorString()")

    omc.sendExpression("loadFile(\"mealgen.mo\")")
    omc.sendExpression("getErrorString()")

    omc.sendExpression("loadFile(\"pump.mo\")")
    omc.sendExpression("getErrorString()")

    omc.sendExpression("loadFile(\"rag_meal.mo\")")
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

    # write patient parameter in parameter.txt
    with open ("parameters.txt", 'wt') as f:                
        f.write(
        #"gen.Meal_length="+str(rand_meal_len)+"\n"+
        #"gen.Meal_period="+str(rand_meal_period)+"\n"+
        "mo_av.stop_simulation="+str(sim_time)+"\n"+
        "rag.K.b="+str(rand_b)+"\n"+
        "rag.K.d="+str(rand_d)+"\n"+
        "rag.K.kmax="+str(rand_kmax)+"\n"+
        "rag.K.kmin="+str(rand_kmin)+"\n"+
        "rag.K.kabs="+str(rand_kabs)+"\n"+
        "rag.K.BW="+str(rand_BW)+"\n"+
        "pu.a="+str(a)+"\n"+
        "pu.b="+str(b)+"\n"
        )
        f.flush()
        os.fsync(f)
        
    os.system("./System -s=rungekutta -overrideFile=parameters.txt > log")

    if (enable_sleep):
        prettyln("Time delay has been activated because simulation time overcome parameter writing time on file parameters.txt\n", "r") 
        time.sleep(1)  

    os.system("rm -f parametres.txt")       # to be on the safe Side
    
    print "\nSimulation Time:\n"
    print "--- %s seconds ---" % (time.time() - get_sim_time), "\n"
    
    # End of Simulation
    
    fail_pump = omc.sendExpression("val(mo_pu.controller,"+str(float(sim_time))+", \"System_res.mat\")")
    min_g = omc.sendExpression("val(mo_av.min_g,"+str(float(sim_time))+", \"System_res.mat\")")
    max_g = omc.sendExpression("val(mo_av.max_g,"+str(float(sim_time))+", \"System_res.mat\")")
    average = omc.sendExpression("val(mo_av.average,"+str(float(sim_time))+", \"System_res.mat\")")
    low_average = omc.sendExpression("val(mo_av.low_average,"+str(float(sim_time))+", \"System_res.mat\")")
    high_average = omc.sendExpression("val(mo_av.high_average,"+str(float(sim_time))+", \"System_res.mat\")")

    if (average == pre_average): 
        enable_sleep = True
    else: pre_average = average
    
    print "\nAverage values: "
    print "min glucose: ", min_g
    print "max glucose: ", max_g
    if (low_average):
        print "The average glucose value is too low: ", average
        fail_test = True
    elif (high_average): 
        print "The average glucose value is too high: ", average
        fail_test = True

    else: print "average glucose: ", average
            
    Global_Average = Global_Average + average
    
    if (fail_pump or fail_test) :  
        counter_fail = counter_fail + 1
        prettyln('fail', 'r')
        prettyln("---------------------------------------------------------------------------------------------------------------------------------\n", 'r')         
    else : 
        counter_ok = counter_ok + 1
        prettyln('pass', 'g')
        prettyln("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n", 'g')
     
# End Loop
    
counter_tot = counter_ok + counter_fail
print "\nGlobal Average of glucose: ", Global_Average/counter_tot
print "\nTotal number of tests: ", counter_tot
print "Number of test passed: ", counter_ok
print "Number of tests failed: ", counter_fail,"\n"

print "--- %s seconds ---" % (time.time() - start_time), "\n"
 
os.system("./clean.sh") 

