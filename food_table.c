#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "food_table.h"
#include "user.h"
#include "other_functions.h"


#define QUANT_ALIMENT0 2
#define TAM_ALIMENTO 50
#define TAM_NOME 50
#define TAM_LINHA 250
#define QUANT_PROT 2
#define QUANT_CARB 2





int macros_por_peso(user *u, ativ_fisica *at, MacrosNutr *saida){

    int peso = u->peso;
    int niveisAtiv = at->intensidade;


    if (niveisAtiv < 0 || niveisAtiv > 4) return 0; // índice inválido

    FILE *f = fopen("macros_tabela.txt", "r");
    if (!f) {
        perror("Erro ao abrir arquivo");
        return 0;
    }

    int linhaPeso;
    float valores[20];

    while (fscanf(f, "%d", &linhaPeso) == 1) {
        int r = fscanf(f, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
                        &valores[0], &valores[1], &valores[2], &valores[3],
                        &valores[4], &valores[5], &valores[6], &valores[7],
                        &valores[8], &valores[9], &valores[10], &valores[11],
                        &valores[12], &valores[13], &valores[14], &valores[15],
                        &valores[16], &valores[17], &valores[18], &valores[19]);

        if (r != 20) break;

        if (linhaPeso == peso) {
            for (int i = 0; i < 4; i++) {
                saida->grupo[i] = valores[niveisAtiv * 4 + i];
            }
            saida->peso = linhaPeso;
            fclose(f);
// Impressão para confirmar
            printf("Peso encontrado: %d\n", saida->peso);
            printf("Grupo %d (4 floats): ", niveisAtiv);
            for (int i = 0; i < 4; i++) {
                printf("%.2f ", saida->grupo[i]);
            }
            printf("\n");

            return 1;
        }
    }

    fclose(f);
    printf("Peso %d nao encontrado no arquivo.\n", peso);
    return 0;
}

/***********************************Busca e retorna o alimento e seus macronutrientes******************************************/
int table_nutriction(infor_nutri_alimento *saida){

char alimento[] = "frango";

    FILE *f = fopen("Tabela_Nutricional.txt", "r");
    if (!f) {
        perror("Erro ao abrir arquivo");
        return 0;
    }

    char linhaAlimento[TAM_ALIMENTO];

    float valores[4];

    while  (fscanf(f, "%s %f %f %f %f",
                  linhaAlimento,
                  &valores[0], &valores[1], &valores[2], &valores[3]) == 5) {
        
        if (strcmp(linhaAlimento, alimento) == 0) {
            for (int i = 0; i < 4; i++) {
                saida->macros_para_100g[i] = valores[i];
            }
            strcpy(saida->alimento, linhaAlimento);
            fclose(f);
// Impressão d confirmação
            printf("Alimento: %s\n", saida->alimento);
            printf("Informacao nutriconal para 100g (Kcal, proteina, carboidrato, gordura): ");
            for (int i = 0; i < 4; i++) {
                printf("%.2f ", saida->macros_para_100g[i]);
            }
            printf("\n");

            return 1;
        }
    }

    fclose(f);
    printf("Alimento %s nao encontrado no arquivo.\n", alimento);
    return 0;
}
/***********************************Gerar tabela nutricional******************************************/

//passa  o alimentos e seus macronutrientes para a struct alimento
void recebe_alimentos(recebeAlimento a[]) {
    int limp;

    for (int i = 0; i < QUANT_ALIMENT0; i++) {
        printf("\n******************************Inicia processo de alimentacao da tabela*********************************\n");

        ler_string(a[i].nome_alimento, TAM_NOME, "\nAlimento: ");

        printf("Calorias para cada 100g do alimento: ");
        scanf(" %f", &a[i].calorias);
        while ((limp = getchar()) != '\n' && limp != EOF);

        printf("Proteína para cada 100g do alimento: ");
        scanf(" %f", &a[i].proteina);
        while ((limp = getchar()) != '\n' && limp != EOF);

        printf("Carboidrato para cada 100g do alimento: ");
        scanf(" %f", &a[i].carboidrato);
        while ((limp = getchar()) != '\n' && limp != EOF);

        printf("Gordura para cada 100g do alimento: ");
        scanf(" %f", &a[i].gordura);
        while ((limp = getchar()) != '\n' && limp != EOF);
    }
}

void grava_alimentos(recebeAlimento a[]){
FILE *f = fopen("Tabela_Nutricional.txt", "w");
    if(f == NULL){
        printf("Erro ao abrir arquivo!");
        return;
    }

// carregar QUANT_ALIMENT0 no arquivo
    for(int i=0; i<QUANT_ALIMENT0; i++){
    fprintf(f, "%s", a[i].nome_alimento);
        fprintf(f, " %.2f %.2f %.2f %.2f\n", a[i].calorias, a[i].proteina, a[i].carboidrato, a[i].gordura);
    }

fprintf(f, "\nArquivo criado com sucesso!\n");

    fclose(f);
    
printf("\nAlimento: %s\n", a->nome_alimento);
printf("calorias: %2.f\n", a->calorias);
printf("proteina: %2.f\n", a->proteina);
printf("carboidrato: %2.f\n", a->carboidrato);
printf("gordura: %2.f\n\n", a->gordura);

}

/***********************************Gerar Menu de alimentos******************************************/
void menu_recebe_alimentos(menu m[]) {

 printf("\n******************************Inicia processo de alimentacao do Menu*********************************\n");

    for (int i = 0; i < QUANT_PROT; i++) {
       
        ler_string(m[i].menu_prot, TAM_NOME, "Proteinas: "); 
    }
printf("\n");

     for (int i = 0; i < QUANT_CARB; i++) {
       
        ler_string(m[i].menu_carb, TAM_NOME, "Carboidratos: "); 
    }
}

void menu_grava_alimentos(menu m[]){
    FILE *f = fopen("Menu.txt", "w");
    if (f == NULL) {
        printf("Erro ao abrir arquivo!");
        return;
    }
    // Grava linha das proteínas
    fprintf(f, "PROTEINAS ");  
    for (int i = 0; i < QUANT_PROT; i++) {
        fprintf(f, "%s, ", m[i].menu_prot); // Escreve alimento 
    }
    fprintf(f, "\n");  

    // Grava linha dos carboidratos
    fprintf(f, "CARBOIDRATOS ");  
    for (int i = 0; i < QUANT_CARB; i++) {
        fprintf(f, "%s, ", m[i].menu_carb);  // Escreve alimento 
    }
    fprintf(f, "\n");  

    fclose(f);
//printf("Proteina: %s\n", m->menu_prot);
//printf("\nCarboidrato: %s\n", m->menu_carb);

    printf("Arquivo criado com sucesso!\n\n");  
}


/***********************************visualiza arquivos gravados******************************************/

void visualiza_aquivo(char *tabela){

    FILE *f;
    char linha[TAM_LINHA];

    f = fopen(tabela, "r");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    // Lê e imprime linha por linha, exatamente como está no arquivo
    while (fgets(linha, sizeof(linha), f) != NULL) {
        printf("%s", linha); // Imprime a linha como está, incluindo a quebra de linha
    }

    fclose(f);
}

