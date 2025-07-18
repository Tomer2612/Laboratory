#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5 /* Define the matrix size (N x N) */
#define BUFFER_SIZE 1024 /* Define buffer size for input */

/* Function to read matrix elements from standard input */
int read_matrix(int matrix[N][N]) {
    char buffer[BUFFER_SIZE];
    int count = 0;
    int num;
    char *token;

    /* Read entire line of input */
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Error: Failed to read input.\n");
        return 0;
    }

    /* Tokenize the input by spaces and newlines */
    token = strtok(buffer, " \t\n");
    while (token != NULL) {
        if (sscanf(token, "%d", &num) != 1) {
            printf("Error: Invalid input. Expected integers only.\n");
            return 0;
        }
        if (count >= N * N) {
            printf("Error: Too many numbers in input.\n");
            return 0;
        }
        matrix[count / N][count % N] = num;
        count++;
        token = strtok(NULL, " \t\n");
    }

    if (count < N * N) {
        printf("Error: Not enough numbers in input.\n");
        return 0;
    }

    return 1;
}

/* Function to print the matrix */
void print_matrix(int matrix[N][N]) {
    int i, j;
    printf("Matrix:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}

/* Function to check if the matrix is a magic square */
int is_magic_square(int matrix[N][N]) {
    int target_sum = 0;
    int sum;
    int i, j;

    /* Calculate the sum of the first row to use as reference */
    for (j = 0; j < N; j++) {
        target_sum += matrix[0][j];
    }

    /* Check sums of all rows */
    for (i = 0; i < N; i++) {
        sum = 0;
        for (j = 0; j < N; j++) {
            sum += matrix[i][j];
        }
        if (sum != target_sum) {
            return 0;
        }
    }

    /* Check sums of all columns */
    for (j = 0; j < N; j++) {
        sum = 0;
        for (i = 0; i < N; i++) {
            sum += matrix[i][j];
        }
        if (sum != target_sum) {
            return 0;
        }
    }

    /* Check sum of main diagonal */
    sum = 0;
    for (i = 0; i < N; i++) {
        sum += matrix[i][i];
    }
    if (sum != target_sum) {
        return 0;
    }

    /* Check sum of secondary diagonal */
    sum = 0;
    for (i = 0; i < N; i++) {
        sum += matrix[i][N - 1 - i];
    }
    if (sum != target_sum) {
        return 0;
    }

    return 1;
}

int main() {
    int matrix[N][N];

    /* Prompt user to enter the elements */
    printf("Please enter %d integers separated by spaces (row by row):\n", N * N);

    /* Read the matrix */
    if (!read_matrix(matrix)) {
        return 1; /* Exit if there was an error in input */
    }

    /* Print the matrix */
    print_matrix(matrix);

    /* Check if the matrix is a magic square and print result */
    if (is_magic_square(matrix)) {
        printf("The matrix is a magic square.\n");
    } else {
        printf("The matrix is NOT a magic square.\n");
    }

    return 0;
}

