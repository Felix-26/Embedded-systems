#include<stdio.h>

int main() {
	int a=10;
	int b=20;
	printf("enter the number a = ");
	scanf("%d",&a);
	printf("enter the number b = ");
    scanf("%d",&b);
	a = (a)^b;
	b=(a)^b;
	a=a^b;
	printf("a = %d\nb = %d\n",a,b);
}
