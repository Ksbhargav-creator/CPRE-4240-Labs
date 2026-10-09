#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

double ray_quot_iter(const matrix* A, vector* v, const double tol, int kMax){

    
    const int size = v->size;
    // Normalize v
    for (int i = 1; i<= size; i++){
        vgetp(v, i) /= vector_norm(v);
    }
    //Calculate Av and lambda
    vector Av = matrix_vector_mult(A, v);
    double lambda = vector_dot_mult(v, &Av);

    int stop = 0;
    int k = 0;
    double res = 1.0;

    while (stop == 0){
        k += 1;

        //Solve (A - lambda*I)*w = v
        matrix B = matrix_copy(A);
        for (int i = 1; i <= size; i++){
            mget(B,i,i) = mgetp(A, i, i) - lambda;
        } 
        vector vc = vector_copy(v);

        vector w = solve(&B,&vc);
        delete_vector(&vc);
        delete_matrix(&B);

        for (int i = 1; i<= size; i++){
            vgetp(v, i) = vget(w, i)/vector_norm(&w);
        }
        delete_vector(&w);

        vector Av = matrix_vector_mult(A, v);
        lambda = vector_dot_mult(v, &Av);

        //residual calculation
        for(int i = 1; i <= size; i++){
            vget(Av, i) -= lambda*vgetp(v, i);
        }
        res = vector_norm(&Av);

        if (k == kMax || res < tol){
            stop = 1;
        }
        
    }

    return lambda;
}