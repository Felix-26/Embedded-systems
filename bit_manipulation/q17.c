#include<stdio.h>
#include<stdlib.h>


int findTheOne(int *arr,int n) {
	int res=0;
	for(int i=0;i<n;i++) {
		res=res^arr[i];
	}
	return res;
}


int main() {
	int i,n,*arr;
	printf("enter the size of the array : ");
	scanf("%d",&n);

	arr = (int *)calloc(n,sizeof(int));
	if(!arr) {
		printf("memory allocation failed !");
		exit(0);
	}

	printf("enter the array : ");
	for(i=0;i<n;i++) {
		scanf("%d",&arr[i]);
	}

	printf("the number in the array that appears odd number of times = %d",findTheOne(arr,n));
	free(arr);
	return 0;
}
