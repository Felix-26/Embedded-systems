#include<stdio.h>

void checkPowerOf4(int n) {
	int i=2;
	if(n>0 && (n&(n-1))==0) {
		printf("%d is a power of 2",n);
		while(i<32) {
			if((n&(1<<i))==n) {
				printf(" and is a power of 4\n");
				return;
			}
			i+=2;
		}
		printf(" and not a power of 4\n");
	} else {
		printf("the number %d is neither a power of 2 nor power of 4.\n",n);
	}
}


int main() {
	int x;
	printf("enter the number to be checked if it is power of 4 : ");
	scanf("%d",&x);
	checkPowerOf4(x);
}
