#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <tgmath.h>
#include <stdlib.h>
#include "user.h"
#include "other_functions.h"


#define TAM_NOME 50
#define TAM_LINHA 256
#define QUANT_ALIMENTO 55

#define GRUPO 5
#define NOME 50
#define QNT_ALIMENTO 11

#define PESOS 26
#define INTERVALO_PESO 5

/***********************************************/
/**************FUNÇÕES GENÉRICAS****************/
/***********************************************/

int aproxima_peso(user* u) {

/**********************************************aproxima_peso************************************************************
* A função recebe o peso da struct user e aproxima segundo o arquivo macros_tabela.txt, que está em intervalos de 5kg. *
* Parâmetros:                                                                                                          *
*  - user *u: aponta para struct com as informações do peso do usuário                                                 *
* Retorno:                                                                                                             *
*  - peso aproximado (int).                                                                                            *
************************************************************************************************************************/

 // Verifica se o peso do usuário foi atribuído corretamente
    if (u->peso <= 0) {
        printf("Erro: peso do usuario nao foi definido. ");
       exit(1);
    }
     /****************************************
     * Alocando memória para vetor de pesos *
     ****************************************/
    int* peso = (int*)malloc(PESOS * sizeof(int));
    if (peso == NULL) {
        printf("Erro: memória não alocada\n");
        exit(1);
    }
     /*****************************************
     * Preenchendo o vetor com INTERVALO_PESO *
     ******************************************/

    for (int i = 0; i < PESOS; i++) {
        peso[i] = (i + 1) * INTERVALO_PESO;
    }
     /********************************
     * Convertendo o peso do usuário *
     *********************************/
    // Converte o peso do usuário (float) para int 
    int peso_convertido = (int)(u->peso + 0.5);  

    /***********************************
     * Encontrando o peso mais próximo *
     ***********************************/
     
    int indice_mais_proximo = 0;
    int menor_diferenca = abs(peso[0] - peso_convertido);  // diferença inicial

    for (int i = 1; i < PESOS; i++) {
        int diferenca = abs(peso[i] - peso_convertido);
        if (diferenca < menor_diferenca) {
            menor_diferenca = diferenca;
            indice_mais_proximo = i;
        }
    }

   int peso_aproximado = peso[indice_mais_proximo];  
    free(peso);  // libera a memória alocada

    return peso_aproximado;  
}

/*************************remove_espacos_str***********************
* A função remove espaços em branco no início e fim de uma string *
* Parâmetros:                                                     *
*  - srt: string destino, a qual se pretende remover os espaços   *
* Retorno:                                                        *
*  - string sem espaços a esquerda e a direita                    *
*******************************************************************/

void remove_espacos_str(char *str) {
    char *inicio = str; // percorrer do início da string
    char *fim;          // encontrará o final da string

    /******************************
    * Removendo espaços do início *
    *******************************/

    // 'inicio' avança até encontrar o primeiro caractere útil.
    while (*inicio == ' ' || *inicio == '\t' || *inicio == '\n') {
        inicio++;
    }
    // Se houve espaços a esquerda 'memmove' move os dados úteis para o início da string.
    // Sobrescrevendo os espaços iniciais.
    if (str != inicio) {

    /**************************************************memmove*****************************************************************
    * strlen(inicio) calcula o tamanho dos caracteres úteis (sem contar espaços no início).                                   *
    * + 1 é adicionado para incluir o caractere, que indica o fim da string.                                                  *
    *  A função 'memmove(destino, origem, tamanho)' move a parte útil da string para o início. Removendo os espaços iniciais. *
    ***************************************************************************************************************************/
        memmove(str, inicio, strlen(inicio) + 1); 
    }

    /**************************
    * Remove espaços do final *
    ***************************/

    // 'fim' aponta para o último caractere da string 
    // strlen(inicio) calcula o tamanho dos caracteres úteis (sem contar espaços no início).
    //str + strlen(str) joga o ponteiro para o caracter nulo '\0' (fim de estring) 
    //por isso -1 ajusta o ponteiro para voltar ao ultimo caracter útil
    fim = str + strlen(str) - 1;

    
    
    // substitui por '\0' e anda para trás, até um caracter útil.
    while (fim >= str && (*fim == ' ' || *fim == '\t' || *fim == '\n')) {
        *fim = '\0'; // Remove o caractere colocando fim de string
        fim--;       // Volta um caractere
    }
}

