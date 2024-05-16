#ifndef S21_CAT_H
#define S21_CAT_H

typedef struct {
  int printNonPrintable_v;
  int numberLines_n;
  int showEnds_E;
  int nonblank_b;
  int squeezeEmptyLines_s;
  int showTabs_T;
  int cerber;
} FLAGS;

FLAGS CatFlagsFind(char **argv, int *index_end_flags);
int FlagParsEnd(int argc, char **argv);
void printSymb(int currentSymbel, int *slashNnumb, int *flags_, int *index,
               int *eline_printed, int prevc_);
int openFile(char *name, int *flags, int nero);
void printErrorFileNotFound(char *argv[], int index_end_flags);

#endif