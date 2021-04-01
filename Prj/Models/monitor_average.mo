block Monitor_Average
/* Check if the patient's average values 
at the end of the simulations are good*/

InputReal glucose_from_patient;     // amount of glucose of the patient
InputReal insulin_from_pump;        // amount of insuline of the pump

OutputReal min_g;                   // minimum level reached by glucose during the simulation
OutputReal max_g;                   // maximum level reached by glucose during the simulation
OutputReal average;                 // average level of glucose during the simulation

OutputReal total_insulin;           // total insulin injected during the simulation
OutputBool low_average;             // indicates a low average of glucose
OutputBool high_average;            // indicates a high average of glucose


Real num_values;                     
Integer sim_step;
parameter Real T = 0.1;
parameter Integer stop_simulation = 1000;       

initial equation
min_g = 10000;
max_g = 0;
average = 0;
total_insulin = 0;
low_average = false;
high_average = false;
sim_step = 0;
num_values = 0;

algorithm

/* Start checking after the adjustment phase */
when sample(1000, T) then 

if(glucose_from_patient < min_g ) then  // temporary minimum level of glucose
min_g := glucose_from_patient;
end if;

if(glucose_from_patient > max_g ) then  // temporary maximum level of glucose
max_g := glucose_from_patient;
end if;

// incremental average
average := ((pre(average) * num_values) + glucose_from_patient) / (num_values + 1);
num_values := num_values + 1.0;

total_insulin := total_insulin + insulin_from_pump;

sim_step := sim_step + 1;

if (sim_step == (stop_simulation*10)) then

// check for low/high average
if (average < 80 ) then
low_average := true;
end if;

if (average > 120) then 
high_average := true;
end if;

end if;

end when;

end Monitor_Average;

