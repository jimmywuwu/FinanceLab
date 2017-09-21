#include "Trinomial.cpp"
#include "stdio.h"
#include <iostream>

double OptionPricing(double X,TrinomialTree t);

int main(int argc, char const *argv[])
	{
		double StrikePrice;
		TrinomialTree t(0.05,0.015,1,2);

		printf("Please enter the Strike Price X : \n");
		scanf("%lf",&StrikePrice);
		printf("the option value pricing by Hull White Trinomial Tree is :%lf\n",OptionPricing(StrikePrice,t));

		return 0;
}	

