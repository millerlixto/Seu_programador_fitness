#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "food_table.h"
#include "user.h"
#include "other_functions.h"


#define QUANT_ALIMENTO 5
#define TAM_LINHA 250
#define QUANT_PROT 2
#define QUANT_CARB 2
#define TAM_NOME             50   // Tamanho máximo de nomes (alimentos e grupos)
#define MACROS                4   // Número de macronutrientes: calorias, proteínas, carboidratos, gorduras
#define ALIMENTOS_POR_GRUPO  10   // Quantidade de alimentos cadastráveis por grupo
#define NUM_GRUPOS            5   // Quantidade de grupos de alimentos: proteínas, carboidratos, legumes, vegetais, bebidas



/*************************************************macros_por_peso*****************************************************
A função  preenche os macros nutrientes para um usuário com base no peso e na intensidade da atividade física
Parâmetros:
  - user *u: aponta para struct com as informações do peso
  - ativ_fisica *at: aponta para a struct com a informação da intensidade da atividade física (nível 0 a 4)
  - MacrosNutr *saida: aponta para a struct onde os dados lidos serão armazenados
Retorno:
  - 1 se os dados forem encontrados e preenchidos corretamente
  - 0 se houver erro (peso não encontrado ou falha ao abrir o arquivo)
   *********************************************************************************************************************/

int macros_por_peso(user *u, ativ_fisica *at, MacrosNutr *saida){

    // recebe o peso do usuário e o nível de atividade física das structs "user" e "ativ_fisica"    
    //aproxima o peso passado pelo usuário. Porque a tabela é organizada em intervalos de 5 kg
    int peso = aproxima_peso (u);
    
    int niveisAtiv = at->intensidade;

    // Verifica se o nível de atividade está dentro dos limites válidos (de 0 a 4)
    if (niveisAtiv < 0 || niveisAtiv > 4) return 0; // índice inválido

    // tenta abrir o arquivo tabela de macros
    FILE *f = fopen("macros_tabela.txt", "r");
    if (!f) {
        printf("Erro ao abrir arquivo"); // exibe erro se não conseguir abrir
        return 0;
    }

    // Variável para armazenar a linha do peso tual
    int linhaPeso;

    // Amazena 20 valores (5 níveis × 4 macros por nível)
    float valores[20];

    // Ler arquivo linha por linha
    while (fscanf(f, "%d", &linhaPeso) == 1) {
        // Lê os 20 valores (4 macros × 5 níveis) da linha
        int r = fscanf(f, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
                        &valores[0], &valores[1], &valores[2], &valores[3],//nível 1
                        &valores[4], &valores[5], &valores[6], &valores[7],//nível 2
                        &valores[8], &valores[9], &valores[10], &valores[11],//nível 3
                        &valores[12], &valores[13], &valores[14], &valores[15],//nível 4
                        &valores[16], &valores[17], &valores[18], &valores[19]);//nível 5

        // Se a linha estiver incompleta, sai do loop
        if (r != 20) break;

        // Verifica se o peso na linha corresponde ao peso passado pelo usuário
        if (linhaPeso == peso) {
            // Copia os 4 valores correspondentes ao nível de atividade física
            // multiplica o nível pela quantidade de macros (pula para linha do nível)
            // O indice i vai varrendo a linha
            for (int i = 0; i < 4; i++) {
                saida->grupo[i] = valores[niveisAtiv * 4 + i];
            }

            // peso encontrado vai para struct "MacrosNutr"
            saida->peso = linhaPeso;


            // Fecha o arquivo
            fclose(f);

            //****************Impressões para validação*******************
          //  printf("Peso encontrado: %d\n", saida->peso);
         //   printf("Grupo %d (4 floats): ", niveisAtiv);
          //  for (int i = 0; i < 4; i++) {
          //      printf("%.2f ", saida->grupo[i]);
           // }
           // *******************************************************************/
            printf("\n");

            // Retorna sucesso
            return 1;
        }
    }

    // Fecha o arquivo se o peso não foi encontrado
    fclose(f);
     //*********************Impressão de validação***************************
   // printf("Peso nao encontrado no arquivo.\n");
    //**********************************************************************
    // Retorna falha
    return 0;
}

