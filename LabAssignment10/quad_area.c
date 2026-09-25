#include <math.h>
#include "quad.h"
 
double triangle_area(double ax, double ay, double bx, double by, double cx, double cy) {
    double abx = bx - ax, aby = by - ay;
    double acx = cx - ax, acy = cy - ay;
    double cross = abx * acy - aby * acx;
    return 0.5 * fabs(cross);
}
 
double quad_area(quad q) {
    double area1 = triangle_area(q.x[0], q.y[0], q.x[1], q.y[1], q.x[2], q.y[2]);
    double area2 = triangle_area(q.x[0], q.y[0], q.x[2], q.y[2], q.x[3], q.y[3]);
    return area1 + area2;
}
