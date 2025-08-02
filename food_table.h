#ifndef INICIAR_H
#define INICIAR_H

#include "user.h"
#include "other_functions.h"

#define TAM_NOME 50
#define MACROS 4
#define ALIMENTOS_POR_GRUPO 10
#define NUM_GRUPOS 5

/***********************************************/
/*******************ESTRUTURAS******************/
/***********************************************/

//*************************recebe lista de alimentos para gravar no menu********************
typedef struct {
    char* grupo_de_alimentos;//grupo de alimentos proteinas, carboidratos, legumes, vegetais, bebidas
    char* nome_alimento;//nome dos alimentos
    float macros[MACROS];//macro nutrientes dos alimetnos(calorias, proteinas, carboidratos, gordura)
} recebeAlimento;

//auxilia a struct recebeAlimento
typedef struct {
    recebeAlimento* recebeAlimento;  // ponteiro para vetor de alimentos(struct recebeAlimento)
    int total_alimentos_cadastrados; // total de alimentos cadastrados
} aux_recebeAlimento;
//******************************************************************************************

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

// imprime plano alimentar 
void planoAlimentar(plano_alimentar* pa);


/****************************************************************************************************/
/***********************************GERA TABELA NUTRICIONAL******************************************/
/***********************************"Tabela_Nutricional.txt"*****************************************/
/****************************************************************************************************/

//função recebe uma lista de alimentos
void recebe_alimentos(aux_recebeAlimento* aux);
//função que carrega a lista de alimentos no arquivo
void grava_alimentos(aux_recebeAlimento* aux);
//função libera memoria alocada pra receber lista de alimentos
void liberar_alimentos(aux_recebeAlimento* aux);



/****************************************************************************************************/
/***********************************GERA MENU DE ALIMENTOS ******************************************/
/****************************************"menu.txt"**************************************************/
/****************************************************************************************************/

//função que carrega os alimentos no arquivo
void menu_grava_alimentos(aux_recebeAlimento* aux);




#endif