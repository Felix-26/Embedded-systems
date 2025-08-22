#include<stdio.h>
#include<stdlib.h>

int *createArr(int n) {
	int *ptr = (int*)calloc(n,sizeof(int));
	return ptr;
}

void resizeArr(int *ptr,int n,int m) {
	int *temp = realloc(ptr,(n+m)*sizeof(int));
	if(temp == NULL) {
		printf("memory allocation failed!");
	} else {
		ptr = temp;
	}
}

void assignVals(int *ptr,int n) {
	int i;
	printf("\nenter the elements :\n");
	for(i=0;i<n;i++) {
		scanf("%d",ptr+i);
	}
}

void displayArr(int *ptr,int n) {
	int i;
	printf("arrar = ");
	for(i=0;i<n;i++) {
		printf("%d  ",*(ptr+i));
	}
	printf("\n");
}


int main() {
        int i,*ptr,n,choice,m;
        printf("Enter the number of integers you need to store : ");
        scanf("%d",&n);
		ptr = createArr(n);
		if(ptr == NULL) {
			printf("memory allocation failed!\n");
		} else {
			assignVals(ptr,n);
			displayArr(ptr,n);
			while(1) {
				printf("do you need to store more elements type 1 if you do otherwise type 0 :");
				scanf("%d",&choice);
				if(choice == 1) {
					printf("how many more elements you need to add : ");
					scanf("%d",&m);
					resizeArr(ptr,n,m);
					assignVals(ptr+n,m);
					n+=m;
					displayArr(ptr,n);
				} else {
					break;
				}
			}
		}
		printf("\n");
        free(ptr);
        return 0;
}
