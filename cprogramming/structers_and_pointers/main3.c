#include<stdio.h>

int main() {
	int y=22,x = 23,z=24;
	int *p = &x,*q,*r;
	q=&y;
	r = &z;
	printf("value of the variable x = %d\n",x);
	printf("address of variable x = %p\n",&x);
	printf("content of pointer p = %p\n",p);
	printf("content inside address stored by pointer p = %d\n",*p);
	printf("address of the pointer p = %p\n",&p);
	printf("*&x = %d\n\n",*(&x));

	printf("value of the variable y = %d\n",y);
	printf("address of variable y = %p\n",&y);
	printf("content of pointer q = %p\n",q);
    printf("content inside address stored by pointer q = %d\n",*q);
	printf("address of the pointer q = %p\n\n",&q);

	printf("value of the variable z = %d\n",z);
	printf("address of variable z = %p\n",&z);
	printf("content of pointer r = %p\n",r);
    printf("content inside address stored by pointer r = %d\n",*r);
	printf("address of the pointer r = %p\n\n",&r);
	return 0;
}
