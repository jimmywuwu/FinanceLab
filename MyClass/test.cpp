#include "math.h"
#include <stdio>
#include <stdlib>
int main(int argc, char const *argv[])
{
	
	
	int n;
	scanf("%d",&n);
	double *x=new double[n];

	for (int i = 0; i < n; ++i)
	{
		scanf("輸入 %lf",x[i]);
	}

	for (int i = 0; i < n; ++i)
	{
		printf("%lf",x[i]);
	}

	return 0;
}