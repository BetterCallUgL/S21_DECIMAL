CC=gcc
CC_FLAGS=-g -Wall -Wextra -std=c11
test_flags=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)
VALGRIND_FLAGS = --log-file="valgrind.txt" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med

ifeq ($(OS),Linux)
	test_libs=-lcheck -lm -lsubunit
	open=xdg-open
else
	test_libs=-lcheck
	open=open
endif

all: clean s21_decimal.a gcov_report clean

s21_decimal.a:
	$(CC) $(CC_FLAGS) -c functions/*.c utilities/*.c
	ar rc s21_decimal.a *.o
	ranlib s21_decimal.a
	rm -f *.o

test:clean
	$(CC) $(CC_FLAGS) $(test_flags) functions/*.c utilities/*.c tests/*.c -o test $(test_libs)
	./test
	mv *.gcda *.gcno tests/

gcov_report: test
	lcov -t "test" -o $(tests_info)test.info -c -d .
	genhtml -o report $(tests_info)test.info
	$(open) report/index.html

clean:
	rm -f tests/*.gcda tests/*.gcno
	rm -f test
	rm -f *.o
	rm -rf report

clang:
	cp ../materials/linters/.clang-format .
	clang-format -i *.h */*.c */*.h
	rm -f .clang-format

valgrind:
	$(CC) $(CC_FLAGS) $(test_flags) functions/*.c utilities/*.c tests/*.c -o test $(test_libs)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) ./test

cleanv:
	rm -rf test-s21_* test