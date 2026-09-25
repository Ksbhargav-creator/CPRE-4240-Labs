#include <math.h>
#include "quad.h"
 
void quad_angles(quad q, double angles[4]) {
    for (int i = 0; i < 4; i++) {
        int prev = (i + 3) % 4;
        int next = (i + 1) % 4;
 
        double v1x = q.x[prev] - q.x[i];
        double v1y = q.y[prev] - q.y[i];
        double v2x = q.x[next] - q.x[i];
        double v2y = q.y[next] - q.y[i];
 
        double cross = v1x * v2y - v1y * v2x;
        double dot   = v1x * v2x + v1y * v2y;
 
        double mag1 = sqrt(v1x * v1x + v1y * v1y);
        double mag2 = sqrt(v2x * v2x + v2y * v2y);
 
        double sin_theta = fabs(cross) / (mag1 * mag2);
 
        if (sin_theta > 1.0) sin_theta = 1.0;
        if (sin_theta < -1.0) sin_theta = -1.0;
 
        double theta = asin(sin_theta);
 
        if (dot < 0) {
            theta = M_PI - theta;
        }
 
        angles[i] = theta * 180.0 / M_PI;
    }
}
 
