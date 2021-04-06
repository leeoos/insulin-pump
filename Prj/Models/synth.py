import math
import os
import os.path
import random
import sys
import time
import numpy as np


# Color is a script that implements a function used to print colored text
# Note: If this causes problems, you can remove it
# but to do this you also need to edit all calls to
# pretty or prettyln in plain print
from color import pretty, prettyln

from OMPython import OMCSessionZMQ

# Removing previos executable, if any...
print '\nremoving old System (if any)...'
os.system("rm -f ./System")   
os.system("rm -f parameters.txt") 
print "done!\n"

# Simulation time and number of patient to test...
sim_time = 2000
num_of_patient = 100

# Remove previous output file, if any...
os.system("rm -f Output/Output_Synth/Output"+str(num_of_patient)+".txt")

# Minimum acceptable blood glucose value
lower_limit = 70

# Generate an Output.txt file
os.system("echo Output >> Output/Output_Synth/Output"+str(num_of_patient)+".txt")

# To prevent overwriting in parameters.txt
pre_insulin = 0        # store the insuline value in the previous simulation...
enable_sleep = False    # send a signal to trigger the delay...
delay = 0.8             # only if pre_insuline is equal to insuline...
                        # which means the values for a or b have been duplicated

# Start counting time to run n Simulation
start_time = time.time()

for i in range(0, num_of_patient):   # Start multiple simulation for n patients

    # Parameters to control the amount of insulin injected by the pump experimentally found 
    a = 1040.0          # original value 1.0
    b = 1.95            # original value 0.001

    # Initializes best values for a, b, insuline and glucose
    insulin_out_min = float("inf")
    best_a = 0
    best_b = 0
    glucose_lev = 0

    # loop variables
    sim_numb = 0
    j = 1

    # Generate  random patient
    print "\nPatient ", i+1
    print "simulating...", '\n'

    rand_b= round(random.uniform(0.5841, 0.8282),4)         # original value 0.7328
    rand_d= round(random.uniform(0.061, 0.1436),4)          # original value 0.1014
    rand_kmax= round(random.uniform(0.0318,0.0869),4)       # original value 0.0426 
    rand_kmin= round(random.uniform(0.0066, 0.01),4)        # original value 0.0076 
    rand_kabs= round(random.uniform(0.0293, 0.1),4)         # original value 0.0542 
    rand_BW= round(random.uniform(83.0, 104.0),2)           # original value 96

    # Randomize meal time and period
    #rand_meal_len = random.randint(590,650)
    #rand_meal_period = random.randint(2300,2450)

    # Start Multiple Simulations  
    exit_ctrl = False       # exit condiction, just in case break does not work
    fail_pump = False       # pump failing condiction

    # Start counting time to run n Simulation
    loop_time = time.time()

    while (not(fail_pump) and not(exit_ctrl)):  
        
        # Build Model 
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
        
                
        # Adjustment of 'a' and 'b' to find best values
        a += 20
        b -= 0.12
        
        # Check if a or b are out of baundaries 
        if (a<=0 or b<=0):
            prettyln("Invalid Value Simulation Ended \n", 'r') 
            exit_ctrl = True
            break 
        
        # Write patient parameters in parameters.txt and run simulation with new values
        with open ("parameters.txt", 'wt') as f:                
            f.write(
            #"gen.Meal_length="+str(rand_meal_len)+'\n'+
            #"gen.Meal_period="+str(rand_meal_period)+'\n'+
            "rag.K.b="+str(rand_b)+'\n'+
            "rag.K.d="+str(rand_d)+'\n'+
            "rag.K.kmax="+str(rand_kmax)+'\n'+
            "rag.K.kmin="+str(rand_kmin)+'\n'+
            "rag.K.kabs="+str(rand_kabs)+'\n'+
            "rag.K.BW="+str(rand_BW)+'\n'+
            "pu.a="+str(a)+'\n'+
            "pu.b="+str(b)+'\n'+
            "mo_hy.correction="+str(lower_limit)+'\n'
            )
            f.flush()
            os.fsync(f)
            
        os.system("./System -s=rungekutta -overrideFile=parameters.txt > log")

        # Apply the delay only in case there are some duplicate values of 'a' or 'b'
        if (delay >= 1.0): 
            prettyln("Delay: "+str(delay)+"s\n", 'r')
            time.sleep(delay)

        # Check for pump failure
        fail_pump = omc.sendExpression("val(mo_pu.controller,"+str(float(sim_time))+", \"System_res.mat\")")     
        
        if (fail_pump) : 
            prettyln("Pump Fail Simulation Ended \n", 'r')              
            print fail_pump
            break
        
        else: # Pump has not fail
            min_g = omc.sendExpression("val(mo_av.min_g,"+str(float(sim_time))+", \"System_res.mat\")")
            max_g = omc.sendExpression("val(mo_av.max_g,"+str(float(sim_time))+", \"System_res.mat\")")
            average = omc.sendExpression("val(mo_av.average,"+str(float(sim_time))+", \"System_res.mat\")")
            total_insulin_out = omc.sendExpression("val(mo_av.total_insulin, "+str(float(sim_time))+", \"System_res.mat\")")
        
            # Check for duplicate values of 'a' or 'b'
            if (pre_insulin == total_insulin_out):    
                prettyln("The delay has been activated because the simulation time exceeds the time for writing parameters to the parameters.txt file \n", 'r')
                delay += 0.2
            else: pre_insulin = total_insulin_out
            
            # Check for an invalid glucose average value due overwriting
            if ((average > max_g or average < min_g) and a > 0 and b > 0): 
                prettyln("Invalid Average Simulation Endend \n", 'r') 
                exit_ctrl = True
                break
            
            # Save best values for insulin at simulation j
            if (total_insulin_out < insulin_out_min): 
                insulin_out_min = total_insulin_out
                best_a = a
                best_b = b
                sim_numb = j

        #os.system("rm -f System_res.mat")       # to be on the safe side
        os.system("rm -f parametres.txt")       # to be on the safe Side

        j += 1

    # End of While Loop
    
    # Write the  experimental results for the i-th patient to Output.txt
    with open ("Output/Output_Synth/Output"+str(num_of_patient)+".txt", 'a') as f:                
        f.write(
        "Patient "+str(i+1)+" dataset:"+'\n'+
        "rag.K.b="+str(rand_b)+'\n'+
        "rag.K.d="+str(rand_d)+'\n'+
        "rag.K.kmax="+str(rand_kmax)+'\n'+
        "rag.K.kmin="+str(rand_kmin)+'\n'+
        "rag.K.kabs="+str(rand_kabs)+'\n'+
        "rag.K.BW="+str(rand_BW)+'\n'+
        "Best value of insuline out: "+str(insulin_out_min)+" at simulation: "+str(sim_numb)+" with: "+'\n'
        "a = "+str(best_a)+'\n'+
        "b = "+str(best_b)+'\n'+
        "Simulation Time: "+"%s seconds" % (time.time() - loop_time)+'\n\n'
        )
        f.flush()
        os.fsync(f)

# End of n-th Simulation
os.system("rm -f parameters.txt")

# Write total Simulation time to Output.txt
with open ("Output/Output_Synth/Output"+str(num_of_patient)+".txt", 'a') as f:                
    f.write(
    "Total Simulation Time: "+"%s seconds" % (time.time() - start_time)+'\n'
    )
    f.flush()
    os.fsync(f)

# Clean Modelica autogenerated files
os.system("./clean.sh ") 

