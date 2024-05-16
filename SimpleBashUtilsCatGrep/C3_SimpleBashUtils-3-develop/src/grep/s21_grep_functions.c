

#include "s21_grep.h"

void initialization_options(FLAGS *options) {
  options->e = 0;
  options->i = 0;
  options->v = 0;
  options->c = 0;
  options->l = 0;
  options->n = 0;
  options->h = 0;
  options->s = 0;
  options->f = 0;
  options->o = 0;
  options->f_cnt = 0;
}

void e_flag(int *pattern_counter, char **patterns, size_t *patterns_size) {
  if (*pattern_counter) {
    *patterns = realloc(*patterns, *patterns_size + 2);
    strcat(*patterns, "|");
    *patterns_size += 2;
  }
  *patterns = realloc(*patterns, *patterns_size + strlen(optarg) + 1);
  strcat(*patterns, optarg);
  *patterns_size += strlen(optarg);
  (*pattern_counter) += 1;
}

int f_flag(int *pattern_counter, char **patterns, size_t *patterns_size) {
  int flag = 1;
  FILE *file = NULL;
  char *str = NULL;
  size_t line_buffer_size = 0;
  if ((file = fopen(optarg, "r"))) {
    while (getline(&str, &line_buffer_size, file) != -1) {
      if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = 0;
      if ((*pattern_counter) > 0) {
        *patterns = realloc(*patterns, *patterns_size + 2);
        strcat(*patterns, "|");
        *patterns_size += 2;
      }
      *patterns = realloc(*patterns, *patterns_size + strlen(str) + 1);
      strcat(*patterns, str);
      *patterns_size += strlen(str);
      (*pattern_counter)++;
    }
    fclose(file);
  } else {
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", optarg);
    flag = 0;
  }
  if (str != NULL) {
    free(str);
  }
  return flag;
}

void input_options(int argc, char **argv, char **patterns, int *flag,
                   FLAGS *options, size_t *patterns_size) {
  int option_index = -1, pattern_counter = 0;
  char ch = ' ';
  const char *optstring = "e:ivclnhsf:o";
  while ((ch = getopt_long(argc, argv, optstring, NULL, &option_index)) != -1 &&
         *flag) {
    switch (ch) {
      case 'e':
        options->e = 1;
        e_flag(&pattern_counter, patterns, patterns_size);
        break;
      case 'i':
        options->i = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'c':
        options->c = 1;
        break;
      case 'l':
        options->l = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 'h':
        options->h = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'f':
        options->f = 1;
        *flag = f_flag(&pattern_counter, patterns, patterns_size);
        break;
      case 'o':
        options->o = 1;
        break;
      case '?':
      default:
        *flag = 0;
    }
  }
  if (!options->e && !options->f) {
    *patterns = realloc(*patterns, *patterns_size + strlen(argv[optind]) + 1);
    strcat(*patterns, argv[optind]);
    *patterns_size += strlen(argv[optind++]) + 1;
  }
  if (options->o && options->e) options->e = 0;
  if (options->o && options->v) options->o = 0;
}

void grep_options_realize(int argc, char **argv, char *patterns,
                          FLAGS *options) {
  options->f_cnt = argc - optind;  // write pattern to single grep
  for (; optind < argc; optind++) {
    FILE *file = NULL;
    if ((file = fopen(argv[optind], "r")) != NULL) {
      process_flags(argv, patterns, file, options);
      fclose(file);
    } else {
      if (!options->s)
        fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                argv[optind]);
    }
  }
}

void process_flags(char **argv, char *patterns, FILE *file, FLAGS *options) {
  int equal_patterns_and_lines = 0;
  processing_incoming_flags(argv, &equal_patterns_and_lines, options, file,
                            patterns);
  if (options->c) {
    if (options->f_cnt > 1 && !options->h) printf("%s:", argv[optind]);
    if (options->l && equal_patterns_and_lines)
      fprintf(stdout, "1\n");
    else
      fprintf(stdout, "%d\n", equal_patterns_and_lines);
  }
  if (options->l && equal_patterns_and_lines)
    fprintf(stdout, "%s\n", argv[optind]);
}

void processing_incoming_flags(char **argv, int *equal_patterns_and_lines,
                               FLAGS *options, FILE *file, char *patterns) {
  char *str = NULL;
  size_t line_buffer_size = 0;
  regex_t reg = {0};
  regmatch_t match_arr[1] = {0};
  int is_true = 0;
  int flag_ext = REG_EXTENDED;
  int number_rows_counter = 1;
  int match_cnt = 1;
  if (options->i) flag_ext |= REG_ICASE;
  regcomp(&reg, patterns, flag_ext);
  while (getline(&str, &line_buffer_size, file) != -1) {
    int flagg = 1;
    is_true = regexec(&reg, str, match_cnt, match_arr, 0);
    if (options->v) {
      if (is_true)
        is_true = 0;
      else
        is_true = 1;
    }
    if (is_true == 0) {
      flags_processed_output(argv, &reg, options, &number_rows_counter, &flagg,
                             &match_cnt, str, &is_true, match_arr);
      (*equal_patterns_and_lines)++;
    }
    number_rows_counter++;
  }
  if (str != NULL) free(str);
  regfree(&reg);
}

void flags_processed_output(char **argv, regex_t *reg, FLAGS *options,
                            int *number_rows_counter, int *flagg,
                            int *match_cnt, char *str, int *is_true,
                            regmatch_t *match_arr) {
  if (!options->c && !options->l) {
    if (options->f_cnt > 1 && !options->h) fprintf(stdout, "%s:", argv[optind]);
    if (options->n && !options->o) fprintf(stdout, "%d:", *number_rows_counter);
    if (options->o && !options->v) {
      *flagg = 0;
      char *point = str;
      while (!(*is_true)) {
        if (match_arr[0].rm_eo == match_arr[0].rm_so) break;
        if (options->n) fprintf(stdout, "%d:", *number_rows_counter);
        fprintf(stdout, "%.*s\n",
                (int)(match_arr[0].rm_eo - match_arr[0].rm_so),
                point + match_arr[0].rm_so);
        point += match_arr[0].rm_eo;
        *is_true = regexec(reg, point, *match_cnt, match_arr, REG_NOTBOL);
      }
    }
    if (!options->o) fprintf(stdout, "%s", str);
    if (str[strlen(str) - 1] != '\n' && *flagg) fprintf(stdout, "\n");
  }
}