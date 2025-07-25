#ifndef INICIAR_H
#define INICIAR_H

#include "user.h"
#include "other_functions.h"

#define TAM_NOME 50
#define QUANT_ALIMENTO 5

/***********************************************/
/*******************ESTRUTURAS******************/
/***********************************************/

//recebe lista de alimentos para gravar no menu
typedef struct{
char nome_alimento[TAM_NOME];
float calorias;
float proteina;
float carboidrato;
float gordura;
}recebeAlimento;

typedef struct {
    float Kcal;
    float prot;
    float carb;
    float gord;
} Atividade;

// Guarda os macros nutrientes e calorias totais diárias
// a ser consumida pelo usuário, baseado no peso e nivél de ativiade física do usuário
typedef struct {
    int peso;
    float grupo[4];    
} MacrosNutr;

//agrupa os alimentos com os macros para cada 100g 
typedef struct {
    char alimento[QUANT_ALIMENTO][TAM_NOME];  // nomes dos alimentos encontrados
    float macros_para_100g[QUANT_ALIMENTO][4]; // Kcal, Prot, Carb, Gord
} infor_nutri_alimento;

typedef struct{
 char menu_prot[0];
 char menu_carb[0];
}menu;

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
void recebe_alimentos(recebeAlimento a[]);
//função que carrega a lista de alimentos no arquivo
void grava_alimentos(recebeAlimento *a);



/****************************************************************************************************/
/***********************************GERA MENU DE ALIMENTOS ******************************************/
/****************************************"menu.txt"**************************************************/
/****************************************************************************************************/

//função recebe uma lista de alimentos para o menu
void menu_recebe_alimentos(menu m[]);
//função que carrega os alimentos no arquivo
void menu_grava_alimentos(menu *m);
//visualiza o arquivo 



#endif