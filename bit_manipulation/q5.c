#include<stdio.h>


void oddeven(int x) {
	if(x&1) {
		printf("the number %d is odd.\n",x);
	} else {
		printf("the number %d is even.\n",x);
	}
}

void printBin(int x) {
	int i;
	for(i=31;i>=0;i--) {
		printf("%3d",i);
	}
	printf("\n");
	for(i=31;i>=0;i--) {
        printf("%3d",(x&(1<<i))?1:0);
    }
	printf("\n");
}

int main() {
	int x;
	printf("enter the number x = ");
	scanf("%d",&x);
	oddeven(x);
	printBin(x);
	return 0;
}
