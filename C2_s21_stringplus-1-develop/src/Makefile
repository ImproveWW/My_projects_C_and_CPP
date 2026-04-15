FLAGS = -Wall -Wextra -std=c11 
CC = gcc
HTML_OPEN = open s21_string.info
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
LIBCHECK = -L. `pkg-config --libs check`
FILES = ./Unit-Tests/test.c ./core_funcs/*.c ./adv_funcs/*.c ./sprintf/s21_sprintf.c ./*.h
# OS:$(shell uname)
# ifeq ($(OS), Darwin)
# 	LIBS = `pkg-config --libs check` --coverage
# else
# 	LIBS = `pkg-config --libs check` -lm -lsubunit --coverage
# endif
all: s21_string.a
style:
	clang-format -n -style=google $(FILES) 
format:
	clang-format -i -style=google $(FILES) 
clean:
	rm -rf rm -f s21_string.a tests.out *.o
	rm -rf report
	rm -rf *.gcno *.gcda 
	rm -rf *.info
rebuild:
	clean
	all
gcov_report:
	gcc -fprofile-arcs -ftest-coverage -o ./test ./Unit-Tests/test.c ./core_funcs/*.c ./adv_funcs/*.c ./sprintf/s21_sprintf.c $(LIBCHECK)
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info 
	open ./report/index.html
#lcov -t "gcov_report" -o tests.info -c -d .
#geninfo ./ --test test.info --test-name gcov --ignore-errors usage
s21_string.a:
	$(CC) $(FLAGS) -c ./core_funcs/s21_memchr.c -o s21_memchr.o
	$(CC) $(FLAGS) -c ./core_funcs/s21_memcmp.c -o s21_memcmp.o
	$(CC) $(FLAGS) -c ./core_funcs/s21_memcpy.c -o s21_memcpy.o
	$(CC) $(FLAGS) -c ./core_funcs/s21_memset.c -o s21_memset.o
	$(CC) $(FLAGS) -c ./core_funcs/s21_strchr.c -o s21_strchr.o
	$(CC) $(FLAGS) -c ./core_funcs/s21_strcspn.c -o s21_strcspn.o
	$(CC) $(FLAGS) -c ./core_funcs/s21_strerror.c -o s21_strerror.o
	$(CC) $(FLAGS) -c ./core_funcs/s21_strlen.c -o s21_strlen.o
	$(CC) $(FLAGS) -c ./core_funcs/s21_strncat.c -o s21_strncat.o
	$(CC) $(FLAGS) -c ./core_funcs/s21_strncmp.c -o s21_strncmp.o
	$(CC) $(FLAGS) -c ./core_funcs/s21_strncpy.c -o s21_strncpy.o
	$(CC) $(FLAGS) -c ./core_funcs/s21_strpbrk.c -o s21_strpbrk.o
	$(CC) $(FLAGS) -c ./core_funcs/s21_strrchr.c -o s21_strrchr.o
	$(CC) $(FLAGS) -c ./core_funcs/s21_strstr.c -o s21_strstr.o
	$(CC) $(FLAGS) -c ./core_funcs/s21_strtok.c -o s21_strtok.o
	$(CC) $(FLAGS) -c ./sprintf/s21_sprintf.c -o s21_sprintf.o
	$(CC) $(FLAGS) -c ./adv_funcs/s21_insert.c -o s21_insert.o
	$(CC) $(FLAGS) -c ./adv_funcs/s21_to_lower.c -o s21_to_lower.o
	$(CC) $(FLAGS) -c ./adv_funcs/s21_to_upper.c -o s21_to_upper.o
	$(CC) $(FLAGS) -c ./adv_funcs/s21_trim.c -o s21_trim.o
 
	ar rcs s21_string.a *.o
test: clean s21_string.a
	gcc $(FLAGS) --coverage Unit-Tests/test.c s21_string.a -o test $(LIBCHECK)
	
