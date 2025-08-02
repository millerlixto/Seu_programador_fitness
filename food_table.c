#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "food_table.h"
#include "user.h"
#include "other_functions.h"


#define QUANT_ALIMENTO 5
#define TAM_LINHA 250
#define TAM_NOME 50   
#define MACROS 4   
#define ALIMENTOS_POR_GRUPO 10   
#define NUM_GRUPOS 5   

/***********************************************/
/**************FUNÇÔES NUTRICINAIS**************/
/***********************************************/

/*************************************************macros_por_peso*****************************************************
A função  preenche os macros nutrientes para um usuário com base no peso e na intensidade da atividade física
Parâmetros:
  - user *u: aponta para struct com as informações do peso
  - ativ_fisica *at: aponta para a struct com a informação da intensidade da atividade física (nível 0 a 4)
  - MacrosNutr *saida: aponta para a struct onde os dados lidos serão armazenados
Retorno:
  - 1 se os dados forem encontrados e preenchidos corretamente
  - 0 se houver erro (peso não encontrado ou falha ao abrir o arquivo)
***********************************************************************************************************************/

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

/****************Impressões de validação***************************

           printf("Peso encontrado: %d\n", saida->peso);
            printf("Grupo %d (4 floats): ", niveisAtiv);
           for (int i = 0; i < 4; i++) {
                printf("%.2f ", saida->grupo[i]);
    
*******************************************************************/
            printf("\n");

            // Retorna sucesso
            return 1;
        }
    }

    // Fecha o arquivo se o peso não foi encontrado
    fclose(f);
/*********************Impressão de validação****

 printf("Peso nao encontrado no arquivo.\n"); 

/**********************************************/
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
*************************************************************************************************************************/

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

**************************tratamento de erro*****************************************************/             
        if (strcmp(nomeAlimento, sa[j].alimentos_escolhidos) == 0) {
            strncpy(saida->alimento[j], nomeAlimento, TAM_NOME - 1);
                saida->alimento[j][TAM_NOME - 1] = '\0';//força que ultimo caracter seja o '\0'

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
        /**********************impressão de validação dos dados gerados **********************************
        else {
            printf("\nAlimento: %s\n", saida->alimento[j]);
            printf("Informacao nutricional para 100g (Kcal, Proteina, Carboidrato, Gordura): ");
            for (int i = 0; i < 4; i++) {
                printf("%.2f ", saida->macros_para_100g[j][i]);
            }
            printf("\n");
        }
        *************************************************************************************************/
/********verificação de gravação na struct**************            
           printf(">>> Copiado com sucesso: %s | %.2f %.2f %.2f %.2f\n",
      saida->alimento[j],
      saida->macros_para_100g[j][0],
      saida->macros_para_100g[j][1],
      saida->macros_para_100g[j][2],
      saida->macros_para_100g[j][3]);
**************************************************************/
    }
    return 1;
}

