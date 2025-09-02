#include<stdio.h>

void clearBitAtPos(int *x,int pos) {
	*x = *x & ~(1<<pos);
}

void printBin(int *x) {
	int i;
	for(i=31;i>=0;i--) {
		printf("%3d",i);
	}
	printf("\n");
	for(i=31;i>=0;i--) {
        printf("%3d",(*x&1<<i) ? 1:0);
    }
	printf("\n");
}

int main() {
	int x,pos;
	printf("enter the number : ");
	scanf("%d",&x);
	printf("enter the bit position at which to clear the bit of number %d : ",x);
	scanf("%d",&pos);
	printf("\nbefore clearing bit x = %d\n",x);
	printBin(&x);
	clearBitAtPos(&x,pos);
	printf("after  clearing bit x = %d\n",x);
	printBin(&x);
	return 0;
}
