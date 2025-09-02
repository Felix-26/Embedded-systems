#include<stdio.h>

void checkPowerOf2(int n) {
	if(n>0 && (n&(n-1))==0){
		printf("the number %d is a power of 2.\n",n);
	} else {
		printf("the numeber %d is not a power of 2.\n",n);
	}
}

int main() {
	int x;
	printf("enter a number to check if it is power of 2 : ");
	scanf("%d",&x);
	checkPowerOf2(x);
	return 0;
}
