#include "stdio.h"
#include "iostream"
#include "math.h"
double EquityValue(double r,double T,double V,double K,double vol,double alpha);
double DebtValue(double r,double T,double V,double K,double vol,double alpha,double tau,double coupon,double Amount);
double BankruptcyCost(double r,double T,double V,double K,double vol,double alpha);
double TaxBenefit(double r,double T,double V,double K,double vol,double alpha,double coupon,double Amount,double tau);
double FirmValue(double r,double T,double V,double K,double vol,double alpha,double coupon,double Amount,double tau);


double Standard_Normal_Distribution(double d){
   int flag=0;   //Flag =1 if d<0
   if(d<0)
     {
      flag=1;
      d=fabs(d);
     }
   double rr=0.2316419;
   double a1=0.31938153;
   double a2=-0.356563782;
   double a3=1.781477937;
   double a4=-1.821255978;
   double a5=1.330274429;
   double k=1/(1+d*rr);
   double PI=3.14159265359;
   double value=1-exp(d*d/(-2))*(a1*k+a2*pow(k,2)+a3*pow(k,3)+a4*pow(k,4)
                  +a5*pow(k,5))/sqrt(2*PI);
   if(flag) return 1-value;
    else return value;
}



int main(int argc, char const *argv[])
{
	double Amount,coupon,tau,V,r,T,vol,alpha;
	// printf("Please enter Debt Face Value : \n");
	// scanf("%lf",&Amount);
	// printf("Please enter coupon rate : \n");
	// scanf("%lf",&coupon);
	// printf("Please enter tau : \n");
	// scanf("%lf",&tau);
	// printf("Please enter V : \n");
	// scanf("%lf",&V);
	// printf("Please enter r : \n");
	// scanf("%lf",&r);
	// printf("Please enter T : \n");
	// scanf("%lf",&T);
	// printf("Please enter vol : \n");
	// scanf("%lf",&vol);
	// printf("Please enter alpha : \n");
	// scanf("%lf",&alpha);
	V=100;
	Amount=100;
	r=0.1;
	T=1;
	vol=0.3;
	alpha=0.1;
	tau=0.1;
	coupon=0.05;
	double K=Amount+coupon*Amount*(1-tau);

	printf("EquityValue : %lf\n",EquityValue(r,T,V,K,vol,alpha));
	printf("DebtValue : %lf\n",DebtValue(r,T,V,K,vol,alpha,tau,coupon,Amount));
	printf("Validate : %lf \n", V+TaxBenefit(r,T,V,K,vol,alpha,coupon,Amount,tau)-BankruptcyCost(r,T,V,K,vol,alpha));

	return 0;
}

double FirmValue(double r,double T,double V,double K,double vol,double alpha,double coupon,double Amount,double tau){
	return EquityValue(r,T,V,K,vol,alpha)+DebtValue(r,T,V,K,vol,alpha,tau,coupon,Amount);
}



double EquityValue(double r,double T,double V,double K,double vol,double alpha){
	  double b=1/exp(r*T);
	double d1=(log(V/(K*b))+vol*vol*T/2)/(vol*sqrt(T));
    double d2=d1-vol*sqrt(T);	
    return V*Standard_Normal_Distribution(d1)-K*exp(-r*T)*Standard_Normal_Distribution(d2);
}

double DebtValue(double r,double T,double V,double K,double vol,double alpha,double tau,double coupon,double Amount){
	double b=1/exp(r*T);
	double d1=(log(V/(K*b))+vol*vol*T/2)/(vol*sqrt(T));
    double d2=d1-vol*sqrt(T);	
    return (1-alpha)*V*Standard_Normal_Distribution(-d1)+(Amount+coupon*Amount)*exp(-r*T)*Standard_Normal_Distribution(d2);
}


double BankruptcyCost(double r,double T,double V,double K,double vol,double alpha){
	  double b=1/exp(r*T);
	double d1=(log(V/(K*b))+vol*vol*T/2)/(vol*sqrt(T));
    double d2=d1-vol*sqrt(T);	
	return alpha*V*Standard_Normal_Distribution(-d1);
}

double TaxBenefit(double r,double T,double V,double K,double vol,double alpha,double coupon,double Amount,double tau){
	  double b=1/exp(r*T);
	double d1=(log(V/(K*b))+vol*vol*T/2)/(vol*sqrt(T));
    double d2=d1-vol*sqrt(T);	
	return exp(-r*T)*(coupon*Amount*T*tau)*Standard_Normal_Distribution(d2);
}