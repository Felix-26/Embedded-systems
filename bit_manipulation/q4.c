#include<stdio.h>


void printBin(int *x) {
	int i;
	for(i=31;i>=0;i--) {
		printf("%3d",i);
	}
	printf("\n");
	for(i=31;i>=0;i--) {
        printf("%3d",(*x&(1<<i))? 1:0 );
    }
	printf("\n");
}

void clearBitAtPos(int *x,int pos) {
	*x = *x & ~(1<<pos);
}

int lastSetPos(int *x) {
	int i=0;
	while(*x!=0 && i<32) {
		if(*x&(1<<i)){
			return i;
		}
		i++;
	}
}

int main() {
	int x,pos;
	printf("enter the number x = ");
	scanf("%d",&x);
	pos = lastSetPos(&x);
	printf("before clearing last set bit = %d \n",x);
	printBin(&x);
	clearBitAtPos(&x,pos);
	printf("after clearing last set bit = %d \n",x);
	printBin(&x);
	return 0;
}
