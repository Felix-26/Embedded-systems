#include<stdio.h>


void checkPowerof8(int x) {
	int i=3;
	if((x&(x-1))==0) {
		printf("%d is a power of 2 ",x);
		while(i<32) {
			if((x&(1<<i))==x) {
				printf(" and  a power of 8.\n");
				return;
			}
			i+=3;
		}
		printf(", but not a power of 8.\n");
	} else {
		printf("%d is neither a power of 2 nor power of 8",x);
	}
}

int main() {
	int x;
	printf("enter the number :");
	scanf("%d",&x);
	checkPowerof8(x);
}
