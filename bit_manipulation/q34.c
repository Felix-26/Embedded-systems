#include<stdio.h>

int add1(int x){
	int m=1;
	while(x&m) {
		x^=m;
		m<<=1;
	}
	x^=m;
	return x;
}

void printBin(int x) {
	for(int i=31;i>=0;i--) {
		printf("%d",(x&(1<<i))?1:0);
	}
	printf("\n");
}

int main() {
	int x;
	scanf("%d",&x);
	x=add1(x);
	printf("after adding 1 = %d\n",x);
	printBin(x);
	return 0;
}
