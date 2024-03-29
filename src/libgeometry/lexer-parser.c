#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "figures.h"
#include "lexer-parser.h"

//== для num_check
#define NUMBERS 10
#define NEGATIVE 1	    // если проверяемое число является отрицательным
#define POSITIVE 0	    // если проверяемое число является положительным
#define FLOAT 1		    // если проверяемое число предполагается рациональным
#define INT 0		    // если проверяемое число предполагается целым
#define ASCII_COOFICIENT 48 // предназначено для нахождения кода ASCII символа числа

short fig_name_check(char* str, int* i, char* figure, int figure_size) // проверяет имя фигуры
{
	for (int j = 0; j < figure_size; j++, *i += 1) {
		if (str[*i] == '\0' && *i != figure_size)
			return 2; // строка закончилась
		if (str[*i] != figure[j])
			return 1; // стоки не равны
	}
	return 0;
}

int num_check(char* str, int* i, int* column, _Bool is_negative, _Bool is_float) // проверяет число ли строка is_test- для тестов
{
	int j, k, i_base;
	int num_i = (str[*i] == '-' && is_negative) ? (*i + 1) : (*i); // проверка
	for (j = 0; j < NUMBERS; j++)
		if (str[num_i] == j + ASCII_COOFICIENT)
			break;
	if (j == 10) {
		for (; str[*i] != '\n'; *i += 1)
			if (str[*i] == '\0')
				return 2; // конец строки
		*column += 1;
		return 0; // не число
	}
	i_base = *i; // индекс передающийся atoi для перевода из строки в число
	*i += 1;
	for (;;) {
		if (str[*i] == '.' && is_float) {
			is_float = 0;
			*i += 1;
		}
		for (k = 0; k < NUMBERS; k++) // скипаем остатки числа
			if (str[*i] == k + ASCII_COOFICIENT) {
				*i += 1;
				break;
			}
		if (k == 10) // если символ не цифра- число кончилось
			break;
	}
	return i_base; // число введено верно i-base- первый байт числа
}

void print_wrong_string(char* str, int error_i, int i, int column, char* error_messange)
{
	for (int k = error_i; str[k] != '\n'; k++) // вывод провинившейся перед синтаксисом строки
		printf("%c", str[k]);
	printf("\n");
	for (int k = error_i; k < i; k++) // пробелы и стрелочка для указания на ошибку
		printf(" ");
	printf("^\n");
	printf("syntax_check ERROR(строка %d): %s\n", column, error_messange);
}

_Bool syntax_check(char* str, int str_size, Circle* circle_mas, int* circle_mas_size, Triangle* triangle_mas, int* triangle_mas_size, _Bool is_test)
{
	int column = 1;		   // номер строки
	int i = 0, num_i, error_i; // i_base- первый байт числа error_i- индекс ошибки в строке
	for (; i < str_size; i++)  // идем по строке
	{
		error_i = i;
		if (str[i] == 'c') //============ ищем круг
		{
			short is_figure = fig_name_check(str, &i, "circle\0", 6); // 1- ошибка ввода; 2- конец строки
			if (is_figure == 2)
				return 0;
			if (is_figure == 1) {
				if (!is_test)
					print_wrong_string(str, error_i, i, column, "ошибка в названии фигуры. Ожидалосось: \"circle\", \"triangle\"\0");
				for (; str[i] != '\n'; i++) // до следующей строки
					if (str[i] == '\0')
						return 0;
				column++;
				continue;
			}
			for (; str[i] == ' '; i++)
				;	   // пропуск пробелов
			if (str[i] != '(') //=================== ищем открывающую скобку
			{
				if (!is_test)
					print_wrong_string(str, error_i, i, column, "ожидалась открывающая скобка '('\0");
				for (; str[i] != '\n'; i++) // до следующей строки
					if (str[i] == '\0')
						return 0;
				column++;
				continue;
			}
			i++; // выйти за скобку
			for (; str[i] == ' '; i++)
				; // пропуск пробелов

			for (short g = 1; g <= 2; g++) // ================= ищем первые 2 аргумента в скобках
			{
				num_i = num_check(str, &i, &column, NEGATIVE, INT);
				if (num_i) {
					if (num_i == 2)
						return 0;
					else {
						if (g == 1)
							circle_mas[*circle_mas_size].point1.x = atoi(&str[num_i]);
						else
							circle_mas[*circle_mas_size].point1.y = atoi(&str[num_i]);
					}
				} else {
					if (!is_test)
						print_wrong_string(str, error_i, i, column, "первый аргумент в скобках не число\0");
					continue;
				}
				for (; str[i] == ' '; i++)
					; // пропуск пробелов
			}

			if (str[i] != ',') //=================== ищем запятую
			{
				if (!is_test)
					print_wrong_string(str, error_i, i, column, "ожидалась запятая ','\0");
				for (; str[i] != '\n'; i++) // до следующей строки
					if (str[i] == '\0')
						return 0;
				column++;
				continue;
			}
			i++; // выйти за запятую
			for (; str[i] == ' '; i++)
				; // пропуск пробелов

			num_i = num_check(str, &i, &column, POSITIVE, FLOAT); //========================== ищем третий аргумент в скобках
			if (num_i) {
				if (num_i == 2)
					return 0;
				else
					circle_mas[*circle_mas_size].radius = atof(&str[num_i]);
			} else {
				if (!is_test)
					print_wrong_string(str, error_i, i, column, "третий аргумент в скобках не число\0");
				continue;
			}
			for (; str[i] == ' '; i++)
				; // пропуск пробелов

			if (str[i] != ')') //=================== ищем закрывающую скобку
			{
				if (!is_test)
					print_wrong_string(str, error_i, i, column, "ожидалась закрывающая скобка ')'\0");
				for (; str[i] != '\n'; i++) // до следующей строки
					if (str[i] == '\0')
						return 0;
				column++;
				continue;
			}
			i++; // выйти за скобку
			column++;
			*circle_mas_size += 1;
		}
		if (str[i] == 't')
			printf("comming soon\n");
	}
	return 1;
}
