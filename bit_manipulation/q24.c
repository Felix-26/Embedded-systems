#include<stdio.h>
#include<stdlib.h>

int xorOfArr(int *arr,int n,int x) {
	int xor1=0,xor2=0;
	for(int i=1;i<=x;i++) {
		xor1^=i;
	}
	for(int i=0;i<n;i++) {
		xor2 ^= arr[i];
	}

	return xor1^xor2;
}

int main() {
	int n,x;
	int *arr;
	printf("enter the highest element : ");
	scanf("%d",&x);
	printf("enter the size of the array : ");
	scanf("%d",&n);

	arr = (int *)calloc(n,sizeof(int));
	if(!arr) {
		printf("memory allocation failed.\n");
		return 0;
	}

	printf("enter the array : ");
	for(int i=0;i<n;i++) {
		scanf("%d",&arr[i]);
	}

	printf("missing element of array = %d\n",xorOfArr(arr,n,x));

	free(arr);
	return 0;
}
