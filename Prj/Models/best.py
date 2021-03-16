import os
import sys
import math
import numpy as np
import time
import os.path
import random


from OMPython import OMCSessionZMQ

print "removing old System (if any) ..."
os.system("rm -f ./System")    # remove previous executable, if any.
print "done!\n"


os.system("touch RandOutput.csv ./System")

a = 1.0 #1.6*650        # original value 1.0
b = 0.001 #0.003*650        # original value 0.001

Global_Average = 0
insulin_out_sum = 0
insulin_out_min = float("inf")          # max value
best_a = 0
best_b = 0
glucose_lev = 0
sim_numb = 0
i1 = 0
make_patient = True



start_time = time.time()

#Patient generation
for i in range(0,10):   # Inizio Ciclo 10
    print "------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
    print "------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
    print "Patient", i
    
    MINIMO = 100000
    MASSIMO = 0

    exit = False
    fail_value = False
    too_low = False
    too_high = False
    sim_time = 1000

    rand_b= round(random.uniform(0.5841, 0.8282),4)         # original value 0.7328
    rand_d= round(random.uniform(0.061, 0.1436),4)          # original value 0.1014
    rand_kmax= round(random.uniform(0.0318,0.0869),4)       # original value 0.0426 
    rand_kmin= round(random.uniform(0.0066, 0.01),4)        # original value 0.0076 
    rand_kabs= round(random.uniform(0.0293, 0.1),4)         # original value 0.0542 
    rand_BW= round(random.uniform(83.0, 104.0),2)           # original value 96

    
    #rand_Vg = round(random.uniform(0.73,1.33),2)           # original value 1
    #rand_Vi = round(random.uniform(0.039,0.062),3)         # original value 0.041

    #rand_meal_len = random.randint(60,120)
    #rand_meal_period = random.randint(300,480)
    #rand_gamma = random.randint(10,30)
    rand_meal_len = 60
    rand_meal_period = 240
    rand_gamma = 100
    
    if (1 <= 0 ) :
        a = round(random.uniform(40.0, 60.0),1)  
        b = round(random.uniform(1.001, 10.001),4)  

    
    while (not(exit)):  # Inizio Ciclo i1
        

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

        omc.sendExpression("loadFile(\"System.mo\")")
        omc.sendExpression("getErrorString()")

        omc.sendExpression("buildModel(System, stopTime="+str(float(sim_time))+")")
        omc.sendExpression("getErrorString()")
        

        print "\nChecking Patient: ", i, "Simulation number: ", i1, "\n"
                
        # Assegnamento Valori di a e b 
        
        if (too_low and not(too_high)) :
            print "Too Low"
            a -= round(random.uniform(1.0, 10.0),1)   
            b += round(random.uniform(0.001, 1.001),4)
            too_low = False

            
        elif (not(too_low) and too_high) :
            print "Too High"
            a += round(random.uniform(1.0, 10.0),1)   
            b += round(random.uniform(0.001, 1.001),4)
            too_high = False

        else :
            a = round(random.uniform(a, a+60.0),1)  
            b = round(random.uniform(b, b+20.001),4)  
            too_low = False
            too_high = False

        
        print
        print "a: ",a
        print "b: ",b
        
        with open ("parameters.txt", 'wt') as f:                
            f.write("gen.Meal_length="+str(rand_meal_len)+"\n"+
            "gen.Meal_period="+str(rand_meal_period)+"\n"+
            "gen.gamma="+str(rand_gamma)+"\n"+
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

        

        for i2 in range(0,sim_time):    # Inizio Ciclo i2
            
            glucose = omc.sendExpression("val(pa.G, "+str(float(i2))+", \"System_res.mat\")")
            
            # checking limit values
            if (glucose < 40 ): 
                fail_value = True
                too_low = True

            elif (glucose > 180):
                fail_value = True
                too_high = True
                
            # checking min max
            if (glucose <= MINIMO): MINIMO = glucose
            if (glucose >= MASSIMO): MASSIMO = glucose

        # Fine Ciclo i2

        print "\ncontrolli"
        print omc.sendExpression("val(pu_co.controller,"+str(float(sim_time))+", \"System_res.mat\")")
        print fail_value

        
        min_g = omc.sendExpression("val(mo_av.min_g,"+str(float(sim_time))+", \"System_res.mat\")")
        max_g = omc.sendExpression("val(mo_av.max_g,"+str(float(sim_time))+", \"System_res.mat\")")
        average = omc.sendExpression("val(mo_av.average,"+str(float(sim_time))+", \"System_res.mat\")")
        low_average = omc.sendExpression("val(mo_av.low_average,"+str(float(sim_time))+", \"System_res.mat\")")
        high_average = omc.sendExpression("val(mo_av.high_average,"+str(float(sim_time))+", \"System_res.mat\")")
                
        
        # Fine Simulazione

        print "\nAverage values: "
        print "min glucose: ", min_g, " expeted: ", MINIMO
        print "max glucose: ", max_g, " expeted: ", MASSIMO
        if (low_average):
            print "The average glucose value is dangerously low: ", average
        if (high_average): 
            print "The average glucose value is dangerously high: ", average
        else:
            print "average glucose: ", average

        print "------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
        
        if (fail_value == False) :
            print "\nFatto"
            print "------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
            print "------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
            with open("RandOutput.csv",'a') as g:
                g.write(str(a)+", "+str(b)+"\n")
                g.flush()
                os.fsync(g)            
            exit = True
            make_patient = False
            i1 = 0
            break
        
        print "Pump failed, try diffrent values ...\n"
        fail_value = False

        MINIMO = 100000
        MASSIMO = 0

        i1 += 1

    # Fine Ciclo i1
 
# Fine Ciclo i0
    
print "--- %s seconds ---" % (time.time() - start_time), "\n"
 
#os.system("libreoffice --calc System_res.csv ./System")
os.system("./clean.sh ./System") 

