#ifndef INVESTIDOR_H
#define INVESTIDOR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TAMANHO_DOS_NOMES 255
#define TAMANHO_DOS_ENDERECOS 255
#define TAMANHO_DO_CPF 255
#define TAMANHO_DA_DATA 255
#define TAMANHO_SALARIO 255
#define TAMANHO_DO_CODIGO 255
#define TAMANHO_CHAR 255

struct data
{
    int dia;
    int mes;
    int ano;
};

struct dados_investidor {
int codigo; //Obrigatorio
int acumulador_codigo_investimento; //Obrigatorio
char nome[TAMANHO_DOS_NOMES]; //Obrigatorio
char cpf[TAMANHO_DO_CPF]; //Obrigatorio
char endereco[TAMANHO_DOS_ENDERECOS];
char data_nascimento[TAMANHO_DA_DATA]; //Obrigatorio
float salario; //Obrigatorio
};

struct dados_investimento {
char codigo_investimento[TAMANHO_CHAR]; //Obrigatorio
int codigo_investidor; //Obrigatorio
char tipo[TAMANHO_CHAR]; //Obrigatorio
float valor; //Obrigatorio
char descricao[TAMANHO_CHAR]; //Obrigatorio
int prazo; //Obrigatorio (Em dias corridos)
float rentabilidade_anual; //Obrigatorio
struct data data_aplicacao; //Obrigatorio, mas caso o usuário não digite pega a data de hoje.
//VALORIZAO ATE HOJE (CAMPO CALCULADO)
};

struct nome_patrimonio {
    char nome_investidor[TAMANHO_CHAR];
    float patrimonio;
};

void limpar_buffer();

void inserir_novo_investidor(FILE *f, FILE *g);

void alterar_nome(FILE *f, char *novo_nome);

void alterar_cpf(FILE *f, char *novo_cpf);

void alterar_endereco(FILE *f,char *novo_endereco);

void alterar_data_nascimento(FILE *f, char *nova_data);

void alterar_investidor_existente(FILE *f);

void listar_investidores(FILE *f,FILE *investimento);

void excluir_investidor(FILE *f,FILE *investimento);

void imprimir_investidor_pelo_codigo(FILE *f,FILE *investimento);

void imprimir_investidores_ordemcrescente_patrimonio(FILE *f,FILE *investimento);

void imprimir_investidores_pelo_tipo(FILE *f,FILE *investimento);

#endif
