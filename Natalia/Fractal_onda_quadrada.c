#include <stdio.h>
#include <string.h>

char* gerar_sequencias(char F, char regra[15], char *string_de_retorno, int estagio_atual, FILE *arquivo_strings) {
  char string_auxiliar[1000000];
  
  if(estagio_atual == 4) {
    //troca de valores
    for (long int cont = 0; cont <= strlen(string_de_retorno); cont++) {
      
      //substituição pela regra
      if (regra[cont] == F) {
        for (long int cont2 = 0; cont2 <= strlen(regra); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = regra[cont2];
        }
      }
        
      //substituição pelo caractere atual
      else {
        string_auxiliar[strlen(string_auxiliar)] = string_de_retorno[cont];
      }
    }
    fprintf(arquivo_strings, "Estágio %d: ", estagio_atual);
    fputs(string_auxiliar, arquivo_strings);
    return "";
  }
  else {
    //troca de valores
    for (long int cont = 0; cont <= strlen(string_de_retorno); cont++) {
      
      //substituição pela regra
      if (regra[cont] == F) {
        for (long int cont2 = 0; cont2 <= strlen(regra); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = regra[cont2];
        }
      }
        
      //substituição pelo caractere atual
      else {
        string_auxiliar[strlen(string_auxiliar)] = string_de_retorno[cont];
      }
    }
    
    //contador de estagios
    if(estagio_atual < 4) {
      fprintf(arquivo_strings, "Estágio %d: ", estagio_atual);
      fputs(string_auxiliar, arquivo_strings);
      fprintf(arquivo_strings, "\n");
    }
  }
  //chamada recursiva
  return gerar_sequencias(F, regra, string_auxiliar, estagio_atual + 1, arquivo_strings);
}

int main() {
  //declarações de variáveis
  char axioma; //axioma do fractal
  int graus; //grau de rotação usado para desenhar
  int n_do_fractal; //identificação do fractal
  int estagios = 1; //contador de interações
  char regra[15]; //regra de formação do fractal
  char string_de_retorno[1000000]; //string usada para armazenar as sequencias geradas
  FILE *pont_estagios; //ponteiro para criação do arquivo .txt

  //criação e alocação de dados
  pont_estagios = fopen("estagios_fractal1.txt", "w"); //abertura e criação do arquivo final de sequencias
  scanf("%d %c %d %s", &n_do_fractal, &axioma, &graus, regra);

  //chamando funções
  gerar_sequencias(axioma, regra, string_de_retorno, estagios, pont_estagios);

  return 0;
  
}
