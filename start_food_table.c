#include<stdio.h>

#include "user.h"
#include "start_food_table.h"
#include "food_table.h"



void alimenta_tabela() {


	recebeAlimento *a = NULL; 
	menu m;


/***********************************Gerar tabela nutricional******************************************/

recebe_alimentos(&a); //recebe as informacões nutricionais dos alimentos 
grava_alimentos(&a);//grava as informacões as nutricionais dos alimentos no arquivo


/***********************************Gerar Menu de alimentos******************************************/

menu_recebe_alimentos(&m);
menu_grava_alimentos(&m);


/***********************************Gera menu para seleção dos alimentos******************************************/



}
