#include <stdio.h>
#include <limits.h> /* For CHAR_BIT */

/* Function to count the number of zero bits in an unsigned int */
int count_zero_bits(unsigned int num) {
    int zero_count = 0;
    int total_bits = sizeof(unsigned int) * CHAR_BIT;
    int i;
    
    for (i = 0; i < total_bits; i++) {
        if ((num & (1U << i)) == 0) {
            zero_count++;
        }
    }
    return zero_count;
}

int main() {
    unsigned int num;
    int zero_bits;
    
    /* Prompt for input */
    printf("Enter a positive whole decimal base number: ");
    if (scanf("%u", &num) != 1) {
        printf("Invalid input. Please enter a positive whole decimal number.\n");
        return 1;
    }
    
    /* Print the input number */
    printf("You entered: %u\n", num);
    
    /* Compute and print the number of zero bits */
    zero_bits = count_zero_bits(num);
    printf("Number of zero bits in %u: %d\n", num, zero_bits);
    
    return 0;
}
