block Monitor_Average

InputReal glucose_from_patient;

OutputReal min_g;
OutputReal max_g;
OutputReal average;
OutputBool low_average;
OutputBool high_average;

Integer i;
Real step;                      //si incrementa di 0.1, serve a determinare il tempo di fine simulazione
parameter Real T = 0.1;
parameter Real stop_simulation = 1000;

initial equation
min_g = 10000;
max_g = 0;
average = 0;
low_average = false;
high_average = false;
i = 0;
step = 0;

algorithm 

when sample(0, T) then 

if(glucose_from_patient < min_g ) then

min_g := glucose_from_patient;

end if;

if(glucose_from_patient > min_g ) then

max_g := glucose_from_patient;

end if;

average := ((pre(average)*i) + glucose_from_patient) / (i+1);
i := i +1;

step := step + T;

if (step == stop_simulation) then

if (average < 80 ) then

low_average := true;

end if;

if ( average > 120 ) then 

high_average := true;

end if;

end if;

end when;

end Monitor_Average;
