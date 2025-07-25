#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "user.h"
#include "other_functions.h"

#define TAM_NOME 100


/**************dados do usuário****************/

//função pede o nome do usuário
void perguntar_nome(user *u) {

    do {

        // Alocar memória para o nome 
        u->nome = (char *)malloc(TAM_NOME * sizeof(char));
        if (u->nome == NULL) {
            //Tratar erro de alocação
            free(u); //Libera a memória de antes de sair
            return;
        }

        ler_string(u->nome, TAM_NOME, "Entre com seu nome: ");//recebe a entrada do usuário

        if (strlen(u->nome) == 0) printf("\nErro: nome invalido.\n");//verifica se a varíável nome está em branco

    } while (strlen(u->nome) == 0);

}

//função pede o sexo do usuário
void perguntar_sexo(user *u) {

    do {
        printf("Qual seu sexo?(F/M) : ");
        scanf(" %c", &u->sexo);

        if (u->sexo != 'f' && u->sexo != 'F' && u->sexo != 'm' && u->sexo != 'M')
            printf("\nErro: sexo invalido.\n");

    } while (u->sexo != 'f' && u->sexo != 'F' && u->sexo != 'm' && u->sexo != 'M');

}

//função pede a idade do usuário
void perguntar_idade(user *u) {

    int return_scanf;
    int valida_idade = 0;

    do {
        printf("Qual sua idade?:  ");
        return_scanf = scanf(" %d", &u->idade);

        if (return_scanf != 1) { //verifica se a entrada é numérica

            printf("\n\nErro: idade invalida!");

            // Limpa buffer 
            limpar_buffer();

        } else if (u->idade <= 0 || u->idade > 130) {
            printf("\n\nErro: idade invalida!");

            // Limpa buffer 
            limpar_buffer();

        } else {

            valida_idade = 1;

        }

        
        limpar_buffer();

    } while (!valida_idade);
}

//função pede a altura do usuário
void perguntar_altura(user *u) {
    int return_scanf;
    int valida_altura = 0;

    do {
        printf("Qual sua altura (cm)?: ");
        return_scanf = scanf(" %d", &u->altura);

        if (return_scanf != 1) {
            printf("\n\nErro: Altura invalida!");

           limpar_buffer();
           
        } else if (u->altura < 50 || u->altura > 250) {
            printf("\n\nErro: Altura invalida! Fora do intervalo (50cm a 250cm)");

           limpar_buffer();

        } else {
            valida_altura = 1;

           limpar_buffer();

        }

    } while (!valida_altura);
}

//função pede o peso do usuário
void perguntar_peso(user *u) {
    int return_scanf;
    int valida_peso = 0;

    do {
        printf("Qual seu peso (kg)?: ");
        return_scanf = scanf(" %f", &u->peso);
        limpar_buffer();

        if (return_scanf != 1) {
            printf("\n\nErro: Peso invalido! Digite apenas numeros.");
            printf("\nPressione 'ENTER' e entre novamente com o peso.\n");

         limpar_buffer();

        } else if (u->peso <= 0) {
            printf("\n\nErro: peso invalido. Informe um valor positivo.");
            printf("\nPressione 'ENTER' e entre novamente com o peso.\n");

      limpar_buffer();

        } else {
            valida_peso = 1;

     limpar_buffer();
        }

    } while (!valida_peso);
}

/**************impressão****************/

//função imprime os dados do usuário
void imprimir_dados(const user *u) {
    printf("Nome: %s\n", u->nome);
    // printf("sexo: %c\n", u->sexo);
    printf("Idade: %d anos\n", u->idade);
    printf("Altura: %d cm\n", u->altura);
    printf("Peso: %.2f kg\n", u->peso);
}
