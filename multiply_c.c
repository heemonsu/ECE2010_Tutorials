#include <stdlib.h>
#include <stdio.h>

// Declaration of the vector product function
double * dot_product(double *vector_1, double *vector_2, int N);

// Vector fucntions
void print_array(double *array, int N);


int main(){
    double vector_1[] = {0.5, 0.6, 0.7};
    double vector_2[] = {1.2, 1.3, 1.4};

    int N = (int) (sizeof(vector_1)/sizeof(vector_1[0]));
    
    double *output;

    output = dot_product(vector_1, vector_2, N);
   
    print_array(output, N);
    return 0;
}


// Print the value of a double array
void print_array(double *array, int N){

    for(int i = 0; i < N; i++){
        printf("%f ", array[i]);
    }
    printf("\n");
}

// Give the dot product of two vector
double * dot_product(double *vector_1, double *vector_2, int N){
    
    double *output;
    output = malloc(N * sizeof(double));

    for(int i = 0; i < N; i++){
        output[i] = vector_1[i] * vector_2[i];
    }

    return output;
}

