#include<stdio.h>
#include<limits.h>

int divide(int divident,int divisor) {
	if(divisor == 0) return INT_MAX;
	if(divident == INT_MIN && divisor == -1) return INT_MAX;

	int a=divident;
	int b=divisor;
	int result;

	while(a>=b) {
		int temp = b,multiple = 1;
		while((temp<<1)<=a) {
			temp <<= 1;
			multiple <<= 1;
		}
		a-=temp;
		result += multiple;
	}

	if((divident<0)^(divisor<0))
		result =-result;
	return result;
}

int main() {
	int divisor,divident;
	printf("enter the divident and the divisor : ");
	scanf("%d%d",&divident,&divisor);
	printf("%d\n",divide(divident,divisor));
	return 0;
}
