#include <stdio.h>

int main() {
    float f = 5.75;
    int i = (int) f;      // float → int (fraction dropped)
    printf("%d\n", i);    // 5

    int x = 7;
    float y = (float) x;  // int → float
    printf("%.2f\n", y);  // 7.00
}
