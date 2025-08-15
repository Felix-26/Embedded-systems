#include<stdio.h>

int main() {
	int a = 5;
	float b =2.5;
	float c = a+b;			// 'a' promotted to float here.
	printf("%f\n",c);
	return 0;
}
