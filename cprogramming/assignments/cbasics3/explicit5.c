#include <stdio.h>
int main() {
    int a = 5, b = 2;
    float result = (float) a / b; // ensures float division
    printf("%.2f\n", result);     // 2.50
}
