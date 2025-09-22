#include<stdio.h>
#include<stdlib.h>


int *getarray(int *n) {
        int i;
        int *arr;
        printf("enter the number of elements (atleast 2) : ");
        scanf("%d",n);

        if(*n>=2)
                arr = (int *)calloc((*n),sizeof(int));
        if(!arr) {
                printf("memory allocation failed!");
                exit(1);
        }

        printf("enter the elements : ");
        for(i=0;i<(*n);i++) {
                scanf("%d",&arr[i]);
        }
        return arr;
}

int seclargest(int arr[],int n) {
        int i,l,sl;
        for(i=0;i<n;i++) {
                if(i==0) {
                        l = arr[i];
                }
                if(l<arr[i]) {
                        l=arr[i];
                }
        }

        printf("largest = %d",l);
        for(i=0;i<n;i++) {
                if(i==0) {
                        sl = arr[i];
                }
                if(arr[i]>sl && arr[i]<l) {
                        sl = arr[i];
                }
        }
        return sl;
}

int main() {
        int n,x,*arr;
        arr = getarray(&n);
        x = seclargest(arr,n);
        printf("second largest number is : %d",x);
        free(arr);
        return 0;
}