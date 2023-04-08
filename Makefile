.PHONY: all clean test bin/geometry
all: show

bin/geometry: obj/src/geometry/main.o obj/src/libgeometry/libgeometry.a 	
	gcc -Wall -Werror $^ -o $@

obj/src/geometry/main.o: src/geometry/main.c
	gcc -Wall -Werror -c -MMD $<  -o $@ -I src

obj/src/libgeometry/libgeometry.a: obj/src/libgeometry/lexer-parser.o obj/src/libgeometry/arithmetic.o obj/src/libgeometry/input.o
	ar rcs $@ $^

obj/src/libgeometry/lexer-parser.o: src/libgeometry/lexer-parser.c
	gcc -Wall -Werror -c -MMD $< -o $@
obj/src/libgeometry/arithmetic.o: src/libgeometry/arithmetic.c
	gcc -Wall -Werror -c -MMD $< -o $@
obj/src/libgeometry/input.o: src/libgeometry/input.c
	gcc -Wall -Werror -c -MMD $< -o $@

show:
	@echo сборка приложения geometry:
	@echo -e '\033[0;32m make bin/geometry \033[0m'
	@echo запуск приложения geometry с тестовыми файлами:
	@echo -e '\033[0;32m make test \033[0m'
	@echo удаление объектных файлов:
	@echo -e '\033[0;32m make clean \033[0m'

test:
	@echo содержимое тестовых файлов:
	@cat input/test_file1
	@cat input/test_file2
	./bin/geometry input/test_file1 input/test_file2

clean::
	rm */*/*/*.[oad]


-include obj/src/geometry/main.d obj/src/libgeometry/lexer-parser.d obj/src/libgeometry/arithmetic.d
