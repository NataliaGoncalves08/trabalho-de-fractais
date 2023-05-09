#include <stdio.h>
#include <string.h>

char* fractais(int op, char* regra, char* stringf) {
  char auxiliar[10000];
  if (op == 0) {
    return stringf;
  }
  else {
    for (int cont = 0; cont <= strlen(stringf); cont++) {
      if (stringf[cont] == 'F') {
        for (int cont2 = 0; cont2 <= strlen(regra); cont2++) {
          auxiliar[strlen(auxiliar)] = regra[cont2];
        }
      }
      else {
        auxiliar[strlen(auxiliar)] = stringf[cont];
      }
    }
  
  }
  return fractais(op - 1, regra, auxiliar);
}

int main() {
  int estagios = 2;
  char rproducao[10000] = "F-F+F+FF-F-F+F";
  char stringfinal[10000];
  char fina[10000]; 
  strcpy(fina, fractais(estagios, rproducao, rproducao));
  printf("%s", fina);
  printf("Acabou =(");
  return 0;
}
