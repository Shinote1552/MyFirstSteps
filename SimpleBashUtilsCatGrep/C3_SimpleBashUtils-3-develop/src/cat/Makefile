CC=gcc
CFLAGS=-Wall -Werror -Wextra
CLANG=clang-format -n

all: cleanapp cleanaout clean s21_cat  

s21_cat: s21_cat.c s21_cat_functions.c
	$(CC) $(CFLAGS) s21_cat.c s21_cat_functions.c -o s21_cat -std=c11
clean:
	rm -rf *.o 
cleanapp:
	rm -rf s21_cat
cleanaout:
	rm -rf a.out


clang: s21_cat.c s21_cat.h s21_cat_functions.c
	$(CLANG) s21_cat.c s21_cat.h s21_cat_functions.c
