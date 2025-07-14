#include<stdio.h>

#include "user.h"
#include "start_food_table.h"
#include "food_table.h"

#define TAM_NOME 50

void alimenta_tabela() {

user u; 
alimento a; 
ativ_fisica at; 
MacrosNutr saida;
infor_nutri_alimento s;
menu m;

char nome_arquivo1 [TAM_NOME] = "Tabela_Nutricional.txt";
char nome_arquivo2 [TAM_NOME] = "Menu.txt";
char nome_arquivo3 [TAM_NOME] = "macros_tabela.txt";

//table_nutriction(&s);

/***********************************Gerar tabela nutricional******************************************/

//recebe_alimentos(&a); //recebe as informacões nutricionais dos alimentos 
//grava_alimentos(&a);//grava as informacões as nutricionais dos alimentos no arquivo


/***********************************Gerar Menu de alimentos******************************************/

//menu_recebe_alimentos(&m);
//menu_grava_alimentos(&m);

/***********************************visualiza arquivos gravados******************************************/

//visualiza_aquivo(nome_arquivo3);

/***********************************Gera menu para seleção dos alimentos******************************************/



    //if (!macros_por_peso(&u, &at, &saida))printf("Nao foi possivel carregar os dados.\n\n");
    
}
