#include <src/libgeometry/arithmetic.h>
#include <thirdparty/ctest.h>
#include <math.h>

CTEST(arithmetic, perimeter_of_circle_test)
{
	const float radius= 3;
	float expected= 2*M_PI*radius;
	float result = perimeter_of_circle(radius);
	ASSERT_EQUAL(expected, result);
}

CTEST(arithmetic, area_of_circle_test)
{
	const float radius= 3;
	float expected= M_PI*radius*radius;
	float result = area_of_circle(radius);
	ASSERT_EQUAL(expected, result);
}
