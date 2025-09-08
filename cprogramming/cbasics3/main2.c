#include<stdio.h>

int add(int a,int b) {
	return a+b;
}

int sub(int a,int b) {
	return a-b;
}

int mul(int a,int b) {
	return a*b;
}

float div(float a,float b) {
	return a/b;
}

void main() {
	int a,b,c,res;
	float resdiv;
	printf("enter the numbers a and b:\n");
	scanf("%d%d",&a,&b);
	printf("select the function to be done:\n");
	printf("1.add\n2.sub\n3.mul\n4.div\n");
	scanf("%d",&c);
	switch(c) {
		case 1:
				res=add(a,b);
				printf("sum = %d\n",res);
				break;
		case 2:
				res=sub(a,b);
				printf("dif = %d\n",res);
				break;
		case 3:
				res=mul(a,b);
				printf("pro = %d\n",res);
				break;
		case 4:
				printf("quo = %f\n",div(a,b));
				break;
		default:
				printf("enter a valid number:\n");
				break;
	}
}
