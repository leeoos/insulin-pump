block Meal

OutputReal delta;

// Note: this parameters could change before the simulation start
// the following values are the defaute values

parameter Real Meal_length = 60;  // lenght of meal (minutes)
parameter Real meal_period = 480;  // periodic meals: every 8 hours.

algorithm

delta := 20;

end Meal;

