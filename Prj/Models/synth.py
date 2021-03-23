import os
import sys
import math
import numpy as np
import time
import os.path
import random


from OMPython import OMCSessionZMQ

print "\nremoving old System (if any) ..."
os.system("rm -f ./System")    # remove previous executable, if any.
print "done!\n"

sim_time = 2000

a = 1040.0 #280.0        # original value 1.0
b = 1.95 #1.0        # original value 0.001

Global_Average = 0
insulin_out_min = float("inf")          # max value
best_a = 0
best_b = 0
glucose_lev = 0
sim_numb = 0
i = 1

start_time = time.time()

#Patient generation
    
exit_ctrl = False
fail_pump = False

rand_b= round(random.uniform(0.5841, 0.8282),4)         # original value 0.7328
rand_d= round(random.uniform(0.061, 0.1436),4)          # original value 0.1014
rand_kmax= round(random.uniform(0.0318,0.0869),4)       # original value 0.0426 
rand_kmin= round(random.uniform(0.0066, 0.01),4)        # original value 0.0076 
rand_kabs= round(random.uniform(0.0293, 0.1),4)         # original value 0.0542 
rand_BW= round(random.uniform(83.0, 104.0),2)           # original value 96

#rand_meal_len = random.randint(60,120)
#rand_meal_period = random.randint(300,480)


# Starting Multiple Simulations    

while (not(fail_pump) and not(exit_ctrl)):  # Inizio Ciclo i1
    

    # Avvio Simulazione Modello 
    
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
    

    print "\nReal Simulation:\n"
            
    # Assegnamento Valori di a e b 
    a += 20
    b -= 0.05
        
    print "Simulation Number ", i, "\n"
    print "a: ", a
    print "b: ", b, "\n"
    
    if (a<=0 or b<=0):
        print "Invalid Value Simulation Endend"
        exit_ctrl = True
        break 
    
    
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
        "pu.b="+str(b)+"\n")
        f.flush()
        os.fsync(f)
        
    os.system("./System -s=rungekutta -overrideFile=parameters.txt > log")

    fail_pump = omc.sendExpression("val(mo_pu.controller,"+str(float(sim_time))+", \"System_res.mat\")")     
    
    if (fail_pump) :                   
        print("Pump Fail Simulation End:")
        print fail_pump
        break
        
    else: 
    
        min_g = omc.sendExpression("val(mo_av.min_g,"+str(float(sim_time))+", \"System_res.mat\")")
        max_g = omc.sendExpression("val(mo_av.max_g,"+str(float(sim_time))+", \"System_res.mat\")")
        average = omc.sendExpression("val(mo_av.average,"+str(float(sim_time))+", \"System_res.mat\")")
        low_average = omc.sendExpression("val(mo_av.low_average,"+str(float(sim_time))+", \"System_res.mat\")")
        high_average = omc.sendExpression("val(mo_av.high_average,"+str(float(sim_time))+", \"System_res.mat\")")
        total_insulin_out = omc.sendExpression("val(mo_av.total_insulin, "+str(float(sim_time))+", \"System_res.mat\")")

        if ((average > max_g or average < min_g) and a > 0 and b > 0): 
            print "Invalid Average Simulation Endend"
            exit_ctrl = True
            break

        
        print "\nAverage values: "
        print "min glucose: ", min_g
        print "max glucose: ", max_g
        print "total injected insulin: ", total_insulin_out
        if (low_average):
            print "The average glucose value is dangerously low: ", average
        elif (high_average): 
            print "The average glucose value is dangerously high: ", average

        else: print "average glucose: ", average
        
        # Best Values
        
        if (total_insulin_out < insulin_out_min): 
            insulin_out_min = total_insulin_out
            best_a = a
            best_b = b
            glucose_lev = average
            sim_numb = i
    

        print("pass")

        print "------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
    
    # Fine Simulazione
    
    i += 1

# Fine Ciclo i1
    
print "\nBest value of insuline out: ", insulin_out_min, "at simulation: ", sim_numb, "with values: "
print "a = ", best_a
print "b = ", best_b
print "glucose = ", glucose_lev, "\n"

print "--- %s seconds ---" % (time.time() - start_time), "\n"
 
#os.system("libreoffice --calc System_res.csv ./System")
os.system("./clean.sh ./System") 
