#include<stdio.h>

void printBin(int x) {
	printf("Binary representation of x : \n");
	for(int i=31;i>=0;i--) {
		printf("%2d",(x&(1<<i)) ? 1:0);
	}
	printf("\n");
}

int main() {
	int x;
	printf("enter a number : ");
	scanf("%d",&x);
	printBin(x);
}
