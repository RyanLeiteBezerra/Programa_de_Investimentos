#ifndef INVESTIMENTO_H
#define INVESTIMENTO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "investidor.h"

void armazenar_data_hoje(struct data *data_hoje);
int ler_codigo_para_investimento(FILE *investidor, int *codigo_investidor, char *codigo_investimento);
void inserir_tipo(char *tipo_investimento);
void inserir_valor(float *valor_investimento);
void inserir_descricao(char *descricao_investimento);
void inserir_data_aplicacao(struct data* data_investimento);
void inserir_prazo(int *prazo_investimento);
void inserir_rentabilidade_anual(float *rentabilidade_anual);
void inserir_novo_investimento(FILE *investimento, FILE *investidor);
void alterar_investimento_existente(FILE *investimento);
void excluir_investimento(FILE *investimento);
float rendimento_investimento(struct dados_investimento investimento);
void imprimir_dados_investimento_pelo_codigo(FILE *investimento);
void imprimir_investimentos_pelo_codigo_investidor(FILE *investimento);
void imprimir_investimentos_alfabeticamente_pelo_tipo(FILE *investimento);
float patrimonio_investidor(int codigo_investidor, FILE *investimento);

#endif
