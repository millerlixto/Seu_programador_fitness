#ifndef USER_H
#define USER_H



typedef struct {//
    
    char *nome;
    char sexo;
    int idade;
    int altura;
    float peso;
   
} user;
/**************dados do usuário****************/
void perguntar_nome(user *u);
void perguntar_sexo(user *u);
void perguntar_idade(user *u);
void perguntar_altura(user *u);
void perguntar_peso(user *u);

/**************impressão****************/
void imprimir_dados(const user *u);

#endif