#include<stdio.h>

void checkBit(int *x,int *pos) {
	if(*x&(1<<*pos) > 1)
		printf("\nthe bit at position %d of number %d is set.\n",*pos,*x);
	else
		printf("\nthe bit at position %d of number %d is not set.\n",*pos,*x);
}

void printBin(int *x) {
	int i;
	for(i=31;i>=0;i--) {
		printf("%3d",i);
	}
	printf("\n");
	for(i=31;i>=0;i--) {
		printf("%3d",(*x&(1<<i))?1:0);
	}
}

int main() {
	int x,pos;
	printf("enter the number : ");
	scanf("%d",&x);
	printf("enter the position of the bit : ");
	scanf("%d",&pos);
	printBin(&x);
	checkBit(&x,&pos);
	printBin(&x);
	return 0;
}
