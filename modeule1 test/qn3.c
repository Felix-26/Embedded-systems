#include<stdio.h>

void print_pyramid(int n) {
        int i,j;
        for(i=1;i<=n;i++) {
                for(j=1;j<=n-i;j++) {
                        printf(" ");
                }
                for(j=1;j<=2*i-1;j++) {
                        printf("*");
                }
                printf("\n");
        }
}

int main() {
        int n;
        printf("enter the size of the pyramid : ");
        scanf("%d",&n);
        print_pyramid(n);
        return 0;
}