#include <math.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_statistics.h>

void mean_var_est(double *par, int N, double *val);

int main(){
    double par[2] = {1, 2};  // True mean and standard deviation
    int N = 10;  // Sample size
    double val[2]; // estimated mean and std

    mean_var_est(par, N, val);

    return 0;

}

void mean_var_est(double *par, int N, double *val){
    gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937); // Define a random number
    long seed = time(NULL) * getpid();
    gsl_rng_set(r, seed); // Intialise random number with a seed

    double *v;
    v = malloc(N * sizeof(double));

    int i;

    // Generate N normally distributed values
    for(i = 0; i < N; i++){
        v[i] = par[0] + gsl_ran_gaussian(r, par[1]);
    }  

    val[0] = gsl_stats_mean(v, 1, N);
    val[1] = sqrt(gsl_stats_variance(v, 1, N));

    printf("%f %f \n", val[0], val[1]);
}
