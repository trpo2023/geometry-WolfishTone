.PHONY : all
hello : hello.c
	gcc -Wall -Werror hello.c -o hello
geometry : geometry.c
	gcc -Wall geometry.c -o geometry