/***************************************definir_fator_atividade_ativo**************************************
* A função guarda o fator de atividade física(usuários ativos) em  struct ativ_fisica                     *
* Parâmetros:                                                                                             *
*  - ativ_fisica *at: aponta para a struct que vai copiar a intensidade da atividade física (nível 0 a 4) *
* Retorno:                                                                                                *
*  - void                                                                                                 *
***********************************************************************************************************/

void definir_fator_atividade_ativo(ativ_fisica  *at){


int return_scanf;// 1<= inteiro <=5
int valida = 0;

/*****************************************
* Selecionando nível de atividade física *
******************************************/

do{
printf("\nDiga qual a intensidade de 0 a 4, sendo:\n\n");
printf("- 0 para sedentario(trabalha de escritorio, passa maior parte do dia sentado.: \n \n"); 
printf("- 1 para levemente ativo(Caminhadas curtas, tarefas domesticas leves, subir escadas ocasionalmente.): \n\n");
printf("- 2 para moderadamente ativo(Corrida leve, natacao, ciclismo, musculacao ou aulas de ginastica na academia.): \n\n");
printf("- 3 para muito ativo(Maratonistas, atletas que treinam quase todos os dias, esportes coletivos de alta intensidade, musculacao pesada frequente.)\n\n");
printf("- 4 para extremamente ativo(Atletas de alta performance, trabalhos com grande esforco fisico continuo (ex: construcao civil).): \n");

/**********************
* Verificando entrada *
***********************/
//O scanf retorna o numero de leituras com sucesso 
//0 se a conversão falhou e EOF(-1), se chegou ao fim do arquivo
//ou houve erro de leitura
return_scanf = scanf(" %d", &at->intensidade);
limpar_buffer();

if(return_scanf != 1){//um argumento esperado, retorno do scanf 1.
printf("Erro: intensidade invalida. Apenas numeros inteiros.\n");
limpar_buffer();
}else if(at->intensidade < 0 || at->intensidade >4){//verifica entrada no intervalo de 0 à 4
printf("Erro: intensidade invalida. Fora do intervalo (0 a 4).\n");
limpar_buffer();
}else{
valida = 1;
limpar_buffer();
}
}while(!valida);

//*****************impressão de validação******************
// printf("Intensidade escolhida: %d\n", at->intensidade) 

}

/*************************************definir_fator_atividade_MenosAtivo***********************************
* A função guarda o fator de atividade física(usuários menos ativos) em  struct ativ_fisica               *
* Parâmetros:                                                                                             *
*  - ativ_fisica *at: aponta para a struct que vai copiar a intensidade da atividade física (nível 1 à 2) *
* Retorno:                                                                                                *
*  - void                                                                                                 *
***********************************************************************************************************/

void definir_fator_atividade_MenosAtivo(ativ_fisica *at){

int return_scanf;// tratamento de entrada
int valida = 0;
/*****************************************
* Selecionando nível de atividade física *
******************************************/
do{
printf("\nSelecione a opcao que mais combina com seu estilo de vida: 0 ou 1, sendo:\n\n");
printf("-0 para sedentario(trabalha de escritorio, passa maior parte do dia sentado. \n\n"); 
printf("-1 para levemente ativo(Caminhadas curtas, tarefas domesticas leves, subir escadas ocasionalmente.)\n");


//O scanf retorna o numero de leituras com sucesso 
//0 se a conversão falou e EOF(-1), se chegou ao fim do arquivo
//ou houve erro de leitura
return_scanf = scanf(" %d", &at->intensidade);
limpar_buffer();

if(return_scanf != 1){//um argumento esperado, retorno so scanf 1.
printf("Erro: intensidade invalida. Apenas numeros inteiros.\n");
limpar_buffer();
}else if(at->intensidade < 0 || at->intensidade > 1){
printf("Erro: intensidade invalida. Fora do intervalo (0 ou 1).\n");
limpar_buffer();
}else{
valida = 1;
limpar_buffer();
}
}while(!valida);
}

/*************************************************valor_MET_User********************************************************
* A função recebe a intensidade da atividade física e seleciona do MET(fator de ativiadade física)                     *
* Parâmetros:                                                                                                          *
*  - ativ_fisica *at: aponta para a struct com a informação da intensidade da atividade física, (nível 0 a 4 ou 1 à 2) *
* Retorno:                                                                                                             *
*  - o MET(float)                                                                                                      *
************************************************************************************************************************/

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

