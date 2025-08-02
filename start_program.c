#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "user.h"
#include "food_table.h"
#include "other_functions.h"

#define GRUPO 5
select_alimento sa[GRUPO];  
user u;
ativ_fisica at;
MacrosNutr saida_MacrosNutr;
infor_nutri_alimento saida_inf_nutri_alimento;
plano_alimentar pa;

char resposta;


//************** Inicia processo ****************/
void iniciar_processo() {
//Alimenta struct "user", com os dados so usuário
  perguntar_nome(&u);
  perguntar_sexo(&u); 
  perguntar_idade(&u);
  perguntar_altura(&u);
  perguntar_peso(&u);

  do {
    printf("Voce pratica alguma atividade fisica? (s/n): ");
    scanf(" %c", &resposta); 
    limpar_buffer();
        resposta = tolower(resposta);//converte caracter para minuculo
        if (resposta == 's') {
        // usuário escolhe de 1 à 5 o nível da tividade física que pratica

           definir_fator_atividade_ativo(&at);
           system("cls");

       } else if (resposta == 'n') {
             // usuário escolhe de 0 à 1 o nível atividade diária
        definir_fator_atividade_MenosAtivo(&at);
        system("cls");
    } else {
        printf("\nResposta invalida! Use 's' para sim ou 'n' para nao.\n");
    }

} while (resposta != 's' && resposta != 'n');
printf("\n************** Dados ***************\n");
imprimir_dados(&u);
printf("\n************** Avaliacao ***************\n");
calc_IMC(&u);
printf("Gasto Energetico Total: %.2f calorias (cal)\n", calc_GET(&at, &u));
printf("\n***************************************\n\n");

printf("Pressione Enter para continuar...");
// espera até o Enter
while (getchar() != '\n'); 
//limpa terminal
system("cls");
//continua aplicação
printf("Continuando...\n");
           //Função recebe peso e nível de atividade, retorna 1 se achou, 0 caso contrário. Guarda na struct "MacrusNutr"
          // o peso e os macros nutrientes relacionado ao peso e nível de atividade
if (!macros_por_peso(&u, &at, &saida_MacrosNutr))printf("Nao foi possivel carregar os dados.\n\n");
select_Menu(sa);
table_nutriction(&saida_inf_nutri_alimento,sa);
         // Copia os dados para o plano alimentar final
pa.MacrosNutr = saida_MacrosNutr;
pa.infor_nutri_alimento = saida_inf_nutri_alimento;
// função que exibe o plano alimentar
planoAlimentar(&pa);
}


