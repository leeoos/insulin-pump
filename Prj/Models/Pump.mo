block Pump


InputReal glucose;        //amount of glucose of the patient
OutputReal insulin_out;   //amount of insulin to give the patient

Real z, err;

parameter Real T = 0.1;   
parameter Real a = 280; //1040.0;           //valore standard: 1.0; 		
parameter Real b = 1.0; //1.95;            //valore standard: 0.001; 
parameter Real ref = 100;            //glucosio desiderato; 

initial equation
insulin_out = 0;
z = 0;

equation
err = (glucose - ref);      //differenza tra glucosio ideale e glucosio attuale

algorithm

when sample(0, T) then

z := pre(z) + T*err;

insulin_out := max(0, a*err + b*pre(z));


end when;

end Pump;

