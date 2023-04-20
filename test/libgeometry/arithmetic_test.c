#include <math.h>
#include <src/libgeometry/figures.h>
#include <src/libgeometry/arithmetic.h>
#include <thirdparty/ctest.h>

CTEST(arithmetic, perimeter_of_circle_test)
{
	const float radius = 3;
	float expected = 2 * M_PI * radius;
	float result = perimeter_of_circle(radius);
	ASSERT_EQUAL(expected, result);
}

CTEST(arithmetic, area_of_circle_test)
{
	const float radius = 3;
	float expected = M_PI * radius * radius;
	float result = area_of_circle(radius);
	ASSERT_EQUAL(expected, result);
}
CTEST(arithmetic, is_circles_intersect_test)
{
	// float is_circles_intersect(Circle circle1, Circle circle2)
	//  пересекаются
	_Bool expected = 1;
	Circle circle1 = {{1, 2}, 10};
	Circle circle2 = {{5, 2}, 7};
	_Bool result = is_circles_intersect(circle1, circle2);
	ASSERT_EQUAL(expected, result);

	// не пересекаются
	expected = 0;
	Circle circle3 = {{15, 20}, 7};
	Circle circle4 = {{1, 4}, 7};
	result = is_circles_intersect(circle3, circle4);
	ASSERT_EQUAL(expected, result);
}
