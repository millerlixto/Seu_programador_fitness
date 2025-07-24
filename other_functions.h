#ifndef OTHER_H
#define OTHER_H

#define NOME 50


//quarda o nível de atividade do usuário: sedentário, levemente ativo, moderadamete ativo, muito ativo, extremamente ativo 
typedef struct{
 int intensidade;                
} ativ_fisica; 
//quarda o alimento escolhido pelo usuário para montar um plano alimentar
typedef struct {
    char alimentos_escolhidos[NOME];
} select_alimento;

/**************funções genéricas****************/

//seleciona o fator de ativiadade
void definir_fator_atividade_ativo(ativ_fisica *at);
//seleciona o fator de atividade para usuários menos ativos
void definir_fator_atividade_MenosAtivo(ativ_fisica *at);
//recebe a intensidade da atividade física e seleciona do MET 
float valor_MET_User(ativ_fisica *at);
//ler string do teclado
void ler_string(char *buffer, int tamanho, const char *mensagem);
//limpa o buffer
void limpar_buffer();

/**************conversões****************/
//Converte cm para m
double convert_Cm_Para_Metro(user *u);

/**************calculos****************/
//função calcula TMB
double calc_TMB(user *u);
//Calculando o Gasto Calórico Total
//O GCT inclui a TMB, 
//mas também leva em consideração a 
//energia gasta em atividades físicas
double calc_GET(ativ_fisica *at, user *u);
//calculo do IMC ínice de maça corporal
void calc_IMC(user *u);
//calculo dos macros
void calc_Macros(user *u,ativ_fisica* at, select_alimento* sa);
// calcula a idade mas próxima da tabela
int buscar_idade_mais_proxima(user*u);

/**************impressão****************/
//função de impressão de dados das funções de da biblioteca other_functions
void imprimir_Dados_Other_Functions(ativ_fisica *at, user *u);

/**************impressão de plano alimentar****************/
void select_menu(select_alimento *sa);





#endif
