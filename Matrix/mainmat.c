#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mymat.h"

#define MAX_LINE 1000
#define MAX_ARGS 20

mat A_MAT, B_MAT, C_MAT, D_MAT, E_MAT, F_MAT;

void prompt() {
    printf("\nEnter command: ");
}

mat* get_mat_by_name(char* name) {
    if (strcmp(name, "A_MAT") == 0) return &A_MAT;
    if (strcmp(name, "B_MAT") == 0) return &B_MAT;
    if (strcmp(name, "C_MAT") == 0) return &C_MAT;
    if (strcmp(name, "D_MAT") == 0) return &D_MAT;
    if (strcmp(name, "E_MAT") == 0) return &E_MAT;
    if (strcmp(name, "F_MAT") == 0) return &F_MAT;
    return NULL;
}

void trim(char* str) {
    int i = 0;
    while (isspace((unsigned char)str[i])) i++;
    if (i > 0) memmove(str, str + i, strlen(str + i) + 1);
    i = strlen(str) - 1;
    while (i >= 0 && isspace((unsigned char)str[i])) str[i--] = '\0';
}

int split_args(char* str, char* args[]) {
    int count = 0;
    char* token = strtok(str, ",");
    while (token != NULL && count < MAX_ARGS) {
        trim(token);
        args[count++] = token;
        token = strtok(NULL, ",");
    }
    return count;
}

int main() {
    char line[MAX_LINE];
    char command[MAX_LINE];
    int offset;
    int only_whitespace;
    int i;
    char* args[MAX_ARGS];

    prompt();
    while (fgets(line, MAX_LINE, stdin) != NULL) {
        printf("You entered: %s", line);

        line[strcspn(line, "\n")] = '\0';

        only_whitespace = 1;
        for (i = 0; line[i] != '\0'; i++) {
            if (!isspace((unsigned char)line[i])) {
                only_whitespace = 0;
                break;
            }
        }
        if (only_whitespace) {
            prompt();
            continue;
        }

        if (sscanf(line, "%s%n", command, &offset) != 1) {
            printf("Invalid command format.\n");
            prompt();
            continue;
        }

        trim(command);

        if (strcmp(command, "stop") == 0) {
            if (line[offset] != '\0' && !isspace((unsigned char)line[offset])) {
                printf("Extraneous text after end of command\n");
            } else {
                printf("Program terminated.\n");
                break;
            }
        } else {
            char* args_str = line + offset;
            int argc = split_args(args_str, args);
            mat *m1, *m2, *m3;
            double numbers[SIZE * SIZE];

            if (strcmp(command, "read_mat") == 0) {
                if (argc < 1) {
                    printf("Missing matrix name\n");
                } else {
                    m1 = get_mat_by_name(args[0]);
                    if (!m1) printf("Undefined matrix name\n");
                    else {
                        for (i = 1; i < argc && i <= SIZE * SIZE; i++) {
                            numbers[i - 1] = atof(args[i]);
                        }
                        read_mat(m1, numbers, argc - 1);
                    }
                }
            } else if (strcmp(command, "print_mat") == 0) {
                if (argc != 1) {
                    printf("Incorrect number of arguments\n");
                } else {
                    m1 = get_mat_by_name(args[0]);
                    if (!m1) printf("Undefined matrix name\n");
                    else print_mat(m1);
                }
            } else if (strcmp(command, "add_mat") == 0 || strcmp(command, "sub_mat") == 0 || strcmp(command, "mul_mat") == 0) {
                if (argc != 3) {
                    printf("Incorrect number of arguments\n");
                } else {
                    m1 = get_mat_by_name(args[0]);
                    m2 = get_mat_by_name(args[1]);
                    m3 = get_mat_by_name(args[2]);
                    if (!m1 || !m2 || !m3) printf("Undefined matrix name\n");
                    else if (strcmp(command, "add_mat") == 0) add_mat(m2, m3, m1);
                    else if (strcmp(command, "sub_mat") == 0) sub_mat(m2, m3, m1);
                    else mul_mat(m2, m3, m1);
                }
            } else if (strcmp(command, "mul_scalar") == 0) {
                if (argc != 3) {
                    printf("Incorrect number of arguments\n");
                } else {
                    m1 = get_mat_by_name(args[0]);
                    m2 = get_mat_by_name(args[2]);
                    if (!m1 || !m2) printf("Undefined matrix name\n");
                    else mul_scalar(m2, atof(args[1]), m1);
                }
            } else if (strcmp(command, "trans_mat") == 0) {
                if (argc != 2) {
                    printf("Incorrect number of arguments\n");
                } else {
                    m1 = get_mat_by_name(args[0]);
                    m2 = get_mat_by_name(args[1]);
                    if (!m1 || !m2) printf("Undefined matrix name\n");
                    else trans_mat(m2, m1);
                }
            } else {
                printf("Undefined command name\n");
            }
        }

        prompt();
    }

    if (feof(stdin)) {
        printf("EOF encountered without 'stop' command.\n");
    }

    return 0;
}
