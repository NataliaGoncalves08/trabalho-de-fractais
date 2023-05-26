#include <stdio.h>
#include <string.h>

#define QUANT_ESTA 4

typedef struct 
{
  int Id;
  char Axioma;
  int Ang;
  char RegraX[23], RegraY[23]; //regras de formação do fractal

}str_frac;

typedef struct 
{
  char string_de_retorno[1000000];
  FILE *pont_estagios;
  int estagios;

}processamento_frac;

typedef struct 
{

  int estagio;
  int Fs;
  int Xs;
  int Ys;
  int Carac;

}anali_esta;

void analise_do_estagio(anali_esta atual[QUANT_ESTA], char* str_ref, int estagio)
{
  atual [estagio - 1].estagio = 0;
  atual [estagio - 1].Carac = 0;
  atual [estagio - 1].Fs = 0;
  atual [estagio - 1].Xs = 0;
  atual [estagio - 1].Ys = 0;

  atual [estagio - 1].estagio = estagio;
  atual [estagio - 1].Carac = strlen(str_ref);
  
  for(int i = 0; i < strlen(str_ref); i++)
  {
    if(str_ref[i] == 'F')
      atual[estagio - 1].Fs++;
      
    else if(str_ref[i] == 'X')
      atual[estagio - 1].Xs++;

    else if(str_ref[i] == 'Y')
      atual[estagio - 1].Ys++;
  }
}

void remover_caracteres(char *string_com_xy) 
{
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

void imprimir_analise(anali_esta atual[QUANT_ESTA], str_frac inicial)
{

  printf("\n Numero do fractal requerido: %d\n Axioma inicial: %c \n Angulo: %dº \n Regra de repetição X: %s \n Regra de repetição Y: %s \n quantidade de estagios: %d\n\n",
 inicial.Id, inicial.Axioma, inicial.Ang, inicial.RegraX, inicial.RegraY, QUANT_ESTA);
  for(int i = 0; i<=QUANT_ESTA; i++)
  {
    if(i<QUANT_ESTA)
      printf(" Estagio %d: %5d F's - %5d caracteres  - %5d X's - %5d Y's\n", atual[i].estagio, atual[i].Fs, atual[i].Carac, atual[i].Xs, atual[i].Ys);
    else
      printf("\n Estagio final: %5d F's - %5d caracteres  - 0 X's - 0 Y's\n", atual[i].Fs, atual[i].Carac);
  }
}

void copiar_str(char* base, char* copia)
{
  for(int i = 0; i < strlen(base); i++)
    copia[i] = base[i];

  copia[strlen(base)] = '\0';
}

char* gerar_sequencia(str_frac p, processamento_frac *atual, anali_esta* caracte) 
{
  char string_auxiliar[1000000];

  //caso base
  if(atual->estagios == QUANT_ESTA) {
    for (long int cont = 0; cont <= strlen(atual->string_de_retorno); cont++) {
      //substituição de X
      if (atual->string_de_retorno[cont] == 'X') {
        for (long int cont2 = 0; cont2 <= strlen(p.RegraX); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = p.RegraX[cont2];
        }
      }
      //substituição de Y
      else if (atual->string_de_retorno[cont] == 'Y'){ 
        for (long int cont2 = 0; cont2 <= strlen(p.RegraY); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = p.RegraY[cont2];
        }
      }
      //substituição pelo caractere atual
      else {
        string_auxiliar[strlen(string_auxiliar)] = atual->string_de_retorno[cont];
      }
    }
    fprintf(atual->pont_estagios, "Estágio %d: ", atual->estagios);
    analise_do_estagio(caracte, string_auxiliar, atual->estagios);
    remover_caracteres(string_auxiliar);
    analise_do_estagio(caracte, string_auxiliar, atual->estagios+1);
    fputs(string_auxiliar, atual->pont_estagios);
    return "fim";
  }
  //primeiro estágio
  else if (atual->estagios == 1) {
    for (int cont = 0; cont < strlen(p.RegraX); cont++) {
      atual->string_de_retorno[strlen(atual->string_de_retorno)] = p.RegraX[cont];
    }
    fprintf(atual->pont_estagios, "Estágio %d: ", atual->estagios);
    analise_do_estagio(caracte, atual->string_de_retorno, atual->estagios);
    fputs(atual->string_de_retorno, atual->pont_estagios);
    fprintf(atual->pont_estagios, "\n");
    
    atual->estagios++;
    return gerar_sequencia(p, atual, caracte);
  }
  
  else {
    //geração de sequencias
    for (long int cont = 0; cont <= strlen(atual->string_de_retorno); cont++) {
  
      //substituição de X
      if (atual->string_de_retorno[cont] == 'X') {

        for (long int cont2 = 0; cont2 <= strlen(p.RegraX); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = p.RegraX[cont2];
        }
      }
      //substituição de Y
      else if (atual->string_de_retorno[cont] == 'Y'){ 
        for (long int cont2 = 0; cont2 <= strlen(p.RegraY); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = p.RegraY[cont2];
        }
      }
      //substituição pelo caractere atual
      else {
        string_auxiliar[strlen(string_auxiliar)] = atual->string_de_retorno[cont];
      }
    }
    //contador de estágios
    if(atual->estagios < 4) {

    // for(int i = 0; i < strlen(string_auxiliar); i++)
    // atual->string_de_retorno[i] = string_auxiliar[i];

    copiar_str(string_auxiliar, atual->string_de_retorno);
      
    fprintf(atual->pont_estagios, "Estágio %d: ", atual->estagios);
    analise_do_estagio(caracte, atual->string_de_retorno, atual->estagios);
    fputs(atual->string_de_retorno, atual->pont_estagios);
    fprintf(atual->pont_estagios, "\n");

    }
  }
  //chamada recursivap, atual
  atual->estagios++;
  return gerar_sequencia(p, atual, caracte);
}

int main() 
{

  str_frac inicial;
  processamento_frac processamento;
  anali_esta caracteres_por_estagio[QUANT_ESTA];

  //declarações de variáveis
  processamento.estagios = 1;

  //criação e alocação de dados
  processamento.pont_estagios = fopen("estagios_fractal2.txt", "w"); //abertura e criação do arquivo final de sequencias

  printf(" Insira o número do axioma desejado: ");
  scanf("%d", &inicial.Id);
  printf(" Insira o axioma inicial: ");
  scanf("%s", &inicial.Axioma);
  printf(" Insira o angulo ");
  scanf("%d", &inicial.Ang);
  printf(" Insira a regra de repetição X ");
  scanf("\n%[^\n]", inicial.RegraX);
  printf(" Insira a regra de repetição Y ");
  scanf("\n%[^\n]", inicial.RegraY);
  
  //chamando funções
  gerar_sequencia(inicial, &processamento, caracteres_por_estagio);

  imprimir_analise(caracteres_por_estagio, inicial);
  
  return 0;
  
}
