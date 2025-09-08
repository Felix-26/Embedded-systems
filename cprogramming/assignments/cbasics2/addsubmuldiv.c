#include<stdio.h>

int add(int,int);
int sub(int,int);
int mul(int,int);
float div(float,float);

int main() {
	float a,b;
	printf("enter a and b");
	scanf("%f%f",&a,&b);
	printf("a + b = %d\n",add(a,b));
	printf("a - b = %d\n",sub(a,b));
	printf("a * b = %d\n",mul(a,b));
	printf("a / b = %f\n",div(a,b));
	return 0;
}


int add(int a,int b) {
    return a + b;
}

int sub(int a,int b) {
	return a - b;
}

int mul(int a,int b) {
    return a * b;
}

float div(float a,float b) {
    return a / b;
}
