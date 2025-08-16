#include<stdio.h>

int main() {
	double d = 3.141159265359;
	float f = (float) d;		// double -> float (precision loss)
	printf("%.10f\n",f);
}
