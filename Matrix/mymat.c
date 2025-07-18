#include <stdio.h>
#include "mymat.h"

void read_mat(mat* m, double* values, int num_values) {
    int i, j, index = 0;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (index < num_values)
                m->data[i][j] = values[index++];
            else
                m->data[i][j] = 0.0;
        }
    }
}

void print_mat(mat* m) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%7.2f ", m->data[i][j]);
        }
        printf("\n");
    }
}

void add_mat(mat* m1, mat* m2, mat* result) {
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            result->data[i][j] = m1->data[i][j] + m2->data[i][j];
}

void sub_mat(mat* m1, mat* m2, mat* result) {
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            result->data[i][j] = m1->data[i][j] - m2->data[i][j];
}

void mul_mat(mat* m1, mat* m2, mat* result) {
    int i, j, k;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            result->data[i][j] = 0.0;
            for (k = 0; k < SIZE; k++) {
                result->data[i][j] += m1->data[i][k] * m2->data[k][j];
            }
        }
    }
}

void mul_scalar(mat* m, double scalar, mat* result) {
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            result->data[i][j] = m->data[i][j] * scalar;
}

void trans_mat(mat* m, mat* result) {
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            result->data[j][i] = m->data[i][j];
}

