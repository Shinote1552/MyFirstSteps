#include <stdio.h>
void hack_bank3(int *pg);
int hack_bank2(int g);
void hack_bank1(int g);

int main() {
  int x;   // объявили переменную х типа int
  x = 7;   // записали в переменную х значение 7
  int *px; // объявили переменную px типа int *
  px = &x; //записали адрес х в указатель px
  int m =*px + 3; //*px разименовали по адресу значние (по ардесу х int* получили
               // его данные int)
  int y = 123; //
  int*p = &y; // p будет равен адресу y,
               // *p = 123 будет равен в данном случае
  printf("%p\n", px);
  printf("%d\n", px);
  printf("%d\n", m);
  printf("Hello, World!\n");

  int g1 = 1;
  int g2 = 2;
  int g3 = 3;

  hack_bank1(g1);
  printf("g1 = %d\n", g1); // 1, богаче не стали

  g2 = hack_bank2(g2);
  printf("g2 = %d\n", g2); // 202, успех

  hack_bank3(&g3);
  printf("g3 = %d\n", g3); // 303, успех
  return 0;
}

void hack_bank1(int g) {
  g = g + 100; // изменили копию кошелька, бесполезно
}

int hack_bank2(int g) {
  g = g + 200;
  return g; // вернули измененное значение
}

void hack_bank3(int *pg) {
  // по указателю меняем значение
  *pg = *pg + 300; // или *pg += 300
}