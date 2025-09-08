#include<stdio.h>


void checkPowerof16(int x) {
        int i=4;
        if((x&(x-1))==0) {
                printf("%d is a power of 2 ",x);
                while(i<32) {
                        if((x&(1<<i))==x) {
                                printf(" and  a power of 16.\n");
                                return;
                        }
                        i+=4;
                }
                printf(", but not a power of 16.\n");
        } else {
                printf("%d is neither a power of 2 nor power of 16",x);
        }
}

int main() {
        int x;
        printf("enter the number :");
        scanf("%d",&x);
        checkPowerof16(x);
}
