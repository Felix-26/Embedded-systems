#include<stdio.h>

int main() {
	int arr[10];
	int *ptr1=&arr[0],*ptr2=arr;
	if(ptr1==ptr2) {
		printf("the two pointers points to the same location.");
	}
	return 0;
}
