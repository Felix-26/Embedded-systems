#include<stdio.h>

float f() {
	return 5;				// return value promoted from int -> float
}

int main() {
	printf("%f\n",f());
	return 0;
}
