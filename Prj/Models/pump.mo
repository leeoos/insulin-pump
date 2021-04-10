block Pump


InputReal glucose;          // amount of glucose of the patient
OutputReal insulin_out;     // amount of insulin to give the patient

Real z, err;

// parameters to define the behavior of the pump
parameter Real T = 0.1;         
parameter Real a = 1040.;       // standard value: 1.0; 		
parameter Real b = 1.95;        // standard value: 0.001; 
parameter Real ref = 100;       // expeted glucose value; 

initial equation
insulin_out = 0;
z = 0;

equation
err = (glucose - ref);          // difference between expected and actual value
algorithm

/* decide the amount of insulin to be injected based on 
the patient's glucose and the previously injected insulin*/
when sample(0, T) then

z := pre(z) + T*err;

insulin_out := max(0, a*err + b*pre(z));

end when;

end Pump;

