#include<stdio.h>

#include "user.h"
#include "start_food_table.h"
#include "food_table.h"



void alimenta_tabela() {


	aux_recebeAlimento aux; 
	


/***********************************Gerar tabela nutricional******************************************/

recebe_alimentos(&aux); //recebe as informacões nutricionais dos alimentos 
grava_alimentos(&aux);//grava as informacões nutricionais dos alimentos no arquivo


/***********************************Gerar Menu de alimentos******************************************/


menu_grava_alimentos(&aux);


/***********************************Gera menu para seleção dos alimentos******************************************/



}
