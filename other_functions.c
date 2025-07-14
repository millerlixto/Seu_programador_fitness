#include <stdio.h>
#include<ctype.h>
#include<string.h>
#include<tgmath.h>
#include<stdlib.h>
#include "user.h"
#include"other_functions.h"


#define TAM_NOME 50
#define TAM_LINHA 256
#define QUANT_ALIMENTO 40
#define QUANT_ALIMENT_pGRUPOS 11

/**************funções genéricas****************/

//recede a intesidade da atividade física
void definir_fator_atividade_ativo(ativ_fisica *at){
// verificação,  1<= inteiro <=5
int return_scanf;
int valida = 0;
do{
printf("\nDiga qual a intensidade de 0 a 4, sendo:\n\n");
printf("- 0 para sedentario(trabalha de escritorio, passa maior parte do dia sentado.\n \n"); 
printf("- 1para levemente ativo(Caminhadas curtas, tarefas domesticas leves, subir escadas ocasionalmente.)\n\n");
printf("- 2 para moderadamente ativo(Corrida leve, natacao, ciclismo, musculacao ou aulas de ginastica na academia.)\n\n");
printf("- 3 para muito ativo(Maratonistas, atletas que treinam quase todos os dias, esportes coletivos de alta intensidade, musculacao pesada frequente.)\n\n");
printf("- 4 para extremamente ativo(Atletas de alta performance, trabalhos com grande esforço físico contínuo (ex: construção civil).)");

return_scanf = scanf(" %d", &at->intensidade);

if(return_scanf != 1){

printf("Erro: duracao invalida. Apenas numeros inteiros.\n");
// Limpa buffer
            int limp;
            while ((limp = getchar()) != '\n' && limp != EOF);
}else if(at->intensidade < 0 || at->intensidade >4){
printf("Erro: intensidade invalida. Fora do intervalo (0 a 4).\n");
// Limpa buffer
            int limp;
            while ((limp = getchar()) != '\n' && limp != EOF);
}else{
valida = 1;
// Limpa buffer
            int limp;
            while ((limp = getchar()) != '\n' && limp != EOF);
}
}while(!valida);
}

//recede a intesidade da atividade física de usuários menos ativo
void definir_fator_atividade_MenosAtivo(ativ_fisica *at){
// verificação,  1<= inteiro <=5
int return_scanf;
int valida = 0;
do{
printf("\nSelecione a opcao que mais combina com seu estilo de vida: 0 ou 1, sendo:\n");
printf("-0 para sedentario(trabalha de escritorio, passa maior parte do dia sentado. \n\n"); 
printf("-1 para levemente ativo(Caminhadas curtas, tarefas domesticas leves, subir escadas ocasionalmente.)\n");

return_scanf = scanf(" %d", &at->intensidade);

if(return_scanf != 1){

printf("Erro: duracao invalida. Apenas numeros inteiros.\n");
// Limpa buffer
            int limp;
            while ((limp = getchar()) != '\n' && limp != EOF);
}else if(at->intensidade < 0 || at->intensidade >1){
printf("Erro: intensidade invalida. Fora do intervalo (1 e 2).\n");
// Limpa buffer
            int limp;
            while ((limp = getchar()) != '\n' && limp != EOF);
}else{
valida = 1;
// Limpa buffer
            int limp;
            while ((limp = getchar()) != '\n' && limp != EOF);
}
}while(!valida);
}

//MET(fator de ativiadade física)
float valor_MET_User(ativ_fisica *at) {
    float met = 0.0;
    switch (at->intensidade) {
        case 0:
            met = 1.2;
            printf("Sedentario\n");
            break;
        case 1:
            met = 1.375;
            printf("Levemente ativo\n");
            break;
        case 2:
            met = 1.55;
            printf("Moderadamente ativo\n");
            break;
        case 3:
            met = 1.725;
            printf("Muito ativo\n");
            break;
        case 4:
            met = 1.9;
            printf("Extremamente Ativo\n");
            break;
    }
    return met;
}

