#include<stdio.h>

void printBin(int n) {
	int i;
	printf("x = %d\n",n);
	for(i=32;i>=0;i--) {
		printf("%3d",i);
	}
	printf("\n");
	for(i=32;i>=0;i--) {
        printf("%3d",(n&(1<<i)) ? 1 : 0);
    }
	printf("\n");
}

void toggle(int *x,int pos) {
	if(*x&(1<<pos)) {
		*x = *x & ~(1<<pos);
	} else {
		*x = *x | (1<<pos);
	}
}

int main() {
	int x,pos;
	printf("enter the number : ");
	scanf("%d",&x);
	printf("enter the position of the bit to be toggled : ");
	scanf("%d",&pos);
	printf("before toggle : \n");
	printBin(x);
	toggle(&x,pos);
	printf("after  toggle : \n");
	printBin(x);
}
