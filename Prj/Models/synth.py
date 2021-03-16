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



initial_a = 1.6*650        # original value 1.0
initial_b = 0.003*650        # original value 0.001

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
while (make_patient):   # Inizio Ciclo 10
    
    exit = False
    fail_patient = False
    fail_pump = False
    sim_time = 0

    rand_b= round(random.uniform(0.5841, 0.8282),4)         # original value 0.7328
    rand_d= round(random.uniform(0.061, 0.1436),4)          # original value 0.1014
    rand_kmax= round(random.uniform(0.0318,0.0869),4)       # original value 0.0426 
    rand_kmin= round(random.uniform(0.0066, 0.01),4)        # original value 0.0076 
    rand_kabs= round(random.uniform(0.0293, 0.1),4)         # original value 0.0542 
    rand_BW= round(random.uniform(83.0, 104.0),2)           # original value 96

    
    #rand_Vg = round(random.uniform(0.73,1.33),2)           # original value 1
    #rand_Vi = round(random.uniform(0.039,0.062),3)         #original value 0.041

    #rand_meal_len = random.randint(60,120)
    #rand_meal_period = random.randint(300,480)
    #rand_gamma = random.randint(10,30)
    rand_meal_len = 60
    rand_meal_period = 240
    rand_gamma = 100
    
    print "\nPatient Generated \n"
    generation_time = time.time()

    # Starting Multiple Simulations    

    while (not(fail_pump) and not(exit)):  # Inizio Ciclo i1
        
        sim_time = sim_time + 500           #incrementing sim_time for first simulation

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
        
        #omc.sendExpression('simulate(System, outputFormat="csv", startTime=0, stopTime=100, numberOfIntervals=5)')
        #omc.sendExpression("getErrorString()")

        if (i1 <= 0 ): print "\nChecking Patient:\n"
        else : print "\nReal Simulation:\n"
                
        # Assegnamento Valori di a e b 
        
        if(i1 <= 0):
            print "pump not in function\n"
            a = 0
            b = 0
        else:
            a = initial_a 
            b = initial_b
            initial_a += 20
            initial_b -= 0.1
            
            print "Simulation Number ", i1, "\n"
            print "a: ", a
            print "b: ", b, "\n"
       
            if (a<=0 or b<=0):
                print "Invalid Value Simulation Endend"
                make_patient = False
                break 
        
        
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
            
            #t = omc.sendExpression("val(time, "+str(float(i2))+", \"System_res.mat\")")
            glucose = omc.sendExpression("val(pa.G, "+str(float(i2))+", \"System_res.mat\")")
            insulin_out = omc.sendExpression("val(pu.insulin_out, "+str(float(i2))+", \"System_res.mat\")")
            #insulin_p = omc.sendExpression("val(pa.I, "+str(float(i2))+", \"System_res.mat\")")
            
            #print "i", omc.sendExpression("val(pu.insulin_out, "+str(float(i2))+", \"System_res.mat\")")
            #print "b", omc.sendExpression("val(pu.b, "+str(float(i2))+", \"System_res.mat\")")
            # if(i1 >= 1) : print(insulin_p)

            if (i2 > 100 ):             #Salta i primi 100
                if (glucose < 40 ):    # Solo al primo giro
                    fail_patient = True
                    break 
                    #print "\nglucosio: ", glucose
                if (i1 >= 1) :
                    insulin_out_sum += insulin_out
                
                
        # Fine Ciclo i2

        #with open("RandOutput.csv",'a') as g:
            #g.write(str(glucose)+", "+str(insulin_out)+"\n")
            #g.flush()
            #os.fsync(g)
            
            min_g = omc.sendExpression("val(mo_av.min_g,"+str(float(sim_time))+", \"System_res.mat\")")
            max_g = omc.sendExpression("val(mo_av.max_g,"+str(float(sim_time))+", \"System_res.mat\")")
            average = omc.sendExpression("val(mo_av.average,"+str(float(sim_time))+", \"System_res.mat\")")
        
            if ((average > max_g or average < min_g) and a > 0 and b > 0): 
                print "Invalid Average Simulation Endend"
                make_patient = False
                exit = True
                break
        
            
        #Controlla che il paziente non sia anomalo (solo al primo giro)
        if (i1 <= 0):             
            if (fail_patient): 
                print "patient fail"
                print "------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
                break
            else:
                patient_fail = False
                make_patient = False
                print "patient ok"
                print "--- %s seconds ---" % (time.time() - generation_time), "\n"
                #i0 += 1
        
        if (i1 >= 1):  
        
            fail_pump = omc.sendExpression("val(pu_co.controller,"+str(float(sim_time))+", \"System_res.mat\")")     
            
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
                
                #media = sum_g / (sim_time-100)
                print "\nAverage values: "
                print "min glucose: ", min_g
                print "max glucose: ", max_g
                print "total injected insulin: ", insulin_out_sum 
                if (low_average):
                    print "The average glucose value is dangerously low: ", average
                if (high_average): 
                    print "The average glucose value is dangerously high: ", average

                print "average glucose: ", average
                
                # Best Insuline
                
                if (insulin_out_sum < insulin_out_min): 
                    insulin_out_min = insulin_out_sum
                    best_a = a
                    best_b = b
                    glucose_lev = average
                    sim_numb = i1
            
                Global_Average = Global_Average + average

                print("pass")

            print "------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
        # Fine Simulazione
        i1 += 1
        sim_time = 500
        insulin_out_sum = 0
    # Fine Ciclo i1
 
# Fine Ciclo i0
    
print "\nGlobal Average of glucose: ", Global_Average, "\n"
print  "Best value of insuline out: ", insulin_out_min, "at simulation: ", sim_numb, "with values: "
print "a = ", best_a
print "b = ", best_b
print "glucose = ", glucose_lev, "\n"

print "--- %s seconds ---" % (time.time() - start_time), "\n"
 
#os.system("libreoffice --calc System_res.csv ./System")
os.system("./clean.sh ./System") 

