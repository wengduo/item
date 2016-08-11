#include <stdio.h>
#include <iostream>

constexpr double show(double p)
{
	return p*p*3.14;
}
//double show(double p)
//{
//	return p*p*3.14;
//}
int main()
{
	
	constexpr double i = show(3);
	double j = show(3);
	printf("%lf\n",i);
	printf("%lf\n", j);
	return 0;
}