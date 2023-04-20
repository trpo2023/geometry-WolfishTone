#include <thirdparty/ctest.h>

#include <src/libgeometry/figures.h>
#include <src/libgeometry/lexer-parser.h>

CTEST(lexer_parser, fig_name_check_test)
{
	int i = 0;
	char* fig = "circle\0";
	int fig_size = 6;

	// верно введенна фигура
	short expected = 0;
	char* str1 = "circle \0";
	short result = fig_name_check(str1, &i, fig, fig_size);
	ASSERT_EQUAL(expected, result);

	// не верно введенная фигура
	expected = 1;
	char* str2 = "sircle \0";
	i = 0;
	result = fig_name_check(str2, &i, fig, fig_size);
	ASSERT_EQUAL(expected, result);

	// конец анализируемой строки
	expected = 2;
	char* str4 = "cir\0";
	i = 0;
	result = fig_name_check(str4, &i, fig, fig_size);
	ASSERT_EQUAL(expected, result);
}
CTEST(lexer_parser, num_check_test)
{
	int column = 0;
	int i = 1;

	// целое положительное число
	int expected = 1;
	int is_negative = 0;
	int is_float = 0;
	char* str = "123 \0";
	int result = num_check(str, &i, &column, is_negative, is_float);
	ASSERT_EQUAL(expected, result);

	// целое отрицательное число
	i = 1;
	is_negative = 1;
	is_float = 0;
	str = " -123 \0";
	result = num_check(str, &i, &column, is_negative, is_float);
	ASSERT_EQUAL(expected, result);

	// положительное число с плавающей точкой
	i = 1;
	is_negative = 0;
	is_float = 1;
	str = " 1.23 \0";
	result = num_check(str, &i, &column, is_negative, is_float);
	ASSERT_EQUAL(expected, result);

	// отрицательное число с плавающей точкой
	i = 1;
	is_negative = 1;
	is_float = 1;
	str = " -1.23 \0";
	result = num_check(str, &i, &column, is_negative, is_float);
	ASSERT_EQUAL(expected, result);

	// число содержащее недопустимый символ в начале
	expected = 0;
	i = 1;
	is_negative = 0;
	is_float = 0;
	str = " e123 \n\0";
	result = num_check(str, &i, &column, is_negative, is_float);
	ASSERT_EQUAL(expected, result);

	// целое отрицательное число c больше чем одним минусом
	i = 1;
	is_negative = 1;
	is_float = 0;
	str = " --123 \n\0";
	result = num_check(str, &i, &column, is_negative, is_float);
	ASSERT_EQUAL(expected, result);
}

CTEST(lexer_parser, syntax_check_test)
{
	Circle circle_mas[100];
	Triangle triangle_mas[100];
	int circle_mas_size = 0, triangle_mas_size = 0;

	// строка введена полностью
	_Bool expected = 1;
	char* str = "circle (1 2 ,3.4)\0";
	int str_size = 17;
	_Bool result = syntax_check(str, str_size, circle_mas, &circle_mas_size, triangle_mas, &triangle_mas_size, 1);
	ASSERT_EQUAL(expected, result);

	// строка закончилась на введении фигуры
	expected = 0;
	str = "circle \0";
	str_size = 7;
	result = syntax_check(str, str_size, circle_mas, &circle_mas_size, triangle_mas, &triangle_mas_size, 1);
	ASSERT_EQUAL(expected, result);

	// строка закончилась на введении открывающей скобки
	str = "circle \0";
	str_size = 7;
	result = syntax_check(str, str_size, circle_mas, &circle_mas_size, triangle_mas, &triangle_mas_size, 1);

	ASSERT_EQUAL(expected, result);

	// строка закончилась на введении первого аргумента в скобках
	str = "circle ( e\0";
	str_size = 10;
	result = syntax_check(str, str_size, circle_mas, &circle_mas_size, triangle_mas, &triangle_mas_size, 1);

	ASSERT_EQUAL(expected, result);

	// строка закончилась на введении второго аргумента в скобках
	str = "circle (1 e \0";
	str_size = 12;
	result = syntax_check(str, str_size, circle_mas, &circle_mas_size, triangle_mas, &triangle_mas_size, 1);

	ASSERT_EQUAL(expected, result);

	// строка закончилась на введении запятой
	str = "circle (1 2 \0";
	str_size = 12;
	result = syntax_check(str, str_size, circle_mas, &circle_mas_size, triangle_mas, &triangle_mas_size, 1);

	ASSERT_EQUAL(expected, result);

	// строка закончилась на введении третьего аргумента в скобках
	str = "circle (1 2 ,\0";
	str_size = 13;
	result = syntax_check(str, str_size, circle_mas, &circle_mas_size, triangle_mas, &triangle_mas_size, 1);

	ASSERT_EQUAL(expected, result);

	// строка закончилась на введении закрывающей скобки
	str = "circle (1 2 ,3.4 \0";
	str_size = 17;
	result = syntax_check(str, str_size, circle_mas, &circle_mas_size, triangle_mas, &triangle_mas_size, 1);

	ASSERT_EQUAL(expected, result);
}
