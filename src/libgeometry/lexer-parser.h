#pragma once

short fig_name_check(char* str, int* i, char* figure, int figure_size);
int num_check(char* str, int* i, int* column, _Bool is_negative, _Bool is_float);
void print_wrong_string(char* str, int error_i, int i, int column, char* error_messange);
_Bool syntax_check(char* str, int str_size, Circle* circle_mas, int* circle_mas_size, Triangle* triangle_mas, int* triangle_mas_size, _Bool is_test);
