/*
 * write a program in c to count a total number of duplicate elements in an array
 */

#include <stdio.h>

// main function
int main() {
    // array declaration with size 100
    // and initialize counter with 0
    int arr[100], i, j, n, count = 0;
    // user prompt to enter array size
    printf("Input the number of elements to be stored in the array :");
    // read array size
    scanf("%d", &n);
    // user prompt to enter array elements
    printf("Input %d elements in the array :", n);
    // read array elements, and store in array
    for (i = 0; i < n; i++) {
        // prompt to enter array element
        printf("element - %d : ", i);
        // read array element
        scanf("%d", &arr[i]);
    }
    // iterate over array
    for (i = 0; i < n; i++) {
        // iterate over array from i+1
        for (j = i + 1; j < n; j++) {
            // check if arr[i] is equal to arr[j]
            if (arr[i] == arr[j]){
                // increment counter
                count++;
                // break the loop
                break;
            }
        }
    }
    // print total number of duplicate elements
    printf("Total number of duplicate elements found in the array is : %d", count);
    // if the program executes successfully, return 0
    return 0;
}
