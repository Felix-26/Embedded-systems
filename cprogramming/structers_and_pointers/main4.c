#include<stdio.h>

void pointers(int **p,int *x) {
	printf("address stored by pointer = %p \n",p);
	printf("content of address stored by pointer = %d\n",**p);
}

int main() {
	int x=2025,*p;
	p = &x;
	pointers(&p,&x);
}
