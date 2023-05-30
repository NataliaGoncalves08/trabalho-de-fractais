#include <stdio.h>
#include <string.h>

#define QUANT_ESTA 5

typedef struct 
{
  int Id;
  char Axioma[7];
  int Ang;
  char Regra[15];

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
  int Carac;

}anali_esta;

 
void analise_do_estagio (anali_esta atual[QUANT_ESTA], char* str_ref, int Estagio)
{
  atual [Estagio - 1].Estagio = 0;
  atual [Estagio - 1].Carac = 0;
  atual [Estagio - 1].Fs = 0;

  atual [Estagio - 1].Estagio = Estagio; 
  atual [Estagio - 1].Carac = strlen(str_ref);
  
  for(int i = 0; i < strlen(str_ref); i++)
  {
    if(str_ref[i] == 'F')
    {
      atual[Estagio - 1].Fs++;
    }
  }
}

void imprimir_analise(anali_esta atual[QUANT_ESTA], str_frac inicial)
{

  printf("\n Numero do fractal requerido: %d\n Axioma inicial: %s \n Angulo: %dº \n Regra de repetição %s \n quantidade de estágio : %d\n ",
 inicial.Id, inicial.Axioma, inicial.Ang, inicial.Regra, QUANT_ESTA);
  for(int i = 0; i<QUANT_ESTA; i++)
  {
    printf("\n Estagio %d: %5d F's - %5d caracteres ", atual[i].Estagio,  atual[i].Fs, atual[i].Carac);
  }
}

char* gerador_sequencias_fractais(str_frac p, processamento_frac *atual, anali_esta * caracte) 
{

  char string_auxiliar[1000000];

  //caso base
  if(atual->Estagio  == QUANT_ESTA) {
    for (long int cont = 0; cont <= strlen(atual->StrResult); cont++) {
      if (atual->StrResult[cont] == 'F') {
        for (long int cont2 = 0; cont2 <= strlen(p.Regra); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = p.Regra[cont2];
        }
      }
      else {
        string_auxiliar[strlen(string_auxiliar)] = atual->StrResult[cont];
      }
    }
    fprintf(atual->PontArqu , "Estágio %d: ", atual->Estagio );
analise_do_estagio(caracte, string_auxiliar, atual->Estagio);
    fputs(string_auxiliar, atual->PontArqu );

    return "Fim";
  }
  //primeira geração
   else if (atual->Estagio  == 1) {
     for (int cont = 0; cont < strlen(p.Axioma); cont++) {
        atual->StrResult[strlen(atual->StrResult)] = p.Axioma[cont];
      }
      fprintf(atual->PontArqu , "Estágio %d: ", atual->Estagio );
analise_do_estagio(caracte, atual->StrResult, atual->Estagio);
      fputs(atual->StrResult, atual->PontArqu );
      fprintf(atual->PontArqu , "\n");
      atual->Estagio ++;
      return gerador_sequencias_fractais(p, atual, caracte);
      
  } 
  //geração de caracteres
  else {
    for (long int cont = 0; cont <= strlen(atual->StrResult); cont++) {
      if (atual->StrResult[cont] == 'F') {
        for (long int cont2 = 0; cont2 <= strlen(p.Regra); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = p.Regra[cont2];
        }
      }
      else {
        string_auxiliar[strlen(string_auxiliar)] = atual->StrResult[cont];
      }
    }
    
    //copia de string_auxiliar para StrResult
    for(long int cont = 0; cont < strlen(string_auxiliar); cont++) {
      atual->StrResult[cont] = string_auxiliar[cont];
    }
    atual->StrResult[strlen(atual->StrResult)] = '\0';

    //gravação no arquivo
    fprintf(atual->PontArqu , "Estágio %d: ", atual->Estagio);
analise_do_estagio(caracte, atual->StrResult, atual->Estagio);
    fputs(atual->StrResult, atual->PontArqu );
    fprintf(atual->PontArqu , "\n");
  }
  atual->Estagio ++;
  return gerador_sequencias_fractais(p, atual, caracte);
}

int main() 
{
  //declarações de variáveis
  str_frac inicial;
  processamento_frac processamento;
  anali_esta caracteres_por_estagio [QUANT_ESTA];
  
  processamento.Estagio  = 1;
  //onde serão escritas as strings de cada Estagio   //FILE *regras; //tirar na versão final, serve apenas pra teste

  //atribuição de valores
  printf(" Insira o número do axioma desejado: ");
  scanf("%d", &inicial.Id);
  printf(" Insira o axioma inicial ");
  scanf("\n%[^\n]", inicial.Axioma);
  printf(" Insira o angulo ");
  scanf("%d", &inicial.Ang);
  printf(" Insira a regra de repetição ");
  scanf("\n%[^\n]", inicial.Regra);

  //abertura de arquivo
  processamento.PontArqu = fopen("Sequencias resultantes.txt", "w");

  //chamar função
  gerador_sequencias_fractais(inicial, &processamento, caracteres_por_estagio) ;

  imprimir_analise(caracteres_por_estagio, inicial);

  return 0;
  
} 