//ler string do teclado
void ler_string(char *buffer, int tamanho, const char *mensagem) {
    printf("%s", mensagem);
    if (fgets(buffer, tamanho, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}
//limpa o buffer
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**************conversões****************/

// Converter centímetros para metros
double convert_Cm_Para_Metro(user *u) {
    double Altura_M = u->altura/100;
  return Altura_M ;
}

/**************calculos****************/

//calcula o taxa de metabolismo basal, usando fator de atividades
double calc_TMB(user *u){ 

      double tmb = 0;
//masculino
      double const HarrisBenedict_m = 88.362; //constante de Harris Benedict para sexo Masculino
      double const coef_peso_m = 13.397;//coeficiente do peso de Harris Benedict para sexo Masculino 
      double const coef_altura_m = 4.799;//coeficiente da altura de Harris Benedict para sexo Masculino 
      double const coef_idade_m = 5.677;//coeficiente da idade de Harris Benedict para sexo Masculino 
//feminino
      double const HarrisBenedict_f = 447.593; //constante de Harris Benedict para sexo feminino
      double const coef_peso_f = 9.247;//coeficiente do peso de Harris Benedict para sexo feminino
      double const coef_altura_f = 3.098;//coeficiente da altura de Harris Benedict para sexo feminino 
      double const coef_idade_f = 4.330;//coeficiente da idade de Harris Benedict para sexo feminino

   char sexo = u->sexo ;
   //conversão para minusculo
   sexo = tolower(sexo);
   
   
   if(sexo == 'm'){
    //TMB_masculino = 88,362+(13,397×peso)+(4,799×altura)−(5,677×idade)
tmb =  HarrisBenedict_m + (  coef_peso_m * u->peso ) + ( coef_altura_m * u->altura ) - ( coef_idade_m * u->idade);
   }else{
    //TMB_feminino = 447,593+(9,247×peso)+(3,098×altura)−(4,330×idade)
tmb =  HarrisBenedict_f + ( coef_peso_f * u->peso ) + ( coef_altura_f * u->altura ) - ( coef_idade_f * u->idade);
   }
   return tmb;
}

//calculo do energetico  total
double calc_GET(ativ_fisica *at, user *u) {
    float met = valor_MET_User(at);
    double tmb = calc_TMB(u);
    return met * tmb;
}
//calcula o indice de maça corporal
void calc_IMC(user *u){
double altura = convert_Cm_Para_Metro(u);
double imc = u->peso/pow(altura,2.0);

if (imc < 18.5) {
    printf("IMC: Abaixo do peso ideal\n");
} else if (imc >= 18.5 && imc <= 24.9) {
    printf("IMC: No peso ideal\n");
} else if (imc >= 25.0 && imc <= 29.9) {
    printf("IMC: Acima do peso ideal\n");
} else if (imc >= 30.0) {
    printf("IMC: Muito acima do peso ideal\n");
}

return;
}

/**************seleção de alimento no menu****************/

void select_menu(select_alimento *sa){

char linha[TAM_LINHA];
char alimentos [QUANT_ALIMENTO][TAM_NOME];
int total =0;


    FILE *f = fopen ("Menu.txt" ,"r");

    if(!f){
    perror("erro ao abrir arquivo");
     return;
     }

    char *token;
    const char s[2] = ",";

    while(fgets(linha, sizeof(linha), f)!=NULL){
    linha[strcspn (linha, "\n")]='\0';

    token = strtok(linha, s);

   int i = 0;
    while(token != NULL && total < QUANT_ALIMENTO){
        strcpy(alimentos [total], token);
        token = strtok(NULL, s);
        total++;
      }
    }
    fclose(f);
   /**************impressão e seleção (função com erro)****************/


int escolha = -1;
int grupo = 0; 
int inicio = grupo * 10;  

sa = malloc(sizeof(select_alimento));

printf("Selecione um alimento do grupo %d:\n\n", grupo + 1);

// Imprime os 10 alimentos com índice de 1 a 10
for (int i = 0; i < 10; i++) {
    printf("%d - %s\n", i + 1, alimentos[inicio + i]);
}

// Lê a escolha
printf("\nDigite o numero do alimento desejado: ");
scanf("%d", &escolha);

// Valida e salva
if (escolha >= 1 && escolha <= 10) {
    strcpy(sa->alimentos_escolhidos[grupo], alimentos[inicio + escolha - 1]);
    printf("Voce escolheu: %s\n", sa->alimentos_escolhidos[grupo]);
} else {
    printf("Escolha inválida.\n");
 }

 printf("alimento: %s\n",sa->alimentos_escolhidos[0]);
}

    

  


/**************impressão****************/

//função imprime os dados other_functions
void imprimir_Dados_Other_Functions(ativ_fisica *at, user *u) {

    printf("Gasto calorico total (MET): %.2f\n", valor_MET_User(at));
    printf("Taxa de Metabolismo Basal (TMB): %.2f\n", calc_TMB(u));
    printf("Gasto Engergetico Total (GET): %.2f\n", calc_GET(at, u));

    
}
