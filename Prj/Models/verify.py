import os
import sys
import math
import numpy as np
import time
import os.path
import random

# Color is a script that implements a function used to print colored text
# Note: If this causes problems, you can remove it
# but to do this you also need to edit all calls to
# pretty or prettyln in plain print     
from color import pretty, prettyln

from OMPython import OMCSessionZMQ

# Remove previous executable, if any ...
print '\nremoving old System (if any) ...'
os.system("rm -f ./System")
print "done!\n"

# Simulation time and number of patient to test ...
sim_time = 2000
num_of_patient = 10

# Remove previous output file, if any ...
os.system("rm -f Output"+str(num_of_patient)+".txt")   

# Initializes total average glucose across all simulations and the test counter
Global_Average = 0
counter_ok = 0
counter_fail = 0
counter_tot = 0

# Parameters to control the amount of insulin injected by the pump experimentally found 
a =  1040       # original value 1.0
b =  1.95       # original value 0.001

# Minimum acceptable blood glucose value
lower_limit = 70

# To prevent overwriting in parameters.txt
pre_average = 0         # store the glucose average value in the previous simulation
delay = 0.6             
enable_sleep = False    # signal to trigger the delay

# Generate an Output.txt files
os.system("echo Output >> Output"+str(num_of_patient)+".txt")

# Note: if you want to store the experimental results in Output.txt 
# set the following variable to True
output = True

# Start counting time to run n Simulation
start_time = time.time()

for i in range(0, num_of_patient):   # Start multiple simulation for n patients

    # Generate a random patient
    print "\nPatient ", i, "\n"

    rand_b= round(random.uniform(0.5841, 0.8282),4)         # original value 0.7328
    rand_d= round(random.uniform(0.0610, 0.1436),4)         # original value 0.1014
    rand_kmax= round(random.uniform(0.0318,0.0869),4)       # original value 0.0426 
    rand_kmin= round(random.uniform(0.0066, 0.01),4)        # original value 0.0076 
    rand_kabs= round(random.uniform(0.0293, 0.1),4)         # original value 0.0542 
    rand_BW= round(random.uniform(83.0, 104.0),2)           # original value 96
    
    # Randomize meal time and period
    #rand_meal_len = random.randint(590,650)
    #rand_meal_period = random.randint(2300,2450)

    # Start counting time to run a single Simulation
    get_sim_time = time.time()
    
    # Build Model for specific patient 
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

    omc.sendExpression("loadFile(\"monitor_hypogly.mo\")")
    omc.sendExpression("getErrorString()")

    omc.sendExpression("loadFile(\"System.mo\")")
    omc.sendExpression("getErrorString()")
    
    omc.sendExpression("buildModel(System, stopTime="+str(float(sim_time))+")")
    omc.sendExpression("getErrorString()")

    # Write patient parameters to parameters.txt and run simulation with new values
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
        "pu.b="+str(b)+"\n"+
        "mo_hy.correction="+str(lower_limit)+"\n"
        )
        f.flush()
        os.fsync(f)
  
    os.system("./System -s=rungekutta -overrideFile=parameters.txt > log")

    # Apply the delay only in case there are some duplicate patients
    if (delay >= 0.8): 
        prettyln("Delay: "+str(delay)+"s\n", 'r')
        time.sleep(delay)  

    # End of a single Simulation
    print "\nSimulation Time:\n"
    print "--- %s seconds ---" % (time.time() - get_sim_time), "\n"
    
    # Get control variables from monitors
    fail_pump = omc.sendExpression("val(mo_pu.controller,"+str(float(sim_time))+", \"System_res.mat\")")
    low_average = omc.sendExpression("val(mo_av.low_average,"+str(float(sim_time))+", \"System_res.mat\")")
    high_average = omc.sendExpression("val(mo_av.high_average,"+str(float(sim_time))+", \"System_res.mat\")")

    # Get glucose values from monitors
    min_g = omc.sendExpression("val(mo_av.min_g,"+str(float(sim_time))+", \"System_res.mat\")")
    max_g = omc.sendExpression("val(mo_av.max_g,"+str(float(sim_time))+", \"System_res.mat\")")
    average = omc.sendExpression("val(mo_av.average,"+str(float(sim_time))+", \"System_res.mat\")")

    # Check for duplicate patients
    if (average == pre_average):    
        prettyln("The delay has been activated because the simulation time exceeds the time for writing parameters to the parameters.txt file \n", 'r')
        delay += 0.2
    else: pre_average = average
    
    if (not(output)):
        # Patient's values
        print "\nAverage values: "
        print "min glucose: ", min_g
        print "max glucose: ", max_g
        if (low_average):
            print "The average glucose value is too low: ", average
        elif (high_average): 
            print "The average glucose value is too high: ", average
        else: print "average glucose: ", average
                
        # check for pump failure
        if (fail_pump or low_average or high_average) :  
            counter_fail = counter_fail + 1
            prettyln('fail', 'r')
            prettyln("---------------------------------------------------------------------------------------------------------------------------------\n", 'r')         
        else : 
            counter_ok = counter_ok + 1
            prettyln('pass', 'g')
            prettyln("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n", 'g')

        Global_Average = Global_Average + average
    
    else:
        if (fail_pump or low_average or high_average) :  
            counter_fail = counter_fail + 1
        else : 
            counter_ok = counter_ok + 1

        # Write the  Experimental Results to Output.txt
        test = lambda x : "fail" if(x) else "pass"
        with open ("Output"+str(num_of_patient)+".txt", 'a') as f:                
            f.write(
            "test "+str(i+1)+": glucose average = "+str(average)+" "+test(fail_pump)+'\n'
            )
            f.flush()
            os.fsync(f)
  
    #os.system("rm -f System_res.mat")       # to be on the safe side
    os.system("rm -f parameters.txt")       # to be on the safe Side

# End of n-th Simulation
os.system("rm -f parameters.txt")

# Final Results
if (not(output)): 
    os.system("rm -f Output"+str(num_of_patient)+".txt")
    print "\nGlobal Average of glucose: ", Global_Average/counter_tot
    print "\nTotal number of tests: ", (counter_ok + counter_fail)
    print "Number of test passed: ", counter_ok
    print "Number of tests failed: ", counter_fail,"\n"

    print"Total Simulation Time:\n"
    print "--- %s seconds ---" % (time.time() - start_time), "\n"

else: # Write the total simulation times to Output.txt
    with open ("Output"+str(num_of_patient)+".txt", 'a') as f:                
        f.write(
        "Total number of tests: "+str(counter_ok + counter_fail)+'\n'
        "Number of test passed: "+str(counter_ok)+'\n'
        "Number of tests failed: "+str(counter_fail)+'\n'
        "Total Simulation Time: "+"%s seconds" % (time.time() - start_time)+"\n"
        )
        f.flush()
        os.fsync(f)

# clean Modelica generated files
os.system("./clean.sh") 

