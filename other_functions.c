#include <stdio.h>
#include<ctype.h>
#include<string.h>
#include<tgmath.h>
#include<stdlib.h>
#include "user.h"
#include"other_functions.h"


#define TAM_NOME 50
#define TAM_LINHA 256
#define QUANT_ALIMENTO 55

#define GRUPO 5
#define NOME 50
#define QNT_ALIMENTO 11

#define PESOS 26
#define INTERVALO_PESO 5

/**************funções genéricas****************/

// Remove espaços em branco no início e fim da string
void trim(char *str) {
    char *inicio = str;
    char *fim;

    // Avança ponteiro para o primeiro caractere não-espaço
    while (*inicio == ' ' || *inicio == '\t' || *inicio == '\n') {
        inicio++;
    }

    // Move o conteúdo ajustado para o início da string
    if (str != inicio) {
        memmove(str, inicio, strlen(inicio) + 1);
    }

    // Agora remove os espaços do final
    fim = str + strlen(str) - 1;
    while (fim >= str && (*fim == ' ' || *fim == '\t' || *fim == '\n')) {
        *fim = '\0';
        fim--;
    }
}

//recede a intesidade da atividade física

void definir_fator_atividade_ativo(ativ_fisica  *at){

// verificação,  1<= inteiro <=5
int return_scanf;
int valida = 0;
do{
printf("\nDiga qual a intensidade de 0 a 4, sendo:\n\n");
printf("- 0 para sedentario(trabalha de escritorio, passa maior parte do dia sentado.: \n \n"); 
printf("- 1 para levemente ativo(Caminhadas curtas, tarefas domesticas leves, subir escadas ocasionalmente.): \n\n");
printf("- 2 para moderadamente ativo(Corrida leve, natacao, ciclismo, musculacao ou aulas de ginastica na academia.): \n\n");
printf("- 3 para muito ativo(Maratonistas, atletas que treinam quase todos os dias, esportes coletivos de alta intensidade, musculacao pesada frequente.)\n\n");
printf("- 4 para extremamente ativo(Atletas de alta performance, trabalhos com grande esforço físico contínuo (ex: construcao civil).): \n");

//tratamento de entrada com scanf
//O scanf retorna o numero de leituras com sucesso 
//0 se a conversão falou e EOF(-1), se chegou ao fim do arquivo
// ou houve erro de leitura
return_scanf = scanf(" %d", &at->intensidade);

// se o scanf receber uma quantidade diferende de argumentos que o esperado 
//pela entrado do usuários, as mensagens de erro são enviadas.
if(return_scanf != 1){//um argumento esperado, retorno do scanf 1.

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

 printf("Intensidade escolhida: %d\n", at->intensidade);
}

//recede a intesidade da atividade física de usuários menos ativo
void definir_fator_atividade_MenosAtivo(ativ_fisica *at){
// verificação,  0 ou 1.
int return_scanf;// tratamento de entrada
int valida = 0;
do{
printf("\nSelecione a opcao que mais combina com seu estilo de vida: 0 ou 1, sendo:\n\n");
printf("-0 para sedentario(trabalha de escritorio, passa maior parte do dia sentado. \n\n"); 
printf("-1 para levemente ativo(Caminhadas curtas, tarefas domesticas leves, subir escadas ocasionalmente.)\n");

//tratamento de entrada com scanf
//O scanf retorna o numero de leituras com sucesso 
//0 se a conversão falou e EOF(-1), se chegou ao fim do arquivo
// ou houve erro de leitura
return_scanf = scanf(" %d", &at->intensidade);
// se o scanf receber uma quantidade diferende de argumentos que o esperado 
//pela entrado do usuários, as mensagens de erro são enviadas.
if(return_scanf != 1){//um argumento esperado, retorno so scanf 1.

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

void select_menu(select_alimento* sa) {
    FILE *f = fopen("Menu.txt", "r");
    if (f == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    char linha[TAM_LINHA];  // Buffer para leitura de linhas
    char* token;

    // Matriz com nomes dos alimentos lidos do arquivo
    char alimentos[GRUPO][QNT_ALIMENTO][NOME] = {{{0}}};  // Limpa todos os dados
    int total_grupos = 0;  // Contador de grupos

    /**************************************
     * Leitura e separação dos alimentos *
     **************************************/
    while (fgets(linha, sizeof(linha), f) != NULL && total_grupos < GRUPO) {
        linha[strcspn(linha, "\n")] = '\0';  // Remove \n do final da linha

        int alimento_idx = 0;
        token = strtok(linha, ",");

        // Separa alimentos da linha atual
        while (token != NULL && alimento_idx < QNT_ALIMENTO) {
            strncpy(alimentos[total_grupos][alimento_idx], token, NOME - 1);
            alimentos[total_grupos][alimento_idx][NOME - 1] = '\0';  // Garante final da string
            alimento_idx++;
            token = strtok(NULL, ",");  // Próximo token
        }

        total_grupos++;
    }

    fclose(f);  // Fecha o arquivo

    /**************************************
     * Escolha dos alimentos pelo usuário *
     **************************************/
    for (int grupo = 0; grupo < total_grupos; grupo++) {
        printf("Escolha 1 alimento do grupo %s:\n", alimentos[grupo][0]);

        // Lista alimentos disponíveis para esse grupo
        for (int i = 1; i < QNT_ALIMENTO && alimentos[grupo][i][0] != '\0'; i++) {
            printf("%d - %s\n", i, alimentos[grupo][i]);
        }

        int escolha;
        do {
            printf("Sua escolha: ");
            scanf("%d", &escolha);

            // Verifica se o número é válido
            if (escolha < 1 || escolha >= QNT_ALIMENTO || alimentos[grupo][escolha][0] == '\0') {
                printf("Opção inválida. Tente novamente.\n");
            }
        } while (escolha < 1 || escolha >= QNT_ALIMENTO || alimentos[grupo][escolha][0] == '\0');

        /*************************************
         * Copiando o alimento para a struct *
         *************************************/

        // Libera memória anterior, se houver
        if (sa[grupo].alimentos_escolhidos != NULL) {
            free(sa[grupo].alimentos_escolhidos);
        }

        // Aloca memória exata para o alimento escolhido (+1 para '\0')
        sa[grupo].alimentos_escolhidos = malloc(strlen(alimentos[grupo][escolha]) + 1);

        // Verifica se a alocação funcionou
        if (sa[grupo].alimentos_escolhidos == NULL) {
            printf("Erro de memória.\n");
            exit(1);  // ou `return` dependendo do seu controle de erros
        }

        // Copia a string escolhida
        strcpy(sa[grupo].alimentos_escolhidos, alimentos[grupo][escolha]);


        // Pausa e limpa a tela (opcional, Windows)
        system("pause");
        system("cls");
    }

    /**************************************
     * Mostra escolhas feitas pelo usuário
     **************************************/
    printf("\nAlimentos escolhidos:\n\n");
    for (int i = 0; i < total_grupos; i++) {
        printf("Grupo %d: %s\n", i + 1, sa[i].alimentos_escolhidos);
    }
}

void calc_Macros(user *u, ativ_fisica* at, select_alimento* sa){
}


/**************peso mais próximo****************/
//recebe o peso da struct user e aproxima segundo tabela, que contem intervalos de 5kg
int aproxima_peso(user* u) {
    // Alocando memória para vetor de pesos
    int* peso = (int*)malloc(PESOS * sizeof(int));
    if (peso == NULL) {
        printf("Erro: memória não alocada\n");
        return -1;
    }

    // Preenchendo o vetor com múltiplos de INTERVALO_PESO
    for (int i = 0; i < PESOS; i++) {
        peso[i] = (i + 1) * INTERVALO_PESO; // começa de 1*INTERVALO
    }

    // Encontrando o peso mais próximo
    int indice_mais_proximo = 0;
    int menor_diferenca = abs(peso[0] - u->peso);

    for (int i = 1; i < PESOS; i++) {
        int diferenca = abs(peso[i] - u->peso);
        if (diferenca < menor_diferenca) {
            menor_diferenca = diferenca;
            indice_mais_proximo = i;
        }
    }

    int peso_aproximado = peso[indice_mais_proximo];  // SALVAR antes de liberar
    free(peso);

    return peso_aproximado;  // RETORNAR valor válido
}

/**************impressão****************/

//função imprime os dados other_functions
void imprimir_Dados_Other_Functions(ativ_fisica *at, user *u) {

    printf("Gasto calorico total (MET): %.2f\n", valor_MET_User(at));
    printf("Taxa de Metabolismo Basal (TMB): %.2f\n", calc_TMB(u));
    printf("Gasto Engergetico Total (GET): %.2f\n", calc_GET(at, u));

    
}