void planoAlimentar(plano_alimentar* pa) {
    // Inicialização de variáveis 
    float quantidade_em_gramas[NUM_GRUPOS] = {0}; // quantidade (em gramas) usada de cada alimento
    float soma_macros[MACROS] = {0}; // macros totais (kcal, proteína, carboidrato, gordura)
    float limite[MACROS];// Define o limite de macros que o usuário deve consumir (copiado da struct MacrosNutr)

    for (int i = 0; i < MACROS; i++) {
        limite[i] = pa->MacrosNutr.grupo[i];
    }

    int macro_atual = 1; //contador

    // Adiciona as gramas de alientos e confere se não passou da quantidade de macros de sejados
    while (macro_atual <= MACROS -1) {
        int progresso = 0; // Marca se conseguiu adicionar algum alimento sem ultrapassar o limite de macros

        // Adicionar alimentos que contribuam para o macro atual
        for (int i = 0; i < NUM_GRUPOS; i++) {
            // Pega o valor do macro atual para 100g de alimento
            float valor_macro = pa->infor_nutri_alimento.macros_para_100g[i][macro_atual];
            if (valor_macro == 0) continue; // pula alimentos se os macros forem zerados

            float incremento = 50.0;               // adicionar 50g por vez
            float fator = incremento / 100.0;      // fator proporcional (macro por 100g)

            // Calcula a nova soma de calorias e do macro atual 
            float nova_kcal = soma_macros[0] + (pa->infor_nutri_alimento.macros_para_100g[i][0] * fator);
            float novo_macro = soma_macros[macro_atual] + (valor_macro * fator);

            // Só adiciona se não ultrapassar o limite de kcal e do macro atual
            if (nova_kcal <= limite[0] && novo_macro <= limite[macro_atual]) {
                // Soma 50g do alimento atual à quantidade total usada
                quantidade_em_gramas[i] += incremento;

                // Atualiza todos os macros 
                for (int j = 0; j < MACROS; j++) {
                    soma_macros[j] += pa->infor_nutri_alimento.macros_para_100g[i][j] * fator;
                }

                progresso = 1; // conseguimos adicionar este alimento
                break;         // tenta mais 50g no mesmo macro
            }
        }

        if (!progresso) {
            // Se o limite já afoi ultrapassado (macro atual)
            macro_atual++;
        } else if (soma_macros[macro_atual] >= limite[macro_atual] * 0.98) {
            // Se já atingimos ao menos 98% da meta do macro atual, podemos passar para o próximo
            macro_atual++;
        }
    }

    // Impressão final dos resultados

    printf("\n************** Sugestao de Quantidades diarias ***************\n");
    printf("******** tente dividir sua alimentacao em 6 refeicoes ********\n\n");

  //  printf("\nQuantidade total de cada alimento utilizada:\n");
    for (int i = 0; i < NUM_GRUPOS; i++) {
        if (quantidade_em_gramas[i] == 0) {
            printf("- %s: A vontade!\n", pa->infor_nutri_alimento.alimento[i]);
        } else {
            printf("- %s: %.1fg\n", pa->infor_nutri_alimento.alimento[i], quantidade_em_gramas[i]);
        }


/**********************impressão de validação dos dados gerados ************************************
   
    printf("\nMacros totais atingidos:\n");
    printf("- Kcal=%.1f, Prot=%.1fg, Carb=%.1fg, Gord=%.1fg\n",
           soma_macros[0], soma_macros[1], soma_macros[2], soma_macros[3]);

    printf("\nMacros desejados:\n");
    printf("- Kcal=%.1f, Prot=%.1fg, Carb=%.1fg, Gord=%.1fg\n",
           limite[0], limite[1], limite[2], limite[3]);

/****************************************************************************************************/  

    }
    printf("\n******************************** ATENCAO! ************************************\n");
    printf("Para melhores resultados, procure um nutricionista ou profissional de saude!\n");
    printf("******************************************************************************\n\n");
    printf("**************Fim de aplicacao***************\n\n\n");
}

/****************************************************************************************************/
/***********************************GERA TABELA NUTRICIONAL******************************************/
/***********************************"Tabela_Nutricional.txt"*****************************************/
/****************************************************************************************************/

/*************************************************recebe_alimentos*********************************************************
* A Função guarda nome de alimentos e seus marcos na struct recebe alimento para depois gerar um arquivo com os alimetos. *
* Parâmetros:                                                                                                             *
*  - recebeAlimento a: aponta para struct onde os dados serão armazenados                                                 *
* Retorno:                                                                                                                *
*  - void                                                                                                                 *
***************************************************************************************************************************/
// Funcao principal para cadastro dos alimentos
void recebe_alimentos(aux_recebeAlimento* aux) {
    const char grupos[NUM_GRUPOS][TAM_NOME] = {
        "proteinas", "carboidratos", "legumes", "vegetais", "bebidas"
    };
    const char nome_macros[MACROS][TAM_NOME] = {
        "calorias: ", "proteinas: ", "carboidratos: ", "gorduras: "
    };

    aux->recebeAlimento = NULL;
    aux->total_alimentos_cadastrados = 0;

    char continuar = 's';

    printf("\n********** Inicio do cadastro de alimentos **********\n");

    int i=0;
    while (continuar == 's') {

        printf("\nGrupo: %s\n", grupos[i]);
        for (int j = 0; j < ALIMENTOS_POR_GRUPO; j++) {

            aux->recebeAlimento = realloc(aux->recebeAlimento, sizeof(recebeAlimento) * (aux->total_alimentos_cadastrados + 1));
            if (!aux->recebeAlimento) {
                printf("Erro na alocacao de memoria.\n");
                exit(1);
            }

            recebeAlimento* novo = &(aux->recebeAlimento[aux->total_alimentos_cadastrados]);

            // Se j == 0, esta entrada representa o grupo (nao um alimento real)
            if (j == 0) {
                novo->grupo_de_alimentos = malloc(strlen(grupos[i]) + 1);
                strcpy(novo->grupo_de_alimentos, grupos[i]);

                novo->nome_alimento = malloc(TAM_NOME);
                strcpy(novo->nome_alimento, "[GRUPO]"); // Indica grupo

                for (int k = 0; k < MACROS; k++) {
                    novo->macros[k] = -1.0f; // Valor especial para grupo, nao alimento real
                }

                aux->total_alimentos_cadastrados++;
                continue; // proximo j
            }

            novo->grupo_de_alimentos = malloc(strlen(grupos[i]) + 1);
            strcpy(novo->grupo_de_alimentos, grupos[i]);

            novo->nome_alimento = malloc(TAM_NOME);
            ler_string(novo->nome_alimento, TAM_NOME, "Nome do alimento: ");

            for (int k = 0; k < MACROS; k++) {
                printf("%s", nome_macros[k]);
                scanf("%f", &novo->macros[k]);
                limpar_buffer();
            }
            aux->total_alimentos_cadastrados++;

            char resposta = ler_sn("Adicionar outro alimento neste grupo? (s/n): ");
            if (resposta == 'n') break;
        }

        continuar = ler_sn("Inserir alimentos em novos grupos? (s/n): ");
        if (continuar == 'n') break;

        int op_valida = 0;
        while(!op_valida) {
            char entrada[10];
            char op;
            ler_string(entrada, 10,
            "\n[P] Proteinas\n[C] Carboidratos\n[L] Legumes\n[V] Vegetais\n[B] Bebidas\n[S] Sair\n\n");
            op = tolower(entrada[0]);

            switch(op) {
            case 'p':
                i=0;
                op_valida = 1;
                break;
            case 'c':
                i=1;
                op_valida = 1;
                break;
            case 'l':
                i=2;
                op_valida = 1;
                break;
            case 'v':
                i=3;
                op_valida = 1;
                break;
            case 'b':
                i=4;
                op_valida = 1;
                break;
            case 's':
                printf("Saindo...\n");
                continuar = 'n';
                op_valida = 1;
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
            }
        }
    }
}

