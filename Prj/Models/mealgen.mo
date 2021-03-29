block MealGenerator

InputBool meal_control;
OutputReal delta;


parameter Integer Meal_length = 600;    // lenght of meal (minutes) 
parameter Integer Meal_period = 2400;   // periodic meals: every 4 hours.
parameter Real T = 0.1;                 // time interval


Integer i, j;
Boolean meal_on, meal_off;

initial equation
i = 0;
j = Meal_length;   
meal_on = false;
meal_off = false;

algorithm

// Periodic meal of duration Meal_length every Meal_period minutes

when sample(0, T) then

//

if (not(meal_control)) then 
/* This determines how a non-hypoglycemic patient would eat */ 

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

//

else // meal_control = True
/* This means that the patient is hypoglycemic and needs to eat a lot more */

if (mod(i, div(Meal_period-600,2)) == 0) then 
meal_on := not(pre(meal_on));
end if;

if (mod(j+499, div(Meal_period-600,2)) == 0) then
meal_off := not(pre(meal_off));
end if;

if (meal_on and not(pre(meal_on))) then 
delta := 105;
elseif (meal_off and not(pre(meal_off))) then
delta := 0;
end if;

//

end if;

// increment meal step counters

i := i + 1;
j := j + 1;

end when;

end MealGenerator;
