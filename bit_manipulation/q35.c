#include<stdio.h>

int xor(int a,int b) {
	int x = a&~b;
	int y = ~a&b;
	return x|y;
}

int main() {
	int a,b;
	printf("enter the numbers a and b :");
	scanf("%d%d",&a,&b);
	printf("xor of 2 numbers without using xor = %d",xor(a,b));
	return 0;
}
