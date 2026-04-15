CC  = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
LIBS = -lgtest -pthread
SRCS = s21_matrix_oop.cpp
OBJS = $(SRCS:.cpp=.o)
TEST = s21_tests.cpp
OBJECT_LIBRARY = s21_matrix_oop.a
HEADER = s21_matrix_oop.h
S21_TEST = test

all: s21_matrix_oop.a test style_check

$(OBJS): %.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

s21_matrix_oop.a: $(OBJS)
	ar rcs $(OBJECT_LIBRARY) $(OBJS)
	ranlib $(OBJECT_LIBRARY)

test: $(OBJECT_LIBRARY)
	$(CC) $(CFLAGS) $(TEST) $(OBJECT_LIBRARY) -o s21_test $(LIBS)
	./s21_test

style_check: 
	cp ../materials/linters/.clang-format .
	clang-format -n -style=Google $(SRCS) $(TEST) $(HEADER)
	rm -rf .clang-format

style_correct:
	cp ../materials/linters/.clang-format .
	clang-format -i -style=Google $(SRCS) $(TEST) $(HEADER)
	rm -rf .clang-format

clean:
	rm -rf *.o *.a s21_test

leaks_check: $(S21_TEST)
	CK_FORK=no leaks --atExit -- ./s21_test

valgrind_check: $(S21_TEST)
	CK_FORK=no valgrind --leak-check=full ./s21_test
