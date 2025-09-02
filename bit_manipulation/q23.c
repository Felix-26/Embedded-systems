#include<stdio.h>


int atob(int a,int b) {
	int count = 0;
	int res = a^b;
	for(int i=31;i>=0;i--) {
		if(res&(1<<i)) {
			count++;
		}
	}
	return count;
}

int main() {
	int a,b;
	printf("enter a and b :");
	scanf("%d%d",&a,&b);
	printf("the number of bits to be flipped to convert a to b = %d.",atob(a,b));
	return 0;
}
