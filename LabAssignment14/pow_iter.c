#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

double pow_iter(const matrix* A, vector* v, const double tol, int kMax){

    const int size = v->size;
    //Normalize v
    for (int i = 1; i<= size; i++){
        vgetp(v, i) /= vector_norm(v);
    }
    //Calculate Av and v.
    vector Av = matrix_vector_mult(A, v);
    double lambda = vector_dot_mult(v, &Av);
    int stop = 0;
    int k = 0;
    double res = 1.0;

    while (stop == 0){
        k += 1;

        vector w = matrix_vector_mult(A, v);

        for (int i = 1; i<= size; i++){
            vgetp(v, i) = vget(w, i)/vector_norm(&w);
        }
        delete_vector(&w);
        // Solve lambda
        Av = matrix_vector_mult(A, v);
        lambda = vector_dot_mult(v, &Av);

        //residual calculation
        for(int i = 1; i <= size; i++){
            vget(Av, i) -= lambda*vgetp(v, i);
        }
        res = vector_norm(&Av);

        if (k > kMax || res < tol){
            stop = 1;
        }
        delete_vector(&Av);
    }

    return lambda;
}