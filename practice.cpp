#include "stdio.h"
#include "iostream"
#include "math.h"

int main(int argc, char const *argv[])
{
	double Z[5];
	double mat[4][4];
	for(int i=0;i<5;i++){
		scanf("%lf",&Z[i]);
	}

	for(int i=1;i<5;i++){
		for(int j=i+1;j<6;j++){
			double a;
			mat[i-1][j-1]=pow(1+Z[i-1],i)/pow(1+Z[j-1],j);
			printf("%lf ",a);
		}
		printf("\n");
	}
	return 0;
}