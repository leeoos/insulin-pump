block Pump

InputReal g;

OutputReal insulin_out;


//initial equation
//insulin_out  = 0;

algorithm

insulin_out := g + 10;

end Pump;
