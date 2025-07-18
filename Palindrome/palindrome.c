#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 80 /* Define the maximum length for the input string */

/* Function to check if a string is a palindrome */
int palindrome(const char *str) {
    int left = 0, right = strlen(str) - 1;
    while (left < right) {
        /* Skip spaces and tabs */
        while (left < right && isspace(str[left])) left++;
        while (left < right && isspace(str[right])) right--;
        
        /* Compare characters (case insensitive) */
        if (str[left] != str[right]) {
            return 0;
        }
        left++;
        right--;
    }
    return 1;
}

int main() {
    char input[MAX_LEN + 1]; /* Define a variable to store the input string */
    
    /* Prompt for input */
    printf("Enter a string: ");
    if (!fgets(input, sizeof(input), stdin)) {
        return 1; /* Return an error code if input fails */
    }
    
    /* Remove trailing newline character if present */
    input[strcspn(input, "\n")] = 0;
    
    /* Print the input string */
    printf("You entered: %s\n", input);
    
    /* Check if the string is a palindrome and print the result */
    printf("%d\n", palindrome(input));
    
    return 0;
}

