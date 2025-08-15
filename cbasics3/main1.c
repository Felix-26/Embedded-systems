#include<stdio.h>

int sum(int a,int b) {
	return a+b;
}

int main() {
	int a,b,result;
	printf("enter the numbers a and b\n");
	scanf("%d%d",&a,&b);
	result = sum(a,b);
	printf("the sum of 2 numbers is %d\n",result);
	printf("%p : a\n",&a);
	printf("%p : b\n",&b);
	printf("%p : result\n",&result);
	return 0;
}
