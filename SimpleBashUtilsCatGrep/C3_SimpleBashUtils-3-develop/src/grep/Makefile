CC=gcc
CFLAGS=-Wall -Werror -Wextra
CLANG=clang-format -i


all: cleanapp cleanaout clean s21_grep  


s21_grep: s21_grep.c s21_grep_functions.c
	$(CC) $(CFLAGS) s21_grep.c s21_grep_functions.c -o s21_grep -std=c11
	
clean:
	rm -rf *.o 
cleanapp:
	rm -rf s21_grep
cleanaout:
	rm -rf a.out

clang: s21_grep.c s21_grep.h s21_grep_functions.c
	$(CLANG) s21_grep.c s21_grep.h s21_grep_functions.c
