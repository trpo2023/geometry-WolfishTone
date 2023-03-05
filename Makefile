.PHONY: all clean test
all: geometry
geometry:  geometry.o main.o
	gcc -Wall -Werror $^ -o $@
geometry.o: src/geometry.c
	gcc -Wall -Werror -c $^ -o $@
main.o: src/main.c
	gcc -Wall -Werror -c $^ -o $@
test:
	./geometry test/test_file1 test/test_file2
clean:
	rm *.o
	rm geometry
