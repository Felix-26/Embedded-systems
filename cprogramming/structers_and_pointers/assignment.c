#include<stdio.h>

#define MAXLEN 10

//function to assign values to the array.
void assign_values(int *arr) {
	int i,*ptr = arr;
	for (i=0;i<MAXLEN;i++) {
		*ptr = i*10+20;
		ptr += 1;			// incrementing array pointer.
	}
}

//function to print the INDEX,VALUE,ADDRESS of the array.
void print_arr(int *arr) {
	int i,*ptr = arr;
	printf("INDEX   VALUE   ADDRESS\n\n");
	for(i=0;i<MAXLEN;i++) {
		printf("%d\t%d\t%p\n",i,*ptr,ptr);
		ptr += 1;
	}
}

//main function
int main() {
	int i,arr[MAXLEN];
	int *ptr = arr;
	assign_values(arr);
	//print_arr(arr);
	for(i=0;i<MAXLEN;i++) {
		printf("%d  ",arr[i]);
	}
	printf("\n*ptr) = %d\n",*ptr);
	ptr++;
	printf("%d\n",*ptr);
	return 0;
}
