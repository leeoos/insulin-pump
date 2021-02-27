block Pump


InputReal glucose;        //amount of glucose of the patient
OutputReal insulin_out;   //amount of insulin to give the patient

Real z, err;
Boolean fail;

parameter Real T = 0.1;   
parameter Real a = 1.6*300;   //1.6*70;           //valore standard: 1.0; se a aumenta i aumenta		
parameter Real b = 0.003*300; //0.003*70;       //valore standard: 0.001; se b diminuisce i diminuisce
parameter Real ref = 100;               //glucosio desiderato; 

initial equation
insulin_out = 0;
z = 0;
fail = false;

equation
err = (glucose - ref);      //differenza tra glucosio ideale e glucosio attuale

algorithm

when sample(15, T) then 

if(glucose >= 250 or glucose <= 75) then

fail := true;

end if;

end when;

when sample(0, T) then

z := pre(z) + T*err;


insulin_out :=  max(0, a*err + b*pre(z));      


end when;

end Pump;

