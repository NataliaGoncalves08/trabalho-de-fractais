#include <stdio.h>
#include <string.h>

char* gerar_sequenciasN(char F, char regra[15], char *string_de_retorno, int estagio_atual, FILE *arquivo_strings) {
  
  char string_auxiliar[1000000]; //string usada para armazenar a string do estagio
  
  if(estagio_atual == 4) {
    
    fprintf(arquivo_strings, "Estágio %d:", estagio_atual);
    fputs(string_de_retorno, arquivo_strings);
    
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
    fputs(string_auxiliar, arquivo_strings);
    fprintf(arquivo_strings, "\n");
    }
  }
  
  return gerar_sequenciasN(F, regra, string_auxiliar, estagio_atual + 1, arquivo_strings);
}

char gerar_sequenciasF(char axioma[7], char regra[15], char *string_de_retorno, int estagio_atual, FILE *arquivo_strings) {
  
  char string_auxiliar[1000000];
  
  if(estagio_atual == 4) {
    fprintf(arquivo_strings, "Estágio %d: ", estagio_atual + 1);
    fputs(string_de_retorno, arquivo_strings);
    return *string_de_retorno;
  }
    
  else if (estagio_atual == 1) {
    for (int cont = 0; cont < strlen(axioma); cont++) {
      if (axioma[cont] == 'F') {
        for (int cont2 = 0; cont2 < strlen(regra); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = regra[cont2];
        }
      }
      else {
        string_auxiliar[strlen(string_auxiliar)] = axioma[cont];
      }
      
    }
    fprintf(arquivo_strings, "Estágio %d: ", estagio_atual + 1);
    fputs(string_auxiliar, arquivo_strings);
    fprintf(arquivo_strings, "\n");
    return gerar_sequenciasF(axioma, regra, string_auxiliar, estagio_atual + 1, arquivo_strings);
    
  } 
  else {
    for (long int cont = 0; cont <= strlen(string_de_retorno); cont++) {
      if (string_de_retorno[cont] == 'F') {
        for (long int cont2 = 0; cont2 <= strlen(regra); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = regra[cont2];
        }
      }
      else {
        string_auxiliar[strlen(string_auxiliar)] = string_de_retorno[cont];
      }
    }
    
    if(estagio_atual < 4) {
    fprintf(arquivo_strings, "Estágio %d: ", estagio_atual + 1);
    fputs(string_auxiliar, arquivo_strings);
    fprintf(arquivo_strings, "\n");
    }
  }
  return gerar_sequenciasF(axioma, regra, string_auxiliar, estagio_atual + 1, arquivo_strings);
}

int main() {
  //declarações de variáveis
  char axiomaN;
  char axiomaF[7]; //caso F
  char P; //apenas pra testar entre o fractal dos dois, tirar na versão final
  int graus, n_do_fractal, estagios = 0;
  char regra[15];
  char string_de_retorno[1000000];
  FILE *pont_estagios; //onde serão escritas as strings de cada estagio
  FILE *regras; //tirar na versão final, serve apenas pra teste

  //criação e alocação de dados

  
  //tirar na versão final
  scanf("%c", &P);
  if(P == 'n') {
    regras = fopen("regras_1N.txt", "r");
    fscanf(regras, "%d %c %d %s", &n_do_fractal, &axiomaN, &graus, regra);
    pont_estagios = fopen("estagios_fractal1.txt", "w");
    fprintf(pont_estagios, "Estágio 1: F\n");
    gerar_sequenciasN(axiomaN, regra, string_de_retorno, estagios + 1, pont_estagios);
  } //funcionando! 
    
  else {
    regras = fopen("regras_1F.txt", "r");
    fscanf(regras, "%d %s %d %s", &n_do_fractal, axiomaF, &graus, regra);
    fprintf(pont_estagios, "Estágio 1: F+F+F+F");
    pont_estagios = fopen("estagios_fractal1.txt", "w");
    gerar_sequenciasF(axiomaF, regra, string_de_retorno, estagios + 1, pont_estagios);
  } //sua versão de gerar_sequencias tem um problema, quando eu coloco as entradas diretamente do teclado ocorre erros nas strings. Tente consertar, a funcão funciona perfeitamente se as entradas estiverem corretas, ja testei em outro lugar
  //tirar na versão final

  return 0;
  
} 
