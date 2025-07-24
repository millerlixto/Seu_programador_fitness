#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "user.h"
#include "food_table.h"
#include "other_functions.h"

#define GRUPO 5

/************** Inicia processo ****************/
void iniciar_processo() {
    user u;
    MacrosNutr saida_MacrosNutr;
    ativ_fisica at;
    char resposta;
    select_alimento sa[5];
    infor_nutri_alimento saida_inf_nutri_alimento;

    // Entrada de dados do usuário          
   
   // perguntar_nome(&u);
   // perguntar_sexo(&u); 
   // perguntar_idade(&u);
   // perguntar_altura(&u);
    perguntar_peso(&u);
    //Pergunta se o usuário pratica atividade física
    do {
        printf("Voce pratica alguma atividade fisica? (s/n): ");
        scanf(" %c", &resposta); // espaço ignora lixo no buffer
        resposta = tolower(resposta);

        if (resposta == 's') {
       // retorna opções em números 1 à 5
          definir_fator_atividade_ativo(&at);
          //Função recebe peso e nível de atividade, retorna 1 se achou, 0 caso contrário. Guarda na struct "MacrusNutr"
          // peso e os macros nutrientes relacionado ao peso e nível de atividade
          macros_por_peso(&u, &at, &saida_MacrosNutr);
          //valida a entrada dos daodsnecessários para a fução funcionar
            if (!macros_por_peso(&u, &at, &saida_MacrosNutr))printf("Nao foi possivel carregar os dados.\n\n");
             //limpar terminal
           // system("cls"); // Windows
            // system("clear"); // Linux/macOS

           // imprimir_dados(&u);
            //printf("\n************** Avaliar Saude ***************\n");

           // calc_IMC(&u);
           // printf("Gasto Energetico Total: %.2f calorias (cal)\n", calc_GET(&at, &u));
           // printf("\n************** Sugestao de Plano Alimentar ***************\n");
            // Gerar plano alimentar para ativos
            select_menu(sa);
            // recebe os alimentos de select_alimentos e guarda os macros para cada 100g na struct INFOR_NUTRI
            table_nutriction(&saida_inf_nutri_alimento,sa);

            

        } else if (resposta == 'n') {
            // Menos ativo: apenas fator de atividade
            definir_fator_atividade_MenosAtivo(&at);
            macros_por_peso(&u, &at, &saida_MacrosNutr);
          if (!macros_por_peso(&u, &at, &saida_MacrosNutr))printf("Nao foi possivel carregar os dados.\n\n");
          //  system("cls");
            // system("clear");

         //   imprimir_dados(&u);
          //  printf("\n************** Avaliacao ***************\n");
            
         //   calc_IMC(&u);
         //   printf("Gasto Energetico Total: %.2f calorias (cal)\n", calc_GET(&at, &u));
          //  printf("\n************** Sugestao de Plano Alimentar ***************\n");
            // Gerar plano alimentar para sedentários
          select_menu(sa);
          table_nutriction(&saida_inf_nutri_alimento,sa);
        } else {
            printf("\nResposta invalida! Use 's' para sim ou 'n' para nao.\n");
        }

    } while (resposta != 's' && resposta != 'n');
    
printf("\n************** ATENCAO! ***************\n");
    printf("\nPara melhores resultados, procure um nutricionista ou profissional de saude!\n\n");
}