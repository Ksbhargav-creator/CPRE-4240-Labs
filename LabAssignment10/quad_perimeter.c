#include <math.h>
#include "quad.h"

double distance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

double quad_perimeter(quad q) {
    double perimeter = 0.0;

    for (int i = 0; i < 4; i++) {
        int next = (i + 1) % 4;
        perimeter += distance(q.x[i], q.y[i], q.x[next], q.y[next]);
    }

    return perimeter;
}
