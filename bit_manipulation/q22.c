#include<stdio.h>
#include<stdlib.h>


int findXorOfSubSets(int *arr,int n) {
	int xor=0;
	int j,subs = 1<<n,pos;
	for(int i=0;i<subs;i++) {
		pos = 0;
		j=i;
		while(j) {
			if(j&1) {
				xor ^= arr[pos];
			}
			j=j>>1;
			pos++;
		}
	}
	return xor;
}

void printBin(int x) {
	for(int i=31;i>=0;i--) {
		printf("%d",(x&(1<<i))?1:0);
	}
	printf("\n");
}

int main() {
	int n,xor,*arr;
	printf("enter the number of elements in the array : ");
	scanf("%d",&n);
	arr=(int *)calloc(n,sizeof(int));
	if(!arr) {
		printf("memory allocation failed.");
		return 0;
	}

	printf("enter the array : ");
	for(int i=0;i<n;i++) {
		scanf("%d",&arr[i]);
	}

	xor = findXorOfSubSets(arr,n);
	printf("XOR of the XOR of all subsets of an array = %d.\n",xor);
	printBin(xor);

	free(arr);
	return 0;
}
