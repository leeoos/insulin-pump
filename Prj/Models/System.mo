class System


MealGenerator gen;              // generates the meal
Patient pa;                     // patient that has an insulin pump
Pump pu;                        // an insulin pump that injects the patient with insulin  
Rate_Appearance_Glucose rag;

Monitor_Pump mo_pu; 
Monitor_Average mo_av;
Monitor_Hipogli mo_hi;
 
equation

//Environment
connect(gen.delta, rag.delta);
connect(rag.Rameal, pa.Rameal);

//Patient-Pump relation
connect(pa.G, pu.glucose);
connect(pa.insulin_from_pump, pu.insulin_out);

//Monitors
connect(pa.G, mo_pu.glucose_from_patient);

connect(pa.G, mo_av.glucose_from_patient);
connect(pu.insulin_out, mo_av.insulin_from_pump);

connect(pa.G, mo_hi.glucose_from_patient);
connect(mo_hi.min_g_control, gen.meal_control); 


end System;
