
block Monitor_Pump

InputReal glucose_from_patient;
OutputBool controller;

parameter Real T = 0.1;

initial equation 
controller = false;

algorithm 

when sample(100, T) then 

if(glucose_from_patient >= 150 or glucose_from_patient <= 40) then // >=200 or <=40

controller := true;

end if;

end when;

end Monitor_Pump;



