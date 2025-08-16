#include<stdio.h>

int main() {
	int i,mark[10] = {1,2,3,4,5,6,7,8,9,10};
	void *ptr;
	for (i=0;i<10;i++) {
		ptr = &mark[i];
		printf("%p		%d\n",ptr,mark[i]);
	}
	return 0;
}
