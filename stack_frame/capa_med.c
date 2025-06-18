#include <stdio.h>
extern int conversion(float gini);

int get_gini(float indice) {
  printf("El índice recibido en C desde py: %.2f\n", indice);
  int resultado = conversion(indice);
  printf("El indice recibido en C desde asm: %d\n", resultado);
  return resultado;
}
int main() {
  int example_index = (double)2.5;
  get_gini(example_index);
  return 0;
}
