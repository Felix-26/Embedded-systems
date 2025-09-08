#include<stdio.h>
#include<string.h>

void printBin(int x) {
	int i;
	for(i=31;i>=0;i--) {
		printf("%d",(x&(1<<i))? 1 : 0);
	}
	printf("\n");
}

void toLower(char *c,int len) {
	int i,x;
	for(i=0;i<len;i++) {
		x = (int)(*(c));
		printf("str[%d]	= %c\t",i,*c);
		printBin(x);
		if((x&(1<<5))==0) {
			*c = *c | (1<<5);
		}
		c=c+1;
	}
}

int main() {
	char str[] = "Felix Thomas";
	toLower(str,strlen(str));
	for(int i=0;i<strlen(str);i++) {
		printf("str[%d] = %c\t",i,str[i]);
		printBin(str[i]);
	}
}
