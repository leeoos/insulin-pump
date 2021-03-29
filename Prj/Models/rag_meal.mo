
record KPar "system parameters"
parameter Real Dose=105;       
parameter Real b=0.7328;
parameter Real d=0.1014;
parameter Real kmax=0.0426 ;
parameter Real kmin=0.0076 ;
parameter Real kabs=0.0542 ;
parameter Real BW=96;
parameter Real f=0.9;       
end KPar;


function k_empt
input KPar K;
input Real Q;
output Real y;

protected Real alpha, beta;

algorithm

alpha := 5/(2*K.Dose*(1-K.b));		//A7

beta := 5/(2*K.Dose*K.d);		    //A8

y := K.kmin + ((K.kmax - K.kmin)/2)*(tanh(alpha*(Q - beta*K.Dose)) - tanh(beta*(Q - K.d*K.Dose)) + 2);	//A6

end k_empt;



model Rate_Appearance_Glucose

InputReal delta;
OutputReal Rameal;


KPar K;
Real Qsto(start=0);
Real Qsto1(start=0);
Real Qsto2(start=0);
Real Qgut(start=0);

initial equation		//A5
 
equation

Qsto = Qsto1 + Qsto2;

der(Qsto1) =(-K.kmax)*Qsto1 + K.Dose*delta;

der(Qsto2) = - k_empt(K, Qsto)*Qsto2 + K.kmax*Qsto1;

der(Qgut) = (-K.kabs)*Qgut +k_empt(K, Qsto)*Qsto2;

Rameal = (K.f*K.kabs*Qgut)/K.BW;


end Rate_Appearance_Glucose;

