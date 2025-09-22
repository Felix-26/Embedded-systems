#include<stdio.h>


unsigned char func(unsigned char c) {
        int x = (int)c;
        x |= (1<<2);
        x &= ~(1<<5);
        x ^= 1;
        c = (unsigned char)x;
        return c;
}

int main() {
        unsigned char x = 'A';
        x = func(x);
        printf("f(x) = %c",x);
        return 0;
}