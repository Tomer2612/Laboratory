#ifndef MYMAT_H
#define MYMAT_H

#define SIZE 4

typedef struct {
    double data[SIZE][SIZE];
} mat;

void read_mat(mat* m, double* values, int num_values);
void print_mat(mat* m);
void add_mat(mat* m1, mat* m2, mat* result);
void sub_mat(mat* m1, mat* m2, mat* result);
void mul_mat(mat* m1, mat* m2, mat* result);
void mul_scalar(mat* m, double scalar, mat* result);
void trans_mat(mat* m, mat* result);

#endif
