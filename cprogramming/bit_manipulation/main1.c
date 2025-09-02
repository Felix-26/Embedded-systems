#include<stdio.h>

void printBin(int x) {
	int n=1,mask;
	for(int i=31;i>=0;i--) {
		mask = 1<<i;
		printf("%d",(x&mask)?1:0);
	}
	printf("\n");
}

void setBit(int pos,int *x) {
	int mask = 1<<pos;
	*x=*x|mask;
	printBin(*x);
}

void clearBit(int pos,int *x) {
	int mask = ~(1<<pos);
	*x=*x&mask;
	printBin(*x);
}

int main() {
	int x,pos;
	printf("enter a number : ");
	scanf("%d",&x);
	printBin(x);
//	printf("enter the set bit position :\t");
//	scanf("%d",&pos);
//	setBit(pos,&x);
//	printf("enter the clear bit position :\t");
//	scanf("%d",&pos);
//	clearBit(pos,&x);
	return 0;
}
