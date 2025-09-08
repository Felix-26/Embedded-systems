#include<stdio.h>

void checkSign(int a,int b){
	if((a>>30)^(b>>30)) {
		printf("2 numbers %d and %d have opposite signs.",a,b);
	} else {
		printf("2 numbers %d and %d have same signs.",a,b);
	}
}


int main() {
	int a,b;
	printf("enter 2 numbers a and b : ");
	scanf("%d%d",&a,&b);
	checkSign(a,b);
	return 0;
}
