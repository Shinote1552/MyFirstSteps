#include "s21_cat.h"

int main(int argc, char **argv) {
  int nero = 0;
  int index_end_flags = 0;

  index_end_flags = FlagParsEnd(argc, argv);
  FLAGS Flags;
  Flags = CatFlagsFind(argv, &index_end_flags);
  int flags[6] = {Flags.nonblank_b,          Flags.numberLines_n,
                  Flags.printNonPrintable_v, Flags.showEnds_E,
                  Flags.showTabs_T,          Flags.squeezeEmptyLines_s};
  for (int indexFile = 1; indexFile < argc; indexFile++) {
    nero = openFile(argv[indexFile], flags, nero);
  }

  if (nero == 1) {
    for (; index_end_flags < argc; index_end_flags++) {
      printErrorFileNotFound(argv, index_end_flags);
    }
  }
  return nero;
}