#include <math.h>

#include "figures.h"
#include "arithmetic.h"
#define sqr(x) (x)*(x)

float perimeter_of_circle(float radius)
{
	return 2 * M_PI * radius;
}

float area_of_circle(float radius)
{
	return M_PI * radius * radius;
}

_Bool is_circles_intersect(Circle circle1, Circle circle2)
{
	double length_between = sqrt(sqr(circle1.point1.x- circle2.point1.x) + sqr(circle1.point1.y- circle2.point1.y));
	if(circle1.radius+circle2.radius> length_between)
		return 1; //пересекаются
	return 0; // не пересекаются
}
