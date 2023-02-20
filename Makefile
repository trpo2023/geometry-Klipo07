all: lab1

main: lab1.c
		gcc -Wall -Werror -o lab1 lab1.c

run:
		./lab1