#include <stdio.h>
#include <string.h>

void remover_caracteres(char *string_com_xy) {
  char string_limpeza[1000000];
  int contador_1 = 0;

  //limpeza
  for(int contador = 0; contador < strlen(string_com_xy); contador++) {
    if((string_com_xy[contador] != 'X') && (string_com_xy[contador] != 'Y')) {
      string_limpeza[contador_1] = string_com_xy[contador];
      contador_1++;
    }
  }
  //finalização da string limpa
  string_limpeza[contador_1] = '\0';
  //copia para a string de parametro
  strncpy(string_com_xy, string_limpeza, contador_1 + 1);
}


char* gerar_sequencia(char X, char regraX[12], char regraY[12], char *string_de_retorno, int estagio_atual, FILE *arquivo_strings) {
  char string_auxiliar[1000000];

  //caso base
  if(estagio_atual == 4) {
    for (long int cont = 0; cont <= strlen(string_de_retorno); cont++) {
      //substituição de X
      if (string_de_retorno[cont] == X) {
        for (long int cont2 = 0; cont2 <= strlen(regraX); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = regraX[cont2];
        }
      }
      //substituição de Y
      else if (string_de_retorno[cont] == 'Y'){ 
        for (long int cont2 = 0; cont2 <= strlen(regraY); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = regraY[cont2];
        }
      }
      //substituição pelo caractere atual
      else {
        string_auxiliar[strlen(string_auxiliar)] = string_de_retorno[cont];
      }
    }
    fprintf(arquivo_strings, "Estágio %d: ", estagio_atual);
    remover_caracteres(string_auxiliar);
    fputs(string_auxiliar, arquivo_strings);
    return "";
  }
  //primeiro estágio
  else if (estagio_atual == 1) {
    for (int cont = 0; cont < strlen(regraX); cont++) {
      string_auxiliar[strlen(string_auxiliar)] = regraX[cont];
    }
    fprintf(arquivo_strings, "Estágio %d: ", estagio_atual);
    fputs(string_auxiliar, arquivo_strings);
    fprintf(arquivo_strings, "\n");
    return gerar_sequencia(X, regraX, regraY, string_auxiliar, estagio_atual + 1, arquivo_strings);
  }
  
  else {
    //geração de sequencias
    for (long int cont = 0; cont <= strlen(string_de_retorno); cont++) {
      //substituição de X
      if (string_de_retorno[cont] == X) {
        for (long int cont2 = 0; cont2 <= strlen(regraX); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = regraX[cont2];
        }
      }
      //substituição de Y
      else if (string_de_retorno[cont] == 'Y'){ 
        for (long int cont2 = 0; cont2 <= strlen(regraY); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = regraY[cont2];
        }
      }
      //substituição pelo caractere atual
      else {
        string_auxiliar[strlen(string_auxiliar)] = string_de_retorno[cont];
      }
    }
    //contador de estágios
    if(estagio_atual < 4) {
    
    fprintf(arquivo_strings, "Estágio %d: ", estagio_atual);
    fputs(string_auxiliar, arquivo_strings);
    fprintf(arquivo_strings, "\n");
    }
  }
  //chamada recursiva
  return gerar_sequencia(X, regraX, regraY, string_auxiliar, estagio_atual + 1, arquivo_strings);
}


int main() {
  //declarações de variáveis
  char axioma; //axioma do fractal
  int graus; //grau de rotação usado para desenhar
  int estagios = 1; //identificação do fractal
  int n_do_fractal; //contador de interações
  char regraX[12], regraY[12]; //regras de formação do fractal
  char string_de_retorno[1000000]; //string usada para armazenar as sequencias geradas
  FILE *pont_estagios; //ponteiro para criação do arquivo .txt


  //criação e alocação de dados
  pont_estagios = fopen("estagios_fractal2.txt", "w"); //abertura e criação do arquivo final de sequencias
  scanf("%d %c %d%s%s", &n_do_fractal, &axioma, &graus, regraX, regraY);

  //chamando funções
  gerar_sequencia(axioma, regraX, regraY, regraX, estagios, pont_estagios);

  return 0;
  
}
