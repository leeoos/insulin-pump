block Monitor_Average

InputReal glucose_from_patient;

OutputReal min_g;
OutputReal max_g;
OutputReal average;
OutputBool min_g_control;
OutputBool low_average;
OutputBool high_average;

Real num_values, tmp_min;                      //si incrementa di 0.1, serve a determinare il tempo di fine simulazione
Integer sim_step, sim_step2;
parameter Real T = 0.1;
parameter Integer stop_simulation = 1000;       // Passalo dallo script

initial equation
min_g_control = false;
tmp_min = 10000;
min_g = 10000;
max_g = 0;
average = 0;
low_average = false;
high_average = false;
sim_step = 0;
sim_step2 = 0; //100;
num_values = 0;

algorithm

when sample(0, T) then

if(sim_step2 == 4000) then

if(tmp_min < 40 ) then
min_g_control := true;
end if;

end if;

if(glucose_from_patient < tmp_min) then
tmp_min := glucose_from_patient;
end if;

sim_step2 := sim_step2 + 1;

end when;


when sample(400, T) then 

if(glucose_from_patient < min_g ) then
min_g := glucose_from_patient;
end if;

if(glucose_from_patient > max_g ) then
max_g := glucose_from_patient;
end if;

average := ((pre(average) * num_values) + glucose_from_patient) / (num_values + 1);
num_values := num_values + 1.0;

sim_step := sim_step + 1;

if (sim_step == (stop_simulation*10)) then

if (average < 80 ) then
low_average := true;
end if;

if (average > 120) then 
high_average := true;
end if;

end if;

end when;

end Monitor_Average;

