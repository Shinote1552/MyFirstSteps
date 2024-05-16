 #!/bin/bash

SUCCESS=0
FAIL=0
DIFF_RES=""


test_diff() {
  if [ "$1" == "" ]; then
    ((SUCCESS++))
    echo "SUCCESS $RESET ./s21_grep $2"
  else
    ((FAIL++))
    echo "FAIL $RESET ./s21_grep $2"
    echo "$DIFF_RES"
  fi
}

LINE="-e realloc s21_grep.c test_file_grep.txt"
./s21_grep $LINE >1.txt
grep $LINE >2.txt
DIFF_RES="$(diff 1.txt 2.txt)"
rm 1.txt 2.txt
test_diff "$DIFF_RES" "$LINE"

LINE="-e realloc -e str s21_grep.c test_file_grep.txt"
./s21_grep $LINE >1.txt
grep $LINE >2.txt
DIFF_RES="$(diff 1.txt 2.txt)"
rm 1.txt 2.txt
test_diff "$DIFF_RES" "$LINE"

LINE="-f templates.txt test_file_grep.txt"
./s21_grep $LINE >1.txt
grep $LINE >2.txt
DIFF_RES="$(diff 1.txt 2.txt)"
rm 1.txt 2.txt
test_diff "$DIFF_RES" "$LINE"

for var3 in -v -c -l -n -h -o -i; do
      LINE="$var3 realloc s21_grep.c test_file_grep.txt"
      ./s21_grep $LINE >1.txt
      grep $LINE >2.txt
      DIFF_RES="$(diff 1.txt 2.txt)"
      rm 1.txt 2.txt
      test_diff "$DIFF_RES" "$LINE"

      LINE="$var3 ^int s21_grep.c"
      ./s21_grep $LINE >1.txt
      grep $LINE >2.txt
      DIFF_RES="$(diff 1.txt 2.txt)"
      rm 1.txt 2.txt
      test_diff "$DIFF_RES" "$LINE"

done

for var2 in -v -c -l -n -h -o -i; do
    for var3 in -v -c -l -n -h -o -i; do
      if [ $var2 == $var3 ]; then
        continue
      fi
      LINE="$var2 $var3 realloc s21_grep.c test_file_grep.txt"
      ./s21_grep $LINE >1.txt
      grep $LINE >2.txt
      DIFF_RES="$(diff 1.txt 2.txt)"
      rm 1.txt 2.txt
      test_diff "$DIFF_RES" "$LINE"

      LINE="$var2 $var3 ^int s21_grep.c"
      ./s21_grep $LINE >1.txt
      grep $LINE >2.txt
      DIFF_RES="$(diff 1.txt 2.txt)"
      rm 1.txt 2.txt
      test_diff "$DIFF_RES" "$LINE"

    done
done

for var in -v -c -l -n -h -o -i; do
  for var2 in -v -c -l -n -h -o -i; do
    for var3 in -v -c -l -n -h -o -i; do
      if [ $var == $var2 ] || [ $var2 == $var3 ] || [ $var == $var3 ]; then
        continue
      fi

      LINE="$var realloc s21_grep.c test_file_grep.txt $var2 $var3"
      ./s21_grep $LINE >1.txt
      grep $LINE >2.txt
      DIFF_RES="$(diff 1.txt 2.txt)"
      rm 1.txt 2.txt
      test_diff "$DIFF_RES" "$LINE"

      LINE="$var ^int s21_grep.c $var2 $var3"
      ./s21_grep $LINE >1.txt
      grep $LINE >2.txt
      DIFF_RES="$(diff 1.txt 2.txt)"
      rm 1.txt 2.txt
      test_diff "$DIFF_RES" "$LINE"
    done
  done
done

echo ""
echo "SUCCEEDED $RESET: $SUCCESS"
echo "FAILED $RESET: $FAIL"
