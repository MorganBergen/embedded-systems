/* write a c program that converts binary to hexadecimal */

#include <stdio.h>
#include <math.h>

int main()
{
    int binary, decimal = 0, i = 0, remainder;
    printf("Enter a binary number: ");
    scanf("%d", &binary);
    while (binary != 0)
    {
        remainder = binary % 10;
        binary /= 10;
        decimal += remainder * pow(2, i);
        ++i;
    }
    printf("decimal number = %d\n", decimal);


    // convert binary to hexadecimal
    int hex[100];
    int j = 0;
    while (decimal != 0)
    {
        hex[j] = decimal % 16;
        decimal = decimal / 16;
        j++;
    }
    printf("hexadecimal number = ");
    for (int i = j - 1; i >= 0; i--)
    {
        if (hex[i] > 9)
        {
            printf("%c\n", hex[i] + 55);
        }
        else
        {
            printf("%d\n", hex[i]);
        }
    }

    // convert decimal to binary
    int binary[100];
    int k = 0;
    while (decimal != 0)
    {
        binary[k] = decimal % 2;
        decimal = decimal / 2;
        k++;
    }
    printf("binary number = ");
    for (int i = k - 1; i >= 0; i--)
    {
        printf("%d\n", binary[i]);
    }


    return 0;
}
