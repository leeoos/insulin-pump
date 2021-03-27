import os
import sys
import math
import numpy as np
import time
import os.path
import random

from color import pretty, prettyln


from OMPython import OMCSessionZMQ

# Removing previos executable, if any ...
print '\nremoving old System (if any) ...'
os.system("rm -f ./System")    
print "done!\n"

sim_time = 2000

a = 1040.0          # original value 1.0
b = 1.95            # original value 0.001

# Minimum acceptable blood glucose value
lower_limit = 70

#
Global_Average = 0
insulin_out_min = float("inf")
best_a = 0
best_b = 0
glucose_lev = 0
sim_numb = 0
i = 1

# Start counting time to run n Simulation
start_time = time.time()

# Generate a random patient 

rand_b= round(random.uniform(0.5841, 0.8282),4)         # original value 0.7328
rand_d= round(random.uniform(0.061, 0.1436),4)          # original value 0.1014
rand_kmax= round(random.uniform(0.0318,0.0869),4)       # original value 0.0426 
rand_kmin= round(random.uniform(0.0066, 0.01),4)        # original value 0.0076 
rand_kabs= round(random.uniform(0.0293, 0.1),4)         # original value 0.0542 
rand_BW= round(random.uniform(83.0, 104.0),2)           # original value 96

#rand_meal_len = random.randint(600, 700)
#rand_meal_period = random.randint(300,480)

# Start Multiple Simulations  

exit_ctrl = False       # exit condiction, just in case break does not work
fail_pump = False       # 

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

    omc.sendExpression("loadFile(\"monitor_hipogli.mo\")")
    omc.sendExpression("getErrorString()")

    omc.sendExpression("loadFile(\"System.mo\")")
    omc.sendExpression("getErrorString()")

    omc.sendExpression("buildModel(System, stopTime="+str(float(sim_time))+")")
    omc.sendExpression("getErrorString()")
    
            
    # Adjustment of a and b to find best values
    a += 20
    b -= 0.05
    
    #
    if (a<=0 or b<=0):
        prettyln("Invalid Value Simulation Ended \n", 'r') 
        exit_ctrl = True
        break 
    
    print "\nSimulation Number ", i, "\n"
    print "a: ", a
    print "b: ", b, "\n"
    
    # Write patient parameters in parameters.txt and run simulation with new values
    with open ("parameters.txt", 'wt') as f:                
        f.write(
        #"gen.Meal_length="+str(rand_meal_len)+"\n"+
        #"gen.Meal_period="+str(rand_meal_period)+"\n"+
        "rag.K.b="+str(rand_b)+"\n"+
        "rag.K.d="+str(rand_d)+"\n"+
        "rag.K.kmax="+str(rand_kmax)+"\n"+
        "rag.K.kmin="+str(rand_kmin)+"\n"+
        "rag.K.kabs="+str(rand_kabs)+"\n"+
        "rag.K.BW="+str(rand_BW)+"\n"+
        "pu.a="+str(a)+"\n"+
        "pu.b="+str(b)+"\n"+
        "mo_hi.correction="+str(lower_limit)+"\n"
        )
        f.flush()
        os.fsync(f)
        
    os.system("./System -s=rungekutta -overrideFile=parameters.txt > log") 

    os.system("rm -f parametres.txt")       # to be on the safe Side

    # check for pump falieur
    fail_pump = omc.sendExpression("val(mo_pu.controller,"+str(float(sim_time))+", \"System_res.mat\")")     
    
    #
    if (fail_pump) : 
        println("Pump Fail Simulation Ended \n", 'r')              
        print fail_pump
        break
        
    else: 
        min_g = omc.sendExpression("val(mo_av.min_g,"+str(float(sim_time))+", \"System_res.mat\")")
        max_g = omc.sendExpression("val(mo_av.max_g,"+str(float(sim_time))+", \"System_res.mat\")")
        average = omc.sendExpression("val(mo_av.average,"+str(float(sim_time))+", \"System_res.mat\")")
        total_insulin_out = omc.sendExpression("val(mo_av.total_insulin, "+str(float(sim_time))+", \"System_res.mat\")")
        
        #
        if ((average > max_g or average < min_g) and a > 0 and b > 0): 
            prettyln("Invalid Average Simulation Endend \n", 'r') 
            exit_ctrl = True
            break

        # printing patient's values
        print "\nAverage values: "
        print "min glucose: ", min_g
        print "max glucose: ", max_g
        print "total injected insulin: ", total_insulin_out
        print "average glucose: ", average
        
        # Save best values for insulin
        if (total_insulin_out < insulin_out_min): 
            insulin_out_min = total_insulin_out
            best_a = a
            best_b = b
            sim_numb = i
    
        prettyln('pass', 'g')
        prettyln("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n", 'g')

    #os.system("rm -f System_res.mat")       # to be on the safe side

    i += 1

# End of While Loop
    
print "\nBest value of insuline out: ", 
pretty(str(insulin_out_min), "g") 
print "at simulation: ", 
pretty(str(sim_numb), "g")
print "with: "
print "a = ", best_a
print "b = ", best_b, "\n"

print "--- %s seconds ---" % (time.time() - start_time), "\n"
 
os.system("./clean.sh ") 

