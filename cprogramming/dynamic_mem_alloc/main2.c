#include<stdio.h>

int main() {
	int i;
	float arr[5] = {1.3,22.79,41.10,5.44,6.9};
	void *ptr = arr;
	for(i=0;i<5;i++) {
		printf("%.2f  ",*((float *)ptr+i));
	}
}
