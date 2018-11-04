#include "mex.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

double * dot_product(double *vector_1, double *vector_2, int N);
void print_array(double *array, int N);

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    double *vector_1, *vector_2;
    int N;

    vector_1 = mxGetPr(prhs[0]);
    vector_2 = mxGetPr(prhs[1]);

    N = mxGetScalar(prhs[2]);

    plhs[0] = mxCreateDoubleMatrix(1, N, mxREAL);

    double *output;
    output = dot_product(vector_1, vector_2, N);

    plhs[0] = mxCreateDoubleMatrix(1, N, mxREAL);
    memcpy(mxGetPr(plhs[0]), output, N*sizeof(double));

    free(output);
}

void print_array(double *array, int N){
    for(int i = 0; i < N; i++){
        printf("%f ", array[i]);
    }
    printf("\n");
}

double * dot_product(double *vector_1, double *vector_2, int N){
    
    double *output;
    output = malloc(N * sizeof(double));

    for(int i = 0; i < N; i++){
        output[i] = vector_1[i] * vector_2[i];
    }

    return output;
}


