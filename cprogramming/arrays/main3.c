#include<stdio.h>

int main() {
	int i,x=0,mark[10];
	for(i=0;i<10;i++) {
		mark[i] = x;
		x+=2;
	}
	for(i=0;i<10;i++) {
		printf("%d\n",mark[i]);
	}
	return 0;
}
