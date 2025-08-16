#include<stdio.h>

int main() {
	int i,mark[10] = {1,2,3,4,5,6,7,8,9,10};
	for (i=0;i<10;i++) {
		mark[i] = i;
	}
	for (i=0;i<10;i++) {
        printf("%d\n",mark[i]);
    }
	return 0;
}
