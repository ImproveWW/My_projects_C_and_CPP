CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -I/opt/goinfre/graftonu/homebrew/Cellar/check/0.15.2/include

DETECT_DISTRO = $(shell if [ -f /etc/os-release ]; then \
                          . /etc/os-release; \
                          if [ "$$ID" = "debian" ] || [ "$$ID" = "ubuntu" ]; then \
                            echo "debian-based"; \
                          else \
                            echo "not-debian-based"; \
                          fi; \
                        elif [ -f /etc/debian_version ]; then \
                          echo "debian-based"; \
                        else \
                          echo "not-debian-based"; \
                        fi)

ifeq ($(DETECT_DISTRO), debian-based)
    LDFLAGS = -lcheck -lpthread -lm -lsubunit -L/opt/goinfre/graftonu/homebrew/Cellar/check/0.15.2/lib 
else
    LDFLAGS = -lcheck -lpthread -lm -L/opt/goinfre/graftonu/homebrew/Cellar/check/0.15.2/lib 
endif

LIBRARY = s21_decimal.a
HEADERS = s21_decimal.h $(wildcard ./HEADERS/*.c) 
TARGET = test_runner

FUNC_FILES = $(wildcard ./auxiliary/*.c)	\
	$(wildcard ./arithmetic/*.c)			\
	$(wildcard ./comparision/*.c)			\
	$(wildcard ./convertors/*.c)			\
	$(wildcard ./comparison/*.c)			\
	$(wildcard ./etc/*.c) 				\


OBJ_LIBRARY := $(patsubst %.c, %.o, $(FUNC_FILES))

OBJ = s21_*.o 
FUNC_TEST = tests/test_*.c 
OBJ_TEST = s21_test_*.c 

COVER_FLAG  = --coverage
LIB_FLAGS 	= ar rcs

all: clean s21_decimal.a test

s21_decimal.a: clean
	$(CC) $(CFLAGS) -c $(FUNC_FILES)
	$(LIB_FLAGS) $(LIBRARY) $(OBJ)
	ranlib s21_decimal.a
	
test: s21_decimal.a
	$(CC) -g $(FUNC_FILES) tests/test_.c $(LDFLAGS) -o $(TARGET)
	./$(TARGET)

gcov_report: s21_decimal.a
	gcc -fprofile-arcs -ftest-coverage $(FUNC_FILES) $(FUNC_TEST) $(LDFLAGS) -o $(TARGET)
	./$(TARGET)
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	rm -rf *.gcda *.gcno *.out $(TARGET)
	
leaks: clean test
	valgrind --log-file="log_file_valgrind.txt" --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(TARGET)

style_check_1:
	cp ../materials/linters/.clang-format .
	find . -type f -name "*.c" -exec clang-format -n {} \;

format_style_1:
	cp ./../materials/linters/.clang-format .
	find . -type f -name "*.c" -exec clang-format -i {} \;
	
clean:
	rm -rf *.o *.a *.gcda *.txt *.gcno *.out *.info report $(TARGET)
