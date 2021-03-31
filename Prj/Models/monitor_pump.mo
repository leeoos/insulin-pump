
block Monitor_Pump
/* Check for pump failure, 
controller triggered by a low level of glucose*/

InputReal glucose_from_patient;     // amount of glucose of the patient

OutputBool controller;              // send a signal to warn of pump failure

parameter Real T = 0.1;

initial equation 
controller = false;

algorithm 

/* Start checking after the adjustment phase */
when sample(1000, T) then 

if(glucose_from_patient >= 150 or glucose_from_patient <= 40) then 

controller := true;

end if;

end when;

end Monitor_Pump;




