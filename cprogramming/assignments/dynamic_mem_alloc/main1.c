#include<stdio.h>
#include<stdlib.h>



int main() {
        int i,*ptr,n;
        printf("Enter the number of integers you need to store : ");
        scanf("%d",&n);
        ptr = (int *)calloc(n,sizeof(int));
        if(ptr==NULL) {
                printf("memory allocation failed!");
        } else {
                for(i=0;i<n;i++) {
                        scanf("%d",(ptr+i));
                }
                printf("\n");
                for(i=0;i<n;i++){
                        printf("%d      ",*(ptr+i));
                }
                printf("\n");
        }
        free(ptr);
        printf("%p",ptr);
        return 0;
}
