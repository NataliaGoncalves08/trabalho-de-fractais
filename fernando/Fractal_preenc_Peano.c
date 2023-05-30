#include <stdio.h>
#include <string.h>

#define QUANT_ESTA 5

typedef struct 
{
  int Id;
  char Axioma;
  int Ang;
  char RegraX[23], RegraY[23]; //regras de formação do fractal

}str_frac;

typedef struct 
{
  char StrResult[1000000];
  FILE *PontArqu;
  int Estagio;

}processamento_frac;

typedef struct 
{

  int Estagio;
  int Fs;
  int Xs;
  int Ys;
  int Carac;

}anali_esta;

void analise_do_estagio(anali_esta atual[QUANT_ESTA], char* str_ref, int Estagio)
{
  atual [Estagio - 1].Estagio = 0;
  atual [Estagio - 1].Carac = 0;
  atual [Estagio - 1].Fs = 0;
  atual [Estagio - 1].Xs = 0;
  atual [Estagio - 1].Ys = 0;

  atual [Estagio - 1].Estagio = Estagio;
  
  
  for(int i = 0; i < strlen(str_ref); i++)
  {
    if(str_ref[i] == 'F')
      atual[Estagio - 1].Fs++;
      
    else if(str_ref[i] == 'X')
      atual[Estagio - 1].Xs++;

    else if(str_ref[i] == 'Y')
      atual[Estagio - 1].Ys++;
  }
  atual [Estagio - 1].Carac = strlen(str_ref) - atual[Estagio - 1].Xs - atual[Estagio -1].Ys;
}

void limpa_str(char* str_ref, int tamanho)
{
  for(int i = 0; i < tamanho; i++)
    str_ref[i] = '\0';
}

void copiar_str(char* base, char* copia)
{
  for(int i = 0; i < strlen(base); i++)
    copia[i] = base[i];

  copia[strlen(base)] = '\0';
}

void remover_caracteres(char string_com_xy[1000000]) 
{
  char string_limpeza[1000000];
  
  //limpeza
  for(int i = 0; i < strlen(string_com_xy); i++)
    {
      if((string_com_xy[i] != 'X') && (string_com_xy[i] != 'Y')) 
      {
        string_limpeza[strlen(string_limpeza)] = string_com_xy[i];
      }
    }
  copiar_str(string_limpeza, string_com_xy);
}

void imprimir_analise(anali_esta atual[QUANT_ESTA], str_frac inicial)
{

  printf("\n Numero do fractal requerido: %d\n Axioma inicial: %c \n Angulo: %dº \n Regra de repetição X: %s \n Regra de repetição Y: %s \n quantidade de Estagio: %d\n\n",
 inicial.Id, inicial.Axioma, inicial.Ang, inicial.RegraX, inicial.RegraY, QUANT_ESTA);

  printf("  Estagio  |    F´s    |  Caracteres  |    X´s    |    Y´s   \n");
  
  for(int i = 0; i<=QUANT_ESTA; i++)
  {
    if(i<QUANT_ESTA)
      printf("     %d        %5d         %5d        %5d       %5d \n", atual[i].Estagio, atual[i].Fs, atual[i].Carac, atual[i].Xs, atual[i].Ys);
    else
      printf("\n Estagio final: %5d F's - %5d caracteres  - 0 X's - 0 Y's\n", atual[i].Fs, atual[i].Carac);
  }
}

char* gerador_sequencias_fractais(str_frac p, processamento_frac *atual, anali_esta* caracte) 
{
  char string_auxiliar[1000000];
  limpa_str(string_auxiliar, strlen(atual->StrResult));
  
  //caso base
  if(atual->Estagio == QUANT_ESTA) {
    for (long int cont = 0; cont <= strlen(atual->StrResult); cont++) {
      //substituição de X
      if (atual->StrResult[cont] == 'X') {
        for (long int cont2 = 0; cont2 <= strlen(p.RegraX); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = p.RegraX[cont2];
        }
      }
      //substituição de Y
      else if (atual->StrResult[cont] == 'Y'){ 
        for (long int cont2 = 0; cont2 <= strlen(p.RegraY); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = p.RegraY[cont2];
        }
      }
      //substituição pelo caractere atual
      else {
        string_auxiliar[strlen(string_auxiliar)] = atual->StrResult[cont];
      }
    }
    fprintf(atual->PontArqu, "\n-----------------------------------------------\n\n     ~-~-~ Estágio %d: ~-~-~\n\n", atual->Estagio);
    analise_do_estagio(caracte, string_auxiliar, atual->Estagio);
    remover_caracteres(string_auxiliar);
    analise_do_estagio(caracte, string_auxiliar, atual->Estagio+1);
    fputs(string_auxiliar, atual->PontArqu);
    return "fim";
  }
  //primeiro estágio
  else if (atual->Estagio == 1) {
    for (int cont = 0; cont < strlen(p.RegraX); cont++) {
      atual->StrResult[strlen(atual->StrResult)] = p.RegraX[cont];
    }
    fprintf(atual->PontArqu, "\n     ~-~-~ Estágio %d: ~-~-~\n\n", atual->Estagio);
    copiar_str(atual->StrResult, string_auxiliar);
    analise_do_estagio(caracte, atual->StrResult, atual->Estagio);
    remover_caracteres(string_auxiliar);
    
    fputs(string_auxiliar, atual->PontArqu);
    fprintf(atual->PontArqu, "\n");

    atual->Estagio++;
    return gerador_sequencias_fractais(p, atual, caracte);
  }
  
  else {
    //geração de sequencias
    
    for (long int cont = 0; cont <= strlen(atual->StrResult); cont++) {

      //substituição de X
      if (atual->StrResult[cont] == 'X') {

        for (long int cont2 = 0; cont2 <= strlen(p.RegraX); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = p.RegraX[cont2];
        }
      }
      //substituição de Y
      
      else if (atual->StrResult[cont] == 'Y'){ 
        for (long int cont2 = 0; cont2 <= strlen(p.RegraY); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = p.RegraY[cont2];
        }
      }
      //substituição pelo caractere atual
      else {
        string_auxiliar[strlen(string_auxiliar)] = atual->StrResult[cont];
      }
    }
    //contador de estágios
    if(atual->Estagio < QUANT_ESTA) {

    // for(int i = 0; i < strlen(string_auxiliar); i++)
    // atual->StrResult[i] = string_auxiliar[i];

    copiar_str(string_auxiliar, atual->StrResult);
    remover_caracteres(string_auxiliar);
    fprintf(atual->PontArqu, "\n-----------------------------------------------\n\n     ~-~-~ Estágio %d: ~-~-~\n\n", atual->Estagio);
    analise_do_estagio(caracte, atual->StrResult, atual->Estagio);
    fputs(string_auxiliar, atual->PontArqu);
    fprintf(atual->PontArqu, "\n");

    }
  }
  //chamada recursivap, atual
  atual->Estagio++;
  return gerador_sequencias_fractais(p, atual, caracte);
}
           
int main() 
{

  str_frac inicial;
  processamento_frac processamento;
  anali_esta caracteres_por_Estagio[QUANT_ESTA];

  //declarações de variáveis
  processamento.Estagio = 1;

  //criação e alocação de dados
  processamento.PontArqu = fopen("Sequencias resultantes.txt", "w"); //abertura e criação do arquivo final de sequencias

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
  gerador_sequencias_fractais(inicial, &processamento, caracteres_por_Estagio);

  imprimir_analise(caracteres_por_Estagio, inicial);

  return 0;

}
