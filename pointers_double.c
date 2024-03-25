#include <stdio.h>

int main()
{
    int x = 7;          // переменная х имеет тип int и значение 7 (пусть она лежит по адресу 100)
int * px = &x;      // переменная pх имеет int* и значение 100 (пусть она лежит по адресу 240)
int ** ppx = &px;   // переменная ppх имеет int** и значение 240 (пусть она лежит по адресу 300)
// распечатаем выражения и их значения; обратите внимание на формат, по которому печатаем
printf("x=%d *px=%d **ppx=%d\n", x, *px, **ppx);    // x=7 *px=7 **ppx=7
printf("&x=%p px=%p *ppx=%p\n", &x, px, *ppx);      // &x=100 px=100 *ppx=100
printf("&px=%p ppx=%p\n", &px, ppx);                // &px=240 ppx=240

// result stdout
//      x=7 *px=7 **ppx=7
//      &x=0x7fff81ce5c44 px=0x7fff81ce5c44 *ppx=0x7fff81ce5c44
//      &px=0x7fff81ce5c48 ppx=0x7fff81ce5c48

    return 0;
}
