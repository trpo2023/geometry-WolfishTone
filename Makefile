.PHONY: all clean test bin/geometry input
all: show

bin/geometry: obj/src/geometry/main.o obj/src/libgeometry/libgeometry.a 	
	gcc -Wall -Werror $^ -o $@ -lm

obj/src/geometry/main.o: src/geometry/main.c
	gcc -Wall -Werror -c -MMD $<  -o $@ -I src

obj/src/libgeometry/libgeometry.a: obj/src/libgeometry/lexer-parser.o obj/src/libgeometry/arithmetic.o obj/src/libgeometry/input.o
	ar rcs $@ $^

obj/src/libgeometry/lexer-parser.o: src/libgeometry/lexer-parser.c
	gcc -Wall -Werror -c -MMD $< -o $@
obj/src/libgeometry/arithmetic.o: src/libgeometry/arithmetic.c
	gcc -Wall -Werror -c -MMD $< -o $@ #-lm
obj/src/libgeometry/input.o: src/libgeometry/input.c
	gcc -Wall -Werror -c -MMD $< -o $@



bin/geometry_test: obj/test/geometry/main.o obj/test/libgeometry/lexer-parser_test.o obj/test/libgeometry/arithmetic_test.o obj/src/libgeometry/libgeometry.a
	gcc -Wall -Werror $^ -o $@ -lm

obj/test/geometry/main.o: test/geometry/main.c
	gcc -Wall -Werror -c -MMD $<  -o $@ -I .

obj/test/libgeometry/lexer-parser_test.o: test/libgeometry/lexer-parser_test.c
	gcc -Wall -Werror -c -MMD $< -o $@ -I .

obj/test/libgeometry/arithmetic_test.o: test/libgeometry/arithmetic_test.c
	gcc -Wall -Werror -c -MMD $< -o $@ -I . 

show:
	@echo сборка приложения geometry:
	@echo -e '\033[0;32m make bin/geometry \033[0m'

	@echo сборка тестов приложения geometry:
	@echo -e '\033[0;32m make bin/geometry_test \033[0m'

	@echo запуск приложения geometry с готовыми входными файлами:
	@echo -e '\033[0;32m make input \033[0m'

	@echo запуск тестов приложения:
	@echo -e '\033[0;32m make test \033[0m'


	@echo удаление объектных файлов:
	@echo -e '\033[0;32m make clean \033[0m'

input:
	@echo содержимое тестовых файлов:
	@cat input/test_file1
	@cat input/test_file2
	./bin/geometry input/test_file1 input/test_file2

test:
	./bin/geometry_test

clean::
	rm */*/*/*.[oad]

-include obj/src/geometry/main.d obj/src/libgeometry/lexer-parser.d obj/src/libgeometry/arithmetic.d obj/test/geometry/main.d obj/test/libgeometry/lexer-parser.d obj/test/libgeometry/arithmetic.d
