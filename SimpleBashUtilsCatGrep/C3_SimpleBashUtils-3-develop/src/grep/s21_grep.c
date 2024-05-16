#include "s21_grep.h"

int main(int argc, char **argv) {
  FLAGS options = {0};
  size_t patterns_size = 1;
  initialization_options(&options);
  if (argc > 1) {
    char *patterns = (char *)malloc(sizeof(char) * 1);
    *patterns = '\0';
    int flag = 1;
    input_options(argc, argv, &patterns, &flag, &options, &patterns_size);
    if (flag) grep_options_realize(argc, argv, patterns, &options);
    if (patterns != NULL) {
      free(patterns);
    }
  } else {
    fprintf(stderr,
            "usage: grep [-abcdDEFGHhIiJLlMmnOopqRSsUVvwXxZz] [-A num] [-B "
            "num] [-C[num]] [-e pattern] "
            "[-f file] [--binary-files=value] [--color=when] [--context[=num]] "
            "[--directories=action] "
            "[--label] [--line-buffered] [--null] [pattern] [file ...]\n");
  }
  return 0;
}
