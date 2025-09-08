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
			if((*c&(1<<5))) {
				*c = *c & ~(1<<5);
			}
			printf("str[%d] = %c\t",i,*c);
			printBin(*c);
			c=c+1;
        }
}

int main() {
        char str[] = "Felix Thomas";
        toLower(str,strlen(str));
}
