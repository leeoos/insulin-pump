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

sim_time = 0
num_of_patient = 100
counter_ok = 0
counter_fail = 0
counter_tot = 0
a = - 1040.0        # original value 1.0
b = - 1.95          # original value 0.001
Global_Average = 0
anomalus_pat = 0
i0 = 0

start_time = time.time()

while (i0 < num_of_patient):    # Inizio Ciclo i0

    # Generating a randomn patient
    print "\nPatient ", i0, "\n"

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
    #rand_delta = random.randint(10,30)
    rand_meal_len = 60
    rand_meal_period = 200 #240
    rand_delta = 100

    fail_test = False

    for i1 in range (0,2):  # Inizio Ciclo i1
        
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
        
        # End of Simulation


        if (i1 <= 0 ): print "\nSimulazione di controllo:\n"
        else : print "\nSimulazione effettiva:\n"
                
        # Assegnamento Valori di a e b 
        a = a + 1040.0        # original value 1.0
        b = b + 1.95          # original value 0.001
        
        with open ("parameters.txt", 'wt') as f:                
            f.write(
            "gen.Meal_length="+str(rand_meal_len)+"\n"+
            "gen.Meal_period="+str(rand_meal_period)+"\n"+
            "gen.par_delta="+str(rand_delta)+"\n"+
            "rag.K.b="+str(rand_b)+"\n"+
            "rag.K.d="+str(rand_d)+"\n"+
            "rag.K.kmax="+str(rand_kmax)+"\n"+
            "rag.K.kmin="+str(rand_kmin)+"\n"+
            "rag.K.kabs="+str(rand_kabs)+"\n"+
            "rag.K.BW="+str(rand_BW)+"\n"+
            "pu.a="+str(a)+"\n"+
            "pu.b="+str(b)+"\n"
            #"pa.Vi="+str(rand_Vi)+"\n"
            )
            f.flush()
            os.fsync(f)
            
        os.system("./System -s=rungekutta -overrideFile=parameters.txt > log")
        
        fail_patient = False
        fail_pump = omc.sendExpression("val(pu_co.controller,"+str(float(sim_time))+", \"System_res.mat\")")
        print(fail_pump)

        if (i1 <= 0) :
            '''
            for i2 in range(100,sim_time):    # Inizio Ciclo i2
                glucose = omc.sendExpression("val(pa.G, "+str(float(i2))+", \"System_res.mat\")")
                if (glucose < 40 ):    
                    fail_patient = True
                    break 
            ''' 
            min_g = omc.sendExpression("val(mo_av.min_g,"+str(float(sim_time))+", \"System_res.mat\")")
            if (min_g < 30):
                fail_patient = True
            # Fine Ciclo i2
            
            #Controlla che il paziente non sia anomalo (solo al primo giro)
            if (fail_patient): 
                anomalus_pat = anomalus_pat + 1
                print '\033[31m'
                print 'Patient Anomalus'
                print "---------------------------------------------------------------------------------------------------------------------------------"                            
                print '\033[0m'            
                break
            else:
                print '\033[32m'
                print 'Patient ok'
                print '\033[0m'            
                i0 += 1
        
        if (i1 >= 1):  
            
            min_g = omc.sendExpression("val(mo_av.min_g,"+str(float(sim_time))+", \"System_res.mat\")")
            max_g = omc.sendExpression("val(mo_av.max_g,"+str(float(sim_time))+", \"System_res.mat\")")
            average = omc.sendExpression("val(mo_av.average,"+str(float(sim_time))+", \"System_res.mat\")")
            low_average = omc.sendExpression("val(mo_av.low_average,"+str(float(sim_time))+", \"System_res.mat\")")
            high_average = omc.sendExpression("val(mo_av.high_average,"+str(float(sim_time))+", \"System_res.mat\")")
            
            
            print "\nAverage values: "
            print "min glucose: ", min_g
            print "max glucose: ", max_g
            #print "min insulin: ", min_i
            #print "max insulin: ", max_i
            if (low_average):
                print "The average glucose value is too low: ", average
                fail_test = True
            elif (high_average): 
                print "The average glucose value is too high: ", average
                fail_test = True

            else: print "average glucose: ", average
                    
            Global_Average = Global_Average + average

            #fail_pump = omc.sendExpression("val(pu_co.controller,"+str(float(sim_time))+", \"System_res.mat\")")

            if (fail_pump or fail_test) :  
                counter_fail = counter_fail + 1
                print '\033[31m'
                print 'fail'
                print "---------------------------------------------------------------------------------------------------------------------------------"                        
                print '\033[0m'            
            else : 
                counter_ok = counter_ok + 1
                print '\033[32m'
                print 'pass'
                print "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
                print '\033[0m'            


    
    # Fine Ciclo i1

    a = -(1.6*650)        # original value 1.0
    b = -(0.003*650)        # original value 0.001
    sim_time = 0

# Fine Ciclo i0
    
counter_tot = counter_ok + counter_fail
print "\nGlobal Average of glucose: ", Global_Average/counter_tot
print "\nTotal number of tests: ", counter_tot
print "Number of test passed: ", counter_ok
print "Number of tests failed: ", counter_fail
print "Number of anomalus patients: ", anomalus_pat, "\n"

print "--- %s seconds ---" % (time.time() - start_time), "\n"
 
os.system("./clean.sh ./System") 

