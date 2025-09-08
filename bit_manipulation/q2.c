#include<stdio.h>


void printBin(int *x) {
	int i;
	for(i=31;i>=0;i--) {
		printf("%3d",i);
	}
	printf("\n");
	for(i=31;i>=0;i--) {
        printf("%3d",(*x&1<<i) ? 1 : 0);
    }
	printf("\n");
}

void setBitAtPos(int *x,int *pos) {
	*x = *x|(1<<*pos);
}

int main() {
	int x,pos;
	printf("enter the number : ");
	scanf("%d",&x);
	printf("enter the bit position of the number %d to be set : ",x);
	scanf("%d",&pos);

	printf("before setting = %d \n",x);
	printBin(&x);
	setBitAtPos(&x,&pos);
	printf("after setting = %d \n",x);
	printBin(&x);
	return 0;
}