/*************************************************tabela_nutriction*****************************************************
A Função busca no arquivo "Tabela_nutricional.txt" os macros nutrientes dos alimentos selecionados na função select_menu
e grava na struct infor_nutri_alimento
Parâmetros:
  - infor_nutri_alimento* saida: aponta para struct onde os dados lidos serão armazenados
  - select_alimento* sa: aponta para a struct com os nomes dos alimentos que serão buscados no arquivo
Retorno:
  - 1 se os dados forem encontrados e preenchidos corretamente
  - 0 se houver erro (falha ao abrir o arquivo)
   *********************************************************************************************************************/


int table_nutriction(infor_nutri_alimento* saida, select_alimento* sa) {
    for (int j = 0; j < NUM_GRUPOS; j++) {

        FILE *f = fopen("Tabela_Nutricional.txt", "r");
        if (!f) {
            perror("Erro ao abrir arquivo");
            return 0;
        }

        char linha[256];
        char *nomeAlimento;
        float valores[4];
        int encontrado = 0;
       
        // Limpa espaços extras do nome escolhido pelo usuário
        remove_espacos_str(sa[j].alimentos_escolhidos);

        while (fgets(linha, sizeof(linha), f)) {
            if (strchr(linha, ',') == NULL) continue;

            nomeAlimento = strtok(linha, ",");
            if (!nomeAlimento) continue;
            // Limpa espaços extras do nome escolhido pelo usuário
               remove_espacos_str(nomeAlimento);

            while (*nomeAlimento == ' ') nomeAlimento++;
            nomeAlimento[strcspn(nomeAlimento, "\n")] = '\0';

            if (sscanf(strtok(NULL, ""), "%f %f %f %f",
                       &valores[0], &valores[1], &valores[2], &valores[3]) != 4) {
                continue;
            }
/********tratamento de erro, espaço a direita da string - strcmp sensível a espaços**************

printf("Comparando: |%s| <-> |%s|\n", nomeAlimento, sa[j].alimentos_escolhidos);
printf("Tamanhos: %zu vs %zu\n", strlen(nomeAlimento), strlen(sa[j].alimentos_escolhidos));

**********************tratamento de erro*****************************************************/             
            if (strcmp(nomeAlimento, sa[j].alimentos_escolhidos) == 0) {
                strncpy(saida->alimento[j], nomeAlimento, TAM_NOME - 1);
                saida->alimento[j][TAM_NOME - 1] = '\0';

                for (int i = 0; i < 4; i++) {
                    saida->macros_para_100g[j][i] = valores[i];
                }
                encontrado = 1;
                break;
            }
        }
        fclose(f);

     if (!encontrado) {
            printf("Alimento \"%s\" nao encontrado na tabela.\n", sa[j].alimentos_escolhidos);
            
        } 
        /**********************impressão dos dados gerados**********************************
        else {
            printf("\nAlimento: %s\n", saida->alimento[j]);
            printf("Informacao nutricional para 100g (Kcal, Proteina, Carboidrato, Gordura): ");
            for (int i = 0; i < 4; i++) {
                printf("%.2f ", saida->macros_para_100g[j][i]);
            }
            printf("\n");
        }
        ***************************************************************************************/
//********verificação de gravação na struct**************            
 //           printf(">>> Copiado com sucesso: %s | %.2f %.2f %.2f %.2f\n",
 //      saida->alimento[j],
 //      saida->macros_para_100g[j][0],
 //      saida->macros_para_100g[j][1],
 //      saida->macros_para_100g[j][2],
 //      saida->macros_para_100g[j][3]);
//**************************************************************/
    }
    return 1;
}
/****************************************************************************************************/
/***********************************GERA TABELA NUTRICIONAL******************************************/
/***********************************"Tabela_Nutricional.txt"*****************************************/
/****************************************************************************************************/

