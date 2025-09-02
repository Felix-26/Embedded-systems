#include<stdio.h>

int checkEven(int x) {
	if(x&1) {
		return 0;
	} else {
		return 1;
	}
}

int main() {
	int x;
	printf("entert the number : ");
	scanf("%d",&x);
	if(checkEven(x)) {
		printf("the number %d is even .\n",x);
	} else {
		printf("the number %d is odd .\n",x);
	}
}
