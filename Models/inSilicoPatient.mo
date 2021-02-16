block Patient

InputReal insulin_in;
InputReal ra_meal;
 
OutputReal glucose;     

//initial equation
//glucose = 0;
//insuline = 0;

algorithm

glucose := ra_meal + insulin_in;

end Patient;
