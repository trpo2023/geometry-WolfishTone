#include <stdio.h>

#include <libgeometry/figures.h>
#include <libgeometry/input.h>
#include <libgeometry/lexer-parser.h>
#include <libgeometry/arithmetic.h>

int main(int argc, char* argv[])
{
	char str[1000];					    // обраюатываемая строка
	int str_size = 0;				    // его размер
	if (argc == 1)					    // если размер массива с переданными атрибутами командной строки состоит из одного элемента- самого запуска программы
		inp_from_kb(str, &str_size);		    // ввод с клавиатуры
	else if (inp_from_file(argc, argv, str, &str_size)) // если не удалось считать строку из файла
		return 1;
	int circle_mas_size = 0, triangle_mas_size = 0; // размеры массивов с индексами объектов фигур
	Circle circle_mas[100];
	Triangle triangle_mas[100];
	syntax_check(str, str_size, circle_mas, &circle_mas_size, triangle_mas, &triangle_mas_size, 0);
	printf("============================\n\n");
	printf("корректно введенные фигуры\n");
	for (int i = 0; i < circle_mas_size; i++) {
		printf("%2d| circle (%d %d, %f)\n", i + 1, circle_mas[i].point1.x, circle_mas[i].point1.y, circle_mas[i].radius);
		printf("\tperimeter: %f\n", perimeter_of_circle(circle_mas[i].radius));
		printf("\tarea: %f\n", area_of_circle(circle_mas[i].radius));
		printf("\tintersects:\n");
		for (int j = 0; j < circle_mas_size; j++)
			if (j != i)
				if (is_circles_intersect(circle_mas[i], circle_mas[j]))
					printf("\t %2d. circle\n", j + 1);
		printf("\n");
	}
	return 0;
}
