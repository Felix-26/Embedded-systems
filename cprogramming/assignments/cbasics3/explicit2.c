#include<stdio.h>

int main() {
    int i = 300;
    char c = (char) i;   // int → char (possible overflow)
    printf("%d\n", c);   // Output depends on char size (may wrap)
}
