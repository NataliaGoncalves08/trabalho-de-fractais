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

void limpeza(char *string, char *string_de_retorno) {
  for(long int cont = 0; cont < strlen(string_de_retorno); cont++) {
    string[cont] = '\0';
  }
}

char* gerar_sequencia(char *regraX, char *regraY, char *string_de_retorno, char* string_auxiliar, int estagio, FILE *arquivo_strings) {
  limpeza(string_auxiliar, string_de_retorno); //limpo a string auxiliar para um novo processamento
  
  if (estagio == 1) {
    for(int cont = 0; cont < strlen(regraX); cont++) {
      string_de_retorno[cont] = regraX[cont];
      string_auxiliar[cont] = regraX[cont];
    }
    remover_caracteres(string_auxiliar);
    fprintf(arquivo_strings, "Estágio %d: ", estagio);
    fputs(string_auxiliar, arquivo_strings);
    return gerar_sequencia(regraX, regraY, string_de_retorno, string_auxiliar, estagio + 1, arquivo_strings); 
    
  }
    
  else if(estagio == 4) {
    for (long int cont = 0; cont <= strlen(string_de_retorno); cont++) {
      //substituição de X
      if (string_de_retorno[cont] == 'X') {
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
    remover_caracteres(string_auxiliar);
    fprintf(arquivo_strings, "\nEstágio %d: ", estagio);
    fputs(string_auxiliar, arquivo_strings);
    return "";
  }
  else {
    for (long int cont = 0; cont <= strlen(string_de_retorno); cont++) {
      //substituição de X
      if (string_de_retorno[cont] == 'X') {
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
    //copia das strings
    for (long int cont = 0; cont < strlen(string_auxiliar); cont++) {
      string_de_retorno[cont] = string_auxiliar[cont];
    }
    remover_caracteres(string_auxiliar);
    fprintf(arquivo_strings, "\nEstágio %d: ", estagio);
    fputs(string_auxiliar, arquivo_strings);
    limpeza(string_auxiliar, string_de_retorno);
    return gerar_sequencia(regraX, regraY, string_de_retorno, string_auxiliar, estagio + 1, arquivo_strings); 
  }
}

int main() {
  //declarações de variáveis
  char axioma; //axioma do fractal
  int graus; //grau de rotação usado para desenhar
  int estagio = 1; //contador de interações
  int n_do_fractal; //identificação do fractal
  char regraX[12];
  char regraY[12]; //regras de formação do fractal
  char string_de_retorno[1000000]; //string usada para armazenar as sequencias geradas
  char string_auxiliar[1000000];
  FILE *pont_estagios; //ponteiro para criação do arquivo .txt

  //criação e alocação de dados
  pont_estagios = fopen("estagios_fractal2.txt", "w"); //abertura e criação do arquivo 
  
  printf("Digite o número do fractal: ");
  scanf("%d", &n_do_fractal);
  printf("Digite o axioma: ");
  scanf("\n%[^\n]", &axioma);
  printf("Digite o ângulo: ");
  scanf("%d", &graus);
  printf("Digite a regra de formação X: ");
  scanf("\n%[^\n]", regraX);
  printf("Digite a regra de formação Y: ");
  scanf("\n%[^\n]", regraY);

  fprintf(pont_estagios, "Número do fractal: %d\nAxioma: %c\nÂngulo: %d\nRegra de formação X: %s\nRegra de Formação Y: %s\n\n", n_do_fractal, axioma, graus, regraX, regraY);

  //chamando funções
  gerar_sequencia(regraX, regraY, string_de_retorno, string_auxiliar, estagio, pont_estagios);

  fclose(pont_estagios);
  return 0;
} 
