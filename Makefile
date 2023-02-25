main: hello.c geometry.c
	gcc -Wall -Werror hello.c -o hello
	gcc -Wall -Werror geometry.c -o geometry
