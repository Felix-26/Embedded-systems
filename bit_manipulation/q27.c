#include<stdio.h>

int swapBits(int x,int i,int j){
	int ib=(x>>i)&1;
	int jb=(x>>j)&1;

	if(ib!=jb) {
		x = x ^ ((1<<i)|(1<<j));
	}
	return x;
}

int main() {
	int x,i,j;
	printf("enter a number = ");
	scanf("%d",&x);
	printf("enter the positions to be swapped = ");
	scanf("%d%d",&i,&j);
	printf("before swapping = %d\nafter swapping = %d\n",x,(swapBits(x,i,j)));
	return 0;
}
