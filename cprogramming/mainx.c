#include<stdio.h>

int func() {
	int a=10;
	a++;
	return a;
}

int main() {
	int a=func();
	printf("%d\n",a);
	a=func();
    printf("%d\n",a);
	a=func();
    printf("%d\n",a);
	return 0;
}
