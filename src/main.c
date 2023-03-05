#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "figures.h"

//======/прототипы функций/==========
_Bool inp_from_file(int argc, char **argv, char *str, int *strl); // ввод из файла
void inp_from_kb(char *str, int *strl); // ввод с клавиатуры
short fig_name_check(char *str, int *i, char *check_mas, int ch_masl); // проверяет имя фигуры
int num_check(char* str, int *i, int* column, _Bool negative); // проверяет число ли строка					
void print_wrong_string(char* str, int i_print, int i); // вывод ошибки
_Bool syntax_check(char *str, int strl, Circle *c_mas, int *c_masl, Triangle *t_mas, int *t_masl);					      

int main(int argc, char *argv[]) 
{
	char str[1000]; // обраюатываемая строка
  	int str_size = 0;   // его размер
  	if (argc == 1) // если размер массива с переданными атрибутами командной строки состоит из одного элемента- самого запуска программы
    		inp_from_kb(str, &str_size); // ввод с клавиатуры
  	else if (inp_from_file(argc, argv, str, &str_size)) // если не удалось считать строку из файла
    		return 1;
	int circle_mas_size = 0, triangle_mas_size = 0; // размеры массивов с индексами объектов фигур
  	Circle circle_mas [100]; 
  	Triangle triangle_mas [100];
  	syntax_check(str, str_size, circle_mas, &circle_mas_size, triangle_mas, &triangle_mas_size);
  	printf("============================\n");
	printf("корректно введенные фигуры\n");
  	for (int i = 0; i < circle_mas_size; i++)
    		printf("circle (%d %d, %f)\n", circle_mas[i].point1.x, circle_mas[i].point1.y, circle_mas[i].radius);
	return 0;
}
