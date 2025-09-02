#include<stdio.h>

int main() {
	int n=16;
	int i=2;
    if(n>0 && (n&(n-1))==0) {
        printf("%d is a power of 2",n);
        while(i<32) {
            if((n&(1<<i))==n) {
                printf("and is a power of 4");
                break;
            }
            i+=2;
        }
        printf("\n");
    } else {
        printf("the number %d is neither a power of 2 nor power of 4.\n",n);
    }
}
