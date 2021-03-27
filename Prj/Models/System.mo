class System


MealGenerator gen;              // a generator that generates the meal
Patient pa;                     // a patient that has an insulin pump
Pump pu;                        // the insulin pump that injects the patient with insulin  
Rate_Appearance_Glucose rag;    // a model that simulate the rate of meal driven glucose appearance 

Monitor_Pump mo_pu;             // a monitor to check if the pump is working correctly during the simulation
Monitor_Average mo_av;          // a monitor to check if the patient's average values at the end of the simulations are good
Monitor_Hipogli mo_hi;          // a monitor to control if the patient's glucose level is too low
 
equation

// Environment
connect(gen.delta, rag.delta);
connect(rag.Rameal, pa.Rameal);

// Patient-Pump relation
connect(pa.G, pu.glucose);
connect(pa.insulin_from_pump, pu.insulin_out);

// Monitors...

// Monitor_Pump
connect(pa.G, mo_pu.glucose_from_patient);

// Monitor_Average
connect(pa.G, mo_av.glucose_from_patient);
connect(pu.insulin_out, mo_av.insulin_from_pump);

// Monitor_Hipogli
connect(pa.G, mo_hi.glucose_from_patient);
connect(mo_hi.min_g_control, gen.meal_control); 


end System;