/**********************************************ler_string**************************************************************
* A função mostra uma mensagem personalizada ao usuário, lê uma string do teclado (com fgets) e remove o caractere de *
* nova linha \n que fgets coloca no final da string (se presente).                                                    *
* Parâmetros:                                                                                                         *
*  -char *buffer: local onde a string digitada será armazenada.                                                       *
*  -int tamanho: número máximo de caracteres a serem lidos (incluindo o de fim de string).                            *
* -const char *mensagem: texto que vai ser mostrado antes da leitura.                                                 *
* Retorno:                                                                                                            *
*  -void                                                                                                              *
***********************************************************************************************************************/

void ler_string(char *buffer, int tamanho, const char *mensagem) {
    printf("%s", mensagem);//mensagem que vai ser passada na leitura
    if (fgets(buffer, tamanho, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';//substiue o "\n"por '\0'
    }
}

/************************************limpa Buffer**********************************************
* A função lê um caractere por vez e descarta, continua até encontrar um fim da linha ou EOF. *
* Parâmetros:                                                                                 *
*  -Sem argumento.                                                                            *
* Retorno:                                                                                    *
*  - void.                                                                                    *
***********************************************************************************************/

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/***********************************************/
/******************CONVERSÕES*******************/
/***********************************************/

/********************convert_Cm_Para_Metro***********************
*A função converter altura que chega em centímetros para metros *
*Parâmetros:                                                    *
*  -user *u aponta para struct com as informações da altura     *
*Retorno:                                                       *
*  - Altura em metros (double).                                 *
*****************************************************************/

double convert_Cm_Para_Metro(user *u) {
    //printf("altura_c: %d\n", u->altura );//impressão de validação
    double Altura_M = u->altura/100.0;
   // printf("altura_M: %.2f\n", Altura_M); //impressão de validação
  return Altura_M ;
}

/***********************************************/
/******************CÁLCULOS*********************/
/***********************************************/

/*****************************calc_TMB*************************************************
*A função cálculo da Taxa Metabólica Basal (TMB) segundo a fórmula de Harris-Benedict *
*Parâmetros:                                                                          *
*  -user *u aponta para struct com as informações da altura, peso, idade, sexo        *
*Retorno:                                                                             *
*  - TMB (double).                                                                    *
***************************************************************************************/

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
   
   /**********************************
    * calculo do TMB para sexo M e F *
    **********************************/
   if(sexo == 'm'){
    //TMB_masculino = 88,362+(13,397×peso)+(4,799×altura)−(5,677×idade)
tmb =  HarrisBenedict_m + (  coef_peso_m * u->peso ) + ( coef_altura_m * u->altura ) - ( coef_idade_m * u->idade);
   }else{
    //TMB_feminino = 447,593+(9,247×peso)+(3,098×altura)−(4,330×idade)
tmb =  HarrisBenedict_f + ( coef_peso_f * u->peso ) + ( coef_altura_f * u->altura ) - ( coef_idade_f * u->idade);
   }
   return tmb;
}

/*************************************calc_GET**********************************************
* A função calcula o gasto energetico  total segundo (Food and Agriculture Organization,   * 
* World Health Organization e United Nations University)                                     *
* Parâmetros:                                                                              *
*  - user *u aponta para struct com as informações do usuário                              *
* - ativ_fisica *aponta para a struct com as informações dos fatores de atividades físicas *
* Retorno:                                                                                 *
*  - GET(met * tmb)(double).                                                               *
********************************************************************************************/

double calc_GET(ativ_fisica *at, user *u) {
    float met = valor_MET_User(at);
    double tmb = calc_TMB(u);
    return met * tmb;
}

/**************************calc_IMC****************************
* A função calcula IMC (Índice de Massa Corporal) criada pelo *
* estatístico e matemático belga Adolphe Quetelet             *
* Parâmetros:                                                 *
*  - user *u aponta para struct com as informações do usuário *
* Retorno:                                                    *
*  - void - imprime o IMC do usuário                          *
***************************************************************/

