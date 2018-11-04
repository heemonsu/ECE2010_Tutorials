#include "mex.h"

#include <stdio.h>
#include <time.h>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){

    // Initialise variables
    long iters = 16000000;
    float sum = 0;
          
    float sec = 0.0;
        
    int reps = 10;
          
    for(int i=0; i<reps; i++){
        // Timing variables
        clock_t start = clock(), diff;
         
        for(int r=0; r<1000; r++){
            for(int c=0; c<iters; c++){
                sum += c * 3.14159;
            }
        }
          
        diff = clock() - start;
    sec += (float)diff / CLOCKS_PER_SEC;
    }

    float mean_sec = sec/reps;
         
    plhs[0] = mxCreateDoubleScalar(mean_sec);
}
