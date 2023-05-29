//reference:  
//https://stackoverflow.com/questions/35853776/c-passing-pointer-to-pointer-to-a-function-and-using-malloc

#include <stdio.h>
#include <stdlib.h>

int scan_in(int***, int***, int**);

int main() {

    int i, 
        cases = 0, 
        *armies = NULL, 
        **arr_atk = {NULL}, 
        **arr_def = {NULL};

    if ((cases = scan_in(&arr_atk, &arr_def, &armies)) < 1) {
        fprintf(stderr, "error: invalid value for cases returned.\n");
        return 1;
    }

    printf ("\n cases         : %d\n", cases);
    printf (" arr_atk[1][2] : %d\n", arr_atk[1][2]);
    printf (" arr_def[0][1] : %d\n\n", arr_def[0][1]);

    for (i = 0; i < cases; ++i) {
        if (arr_atk[i]) free(arr_atk[i]);
        if (arr_def[i]) free(arr_def[i]);
    }

    if (arr_atk) free(arr_atk);
    if (arr_def) free(arr_def);
    if (armies)  free(armies);

    return 0;
}

int scan_in(int*** arr_atk, int*** arr_def, int** armies) {
    int i, j, cases;

    scanf("%d", &cases);

    // printf("%zu %zu %zu\n", sizeof(***arr_atk), sizeof(**arr_atk), sizeof(*armies));
    
    *arr_atk = malloc( sizeof(**arr_atk) * cases);
    *arr_def = malloc( sizeof(**arr_def) * cases);
    *armies  = malloc( sizeof(*armies)   * cases);

    for (i = 0; i < cases; ++i) {
        if (scanf("%d", &(*armies)[i]) != 1) {
            fprintf(stderr, "scan_in() error: input failure.\n");
            return 0;
        }

        (*arr_atk)[i] = malloc( sizeof(***arr_atk) * (*armies)[i]);
        (*arr_def)[i] = malloc( sizeof(***arr_def) * (*armies)[i]);

        for (j = 0; j < (*armies)[i]; ++j) {
            if (scanf("%d", &(*arr_atk)[i][j]) != 1) {
                fprintf(stderr, "scan_in() error: input failure.\n");
                return 0;
            }
        }

        for (j = 0; j < (*armies)[i]; ++j) {
            if (scanf("%d", &(*arr_def)[i][j]) != 1) {
                fprintf(stderr, "scan_in() error: input failure.\n");
                return 0;
            }
        }
    }

    return cases;
}