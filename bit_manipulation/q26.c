#include<stdio.h>

int reverse(int x) {
	int n=0;
	while(x>0) {
		if(x&1) {
			n = (n<<1) | 1;
		} else {
			n = (n<<1) & 0;
		}
		x=x>>1;
	}
	return n;
}

void printBin(int x) {
	printf("Binary representaion of %d\t= ",x);
	for(int i=31;i>=0;i--) {
		printf("%d",(x&(1<<i))?1:0);
	}
	printf("\n");
}

int main() {
    int x;
    printf("enter a number : ");
    scanf("%d",&x);
	printBin(x);
	x = reverse(x);
    printBin(x);
}
