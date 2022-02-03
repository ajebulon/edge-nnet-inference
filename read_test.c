#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char filename[64] = "tests/weights_or.txt";
    FILE *f;

    if ((f = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error- Unable to open %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // int c;
    // bool row_start = false;
    // bool col_start = false;
    // char str_float[64];
    // int str_float_idx = 0;
    // float real_float;
    // while ((c = fgetc(f)) != EOF) {
    //     printf("%c", (char)c);

    //     if (c == '[') {
    //         if (!row_start) { // COL has not started
    //             row_start = true;
    //             printf("\n\t>\n");
    //             continue;
    //         } else { // Start COL when [ is found if ROW already start
    //             col_start = true;
    //             printf("\n\t\t>\n");
    //             continue;
    //         }
    //     } else if (c == ']') {
    //         if (col_start) { // Stop processing COL-wise
    //             col_start = false;
    //             printf("\n\t\t<\n");

    //             real_float = atof(str_float);
    //             printf("\nval: %.6f\n\n", real_float);
    //             memset(str_float, 0, 64);
    //             str_float_idx = 0;

    //             continue;
    //         } else { // Stop processing ROW
    //             row_start = false;
    //             printf("  <\n");


    //             continue;
    //         }
    // }

    int c;
    bool group_start = false;
    bool array_start = false;
    char str_float[64];
    int str_float_idx = 0;
    float real_float;
    int array_cnt = 0;

    while ((c = fgetc(f)) != EOF) {
        printf("%c", (char)c);

        if (c == '[') {
            if (!group_start) {
                group_start = true;
                printf("  >\n");
                continue;
            } else {
                array_start = true;
                printf("    >>\n");
                continue;
            }
        } else if (c == ',' || c == ']') {
            real_float = atof(str_float);
            printf("\nval: %.6f\n\n", real_float);
            memset(str_float, 0, 64);
            str_float_idx = 0;
        } else if (c == ']') {
            if (array_start) {                
                array_start = false;
                printf("    <<\n");
                continue;
            } else {
                group_start = false;
                printf("  <\n");
                continue;
            }
        } else if (c == '\n') {
            array_start = false;
            group_start = false;
            memset(str_float, 0, 64);
            str_float_idx = 0;
            continue;
        } else {
            str_float[str_float_idx] = c;
            str_float_idx++;
        }
    }

    return 0;
}