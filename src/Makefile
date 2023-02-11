GCC=gcc
CFLAGS=-Wall -Wextra -Werror -g -std=c11
LIBS=-lcheck
LFLAGS=-fprofile-arcs -ftest-coverage
LINUX = -lrt -lpthread -lm -lsubunit
OS=$(shell uname -s)

all: clean test

test: 
ifeq ($(OS), Darwin)
	$(GCC) $(CFLAGS) s21_test.c obj_parcer.c -o test.out $(LIBS)
	./test.out
else
	$(GCC) $(CFLAGS) s21_test.c obj_parcer.c -o test.out $(LIBS) $(LINUX)
	./test.out
endif

gcov_report: obj_parcer.c
ifeq ($(OS), Darwin)
	$(GCC) $(CFLAGS) $(LFLAGS) s21_test.c obj_parcer.c -o s21_test.out $(LIBS)
else
	$(GCC) $(CFLAGS) $(LFLAGS) s21_test.c obj_parcer.c -o s21_test.out $(LIBS) $(LINUX)
endif
	./s21_test.out
	lcov -t "s21_test" -o s21_test.info -c -d .
	genhtml -o report s21_test.info

open:
ifeq ($(OS), Darwin)
	open report/index.html
else
	xdg-open report/index.html
endif

rebuild: clean all

check:
	cp ../materials/linters/.clang-format ./
	clang-format -n obj_parcer.c
	clang-format -n obj_parcer.h
	clang-format -n s21_test.c
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test.out
else
	valgrind ./test.out --leak-check=full
endif
	make clean
	rm -rf .clang-format

install:
	make clean
	mkdir build
	cd build && qmake ../3D_Viewer/3D_Viewer.pro && make
	cp -r obj_files /Users/$(USER)
	open build/3D_Viewer.app/Contents/MacOS/3D_Viewer

uninstall:
	rm -rf build* /Users/$(USER)/obj_files

open_app:
	open build/3D_Viewer.app/Contents/MacOS/3D_Viewer

dvi:
	open readme.html

dist:
	rm -rf dist3D_Viewer.0/
	rm -rf dist3D_Viewer.0
	mkdir dist3D_Viewer.0/
	mkdir dist3D_Viewer.0/src
	cp -r obj_files dist3D_Viewer.0/src/
	cp Makefile obj_parcer* s21* dist3D_Viewer.0/src/
	cp build/3D_Viewer.app/Contents/MacOS/3D_Viewer dist3D_Viewer.0/src/
	tar cvzf dist3D_Viewer.0.tgz dist3D_Viewer.0

clean:
	rm -rf *.gc* *.o *.a *.out *.info *.dSYM *.tgz dist*
	rm -rf report
	rm -rf build* /Users/$(USER)/obj_files