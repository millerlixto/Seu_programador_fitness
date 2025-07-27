#ifndef INICIAR_H
#define INICIAR_H

#include "user.h"
#include "other_functions.h"

#define TAM_NOME 50
#define MACROS 4
#define ALIMENTOS_POR_GRUPO 10
#define NUM_GRUPOS          5

/***********************************************/
/*******************ESTRUTURAS******************/
/***********************************************/
 
//recebe lista de alimentos para gravar no menu
typedef struct {
    char grupo_de_alimentos[NUM_GRUPOS][TAM_NOME];//grupo de alimentos proteinas, carboidratos, legumes, vegetais, bebidas
    char nome_alimento[ALIMENTOS_POR_GRUPO][TAM_NOME];//nome dos alimentos(10 alimentos por grupo)
    float macros[ALIMENTOS_POR_GRUPO][MACROS];//macro nutrientes dos alimetnos(calorias, proteinas, carboidratos, gordura)
} recebeAlimento;

// Guarda os macros nutrientes e calorias totais diárias
// a ser consumida pelo usuário, baseado no peso e nivél de ativiade física do usuário
typedef struct {
    int peso;
    float grupo[MACROS];//macros diários
} MacrosNutr;

//agrupa os alimentos com os macros para cada 100g 
typedef struct {
    char alimento[NUM_GRUPOS][TAM_NOME];  // nomes dos alimentos encontrados
    float macros_para_100g[NUM_GRUPOS][MACROS]; // Kcal, Prot, Carb, Gord
} infor_nutri_alimento;

typedef struct {
    char alimentos[NUM_GRUPOS][ALIMENTOS_POR_GRUPO][TAM_NOME];// recebe os alimentos que irão gerar o arquivo 
} menu;

typedef struct{
infor_nutri_alimento infor_nutri_alimento;
MacrosNutr MacrosNutr;//aponta para a struct onde estão os macros diários a ser consumidos
}plano_alimentar;

/***********************************************/
/**************FUNÇÔES NUTRICINAIS**************/
/***********************************************/

//Função recebe peso e nível de atividade, retorna 1 se achou, 0 caso contrário. Guarda na struct "MacrusNutr"
// peso e os macros nutrientes relacionado ao peso e nível de atividade
int macros_por_peso(user *u, ativ_fisica *at, MacrosNutr *saida);

// recebe os alimentos de select_alimentos e guarda os macros para cada 100g na struct INFOR_NUTRI
int table_nutriction(infor_nutri_alimento* saida, select_alimento* sa);


/****************************************************************************************************/
/***********************************GERA TABELA NUTRICIONAL******************************************/
/***********************************"Tabela_Nutricional.txt"*****************************************/
/****************************************************************************************************/

//função recebe uma lista de alimentos
void recebe_alimentos(recebeAlimento** a);
//função que carrega a lista de alimentos no arquivo
void grava_alimentos(recebeAlimento** a);



/****************************************************************************************************/
/***********************************GERA MENU DE ALIMENTOS ******************************************/
/****************************************"menu.txt"**************************************************/
/****************************************************************************************************/

//função recebe uma lista de alimentos para o menu
void menu_recebe_alimentos(menu* m);
//função que carrega os alimentos no arquivo
void menu_grava_alimentos(menu* m);
//visualiza o arquivo 

void atualizar(plano_alimentar* pa);



#endif