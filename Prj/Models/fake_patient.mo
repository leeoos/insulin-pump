block Patient

InputReal Rameal;                 // food intake
InputReal insulin_from_pump;      //insulin from the pump

OutputReal G;                    // blood glucose measured by the pump

Real Gp;
Real Ip;
Real I;

parameter Real Gb = 127;
parameter Real Ib = 54;
parameter Real Vg = 1.0;
parameter Real Vi = 0.062; 

initial equation
G = Gb;
I = Ib;        
Gp = Gb/Vg;
Ip = Ib * Vi;


equation

// Revision of equation A2 to interface with insulin pump
  I  = (Ip + insulin_from_pump)/Vi;
   
  G  = Gp/Vg;


// FAKE PATIENT EQUATIONS!!! Just TO SHOW INTERFACING patient-pump  !!

  der(Ip) = -(0.1)*Ip + insulin_from_pump + 0.3*Gp;	
  der(Gp) = 20*Rameal - 0.1*Gp - 0.00001*I*Gp;      


end Patient;      
