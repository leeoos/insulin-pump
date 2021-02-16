
model Rate_Appearance_Glucose

InputReal delta;

OutputReal ra_meal;

algorithm

ra_meal := delta + 10;

end Rate_Appearance_Glucose;