/***************************grava_alimentos**********************************************
* A Função grava o nome dos alimentos e seus marcos no arquivo "Tabela_Nutricional.txt". *
* Parâmetros:                                                                            *
*  - recebeAlimento a: aponta para struct onde os dados estão armazenados                *
* Retorno:                                                                               *
*  - void                                                                                *
******************************************************************************************/

void grava_alimentos(aux_recebeAlimento* aux) {
    FILE *f = fopen("Tabela_Nutricional.txt", "w");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < aux->total_alimentos_cadastrados; i++) {
        if (strcmp(aux->recebeAlimento[i].nome_alimento, "[GRUPO]") == 0) {
            fprintf(f, "%s\n", aux->recebeAlimento[i].grupo_de_alimentos);
        } else {
            fprintf(f, "%s, ", aux->recebeAlimento[i].nome_alimento);
            for (int k = 0; k < MACROS; k++) {
                fprintf(f, "%.2f", aux->recebeAlimento[i].macros[k]);
                if (k < MACROS - 1) fprintf(f, " ");
            }
            fprintf(f, "\n");
        }
    }
    fclose(f);
}

/***************************liberar_alimentos*********************************************
* A Função libera a memoria alocada para a struct recebeAlimento.                        *
* Parâmetros:                                                                            *
*  -  *aux  aponta para struct aux_recebeAlimento                                        *
* Retorno:                                                                               *
*  - void                                                                                *
******************************************************************************************/

void liberar_alimentos(aux_recebeAlimento* aux) {
    for (int i = 0; i < aux->total_alimentos_cadastrados; i++) {
        free(aux->recebeAlimento[i].grupo_de_alimentos);
        free(aux->recebeAlimento[i].nome_alimento);
    }
    free(aux->recebeAlimento);
}

/****************************************************************************************************/
/***********************************GERA MENU DE ALIMENTOS ******************************************/
/****************************************"menu.txt"**************************************************/
/****************************************************************************************************/


/*******************************menu_grava_alimentos******************************
* A Função grava os nome de alimentos separados por grupos no arquivo "menu.txt" *
* Parâmetros:                                                                    *
*  - aux_recebeAlimento* aux: aponta para struct onde os dados estão armazenados                  *
* Retorno:                                                                       *
*  - void                                                                        *
**********************************************************************************/
void menu_grava_alimentos(aux_recebeAlimento* aux) { 
    FILE *f = fopen("Tabela_Nutricional.txt", "w");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int i = 0;
    while (i < aux->total_alimentos_cadastrados) {
        if (strcmp(aux->recebeAlimento[i].nome_alimento, "[GRUPO]") == 0) {
            fprintf(f, "%s", aux->recebeAlimento[i].grupo_de_alimentos);
            i++;

            while (i < aux->total_alimentos_cadastrados &&
                   strcmp(aux->recebeAlimento[i].nome_alimento, "[GRUPO]") != 0) {
                fprintf(f, ", %s", aux->recebeAlimento[i].nome_alimento);
                i++;
            }
            fprintf(f, "\n");
        } else {
            i++; // pular itens fora do grupo (não esperado)
        }
    }

    fclose(f);
}




