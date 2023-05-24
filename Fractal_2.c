#include <stdio.h>
#include <string.h>

void remover_caracteres(char *string_com_xy) {
  char string_limpeza[1000000];
  int contador_1 = 0;
  for(int contador = 0; contador < strlen(string_com_xy); contador++) {
    if((string_com_xy[contador] != 'X') && (string_com_xy[contador] != 'Y')) {
      string_limpeza[contador_1] = string_com_xy[contador];
      contador_1++;
    }
  }
  string_limpeza[contador_1] = '\0';
  strncpy(string_com_xy, string_limpeza, contador_1 + 1);
}


char* gerar_sequencias(char X, char regraX[12], char regraY[12], char *string_de_retorno, int estagio_atual, FILE *arquivo_strings) {
  char string_auxiliar[1000000];
  
  if(estagio_atual == 4) {
    fprintf(arquivo_strings, "Estágio %d: ", estagio_atual);
    remover_caracteres(string_de_retorno);
    fputs(string_de_retorno, arquivo_strings);
    
    return string_de_retorno;
  }
    
  else {

    for (long int cont = 0; cont <= strlen(string_de_retorno); cont++) {
      if (string_de_retorno[cont] == X) {
        for (long int cont2 = 0; cont2 <= strlen(regraX); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = regraX[cont2];
        }
      }
      else if (string_de_retorno[cont] == 'Y'){ 
        for (long int cont2 = 0; cont2 <= strlen(regraY); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = regraY[cont2];
        }
      }
      else {
        string_auxiliar[strlen(string_auxiliar)] = string_de_retorno[cont];
      }
    }
    
    if(estagio_atual < 4) {
    
    fprintf(arquivo_strings, "Estágio %d: ", estagio_atual);
    fputs(string_auxiliar, arquivo_strings);
    fprintf(arquivo_strings, "\n");
    }
  }
  return gerar_sequencias(X, regraX, regraY, string_auxiliar, estagio_atual + 1, arquivo_strings);
}


int main() {
  //declarações de variáveis
  char axioma;
  int graus, estagios = 0;
  char regraX[15], regraY[15]; //caso F mude para 23
  char string_de_retorno[1000000];
  FILE *pont_estagios;

  //criação e alocação de dados
  pont_estagios = fopen("estagios_fractal2.txt", "w");
  
  axioma = getchar();
  scanf("%d", &graus);
  scanf("%s", regraX);
  scanf("%s", regraY);
  fprintf(pont_estagios, "Estagio 1: X");
  gerar_sequencias(axioma, regraX, regraY, regraX, estagios + 1, pont_estagios);

  return 0;
  
}
