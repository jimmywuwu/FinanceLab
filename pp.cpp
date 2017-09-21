#include "stdio.h"
#include "iostream"

int max_point(int a[3]);

int main(int argc, char const *argv[])
{
	int a[3];
	a[0]=1;
	a[1]=2;
	a[2]=3;

	std::cout << std::max_element(a);
	return 0;
}

