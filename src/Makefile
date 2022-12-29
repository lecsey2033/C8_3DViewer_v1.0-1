CC=gcc
CFLAGS=-Wall -Wextra -Werror -g -std=c11
#OS=$(shell uname -s)

all: clean parcing

parcing: obj_parcer.c
	$(CC) $(CFLAGS) obj_parcer.c -o parcer.out

clean:
	rm -rf *.gc* *.o *.a *.out *.info test.out test.out.dSYM
	rm -rf report