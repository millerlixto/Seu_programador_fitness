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
    MacrosNutr saida;
    ativ_fisica at;
    char resposta;
    select_alimento sa[5];

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
          macros_por_peso(&u, &at, &saida);
            if (!macros_por_peso(&u, &at, &saida))printf("Nao foi possivel carregar os dados.\n\n");
             //limpar terminal
           // system("cls"); // Windows
            // system("clear"); // Linux/macOS

           // imprimir_dados(&u);
            //printf("\n************** Avaliar Saude ***************\n");

           // calc_IMC(&u);
           // printf("Gasto Energetico Total: %.2f calorias (cal)\n", calc_GET(&at, &u));
           // printf("\n************** Sugestao de Plano Alimentar ***************\n");
            // Gerar plano alimentar para ativos
           // select_menu(sa);

            

        } else if (resposta == 'n') {
            // Menos ativo: apenas fator de atividade
            definir_fator_atividade_MenosAtivo(&at);
            macros_por_peso(&u, &at, &saida);
          if (!macros_por_peso(&u, &at, &saida))printf("Nao foi possivel carregar os dados.\n\n");
          //  system("cls");
            // system("clear");

         //   imprimir_dados(&u);
          //  printf("\n************** Avaliacao ***************\n");
            
         //   calc_IMC(&u);
         //   printf("Gasto Energetico Total: %.2f calorias (cal)\n", calc_GET(&at, &u));
          //  printf("\n************** Sugestao de Plano Alimentar ***************\n");
            // Gerar plano alimentar para sedentários
        //    select_menu(sa);
        } else {
            printf("\nResposta invalida! Use 's' para sim ou 'n' para nao.\n");
        }

    } while (resposta != 's' && resposta != 'n');
    
printf("\n************** ATENCAO! ***************\n");
    printf("\nPara melhores resultados, procure um nutricionista ou profissional de saude!\n\n");
}