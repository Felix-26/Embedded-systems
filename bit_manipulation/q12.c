#include<stdio.h>
#include<stdlib.h>


int findUnique(int *arr,int n) {
	int i,num1=0,num2=0,res = 0;
	for(i=0;i<n;i++) {
		printf("%d",res);
        res=res^arr[i];
        printf("^%d = %d\n",arr[i],res);
	}

	res = res&-res;

	for(i=0;i<n;i++) {
		if(arr[i]&res) {
			num1=num1^arr[i];
		} else {
			num2=num2^arr[i];
		}
	}
	printf("unique numbers in the array : %d and %d\n",num1,num2);
	return res;
}

int main() {
	int *arr;
	int n,i,res;
	printf("enter the size of the array :");
	scanf("%d",&n);
	arr = (int *)calloc(n,sizeof(int));
	if(!arr) {
		printf("memory allocation failed !\n");
		return 0;
	}

	printf("enter the array : ");
	for(int i=0;i<n;i++) {
		scanf("%d",&arr[i]);
	}
	res = findUnique(arr,n);

/*
	res=0;
	for(i=0;i<n;i++) {
		printf("%d",res);
		res=res^arr[i];
		printf("^%d = %d\n",arr[i],res);
	}
*/
//	printf("unique number in the array : %d ",findUnique(arr,n));

	free(arr);
}
