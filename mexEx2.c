#include "mex.h"

#include <math.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_statistics.h>
#include <gsl/gsl_cdf.h>

void mean_var_est(double *par, int N, double *val){
    gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);
    long seed = time(NULL) * getpid();
    gsl_rng_set(r, seed);

    double *v;
    v = malloc(N * sizeof(double));

    int i;
    for(i = 0; i < N; i++){
        v[i] = par[0] + gsl_ran_gaussian(r, par[1]);
    }

    val[0] = gsl_stats_mean(v, 1, N);
    val[1] = sqrt(gsl_stats_variance(v, 1, N));
}

// This is the gateway function which replaces the main routine
// plhs[] - the array of output values
// prhs[] - the array of input values

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    double *par, *val; // C variable declaration
    int N;
    
    par = mxGetPr(prhs[0]); // Sets par to be the first of the input values
    N = mxGetScalar(prhs[1]); // Set the value of N as the second input value

    plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL); // Creates a 1x2 matrix

    val = mxGetPr(plhs[0]);

    mean_var_est(par, N, val);
}

