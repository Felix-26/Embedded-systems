#include<stdio.h>

int letterPos(char c) {
	c = c & ~(1<<5);

	return c&31;
}

int main() {
	char c;
	printf("enter a letter to check the postion : \n");
	scanf("%c",&c);
	printf("Letter position of %c = %d\n",c,(letterPos(c)));
}
