/* @file            main.c
 * @author          morgan bergen
 * @date            jan 27 2023
 * @brief           standard input and output
 * @description     getchar
 */

#include <stdio.h>

int main(int argc, char *argv[]) {

    printf("%d", argc);

    printf("%s%s", argv[0], argv[1]);

    return(0);
}
