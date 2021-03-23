block Monitor_Average

InputReal glucose_from_patient;
InputReal insulin_from_pump;

OutputReal min_g;
OutputReal max_g;
OutputReal average;

OutputReal total_insulin;

OutputBool low_average;
OutputBool high_average;


Real num_values;                      //si incrementa di 0.1, serve a determinare il tempo di fine simulazione
Integer sim_step;
parameter Real T = 0.1;
parameter Integer stop_simulation = 1000;       // Passalo dallo script

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

when sample(1000, T) then 

if(glucose_from_patient < min_g ) then
min_g := glucose_from_patient;
end if;

if(glucose_from_patient > max_g ) then
max_g := glucose_from_patient;
end if;

average := ((pre(average) * num_values) + glucose_from_patient) / (num_values + 1);
num_values := num_values + 1.0;

total_insulin := total_insulin + insulin_from_pump;

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

