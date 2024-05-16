#ifndef S21_CAT
#define S21_CAT

#define _GNU_SOURCE

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct FLAGS {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int f_cnt;
} FLAGS;

void initialization_options(FLAGS *options);
void input_options(int argc, char **argv, char **patterns, int *flag,
                   FLAGS *options, size_t *patterns_size);
void grep_options_realize(int argc, char **argv, char *patterns,
                          FLAGS *options);
void e_flag(int *e_count, char **patterns, size_t *patterns_size);
int f_flag(int *e_count, char **patterns, size_t *patterns_size);
void process_flags(char **argv, char *pattern, FILE *steam, FLAGS *options);
void processing_incoming_flags(char **argv, int *equal_patterns_and_lines,
                               FLAGS *options, FILE *file, char *patterns);
void flags_processed_output(char **argv, regex_t *reg, FLAGS *options,
                            int *number_rows_counter, int *flagg,
                            int *match_cnt, char *str, int *is_true,
                            regmatch_t *match_arr);

#endif