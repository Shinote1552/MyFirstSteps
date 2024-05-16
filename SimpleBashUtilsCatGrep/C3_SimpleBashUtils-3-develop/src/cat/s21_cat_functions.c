#define _GNU_SOURCE

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_cat.h"

FLAGS CatFlagsFind(char **argv, int *index_end_flags) {
  const char short_options[] = "neEbvstT";
  int lastFlagArgc = *index_end_flags;
  FLAGS flags = {0, 0, 0, 0, 0, 0, 0};
  struct option longOptions[] = {{"number-nonblank", 0, 0, 'b'},
                                 {"number", 0, 0, 'n'},
                                 {"squeeze-blank", 0, 0, 's'},
                                 {0, 0, 0, 0}};
  int currentFlag =
      getopt_long(lastFlagArgc, argv, short_options, longOptions, NULL);

  for (int i = 1; i < lastFlagArgc; i++) {
    for (; currentFlag != -1;
         currentFlag = getopt_long(lastFlagArgc, argv, short_options,
                                   longOptions, NULL)) {
      switch (currentFlag) {
        case 'n':
          flags.numberLines_n = 1;
          break;
        case 'e':
          flags.printNonPrintable_v = 1;
          flags.showEnds_E = 1;
          break;
        case 'v':
          flags.printNonPrintable_v = 1;
          break;
        case 'E':
          flags.showEnds_E = 1;
          break;
        case 'b':
          flags.nonblank_b = 1;
          break;
        case 's':
          flags.squeezeEmptyLines_s = 1;
          break;
        case 't':
          flags.printNonPrintable_v = 1;
          flags.showTabs_T = 1;
          break;
        case 'T':
          flags.showTabs_T = 1;
          break;
      }
    }
  }
  flags.numberLines_n =
      (flags.nonblank_b == 1) ? 0 : flags.numberLines_n;  // n flag priority
  return flags;
}

int FlagParsEnd(int argc, char **argv) {
  int indexLast = 0;
  char *tstring;
  for (int i = 1; i < argc; i++) {
    tstring = argv[i];
    if (tstring[0] == '-') {
      indexLast = i + 1;
    } else {
      break;
    }
  }
  return indexLast;
}

void printSymb(int currentSymbel, int *slashNnumb, int *flags_, int *index,
               int *eline_printed, int prevc_) {
  if (!(flags_[5] == 1 && *slashNnumb == '\n' && currentSymbel == '\n' &&
        *eline_printed)) {  // s[5]
    if (*slashNnumb == '\n' && currentSymbel == '\n')
      *eline_printed = 1;
    else
      *eline_printed = 0;
    if (((flags_[1] == 1 && flags_[0] == 1) ||
         (flags_[0] == 1 && currentSymbel != '\n')) &&
        *slashNnumb == '\n') {  // n[1] b[0]
      *index += 1;
      printf("%6d\t", *index);
    } else if ((flags_[1] == 1 || prevc_ != '\n') &&
               *slashNnumb == '\n') {  // realize n flag
      (*index)++;
      printf("%6d\t", *index);
    }
    if (flags_[3] == 1 && (flags_[1] == 1 || flags_[0] == 1))  // -e[3]
    {
      if (currentSymbel == '\n' && prevc_ == '\n' && flags_[1] != 1) {
        printf("      \t");  //  6spc + tab
      }
      if (currentSymbel == '\n') printf("$");
    }
    if (flags_[3] == 1 && flags_[1] != 1 && flags_[0] != 1 &&
        currentSymbel == '\n')
      printf("$");
    if (flags_[4] == 1 && currentSymbel == '\t') {
      printf("^");
      currentSymbel = '\t' + 64;
    }
    if (flags_[2] == 1 && currentSymbel >= 0 && currentSymbel <= 31 &&
        currentSymbel != '\n' && currentSymbel != '\t') {
      printf("^");
      currentSymbel = currentSymbel + 64;
    } else if (flags_[2] == 1 && currentSymbel == 127) {
      printf("^");
      currentSymbel = currentSymbel - 64;
    } else if (flags_[2] == 1 && currentSymbel > 127 && currentSymbel < 160)
      printf("M-^%c", currentSymbel - 64);
    fputc(currentSymbel, stdout);
  }
  *slashNnumb = currentSymbel;
}

int openFile(char *name, int *flags, int nero) {
  FILE *f = fopen(name, "rt");

  if (f != NULL) {
    int index = 0;
    int eline_printed = 0;
    int prevc = '\n';
    int currentSymbel = fgetc(f);
    int slashNnumber = '\n';
    while (currentSymbel != EOF) {
      printSymb(currentSymbel, &slashNnumber, flags, &index, &eline_printed,
                prevc);
      prevc = currentSymbel;
      currentSymbel = fgetc(f);
    }
    fclose(f);
    nero = 0;
  } else
    nero = 1;
  return nero;
}

void printErrorFileNotFound(char *argv[], int index_end_flags) {
  fprintf(stderr, "cat: %s: No such file or directory\n",
          argv[index_end_flags]);
}