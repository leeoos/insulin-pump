block Monitor_Hipogli

InputReal glucose_from_patient;

OutputBool min_g_control;


Real tmp_min;                      
Integer sim_step;
parameter Real T = 0.1; 

initial equation
min_g_control = false;
tmp_min = 10000;
sim_step = 100;

algorithm

when sample(100, T) then

if(sim_step == 4000) then

if(tmp_min < 70 ) then
min_g_control := true;
end if;

end if;

if(glucose_from_patient < tmp_min) then
tmp_min := glucose_from_patient;
end if;

sim_step := sim_step + 1;

end when;

end Monitor_Hipogli;