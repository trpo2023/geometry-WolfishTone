.PHONY: all clean test
all: geometry
geometry:  geometry.o main.o
	gcc -Wall -Werror $^ -o $@
geometry.o: src/geometry.c
	gcc -Wall -Werror -c $^ -o $@
main.o: src/main.c
	gcc -Wall -Werror -c $^ -o $@
clean:
	rm *.o
	rm geometry
