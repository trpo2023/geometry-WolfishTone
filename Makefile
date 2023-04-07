.PHONY: all clean test geometry
all: show

geometry: obj/src/geometry/main.o obj/src/libgeometry/libgeometry.a
	gcc -Wall -Werror $^ -o $@

obj/src/geometry/main.o: src/geometry/main.c
	gcc -Wall -Werror -c -MMD $^ -o $@ -I src

obj/src/libgeometry/libgeometry.a: obj/src/libgeometry/lexer.o obj/src/libgeometry/parser.o
	ar rcs $@ $^

obj/src/libgeometry/lexer.o: src/libgeometry/lexer.c
	gcc -Wall -Werror -c -MMD $^ -o $@ -I src
obj/src/libgeometry/parser.o: src/libgeometry/lexer.c
	gcc -Wall -Werror -c -MMD $^ -o $@ -I src
show:
	@echo сборка приложения geometry:
	@echo -e '\033[0;32m  geometry \033[0m'
	@echo запуск приложения geometry с тестовыми файлами:
	@echo -e '\033[0;32m  test \033[0m'
	@echo удаление объектных файлов:
	@echo -e '\033[0;32m  clean \033[0m'

test:
	@echo содержимое тестовых файлов:
	@cat test/test_file1
	@cat test/test_file2
	./geometry test/test_file1 test/test_file2

clean:
	rm */*/*/*.o
	rm */*/*/*.a

-include main.d lexer.d parser.d
