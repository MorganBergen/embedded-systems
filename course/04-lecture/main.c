#include <stdio.h>

int main() {
    int var1 = 100;
    printf("%d\n", var1++); // 100
    printf("%d\n", ++var1); // 102
    printf("%d\n", var1--); // 102
    printf("%d\n", --var1); // 100
    return(0);
}
