#include<stdio.h>

void countSetBits(int n) {
	int i;
	int count = 0;
	for(i=31;i>=0;i--) {
		if(n&(1<<i)) {
			count++;
		}
    }
	printf("\nnumber of set bits = %d\nnumber of unset bits = %d\n",count,32-count);
	for(i=31;i>=0;i--) {
		printf("%3d",i);
	}
	printf("\n");
	for(i=31;i>=0;i--) {
        printf("%3d",((n&(1<<i))?1:0));
    }
    printf("\n");
}


int main() {
	int x;
	printf("enter the number : ");
	scanf("%d",&x);
	countSetBits(x);
	return 0;
}
