/* Note: It is possible to swap the original values with the commented ones 
to simulate a hypoglycemic patient */
record KPar "system parameters"
parameter Real Dose=105;            // fixed      
parameter Real b=0.7328;            // 0.7336;
parameter Real d=0.1014;            // 0.1158;
parameter Real kmax=0.0426 ;        // 0.0661;
parameter Real kmin=0.0076 ;        // 0.0094;
parameter Real kabs=0.0542 ;        // 0.0843;
parameter Real BW=96;               // 97.45;
parameter Real f=0.9;               // fixed
end KPar;


function k_empt
input KPar K;
input Real Q;
output Real y;

protected Real alpha, beta;

algorithm
/* equations from diabetes-simulator-in-silico-2020.pdf (appendix) in Insulin-Pump/Requirment */

alpha := 5/(2*K.Dose*(1-K.b));		// A7

beta := 5/(2*K.Dose*K.d);		    // A8

y := K.kmin + ((K.kmax - K.kmin)/2)*(tanh(alpha*(Q - beta*K.Dose)) - tanh(beta*(Q - K.d*K.Dose)) + 2);	// A6

end k_empt;


model Rate_Appearance_Glucose

InputReal delta;            // glucose assimilation parameter

OutputReal Rameal;          // Rate of Glucose Appearance


KPar K;
Real Qsto(start=0);
Real Qsto1(start=0);
Real Qsto2(start=0);
Real Qgut(start=0);

initial equation		// A5
 
equation

Qsto = Qsto1 + Qsto2;

der(Qsto1) =(-K.kmax)*Qsto1 + K.Dose*delta;

der(Qsto2) = - k_empt(K, Qsto)*Qsto2 + K.kmax*Qsto1;

der(Qgut) = (-K.kabs)*Qgut +k_empt(K, Qsto)*Qsto2;

Rameal = (K.f*K.kabs*Qgut)/K.BW;


end Rate_Appearance_Glucose;

