block MealGenerator

OutputReal delta;

parameter Real Meal_length = 60;  // lenght of meal (minutes) 
parameter Real Meal_period = 480;  // periodic meals: every 8 hours.
parameter Real gamma = 20;

Boolean meal_on, meal_off;

initial equation
meal_on = false;
meal_off = false;

equation

// periodic meal of duration Meal_length every Meal_period minutes

when sample(0, Meal_period/2) then
meal_on = not(pre(meal_on));
end when;

when sample(Meal_length, Meal_period/2) then
meal_off = not(pre(meal_off));
end when;

when edge(meal_on) then
delta = gamma;
elsewhen edge(meal_off) then
delta = 0;
end when;



end MealGenerator;