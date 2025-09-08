#include<stdio.h>

int main() {
	int a=10;
	int *p = &a;
	void *ptr = &a;

	printf("*p = %d\n",*p);
	printf("*ptr = %d\n",*((int *)ptr));
	printf("address = %p\n",p);

	*p = 30;
	
	printf("after *p=30\n");
	printf("*p = %d\n",*p);
    printf("*ptr = %d\n",*((int *)ptr));
	printf("address = %p\n",p);

	*(int *)ptr = 40;

	printf("after *((int *)ptr)=40\n");
    printf("*p = %d\n",*p);
    printf("*ptr = %d\n",*((int *)ptr));
	printf("address = %p\n",p);
	return 0;
}
