#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void number_to_words(int num, FILE* out) {
    const char* ones[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
                          "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen",
                          "seventeen", "eighteen", "nineteen"};
    const char* tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    if (num < 20) {
        fprintf(out, "%s\n", ones[num]);
    } else {
        int t = num / 10;
        int o = num % 10;
        if (o == 0) {
            fprintf(out, "%s\n", tens[t]);
        } else {
            fprintf(out, "%s %s\n", tens[t], ones[o]);
        }
    }
}

int main(int argc, char* argv[]) {
    FILE *in = stdin, *out = stdout;
    int num;

    if (argc > 3) {
        fprintf(stderr, "Error: too many arguments. Usage: %s [input_file] [output_file]\n", argv[0]);
        return 1;
    }
    if (argc >= 2) {
        in = fopen(argv[1], "r");
        if (!in) {
            fprintf(stderr, "Error opening input file '%s': %s\n", argv[1], strerror(errno));
            return 1;
        }
    }
    if (argc == 3) {
        out = fopen(argv[2], "w");
        if (!out) {
            fprintf(stderr, "Error opening output file '%s': %s\n", argv[2], strerror(errno));
            if (in != stdin) fclose(in);
            return 1;
        }
    }

    while (fscanf(in, "%d", &num) == 1) {
        if (num >= 0 && num <= 99) {
            number_to_words(num, out);
        }
    }

    if (in != stdin) fclose(in);
    if (out != stdout) fclose(out);
    return 0;
}
