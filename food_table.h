#ifndef INICIAR_H
#define INICIAR_H

#include "user.h"
#include "other_functions.h"

#define TAM_ALIMENTO 50

//recebe entrada do usuário para carregar
//aquivo com as opçoes de alimentos, na tabela nutricional
typedef struct{
char nome_alimento[TAM_ALIMENTO];
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

// Quarda os macros nutrientes e calorias totais diárias
// a ser consumida pelo usuário, 
//baseado no peso e nivél de ativiade física do usuário
typedef struct {
    int peso;
    float grupo[4];    
} MacrosNutr;

typedef struct {
    char alimento[TAM_ALIMENTO];          //  (alimento)
    float macros_para_100g[0];    // macros para cada 100g de alimento
}infor_nutri_alimento;

typedef struct{
 char menu_prot[0];
 char menu_carb[0];
}menu;

//Função recebe peso e nível de atividade, retorna 1 se achou, 0 caso contrário
int macros_por_peso(user *u, ativ_fisica *at, MacrosNutr *saida);

//função retorna os macros nutrientes por alimento
int table_nutriction(infor_nutri_alimento *saida);


/***********************************Gerar alimentos na tabela nutricional******************************************/
//função recebe uma lista de alimentos
void recebe_alimentos(recebeAlimento a[]);
//função que carrega a lista de alimentos no arquivo
void grava_alimentos(recebeAlimento *a);



/***********************************Gerar Menu de alimentos******************************************/
//função recebe uma lista de alimentos para o menu
void menu_recebe_alimentos(menu m[]);
//função que carrega os alimentos no arquivo
void menu_grava_alimentos(menu *m);
//visualiza o arquivo 

/***********************************visualiza arquivos gravados******************************************/

void visualiza_aquivo(char *tabela);


#endif