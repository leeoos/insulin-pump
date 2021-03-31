block Monitor_Hypogly

InputReal glucose_from_patient;     // amount of glucose of the patient

OutputBool min_g_control;           // indicates that the patient is hypoglycemic

parameter Real correction = 70;     // the lowest acceptable glucose level before applying the correction

Real tmp_min;                      
Integer sim_step;
parameter Real T = 0.1; 

initial equation
min_g_control = false;
tmp_min = 10000;
sim_step = 100;

algorithm

/* Star checking for hypoglycemic after the pump installation phase */
when sample(100, T) then

if(sim_step == 4000) then       // end of the adjustment phase

if(tmp_min < correction ) then
min_g_control := true;
end if;

end if;


if(glucose_from_patient < tmp_min) then     // temporary minimum level of glucose
tmp_min := glucose_from_patient;
end if;

sim_step := sim_step + 1;                   // count the steps of the simulation

end when;

end Monitor_Hypogly;