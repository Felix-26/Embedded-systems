#include<stdio.h>

int main() {
	char x = 'A';
	switch(x) {
		// char -> int
		case 65 :
				printf("%c is typecasted to %d",x,x);
				break;
	}
	return 0;
}
