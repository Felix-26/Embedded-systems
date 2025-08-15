#include<stdio.h>

double func(double d) {
	return d*2;
}

int main() {
	double x = func(5);			// func parameter is promoted from int -> double 
	printf("%lf\n",x);
	return 0;
}
