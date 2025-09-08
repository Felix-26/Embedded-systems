#include<stdio.h>

int main() {
	int a,b;
	printf("enter the numbers a and b = ");
	scanf("%d%d",&a,&b);
	if(a^b)
		printf("both numbers are not equal.");
	else
		printf("both numbers are equal.");
	return 0;
}
