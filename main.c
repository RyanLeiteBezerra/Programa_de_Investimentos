#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "investidor.h"
#include "investimento.h"
#include "util.h"

enum opcoes_menu{
    op1 = 1,
    op2 = 2,
    op3 = 3,
    op4 = 4,
    op5 = 5,
    op6 = 6,
    op7 = 7,
    op8 = 8
};

// Protótipos
void menu_investidor(FILE *investidor, FILE *codigo, FILE *investimento);
void menu_investimento(FILE *investidor, FILE *investimento);

void menu_principal(FILE *investidor, FILE *codigo, FILE *investimento)
{
    char resposta_usuario[10];

    do {
        printf("======== MENU PRINCIPAL ========\n\n");
        printf("1. Acessar menu investidor\n");
        printf("2. Acessar menu investimentos\n");
        printf("3. Sair\n");
        printf("\n================================\n\n");
        printf("Selecione uma opcao: ");
        fgets(resposta_usuario, 10, stdin);
        resposta_usuario[strcspn(resposta_usuario, "\n")] = '\0';

        if (atoi(resposta_usuario) == op1) {
            menu_investidor(investidor, codigo, investimento);
        }
        else if (atoi(resposta_usuario) == op2) {
            menu_investimento(investidor, investimento);
        }
        else if (atoi(resposta_usuario) == op3) {
            printf("Encerrando o programa...\n");
        }
        else {
            printf("Opcao invalida!\n\n");
        }
    } while (atoi(resposta_usuario) != op3);
}

void menu_investidor(FILE *investidor, FILE *codigo, FILE *investimento)
{
    char resposta_usuario[10];

    do {
        printf("\n============================ MENU INVESTIDOR ============================\n\n");
        printf("1. Inserir novo investidor\n");
        printf("2. Alterar investidor existente\n");
        printf("3. Excluir investidor\n");
        printf("4. Imprimir dados de um investidor com base no seu codigo\n");
        printf("5. Imprimir dados de investidores que tenham um tipo de investimento\n");
        printf("6. Imprimir todos os investidores\n");
        printf("7. Imprimir todos os investidores em ordem crescente de patrimonio\n");
        printf("8. Sair\n");
        printf("\n=========================================================================\n\n");
        printf("Selecione uma opcao: ");
        fgets(resposta_usuario, 10, stdin);
        resposta_usuario[strcspn(resposta_usuario, "\n")] = '\0';

        printf("\n");

        if (atoi(resposta_usuario) == op1) 
        {
            printf("\t\t\tINSERINDO NOVO INVESTIDOR\n\n");
            inserir_novo_investidor(investidor, codigo);
        }
        else if (atoi(resposta_usuario) == op2) {
            printf("\t\t\tALTERANDO INVESTIDOR\n\n");
            alterar_investidor_existente(investidor);
        }
        else if (atoi(resposta_usuario) == op3) {
            printf("\t\t\tEXCLUINDO INVESTIDOR\n\n");
            excluir_investidor(investidor, investimento);
        }
        else if (atoi(resposta_usuario) == op4) {
            printf("\t\t\tBUSCANDO INVESTIDOR\n\n");
            imprimir_investidor_pelo_codigo(investidor, investimento);
        }
        else if (atoi(resposta_usuario) == op5) {
            printf("\t\t\tBUSCANDO INVESTIDORES\n\n");
            imprimir_investidores_pelo_tipo(investidor, investimento);
        }
        else if (atoi(resposta_usuario) == op6) {
            printf("\t\t\tINVESTIDORES REGISTRADOS\n\n");
            listar_investidores(investidor, investimento);
        }
        else if (atoi(resposta_usuario) == op7) {
            printf("\t\t\tINVESTIDORES & PATRIMONIOS\n\n");
            imprimir_investidores_ordemcrescente_patrimonio(investidor, investimento);
        }
        else if (atoi(resposta_usuario) == op8) {
            printf("Voltando ao menu principal...\n\n");
        }
        else {
            printf("Opcao invalida!\n\n");
        }

    } while (atoi(resposta_usuario) != op8);
}

void menu_investimento(FILE *investidor, FILE *investimento)
{
    char resposta_usuario[10];

    do {
        printf("\n======================= MENU INVESTIMENTO =======================\n\n");
        printf("1. Inserir novo investimento\n");
        printf("2. Alterar investimento existente\n");
        printf("3. Excluir investimento\n");
        printf("4. Mostrar dados de um investimento com base no seu codigo\n");
        printf("5. Mostrar investimentos de um investidor pelo seu codigo\n");
        printf("6. Mostrar investimentos em ordem alfabetica por tipo\n");
        printf("7. Sair\n");
        printf("\n=================================================================\n\n");
        printf("Selecione uma opcao: ");
        fgets(resposta_usuario, 10, stdin);
        resposta_usuario[strcspn(resposta_usuario, "\n")] = '\0';

        printf("\n");

        if (atoi(resposta_usuario) == op1) {
            printf("\t\tINSERINDO NOVO INVESTIMENTO\n\n");
            inserir_novo_investimento(investimento,investidor);
        }
        else if (atoi(resposta_usuario) == op2) {
            printf("\t\t\tALTERANDO INVESTIMENTO\n\n");
            alterar_investimento_existente(investimento);
        }
        else if (atoi(resposta_usuario) == op3) {
            printf("\t\t\tEXCLUINDO INVESTIMENTO\n\n");
            excluir_investimento(investimento);
        }
        else if (atoi(resposta_usuario) == op4) {
            printf("\t\t\tBUSCANDO INVESTIMENTO\n\n");
            imprimir_dados_investimento_pelo_codigo(investimento);
        }
        else if (atoi(resposta_usuario) == op5) {
            printf("\t\t\tBUSCANDO INVESTIMENTOS\n\n");
            imprimir_investimentos_pelo_codigo_investidor(investimento);
        }
        else if (atoi(resposta_usuario) == op6) {
            printf("\t\tINVESTIMENTO ORDENADOS PELO TIPO\n\n");
            imprimir_investimentos_alfabeticamente_pelo_tipo(investimento);
        }
        else if (atoi(resposta_usuario) == op7) {
            printf("Voltando ao menu principal...\n\n");
        }
        else {
            printf("Opcao invalida!\n\n");
        }

    } while (atoi(resposta_usuario) != op7);
}

int main()
{
    FILE *investidor, *codigo, *investimento;
    iniciar_arquivos(&investidor, &codigo, &investimento);

    menu_principal(investidor, codigo, investimento);

    fechar_arquivos(&investidor, &codigo, &investimento);
    return 0;
}
