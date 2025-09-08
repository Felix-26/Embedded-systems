#include<stdio.h>

int swapBits(int n) {
	int evenBits = n&0xAAAAAAAA;
	int oddBits = n&0x55555555;
	evenBits>>=1;
	oddBits<<=1;
	return (oddBits|evenBits);
}

void printBin(int x) {
	for(int i=31;i>=0;i--) {
		printf("%d",(x&(1<<i))?1:0);
	}
	printf("\n");
}


int main() {
	int x;
	printf("enter a number : ");
	scanf("%d",&x);
	printf("before swapping :");
	printBin(x);
	x=swapBits(x);
	printf("after swapping : ");
	printBin(x);
}
