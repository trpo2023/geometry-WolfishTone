#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define print_str(str, strl)                                                   \
  for (int i = 0; i < strl; printf("%c", str[i]), i++)
typedef struct {
  int x;
  int y;
} Coo;
typedef struct // 0
{
  Coo point1;
  int radius;
} Circle;
typedef struct // 1
{
  Coo point1; // повторяется
  Coo point2;
  Coo point3;
} Triangle;
_Bool inp_from_file(int argc, char **argv, char *str, int *strl) {
  if (argc != 2)
    return 0;
  FILE *inp_f;
  if ((inp_f = fopen(argv[1], "r")) == NULL) {
    printf("inp_from_file ERROR: %s Не удалось открыть файл\n", argv[1]);
    return 0;
  }
  if(inp_f== 0){
	printf("inp_from_file ERROR:файл  %s пуст\n", argv[1]);
  }
  char c;
  for(;;)
  {
		c = fgetc (inp_f);
		if (c == -1)
		{
			if ( feof (inp_f) != 0)
            			break;
        		 else
         		{
            			printf("\ninp_from_file ERROR: Ошибка чтения файла %s\n", argv[1]);
           			break;
         		}
      		}
		str[*strl]= c;
		*strl+=1;
   }
  fclose(inp_f);
  str[*strl] = '\0';
  *strl += 1;
  return 1;
}
void inp_from_kb(char *str, int *strl) {
  puts("введите геометрические фигуры через Enter. для окончания ввода нажмите "
       "Ctrl+d");
  for (char a = 0; (a = getchar()) != -1;) {
    str[*strl] = a;
    *strl += 1;
  }
  *strl += 1;
  str[*strl - 1] = '\0';
}
short fig_name_check(char *str, int *i, char *check_mas,
                     int ch_masl) // проверяет имя фигуры
{
  for (int j = 0; j < ch_masl; j++, *i += 1) {
    if (str[*i] == '\0' && *i != ch_masl)
      return 2;
    if (str[*i] != check_mas[j])
      return 0;
  }
  return 1;
}
int num_check(char* str, int *i, int* column, _Bool negative)
{
	int j, k, i_base;
	for (j = 0; j < 10; j++)
	{
		if(str[*i]== '-' && negative) // если нужно записать отрицательное число
			break;
		if (str[*i] == j + 48)
			break;
	}
	if (j == 10)
	{
		for (; str[*i] != 10; *i+=1) 
			if (str[*i] == '\0') 
				return 2; // конец строки
		*column+=1;
		return 0; // не число
	}
	i_base= *i;
	*i+=1;
	for (;;) 
	{
		for (k = 0; k < 10; k++)
			if (str[*i] == k + 48) 
			{
				*i+=1;
				break;
			}
		if (k == 10)
			break;
	}
	return i_base; // число введено верно i-base- первый байт числа
}
void print_string(char* str, int i_print, int i)
{
	for(int k= i_print;str[k]!=10;k++)
		printf("%c", str[k]);
	printf("\n");
	for(int k= i_print;k<i;k++)
		printf(" ");
	printf("^\n");
}
_Bool syntax_check(char *str, int strl, Circle *c_mas, int *c_masl,
                   Triangle *t_mas, int *t_masl) {
  int column = 1; // номер строки
  int circ_size = 6;
  char *circle = "circle\0";
  int i = 0, i_base, i_print;
  for (; i < strl; i++) // идем по строке
  {
bp: i_print= i;
    if (str[i] == 'c') //============ ищем круг
    {
      int f_f_n = fig_name_check(
          str, &i, circle, circ_size); // 0- ошибка ввода; 2- окончание строки
      if (f_f_n == 2) 
        return 0;
      if (f_f_n == 0) {
	print_string(str, i_print, i);
        printf("syntax_check ERROR(строка %d): ошибка в названии фигуры. "
               "Ожидалосось: \"circle\", \"triangle\"\n",
               column);
        for (; str[i] != 10; i++) // до следующей строки
          if (str[i] == '\0')
            return 0;
        column++;
        goto bp;
      }
      for (; str[i] == ' '; i++)
        ; // пропуск пробелов

      if (str[i] != '(') //=================== ищем открывающую скобку
      {
	print_string(str, i_print, i);
        printf(
            "syntax_check ERROR(строка %d): ожидалась открывающая скобка '('\n",
            column);
        for (; str[i] != 10; i++) // до следующей строки
          if (str[i] == '\0')
            return 0;
        column++;
        goto bp;
      }
      i++; // выйти за скобку
      for (; str[i] == ' '; i++)
        ; // пропуск пробелов

      i_base= num_check(str, &i, &column, 1);//========================== ищем первое первый аргумент в скобках
      if (i_base)
      {
	      if(i_base== 2)
                      return 0;
	      else
		      c_mas[*c_masl].point1.x = atoi(&str[i_base]);
      }
      else
      {
		print_string(str, i_print, i);
	      printf("syntax_check ERROR(строка %d): первый аргумент в скобках не "
              "число\n",
              column);
	      goto bp;
      }
      for (; str[i] == ' '; i++)
        ; // пропуск пробелов

      i_base= num_check(str, &i, &column, 1);//========================== ищем второй аргумент в скобках
      if (i_base)
      {
	      if(i_base== 2)
                      return 0;
	      else
		      c_mas[*c_masl].point1.y = atoi(&str[i_base]);
      }
      else
      {
		print_string(str, i_print, i);
	      printf("syntax_check ERROR(строка %d): второй аргумент в скобках не "
              "число\n",
              column);
	      goto bp;
      }
        for (; str[i] == ' '; i++)
        ; // пропуск пробелов

      if (str[i] != ',') //=================== ищем запятую
      {
	print_string(str, i_print, i);
        printf("syntax_check ERROR(строка %d): ожидалась запятая ','\n",
               column);
        for (; str[i] != 10; i++) // до следующей строки
          if (str[i] == '\0')
            return 0;
        column++;
        goto bp;
      }
      i++; // выйти за скобку
      for (; str[i] == ' '; i++)
        ; // пропуск пробелов

      i_base= num_check(str, &i, &column, 0);//========================== ищем третий аргумент в скобках
      if (i_base)
      {
	      if(i_base== 2)
                      return 0;
	      else
		      c_mas[*c_masl].radius = atoi(&str[i_base]);
      }
      else
      {
		print_string(str, i_print, i);
	      printf("syntax_check ERROR(строка %d): третий аргумент в скобках не "
              "число\n",
              column);
	      goto bp;
      }
      for (; str[i] == ' '; i++)
        ; // пропуск пробелов

      if (str[i] != ')') //=================== ищем закрывающую скобку
      {
	print_string(str, i_print, i);
        printf(
		            "syntax_check ERROR(строка %d): ожидалась закрывающая скобка ')'\n",
            column);
        for (; str[i] != 10; i++) // до следующей строки
          if (str[i] == '\0') 
            return 0;
        column++;
        goto bp;
      }
      i++; // выйти за скобку
      column++;
      *c_masl += 1;
    }
    if (str[i] == 't')
      printf("comming soon\n");
  }
  return 1;
}
int main(int argc, char *argv[]) {
  char str[1000]; // обраюатываемая строка
  int strl = 0;
  if (argc == 1)	
    inp_from_kb(str, &strl); // ввод с клавиатуры
  else if (!inp_from_file(argc, argv, str, &strl))
    return 0;
  int c_masl = 0, t_masl = 0; // массив с индексами объектов
  Circle c_mas[100];
  Triangle t_mas[100];
  syntax_check(str, strl, c_mas, &c_masl, t_mas, &t_masl);
  printf("корректно введенные фигуры\n");
  for (int i = 0; i < c_masl; i++)
    printf("circle (%d %d, %d)\n", c_mas[i].point1.x, c_mas[i].point1.y,
           c_mas[i].radius);
}
