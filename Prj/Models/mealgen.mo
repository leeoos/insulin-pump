block MealGenerator

InputBool meal_control;
OutputReal delta;


parameter Integer Meal_length = 600;  // lenght of meal (minutes) 
parameter Integer Meal_period = 2400;  // periodic meals: every 4 hours.
//parameter Real par_delta = 100;    //original value 20
parameter Real T = 0.1;

//Real Meal_length;
//Real Meal_period;
//Real par_delta;
Real tmp;
Integer i, j;
Boolean meal_on, meal_off, test;

initial equation
//Meal_length = 60;   
//Meal_period = 240;  
//par_delta = 100;
test = false;
tmp = 0;
i = 0;
j = Meal_length;   
meal_on = false;
meal_off = false;

//equation

algorithm

// periodic meal of duration Meal_length every Meal_period minutes

when sample(0, T) then

if (meal_control) then // Mangia Molto di piu

test := true;

if (mod(i, div(Meal_period-400,2)) == 0) then 
meal_on := not(pre(meal_on));
end if;

if (mod(j+20, div(Meal_period-400,2)) == 0) then
meal_off := not(pre(meal_off));
end if;

if (meal_on and not(pre(meal_on))) then 
delta := 105;
tmp := delta;
elseif (meal_off and not(pre(meal_off))) then
delta := 0;
end if;


else // Mangia in maniera normale

if (mod(i, div(Meal_period,2)) == 0) then 
meal_on := not(pre(meal_on));
end if;

if (mod(j, div(Meal_period,2)) == 0) then
meal_off := not(pre(meal_off));
end if;

if (meal_on and not(pre(meal_on))) then 
delta := 100;
elseif (meal_off and not(pre(meal_off))) then
delta := 0;
end if;

end if;

i := i + 1;
j := j + 1;

end when;

/*

when sample(0, Meal_period/2) then
meal_on = not(pre(meal_on));
end when;

when sample(Meal_length, Meal_period/2) then
meal_off = not(pre(meal_off));
end when;

when edge(meal_on) then

//if (meal_control) then
//delta = par_delta+60;
//else
delta = 100;
//end if;

elsewhen edge(meal_off) then
delta = 0;

end when;

*/
end MealGenerator;
