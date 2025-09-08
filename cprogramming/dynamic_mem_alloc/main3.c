#include<stdio.h>
#include<stdlib.h>



int main() {
	int i,*ptr,n;
	printf("Enter the number of integers you need to store : ");
	scanf("%d",&n);
	ptr = (int *)malloc(n*sizeof(int));
	printf("%ptr\n",ptr);
	if(ptr==NULL) {
		printf("memory allocation failed!");
	} else {
		for(i=0;i<n;i++) {
			scanf("%d",(ptr+i));
		}
		printf("\n");
		for(i=0;i<n;i++){
			printf("%d	",*(ptr+i));
		}
		printf("\n");
	}
	free(ptr);
	printf("%ptr\n",ptr);
	return 0;
}