void calc_IMC(user *u){
    double altura = convert_Cm_Para_Metro(u);
    double imc = u->peso/(pow(altura,2.0));

    if (imc < 16.0) {//classificação segundo (OMS)
        printf("IMC: Magreza grave\n");
    } else if (imc >= 16.0 && imc < 17.0) {
        printf("IMC: Magreza moderada\n");
    } else if (imc >= 17.0 && imc < 18.5) {
        printf("IMC: Magreza leve\n");
    } else if (imc >= 18.5 && imc < 25.0) {
        printf("IMC: Peso normal\n");
    } else if (imc >= 25.0 && imc < 30.0) {
        printf("IMC: Sobrepeso\n");
    } else if (imc >= 30.0 && imc < 35.0) {
        printf("IMC: Obesidade grau 1\n");
    } else if (imc >= 35.0 && imc < 40.0) {
        printf("IMC: Obesidade grau 2\n");
    } else {
        printf("IMC: Obesidade grau 3\n");
    }

    return;
}

/**********************************************select_Menu**********************************************************
*A função abre o arquivo "Menu.txt" ler e passar uma serie de alimentos para seleção do usiário no plano alimentar.*
*Parâmetros:                                                                                                       *
*  - select_alimento* sa aponta para struct que vai guardar os alimentos selecionados pelo usuário.                *
*Retorno:                                                                                                          *
*  - void.                                                                                                         *
********************************************************************************************************************/

void select_Menu(select_alimento* sa) {

    FILE *f = fopen("Menu.txt", "r");
    if (f == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    char linha[TAM_LINHA];  // leitura de linhas
    char* token;

    // Matriz com nomes dos alimentos lidos do arquivo
    char alimentos[GRUPO][QNT_ALIMENTO][NOME] = {{{0}}};  
    int total_grupos = 0;  // Contador 

    /**************************************
     * Leitura e separação dos alimentos *
     **************************************/
    while (fgets(linha, sizeof(linha), f) != NULL && total_grupos < GRUPO) {
        linha[strcspn(linha, "\n")] = '\0';  // Remove \n do final da linha

        int alimentoLido = 0;
        token = strtok(linha, ",");

        // Separa alimentos da linha atual
        while (token != NULL && alimentoLido < QNT_ALIMENTO) {
            strncpy(alimentos[total_grupos][alimentoLido], token, NOME - 1);
            alimentos[total_grupos][alimentoLido][NOME - 1] = '\0';  // Garante final da string
            alimentoLido++;
            token = strtok(NULL, ",");  // Próximo token
        }

        total_grupos++;
    }

    fclose(f);  

    /**************************************
     * Escolha dos alimentos pelo usuário *
     **************************************/
    for (int grupo = 0; grupo < total_grupos; grupo++) {
         printf("\n************** Sugestao de de alimento para plano alimentar ***************\n");
        printf("Escolha 1 alimento do grupo %s:\n", alimentos[grupo][0]);

        // Lista alimentos disponíveis para esse grupo
        for (int i = 1; i < QNT_ALIMENTO && alimentos[grupo][i][0] != '\0'; i++) {
            printf("%d - %s\n", i, alimentos[grupo][i]);
        }

        int escolha;
        do {
            printf("Sua escolha: ");
            scanf(" %d", &escolha);
            
            limpar_buffer();

            // Verifica se o número é válido
            if (escolha < 1 || escolha >= QNT_ALIMENTO || alimentos[grupo][escolha][0] == '\0') {
                printf("Opcao invalida. Tente novamente.\n");
            }
        } while (escolha < 1 || escolha >= QNT_ALIMENTO || alimentos[grupo][escolha][0] == '\0');

        /***********************
         * Copia para a struct *
         ***********************/

        // Libera memória anterior, se houver
        if (sa[grupo].alimentos_escolhidos != NULL) {
            free(sa[grupo].alimentos_escolhidos);
        }

        sa[grupo].alimentos_escolhidos = malloc(strlen(alimentos[grupo][escolha]) + 1);

        // Verifica se a alocação funcionou
        if (sa[grupo].alimentos_escolhidos == NULL) {
            printf("Erro de memória.\n");
            exit(1);  
        }

        // Copia a string escolhida
        strcpy(sa[grupo].alimentos_escolhidos, alimentos[grupo][escolha]);


        system("pause");
        system("cls");
    }

    /****************************************
     * Imprime escolhas feitas pelo usuário *
     ****************************************/
    printf("\n************** Sugestao de Plano Alimentar ***************\n\n");
    printf("\nAlimentos escolhidos:\n\n");
    for (int i = 0; i < total_grupos; i++) {
        printf("Grupo %d: %s\n", i + 1, sa[i].alimentos_escolhidos);
    }
}

void calc_Macros(user *u, ativ_fisica* at, select_alimento* sa){
}








    

