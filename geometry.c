#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define print_str(str, strl)                                                   \
  for (int i = 0; i < strl; printf("%c", str[i]), i++)
#define space_del(i) for (; str[i] != ' '; i++)
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
  printf("inp_from_file SUCCESS: %s успешно открыт\n", argv[1]);
  fgets(str, 255, inp_f);
  *strl = strlen(str);
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
_Bool syntax_check(char *str, int strl, Circle *c_mas, int *c_masl,
                   Triangle *t_mas, int *t_masl) {
  int column = 1; // номер строки
  int circ_size = 6;
  char *circle = "circle\0";
  int i = 0, j, k;
  for (; i < strl; i++) // идем по строке
  {
  bp:
    if (str[i] == 'c') //============ ищем круг
    {
      int f_f_n = fig_name_check(
          str, &i, circle, circ_size); // 0- ошибка ввода; 2- окончание строки
      if (f_f_n == 2) {
        printf("syntax_check ERROR(строка %d): строка закончилась на введении "
               "названия фигуры\n",
               column);
        return 0;
      }
      if (f_f_n == 0) {
        printf("syntax_check ERROR(строка %d): ошибка в названии фигуры. "
               "Ожидалосось: \"circle\", \"triangle\"\n",
               column);
        for (; str[i] != 10; i++) // до следующей строки
          if (str[i] == '\0') {
            printf("syntax_check ERROR(строка %d): строка закончилась на "
                   "введении названия фигуры\n",
                   column);
            return 0;
          }
        column++;
        goto bp;
      }
      printf("syntax_check SUCCESS(строка %d): название фигуры введено верно\n",
             column);
      for (; str[i] == ' '; i++)
        ; // пропуск пробелов

      if (str[i] != '(') //=================== ищем открывающую скобку
      {
        printf(
            "syntax_check ERROR(строка %d): ожидалась открывающая скобка '('\n",
            column);
        for (; str[i] != 10; i++) // до следующей строки
          if (str[i] == '\0') {
            printf("syntax_check ERROR(строка %d): строка закончилась на "
                   "введении открывающей скобки '('\n",
                   column);
            return 0;
          }
        column++;
        goto bp;
      }
      i++; // выйти за скобку
      printf(
          "syntax_check SUCCESS(строка %d): открывающая скобка введена верно\n",
          column);
      for (; str[i] == ' '; i++)
        ; // пропуск пробелов

      for (j = 0; j < 10; j++) //========================== ищем первое первый
                               //аргумент в скобках
        if (str[i] == j + 48)
          break;
      if (j == 10) {
        printf("syntax_check ERROR(строка %d): первый аргумент в скобках не "
               "число\n",
               column);
        for (; str[i] != 10; i++) {
          printf(" %d\n", i);
          if (str[i] == '\0') {
            printf("syntax_check ERROR(строка %d): строка закончилась на "
                   "введении первого аргумента в скобках\n",
                   column);
            return 0;
          }
        }
        column++;
        goto bp;
      }
      c_mas[*c_masl].point1.x = atoi(&str[i]);
      for (;;) {
        for (k = 0; k < 10; k++)
          if (str[i] == k + 48) {
            i++;
            break;
          }
        if (k == 10)
          break;
      }
      printf("syntax_check SUCCESS(строка %d): первый аргумент в скобках "
             "введен верно\n",
             column);
      for (; str[i] == ' '; i++)
        ; // пропуск пробелов

      for (j = 0; j < 10;
           j++) //========================== ищем второй аргумент в скобках
        if (str[i] == j + 48)
          break;
      if (j == 10) {
        if (str[i] == ',')
          printf("syntax_check ERROR(строка %d): ожидалось число\n", column);
        else
          printf("syntax_check ERROR(строка %d): второй аргумент в скобках не "
                 "число\n",
                 column);
        for (; str[i] != 10; i++)
          if (str[i] == '\0') {
            printf("syntax_check ERROR(строка %d): строка закончилась на "
                   "введении второго аргумента в скобках\n",
                   column);
            return 0;
          }
        column++;
        goto bp;
      }
      c_mas[*c_masl].point1.y = atoi(&str[i]);
      for (;;) {
        for (k = 0; k < 10; k++)
          if (str[i] == k + 48) {
            i++;
            break;
          }
        if (k == 10)
          break;
      }
      printf("syntax_check SUCCESS(строка %d): второй аргумент в скобках "
             "введен верно\n",
             column);
      for (; str[i] == ' '; i++)
        ; // пропуск пробелов

      if (str[i] != ',') //=================== ищем запятую
      {
        printf("syntax_check ERROR(строка %d): ожидалась запятая ','\n",
               column);
        for (; str[i] != 10; i++) // до следующей строки
          if (str[i] == '\0') {
            printf("syntax_check ERROR(строка %d): строка закончилась на "
                   "введении запятой ','\n",
                   column);
            return 0;
          }
        column++;
        goto bp;
      }
      i++; // выйти за скобку
      printf("syntax_check SUCCESS(строка %d): запятая введена верно\n",
             column);
      for (; str[i] == ' '; i++)
        ; // пропуск пробелов

      for (j = 0; j < 10;
           j++) //========================== ищем третий аргумент в скобках
        if (str[i] == j + 48)
          break;
      if (j == 10) {
        if (str[i] == ',')
          printf("syntax_check ERROR(строка %d): ожидалось число\n", column);
        else
          printf("syntax_check ERROR(строка %d): третий аргумент в скобках не "
                 "число\n",
                 column);
        for (; str[i] != 10; i++) {
          printf(" %d\n", i);
          if (str[i] == '\0') {
            printf("syntax_check ERROR(строка %d): строка закончилась на "
                   "введении третьего аргумента в скобках\n",
                   column);
            return 0;
          }
        }
        column++;
        goto bp;
      }
      c_mas[*c_masl].radius = atoi(&str[i]);
      for (;;) {
        for (k = 0; k < 10; k++)
          if (str[i] == k + 48) {
            i++;
            break;
          }
        if (k == 10)
          break;
      }
      printf("syntax_check SUCCESS(строка %d): третий аргумент в скобках "
             "введен верно\n",
             column);
      for (; str[i] == ' '; i++)
        ; // пропуск пробелов

      if (str[i] != ')') //=================== ищем закрывающую скобку
      {
        printf(
            "syntax_check ERROR(строка %d): ожидалась закрывающая скобка ')'\n",
            column);
        for (; str[i] != 10; i++) // до следующей строки
          if (str[i] == '\0') {
            printf("syntax_check ERROR(строка %d): строка закончилась на "
                   "введении закрывающей скобки ')'\n",
                   column);
            return 0;
          }
        column++;
        goto bp;
      }
      i++; // выйти за скобку
      printf(
          "syntax_check SUCCESS(строка %d): закрывающая скобка введена верно\n",
          column);
      column++;
      *c_masl += 1;
      printf("круг №%d\n", *c_masl);
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
  Circle c_mas[20];
  Triangle t_mas[20];
  printf("====================================\n");
  syntax_check(str, strl, c_mas, &c_masl, t_mas, &t_masl);
  for (int i = 0; i < c_masl; i++)
    printf("circle (%d %d, %d)\n", c_mas[i].point1.x, c_mas[i].point1.y,
           c_mas[i].radius);
}
