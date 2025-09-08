#include<stdio.h>
#include<string.h>

void invertCase(char *c) {
	if(*c>='A' && *c <= 'Z' || (*c >= 'a' && *c <='z')) {
		if(*c&(1<<5)) {
			*c = *c & ~(1<<5);
		} else {
			*c = *c | (1<<5);
		}
	}
}

int main() {
	char str[] = "Felix Thomas";
	for(int i=0;i<strlen(str);i++) {
		invertCase(&(str[i]));
	}
	printf("inverted string = %s",str);
}