/*************************************************recebe_alimentos*********************************************************
* A Função guarda nome de alimentos e seus marcos na struct recebe alimento para depois gerar um arquivo com os alimetos. *
* Parâmetros:                                                                                                             *
*  - recebeAlimento a[]: aponta para struct onde os dados serão armazenados                                               *
* Retorno:                                                                                                                *
*  - void                                                                                                                 *
***************************************************************************************************************************/
void recebe_alimentos(recebeAlimento** a) {
    *a = malloc(sizeof(recebeAlimento));
    if (*a == NULL) {
        printf("Erro de alocacao!\n");
        return;
    }

    char grupos[NUM_GRUPOS][TAM_NOME] = {
        "proteinas", "carboidratos", "legumes", "vegetais", "bebidas"
    };
    char nome_macros[MACROS][TAM_NOME] = {
        "calorias: ", "proteinas: ", "carboidratos: ", "gorduras: "
    };

    printf("\n****************************** Início do cadastro de alimentos ******************************\n");

    int alimento_atual = 0;

    for (int i = 0; i < NUM_GRUPOS; i++) {
        strcpy((*a)->grupo_de_alimentos[i], grupos[i]);
        printf("%s\n", (*a)->grupo_de_alimentos[i]);

        for (int j = 0; j < ALIMENTOS_POR_GRUPO; j++) {
            printf(" %dº - ", j + 1);
            ler_string((*a)->nome_alimento[alimento_atual], TAM_NOME, "Alimento: ");

            for (int k = 0; k < MACROS; k++) {
                printf("%s", nome_macros[k]);
                scanf("%f", &(*a)->macros[alimento_atual][k]);
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
            alimento_atual++;
            printf("\n");
        }
    }
}

/***************************grava_alimentos**********************************************
* A Função grava o nome dos alimentos e seus marcos no arquivo "Tabela_Nutricional.txt". *
* Parâmetros:                                                                            *
*  - recebeAlimento a[]: aponta para struct onde os dados estão armazenados              *
* Retorno:                                                                               *
*  - void                                                                                *
******************************************************************************************/

void grava_alimentos(recebeAlimento** a) {
    FILE *f = fopen("Tabela_Nutricional.txt", "w");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int alimento_atual = 0;

    for (int i = 0; i < NUM_GRUPOS; i++) {
        fprintf(f, "%s\n", (*a)->grupo_de_alimentos[i]);

        for (int j = 0; j < ALIMENTOS_POR_GRUPO; j++) {
            fprintf(f, "%s, ", (*a)->nome_alimento[alimento_atual]);

            for (int k = 0; k < MACROS; k++) {
                fprintf(f, "%.2f ", (*a)->macros[alimento_atual][k]);
            }
            fprintf(f, "\n");
            alimento_atual++;
        }
    }

    fclose(f);
}
/****************************************************************************************************/
/***********************************GERA MENU DE ALIMENTOS ******************************************/
/****************************************"menu.txt"**************************************************/
/****************************************************************************************************/

/*****************************************menu_recebe_alimentos*********************************************************
* A Função guarda nome de alimentos e seus marcos na struct menu para depois gerar um arquivo com um menu de alimetos. *
* Parâmetros:                                                                                                          *
*  - menu m[]: aponta para struct onde os dados serão armazenados                                                      *
* Retorno:                                                                                                             *
*  - void                                                                                                              *
************************************************************************************************************************/
void menu_recebe_alimentos(menu m[]) {

 printf("\n******************************Inicia processo de alimentacao do Menu*********************************\n");

    for (int i = 0; i < QUANT_PROT; i++) {
       
        ler_string(m[i].menu_prot, TAM_NOME, "Proteinas: "); 
    }
printf("\n");

     for (int i = 0; i < QUANT_CARB; i++) {
       
        ler_string(m[i].menu_carb, TAM_NOME, "Carboidratos: "); 
    }
}
/*******************************menu_grava_alimentos******************************
* A Função grava os nome de alimentos separados por grupos no arquivo "menu.txt" *
* Parâmetros:                                                                    *
*  - menu m[]: aponta para struct onde os dados estão armazenados                *
* Retorno:                                                                       *
*  - void                                                                        *
**********************************************************************************/
void menu_grava_alimentos(menu m[]){
    FILE *f = fopen("Menu.txt", "w");
    if (f == NULL) {
        printf("Erro ao abrir arquivo!");
        return;
    }
    // Grava linha das proteínas
    fprintf(f, "PROTEINAS ");  
    for (int i = 0; i < QUANT_PROT; i++) {
        fprintf(f, "%s, ", m[i].menu_prot); // Escreve alimento 
    }
    fprintf(f, "\n");  

    // Grava linha dos carboidratos
    fprintf(f, "CARBOIDRATOS ");  
    for (int i = 0; i < QUANT_CARB; i++) {
        fprintf(f, "%s, ", m[i].menu_carb);  // Escreve alimento 
    }
    fprintf(f, "\n");  

    fclose(f);
//printf("Proteina: %s\n", m->menu_prot);
//printf("\nCarboidrato: %s\n", m->menu_carb);

    printf("Arquivo criado com sucesso!\n\n");  
}


