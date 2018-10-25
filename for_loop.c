#include <stdio.h>
#include <time.h>

int main()
{
    // Initialise variables
    long iters = 16000000;
    float sum = 0.0;

    float sec = 0.0;

    for(int i=0; i<10; i++){
        // Timing variables
        clock_t start = clock(), diff;

        for(int r=0; r<1000; r++){
            for(int c=0; c<iters; c++){
                sum += c*3.1415;
            }
        }

        diff = clock() - start;
        sec += (float)diff / CLOCKS_PER_SEC;
    }
    float mean_sec = sec/10.0;
    printf("Average time take %f seconds \n", mean_sec);

    return 0;
}
