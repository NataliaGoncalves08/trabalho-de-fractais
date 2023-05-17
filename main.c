#include <stdio.h>
#include <string.h>

char* gerar_sequencias(char F, char regra[15], char *string_de_retorno, int estagio_atual, FILE *arquivo_strings) {
  char string_auxiliar[1000000];
  if(estagio_atual == 4) {
    fprintf(arquivo_strings, "Estágio %d: ", estagio_atual);
    //fprintf(arquivo_strings, "%s\n", string_auxiliar);
    fputs(string_auxiliar, arquivo_strings);
    fprintf(arquivo_strings, "\n");
    
    return string_de_retorno;
  }
  else {
    for (long int cont = 0; cont <= strlen(string_de_retorno); cont++) {
      if (regra[cont] == F) {
        for (long int cont2 = 0; cont2 <= strlen(regra); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = regra[cont2];
        }
      }
      else {
        string_auxiliar[strlen(string_auxiliar)] = string_de_retorno[cont];
      }
    }
    if(estagio_atual < 4) {
    fprintf(arquivo_strings, "Estágio %d: ", estagio_atual);
    //fprintf(arquivo_strings, "%s\n", string_auxiliar);
    fputs(string_auxiliar, arquivo_strings);
    fprintf(arquivo_strings, "\n");
    }
  }
  return gerar_sequencias(F, regra, string_auxiliar, estagio_atual + 1, arquivo_strings);
}

int main() {
  //declarações de variáveis
  char axioma;
  int graus, estagios = 0;
  char regra[15];
  char string_de_retorno[1000000];
  FILE *pont_estagios;

  //criação e alocação de dados
  pont_estagios = fopen("estagios.txt", "w");
  scanf("%c %d %s", &axioma, &graus, regra);

  //chamando funções
  gerar_sequencias(axioma, regra, string_de_retorno, estagios, pont_estagios); //PARTE 1

  return 0;
  
}
