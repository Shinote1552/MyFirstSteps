#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float fahr(int cel);


int main () {
    int cel;    // градусы Цельсия
    float f;    // градусы Фаренгейта
    


     if(scanf("%d", &cel)!=1) {

        printf("has finished with error\n");
		printf("n/a");
        return 1;
	}
       
    f = fahr(cel);
    printf("%.2f\n",f); // .2f - печатать с точностью до 2 знаков после .

    printf("has finished");
    // getchar();
    return 0;
}

float fahr(int cel){
    float result = 0;
    result = cel * 9.000000/5.000000 + 32.000000;
    return result;

}