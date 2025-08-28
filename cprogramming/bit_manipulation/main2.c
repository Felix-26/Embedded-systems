#include<stdio.h>

int main() {
	int a=10;
	int b=20;
	a = (a&b)^b;
	b=(a&b)^a;
	b=a&b;
	printf("%d\n%d\n",a,b);
}
