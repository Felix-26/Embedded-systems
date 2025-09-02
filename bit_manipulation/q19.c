#include<stdio.h>

int xorUsingFor(int n) {
	int res=0;
	for(int i=1;i<=n;i++) {
		res^=i;
	}
	return res;
}

int xorUsingper(int n) {
	if(n%4==0)
		return n;
	else if(n%4==1)
		return 1;
	else if(n%4==2)
		return n+1;
	else if(n%4==3)
		return 0;
}

int main() {
	int n;
	printf("enter the number : ");
	scanf("%d",&n);
	printf("xor of 1 -> %d = %d\n",n,xorUsingper(n));
	return 0;
}
