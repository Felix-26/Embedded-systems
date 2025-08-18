#include<stdio.h>
#pragma pack(1)    //to not use structure padding. other wise used by default.

struct Test {
	int n : 8;
	char c : 8;
//	int b;
	char a : 8;
	//double d;
};

int main() {
	printf("%ld",sizeof(struct Test));
}
