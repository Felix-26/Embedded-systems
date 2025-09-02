#include<stdio.h>

void swap(int *a,int *b) {
	*a = *a^*b;
	*b = *a^*b;
	*a = *a^*b;
}


int main() {
	int a,b;
	printf("enter the numbers a and b : ");
	scanf("%d%d",&a,&b);
	swap(&a,&b);
	printf("the swapped numbers \na = %d\nb = %d\n",a,b);
}
