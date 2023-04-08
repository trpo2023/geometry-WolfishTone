#include <stdio.h>

_Bool inp_from_file(int argc, char** argv, char* str, int* str_size) // ввод из файла
{
	FILE* input_file;				       // открываемый файл
	for (int arg_index = 1; arg_index < argc; arg_index++) // если передано несколько файлов
	{
		if ((input_file = fopen(argv[arg_index], "r")) == 0) // если не удалось открыть файл
		{
			printf("inp_from_file ERROR: %s Не удалось открыть файл\n", argv[arg_index]);
			return 1; // код ошибки 1 не удалось открыть файл
		}
		char c;
		for (;;) {
			c = fgetc(input_file); // получаем очередной символ.работает как scanf
			if (c == -1) {
				if (feof(input_file) != 0)
					break;
				else {
					printf("\ninp_from_file ERROR: Ошибка чтения файла %s\n", argv[1]);
					break;
				}
			}
			str[*str_size] = c;
			*str_size += 1;
		}
		fclose(input_file); // закрываем файл
		*str_size += 1;
		if (arg_index != argc - 1)
			str[*str_size - 1] = '\n';
	}
	str[*str_size] = '\0'; // добавляем в конец символ конца строки, потом понадобится
	*str_size += 1;
	return 0;
}

void inp_from_kb(char* str, int* str_size) // ввод с клавиатуры
{
	puts("введите геометрические фигуры через Enter. для окончания ввода нажмите Ctrl+d");
	for (char a = 0; (a = getchar()) != -1;) {
		str[*str_size] = a;
		*str_size += 1;
	}
	*str_size += 1;
	str[*str_size - 1] = '\0'; // добавляем в конец символ конца строки, потом понадобится
}

