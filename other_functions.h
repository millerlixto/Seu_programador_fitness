#ifndef OTHER_H
#define OTHER_H

/***********************************************/
/*******************ESTRUTURAS******************/
/***********************************************/

//guarda o nível de atividade do usuário: sedentário, levemente ativo, moderadamete ativo, muito ativo, extremamente ativo 
typedef struct{
 int intensidade;                
} ativ_fisica; 
//guarda o alimento escolhido pelo usuário para montar um plano alimentar
typedef struct {
    char* alimentos_escolhidos; 
} select_alimento;

/***********************************************/
/**************FUNÇÕES GENÉRICAS****************/
/***********************************************/

//recebe o peso da struct user e aproxima segundo tabela, que contem intervalos de 5kg
int aproxima_peso(user* u);
//remover espaços no início e no fim das strings
void remove_espacos_str(char *str);
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

/***********************************************/
/******************CONVERSÕES*******************/
/***********************************************/

//Converte cm para m
double convert_Cm_Para_Metro(user *u);

/***********************************************/
/******************CÁLCULOS*********************/
/***********************************************/

//função calcula TMB
double calc_TMB(user *u);
//Calculando o Gasto Calórico Total, o GCT inclui a TMB, 
//também leva em consideração a energia gasta em atividades físicas
double calc_GET(ativ_fisica *at, user *u);
//calculo do IMC ínice de maça corporal
void calc_IMC(user *u);
//Seleção de alimento no menu
void select_Menu(select_alimento* sa);
//calculo dos macros
void calc_Macros(user *u,ativ_fisica* at, select_alimento* sa);









#endif
