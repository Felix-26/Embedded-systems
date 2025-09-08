#include<stdio.h>

void printBin(int x) {
/*
	for(int i=31;i>=0;i--) {
		printf("%3d",i);
	}
	printf("\n");
*/
    for(int i=31;i>=0;i--) {
        printf("%d",(x&(1<<i))?1:0);
    }
    printf("\n");
}

void copyBitsOnRange(int *x,int *y,int l,int r) {
	int left = *y>>(l+1);
	int right = *y>>(r);
	left = left<<(l+1);
    right = right<<(r);
	int xor = right^left;
/*
	printf("left = 	\n");
	printBin(left);
	printf("right = \n");
	printBin(right);
	printf("mask =   \n");
	printBin(xor);
*/
	*x=*x|xor;
}

void toggleOnRange(int *x,int l,int r) {
	int left = *x>>(l+1);
    int right = *x>>(r);
    left = left<<(l+1);
    right = right<<(r);
    int xor = right^left;
	*x=*x^xor;
}

void main() {
	int x,y,l,r;
	printf("enter the number x and y : ");
	scanf("%d%d",&x,&y);
	printf("enter the start and end position of the range (l>r): ");
	scanf("%d%d",&l,&r);
	printf("x =    \n");
	printBin(x);
	printf("y =    \n");
	printBin(y);
	printf("after copying range l to r from y to x , x becomes :\n");
	copyBitsOnRange(&x,&y,l,r);
	printBin(x);
	printf("after toggling set bits of range l to r of , y becomes :\n");
	toggleOnRange(&y,l,r);
	printBin(y);
}
