#include <stdio.h>
#include <stdlib.h>
#include "quad.h"

int main()
{
    printf("\nI am in the **main** function.\n");
    
    quad q;

    q.x[0] = 0.0; q.y[0] = 0.0;
    q.x[1] = 0.0; q.y[1] = 1.0;
    q.x[2] = 1.0; q.y[2] = 1.0;
    q.x[3] = 1.0; q.y[3] = 0.0;

    double quad_perimeter(quad q);
    double perimeter = 0.0;
    perimeter = quad_perimeter(q);

    double quad_area(quad q);
    double area = 0.0;
    area = quad_area(q);

    void quad_angles(quad q, double angles[4]);
    double angles[4];
    quad_angles(q, angles);

    printf("\nResults:\n");
    printf("The area is %f\n", area);
    printf("The perimeter is %f\n", perimeter);
    printf("The angles are: %f, %f, %f, %f\n", angles[0], angles[1], angles[2], angles[3]);

    return 0;
};
