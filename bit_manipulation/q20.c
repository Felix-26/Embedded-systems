#include<stdio.h>


int xorton(int n) {
	if(n%4==0) return n;
	if(n%4==1) return 1;
	if(n%4==2) return n+1;
	if(n%4==3) return 0;
}

int main() {
	int l,r;
	printf("enter L and R : ");
	scanf("%d%d",&l,&r);
	int res1 = xorton(r);
	int res2 = xorton(l-1);
	printf("xor of numbers from l to r = %d.",res1^res2);
}
