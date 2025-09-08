#include <stdio.h>
int main() {
    int x = 10;
    void *ptr = &x;              // store in void pointer
    int *int_ptr = (int *) ptr;  // cast back to int pointer
    printf("%d\n", *int_ptr);    // 10
	printf("%p\n", ptr);
	return 0;
}
