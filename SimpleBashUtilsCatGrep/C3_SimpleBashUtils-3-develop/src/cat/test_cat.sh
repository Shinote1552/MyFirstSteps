#!/bin/bash

SUCCESS=0
FAIL=0
DIFFRES=""
FLAGS="b e n s t v"
BASE="$(tput setaf 7)"
declare -a tests=(
    "VAR test_file.txt"
)

testing() {
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_cat $t > test_s21_cat.log
    cat $t > test_sys_cat.log
    DIFFRES="$(diff -s test_s21_cat.log test_sys_cat.log)"
    RESULT="SUCCESS"
    if [ "$DIFFRES" == "Files test_s21_cat.log and test_sys_cat.log are identical" ]
    then
      ((SUCCESS++))
        RESULT="SUCCESS"
    else
      ((FAIL++))
        RESULT="FAIL" 
    fi
    echo "${RESULT}${BASE} cat $t"
    rm test_s21_cat.log test_sys_cat.log
}

for var1 in $FLAGS
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

for var1 in $FLAGS
do
    for var2 in $FLAGS
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1 -$var2"
                testing $i
            done
        fi
    done
done

for var1 in $FLAGS
do
    for var2 in $FLAGS
    do
        for var3 in $FLAGS
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1 -$var2 -$var3"
                    testing $i
                done
            fi
        done
    done
done

for var1 in $FLAGS
do
    for var2 in $FLAGS
    do
        for var3 in $FLAGS
        do
            for var4 in $FLAGS
            do
                if [ $var1 != $var2 ] && [ $var2 != $var3 ] \
                && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    for i in "${tests[@]}"
                    do
                        var="-$var1 -$var2 -$var3 -$var4"
                        testing $i
                    done
                fi
            done
        done
    done
done

echo "FAIL: ${FAIL}${BASE}"
echo "SUCCESS: ${SUCCESS}${BASE}"