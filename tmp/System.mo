class System


Meal generator; // generates the meal
Patient patient;        // patient that has an insulin pump
Pump pump;           // an insulin pump that injects the patient with insulin  
Rate_Appearance_Glucose rag;

equation

//Environment
connect(generator.delta, rag.delta);
connect(rag.ra_meal, patient.ra_meal);

//Patient-Pump relation
connect(patient.glucose, pump.g);
connect(pump.insulin_out, patient.insulin_in);


end System;
