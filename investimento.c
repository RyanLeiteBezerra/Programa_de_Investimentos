#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "investidor.h"

void armazenar_data_hoje(struct data *data_hoje)
{
    time_t t = time(NULL);
    struct tm *dataAtual = localtime(&t);
    data_hoje->dia = dataAtual->tm_mday;
    data_hoje->mes = dataAtual->tm_mon + 1;
    data_hoje->ano = dataAtual->tm_year + 1900;
}

int ler_codigo_para_investimento(FILE *investidor, int *codigo_investidor, char *codigo_investimento)
{
        char codigo[TAMANHO_CHAR];
        int codigo_inserido;
        int codigo_existente;
        int continuar_lendo;
        char resposta_usuario[2];

        do
        {

        codigo_existente = 0;
        continuar_lendo = 1;
        codigo_inserido = 0;


        printf("Digite o codigo do investidor para adicionar um investimento:\n");
        fgets(codigo,TAMANHO_CHAR, stdin);
        codigo[strcspn(codigo, "\n")] = '\0';

        if(codigo[0] == '\0')
        {
            printf("Voce precisa digitar algo!\n");
        }
        else
        {
            //LOOP PARA LER TODOS OS STRUCTS DO ARQUIVO.BIN:

            fseek(investidor,0,SEEK_SET); //COLOCAR O PONTEIRO NO INÍCIO DO ARQUIVO

            while(!feof(investidor))
            {
                struct dados_investidor alguem;

                fread(&alguem,sizeof(struct dados_investidor),1,investidor);

                char codigo_algum_investidor[TAMANHO_CHAR];
                sprintf(codigo_algum_investidor, "%d", alguem.codigo);

                //VERIFICAR SE TEM ALGUEM COM O MESMO NOME:
                if (strcmp(codigo,codigo_algum_investidor)==0)
                {
                    codigo_existente = 1;
                    codigo_inserido = 1;

                    *codigo_investidor = alguem.codigo;
                    sprintf(codigo_investimento, "%d.%d", alguem.codigo, alguem.acumulador_codigo_investimento+1);

                    //ESCREVER NO INVESTIDOR.BIN O NOVO VALOR DE ACUMULADOR_CODIGO_INVESTIMENTO:

                    alguem.acumulador_codigo_investimento = alguem.acumulador_codigo_investimento + 1;

                    fseek(investidor,-sizeof(struct dados_investidor),SEEK_CUR);
                    fwrite(&alguem,sizeof(struct dados_investidor),1,investidor);

                    break;
                }
            } 
        }

        if (codigo_existente == 0 && codigo[0] != '\0')
        {
            printf("\nNao existe investidor com esse codigo!\n");
            continuar_lendo = 0;
        }

        } while(codigo_inserido == 0 && continuar_lendo == 1);

        if(codigo_inserido == 1)
            return 1;
        if(continuar_lendo == 0)
            return 0;
}

void inserir_tipo(char *tipo_investimento)
{
        char tipo[TAMANHO_CHAR];
        int tipo_inserido;

        do
        {

        tipo_inserido = 0;

        printf("Digite o tipo do investimento:\n");
        fgets(tipo,TAMANHO_CHAR, stdin);
        tipo[strcspn(tipo, "\n")] = '\0';

        int tamanho_nome = strlen(tipo);

        for (int i = 0; i < tamanho_nome; i++)
        {
            tipo[i] = toupper(tipo[i]);
        }

        if(tipo[0] == '\0')
        {
            printf("O tipo do investimento e obrigatorio!\n");
        }
        else
        {
            tipo_inserido = 1;
            strcpy(tipo_investimento,tipo);
        }

        } while(tipo_inserido == 0);
}

void inserir_valor(float *valor_investimento)
{
                char valor[TAMANHO_CHAR];
                int valor_inserido = 0;

                do
                {
                    valor_inserido = 0;

                    printf("Digite o valor do investimento (R$):\n");
                    fgets(valor,TAMANHO_CHAR, stdin);
                    valor[strcspn(valor, "\n")] = '\0';

                    //TROCAR O A VIRGULA POR PONTO:
                    valor[strcspn(valor,",")] = '.';

                    if(valor[0] == '\0')
                    printf("O valor do investimento eh obrigatorio!\n");
                    else
                    {
                    *valor_investimento = atof(valor);
                    valor_inserido = 1;
                    }

                }while(valor_inserido == 0);
}

void inserir_descricao(char *descricao_investimento)
{
                char descricao[TAMANHO_CHAR];
                int descricao_inserido = 0;

                do
                {
                    descricao_inserido = 0;

                    printf("Digite uma descricao para esse investimento:\n");
                    fgets(descricao,TAMANHO_CHAR, stdin);
                    descricao[strcspn(descricao, "\n")] = '\0';

                    if(descricao[0] == '\0')
                        printf("A descricao do investimento e obrigatoria!\n");
                    else
                    {
                        strcpy(descricao_investimento,descricao);
                        descricao_inserido = 1;
                    }

                }while(descricao_inserido == 0);
}

void inserir_data_aplicacao(struct data* data_investimento)
{
    int data_inserida;
    char resposta_usuario[2];
    char dia[3], mes[3], ano[5];

    do
    {
        data_inserida = 0;

        do {
            printf("Como voce deseja armazenar a data de aplicacao?\n\n");
            printf("- Inserir (manualmente) (Digite 1)\n");
            printf("- Inserir a data de hoje (automaticamente) (Digite 2)\n\n");

            fgets(resposta_usuario, 2, stdin);
            resposta_usuario[strcspn(resposta_usuario, "\n")] = '\0';

            limpar_buffer();

        } while (!(resposta_usuario[0] == '1' || resposta_usuario[0] == '2'));

        if (resposta_usuario[0] == '1') {
            printf("Preencha a data de aplicacao do investimento (dd/mm/yyyy):\n");

            printf("Dia: ");
            fgets(dia, 3, stdin);
            dia[strcspn(dia, "\n")] = '\0';

            limpar_buffer();

            printf("Mes: ");
            fgets(mes, 3, stdin);
            mes[strcspn(mes, "\n")] = '\0';

            limpar_buffer();

            printf("Ano: ");
            fgets(ano, 5, stdin);
            ano[strcspn(ano, "\n")] = '\0';

            if (strlen(dia) == 0 || strlen(mes) == 0 || strlen(ano) == 0) {
                printf("E obrigatorio preencher completamente a data de nascimento!\n");
            } else {
                int dia_num = atoi(dia);
                int mes_num = atoi(mes);
                int ano_num = atoi(ano);

                if (dia_num < 1 || dia_num > 31 || mes_num < 1 || mes_num > 12 || ano_num < 1900 || ano_num > 9999) {
                    printf("A data de aplicacao eh invalida!\n");
                } else {
                    data_investimento->dia = dia_num;
                    data_investimento->mes = mes_num;
                    data_investimento->ano = ano_num;
                    data_inserida = 1;
                }
            }
        }

        if (resposta_usuario[0] == '2') {
            armazenar_data_hoje(data_investimento);
            data_inserida = 1;
        }

    } while (data_inserida == 0);
}


void inserir_prazo(int *prazo_investimento)
{
    char prazo[TAMANHO_CHAR];
    int prazo_inserido = 0;

    do
    {
        prazo_inserido = 0;

        printf("Digite o prazo do investimento (Em dias corridos):\n");
        fgets(prazo,TAMANHO_CHAR, stdin);
        prazo[strcspn(prazo, "\n")] = '\0';

        if(prazo[0] == '\0')
        printf("O prazo do investimento eh obrigatorio!\n");
        else
        {
            *prazo_investimento = atoi(prazo);
            prazo_inserido = 1;
        }

    }while(prazo_inserido == 0);
}

void inserir_rentabilidade_anual(float *rentabilidade_anual)
{
    char rentabilidade[TAMANHO_CHAR];
    int rentabilidade_inserido = 0;

    do
    {
        rentabilidade_inserido = 0;

        printf("Digite a rentabilidade anual do investimento (Em porcentagem):\n");
        fgets(rentabilidade,TAMANHO_CHAR, stdin);
        rentabilidade[strcspn(rentabilidade, "\n")] = '\0';

        //TROCAR O A VIRGULA POR PONTO:
        rentabilidade[strcspn(rentabilidade,",")] = '.';

        if(rentabilidade[0] == '\0')
        printf("A rentabilidade anual do investimento eh obrigatoria!\n");
        else
        {
            *rentabilidade_anual = atof(rentabilidade);
            rentabilidade_inserido = 1;
        }    

    }while(rentabilidade_inserido == 0);
}

void inserir_novo_investimento(FILE *investimento,FILE *investidor)
{
    struct dados_investimento novo_investimento;

    int continuar = 0;
    //////////////////////////////////////////////////////////////
    int codigo_investidor;
    char codigo_investimento[TAMANHO_CHAR];
    char tipo_investimento[TAMANHO_CHAR];
    float valor_investimento;
    char descricao_investimento[TAMANHO_CHAR];
    int prazo_investimento;
    float rentabilidade_investimento;
    struct data data_aplicacao;
    //////////////////////////////////////////////////////////////

    continuar = ler_codigo_para_investimento(investidor,&codigo_investidor,codigo_investimento);

    if(continuar == 1)
    {
        int investimento_deletado_encontrado = 0;

        inserir_tipo(tipo_investimento);
        inserir_valor(&valor_investimento);
        inserir_descricao(descricao_investimento);
        inserir_prazo(&prazo_investimento);
        inserir_rentabilidade_anual(&rentabilidade_investimento);
        inserir_data_aplicacao(&data_aplicacao);

        //INSERIR DADOS NA STRUCT:
        novo_investimento.codigo_investidor = codigo_investidor;
        strcpy(novo_investimento.codigo_investimento,codigo_investimento);
        strcpy(novo_investimento.tipo,tipo_investimento);
        novo_investimento.valor = valor_investimento;
        strcpy(novo_investimento.descricao,descricao_investimento);
        novo_investimento.prazo = prazo_investimento;
        novo_investimento.rentabilidade_anual = rentabilidade_investimento;
        novo_investimento.data_aplicacao = data_aplicacao;

        //ENCONTRAR UM INVESTIMENTO DELETADO NO ARQUIVO P/ SOBRESCREVER:
            fseek(investimento,0,SEEK_SET);

            while(!feof(investimento))
            {
                struct dados_investimento alguem;

                fread(&alguem,sizeof(struct dados_investimento),1,investimento);

                if(strcmp(alguem.codigo_investimento,"\0")==0)
                {
                    fseek(investimento,-sizeof(struct dados_investimento),SEEK_CUR);
                    fwrite(&novo_investimento, sizeof(struct dados_investimento),1,investimento);

                    investimento_deletado_encontrado = 1;
                    break;
                }
            }
        /////////////////////////////////////////////////////////////////

        //ESCREVER NO FINAL DO ARQUIVO, CASO NÃO ENCONTRE INVESTIMENTO DELETADO:
            if(investimento_deletado_encontrado == 0)
            {
                fseek(investimento,0,SEEK_END);
                fwrite(&novo_investimento, sizeof(struct dados_investimento),1,investimento);
            }
        /////////////////////////////////////////////////////////////////

        limpar_buffer();
    }
}

void alterar_investimento_existente(FILE *investimento)
{
    struct dados_investimento novo_investimento;
    int investimento_alterado;
    int codigo_existente;
    char resposta_usuario[2];
    int sair;

    do
    {
        char codigo[TAMANHO_CHAR];
        investimento_alterado = 0;
        codigo_existente = 0;
        sair = 0;

        printf("Digite o codigo do investimento cujo os dados deseja alterar:\n");
        fgets(codigo, TAMANHO_CHAR, stdin);
        codigo[strcspn(codigo,"\n")] = '\0';

        if(codigo[0] == '\0')
        {
            printf("Voce precisa digitar algo!\n");
        }
        else
        {
            fseek(investimento,0,SEEK_SET);

            while(!feof(investimento))
            {
                fread(&novo_investimento,sizeof(struct dados_investimento),1,investimento);

                if(strcmp(codigo,novo_investimento.codigo_investimento)==0)
                {
                    printf("Quais dados voce deseja alterar do investimento?\n\n");
                    do
                    {
                        printf("- Tipo (Digite 1)\n");
                        printf("- Valor (Digite 2)\n");
                        printf("- Descricao (Digite 3)\n");
                        printf("- Prazo (Digite 4)\n");
                        printf("- Rentabilidade Anual (Digite 5)\n");
                        printf("- Data de aplicacao (Digite 6)\n");
                        printf("- Sair (Digite 7)\n\n");

                        fgets(resposta_usuario, 2, stdin);
                        resposta_usuario[strcspn(resposta_usuario,"\n")] = '\0';

                        limpar_buffer();

                        if(resposta_usuario[0] == '1')
                            inserir_tipo(novo_investimento.tipo);
                        if(resposta_usuario[0] == '2')
                            inserir_valor(&novo_investimento.valor);
                        if(resposta_usuario[0] == '3')
                            inserir_descricao(novo_investimento.descricao);
                        if(resposta_usuario[0] == '4')
                            inserir_prazo(&novo_investimento.prazo);
                        if(resposta_usuario[0] == '5')
                            inserir_rentabilidade_anual(&novo_investimento.rentabilidade_anual);
                        if(resposta_usuario[0] == '6')
                            inserir_data_aplicacao(&novo_investimento.data_aplicacao);
                        if(resposta_usuario[0] == '7')
                        {
                            fseek(investimento,0,SEEK_SET);

                            do{ //REPOSICIONAR O PONTEIRO
                            
                                struct dados_investimento algum;

                                fread(&algum,sizeof(struct dados_investimento),1,investimento);

                                if(strcmp(codigo,algum.codigo_investimento)==0)
                                {
                                    fseek(investimento,-sizeof(struct dados_investimento), SEEK_CUR); //COLOCAR O PONTEIRO UMA POSIÇÃO ANTES DA POSIÇÃO QUE DESEJO SOBRESCREVER
                                    fwrite(&novo_investimento, sizeof(struct dados_investimento),1,investimento);
                                    investimento_alterado = 1;
                                    break;
                                }

                            }while(!feof(investimento));
                        }

                    }while(!(resposta_usuario[0] == '7'));

                        codigo_existente = 1;
                        break;
                }
            }

            if(codigo_existente == 0 && codigo[0] != '\0')
            {
                printf("\nNao existe investimento com esse codigo!\n");
                sair = 1;
            }
        }

    }while(investimento_alterado == 0 && sair == 0);
}

void excluir_investimento(FILE *investimento)
{
    char codigo[TAMANHO_CHAR];
    struct dados_investimento algum;
    int codigo_existente;
    int investimento_excluido;
    int continuar_excluindo;

    do
    {
        codigo_existente = 0;
        continuar_excluindo = 1;
        investimento_excluido = 0;

        printf("Digite o codigo do investimento que deseja deletar:\n");
        fgets(codigo,TAMANHO_DOS_NOMES, stdin);
        codigo[strcspn(codigo, "\n")] = '\0';

        if(codigo[0] == '\0')
        {
            printf("Voce precisa digitar algo!\n");
        }
        else
        {
            //LOOP PARA LER TODOS OS STRUCTS DO ARQUIVO.BIN:

            fseek(investimento,0,SEEK_SET); //COLOCAR O PONTEIRO NO INÍCIO DO ARQUIVO

            while(!feof(investimento))
            {
                struct dados_investimento algum;

                fread(&algum,sizeof(struct dados_investimento),1,investimento);

                if (strcmp(codigo,algum.codigo_investimento)==0)
                {
                    //COLOCAR VAZIO NOS DADOS DO INVESTIMENTO
                    strcpy(algum.codigo_investimento,"\0");

                    fseek(investimento,-sizeof(struct dados_investimento),SEEK_CUR);
                    fwrite(&algum,sizeof(struct dados_investimento),1,investimento);

                    codigo_existente = 1;
                    investimento_excluido = 1;
                    break;
                }
            }
        }
        
        if(codigo_existente == 0 && codigo[0] != '\0')
        {
            printf("\nNao existe investimento com esse codigo!\n");
            continuar_excluindo = 0;
        }

    } while (investimento_excluido == 0 && continuar_excluindo == 1);
}

float rendimento_investimento(struct dados_investimento investimento)
{
    float valor_atualizado;

    time_t t = time(NULL);
    struct tm *dataAtual = localtime(&t);
    int diaAtual = dataAtual->tm_mday;
    int mesAtual = dataAtual->tm_mon + 1;
    int anoAtual = dataAtual->tm_year + 1900;

    time_t tAplicacao, tAtual;
    struct tm dataAplicacao;
    dataAplicacao.tm_year = investimento.data_aplicacao.ano - 1900;
    dataAplicacao.tm_mon = investimento.data_aplicacao.mes - 1;
    dataAplicacao.tm_mday = investimento.data_aplicacao.dia;
    dataAplicacao.tm_hour = 0;
    dataAplicacao.tm_min = 0;
    dataAplicacao.tm_sec = 0;
    dataAplicacao.tm_isdst = -1;
    tAplicacao = mktime(&dataAplicacao);
    tAtual = mktime(dataAtual);
    int diferencaDias = (int)difftime(tAtual, tAplicacao) / (60 * 60 * 24);

    if(diferencaDias < investimento.prazo)
    {
        float taxa = 1.0 + (investimento.rentabilidade_anual / 100.0);
        valor_atualizado = investimento.valor * pow(taxa, (float)diferencaDias/365);
    }
    else
    {
        float taxa = 1.0 + (investimento.rentabilidade_anual / 100.0);
        valor_atualizado = investimento.valor * pow(taxa, (float)investimento.prazo/365);
    }
    
    return valor_atualizado;
}

void imprimir_dados_investimento_pelo_codigo(FILE *investimento)
{
    struct dados_investimento algum;
    char codigo[TAMANHO_CHAR];

    int codigo_existente;
    int investimento_imprimido;
    int continuar_procurando;

    do
    {
        codigo_existente = 0;
        investimento_imprimido = 0;
        continuar_procurando = 1;

        printf("Digite o codigo do investimento cujos os dados deseja imprimir:\n");
        fgets(codigo, TAMANHO_CHAR,stdin);
        codigo[strcspn(codigo,"\n")] = '\0';

        if(codigo[0] == '\0')
            printf("Voce precisa digitar algo!\n");
        else
        {
            fseek(investimento,0,SEEK_SET);

            do
            {
                fread(&algum,sizeof(struct dados_investimento),1,investimento);

                if(strcmp(codigo,algum.codigo_investimento)==0)
                {
                    printf("-----------------------------------\n");
                    printf("Codigo do investimento - %s\n\n",algum.codigo_investimento);
                    printf("- Codigo do investidor: %d\n",algum.codigo_investidor);
                    printf("- Tipo: %s\n", algum.tipo);
                    printf("- Valor: R$ %.2f\n", algum.valor);
                    printf("- Descricao: %s\n", algum.descricao);
                    printf("- Prazo: %d dias\n", algum.prazo);
                    printf("- Rentabilidade Anual: %.2f %%\n", algum.rentabilidade_anual);
                    printf("- Data de Aplicacao: %02d/%02d/%04d\n", algum.data_aplicacao.dia,
                        algum.data_aplicacao.mes, algum.data_aplicacao.ano);
                    printf("- Valorizacao ate hoje: %.2f\n",rendimento_investimento(algum));
                    printf("-----------------------------------\n");

                    codigo_existente = 1;
                    investimento_imprimido = 1;
                    break;
                }

            }while(!feof(investimento));
        }

        if(codigo[0] != '\0' && codigo_existente == 0)
        {
            printf("\nNao existe investimento com esse codigo!\n");
            continuar_procurando = 0;
        }
        
    }while(investimento_imprimido == 0 && continuar_procurando == 1);
}

void imprimir_investimentos_pelo_codigo_investidor(FILE *investimento)
{
    char codigo[TAMANHO_CHAR];
    struct dados_investimento algum;

    int codigo_existente = 0;
    int investimentos_imprimidos = 0;
    int continuar_procurando = 1;

    do
    {

        codigo_existente = 0;
        investimentos_imprimidos = 0;
        continuar_procurando = 1;

        printf("Digite o codigo do investidor cujos investimentos deseja imprimir:\n");
        fgets(codigo, TAMANHO_CHAR, stdin);
        codigo[strcspn(codigo, "\n")] = '\0';

        if(codigo[0] == '\0')
        {
            printf("Voce precisa digitar algo!\n");
        }
        else if(atoi(codigo) == 0)
        {
            printf("\nNao existe investidor com esse codigo!\n");
            continuar_procurando = 0;
        }
        else
        {
            fseek(investimento, 0, SEEK_SET);

            while (fread(&algum, sizeof(struct dados_investimento), 1, investimento) == 1)
            {
                char str[TAMANHO_CHAR];
                sprintf(str, "%d", algum.codigo_investidor);

                if (strcmp(codigo, str) == 0)
                {
                    codigo_existente = 1;
                    if(strcmp(algum.codigo_investimento,"\0") != 0)
                    {
                    printf("-----------------------------------\n");
                    printf("- Codigo do investimento: %s\n", algum.codigo_investimento);
                    printf("- Tipo: %s\n", algum.tipo);
                    printf("- Valor: R$ %.2f\n", algum.valor);
                    printf("- Descricao: %s\n", algum.descricao);
                    printf("- Prazo: %d dias\n", algum.prazo);
                    printf("- Rentabilidade Anual: %.2f %%\n", algum.rentabilidade_anual);
                    printf("- Data de Aplicacao: %02d/%02d/%04d\n", algum.data_aplicacao.dia,
                        algum.data_aplicacao.mes, algum.data_aplicacao.ano);
                    printf("- Valorizacao ate hoje: %.2f\n", rendimento_investimento(algum));
                    printf("-----------------------------------\n");
                    investimentos_imprimidos = 1;
                    }
                }
            }

            if (codigo_existente == 0)
            {
                printf("\nNao existe investidor com esse codigo ou esse investidor nao possui investimentos!\n");
                continuar_procurando = 0;
            }
            if(codigo_existente == 1 && investimentos_imprimidos == 0)
            {
                printf("\nEsse investidor nao possui investimentos!\n");
                continuar_procurando = 0;
            }

        }

    }while(investimentos_imprimidos == 0 && continuar_procurando == 1);
}

void imprimir_investimentos_alfabeticamente_pelo_tipo(FILE *investimento)
{
    struct dados_investimento algum;
    struct dados_investimento *investimentos = NULL;
    int contador = 0;

    //ARMAZENAR TODOS OS INVESTIMENTO NAO VAZIOS NO PONTEIRO:

    fseek(investimento,0,SEEK_SET);

    while(fread(&algum,sizeof(struct dados_investimento),1,investimento) == 1){

        if(strcmp(algum.codigo_investimento,"\0") != 0)
        {
            investimentos = realloc(investimentos, (contador + 1) * sizeof(struct dados_investimento));
            investimentos[contador] = algum;
            contador++;
        }

    }

    //ORDENAR ESSE PONTEIRO:

    for(int i=0 ; i<contador ; i++)
    {
        for(int j=i ; j<contador ; j++)
        {
            if(strcmp(investimentos[i].tipo, investimentos[j].tipo) > 0)
            {
                struct dados_investimento aux = investimentos[i];
                investimentos[i] = investimentos[j];
                investimentos[j] = aux;
            }
        }
    }

    //IMPRIMIR O PONTEIRO ORDENADO:

    for(int i=0 ; i<contador ; i++)
    {
        {
            printf("-----------------------------------\n");
            printf("Tipo - %s\n\n", investimentos[i].tipo);
            printf("- Codigo do investimento - %s\n",investimentos[i].codigo_investimento);
            printf("- Codigo do investidor - %d\n",investimentos[i].codigo_investidor);
            printf("- Valor: R$ %.2f\n", investimentos[i].valor);
            printf("- Descricao: %s\n", investimentos[i].descricao);
            printf("- Prazo: %d dias\n", investimentos[i].prazo);
            printf("- Rentabilidade Anual: %.2f %%\n", investimentos[i].rentabilidade_anual);
            printf("- Data de Aplicacao: %02d/%02d/%04d\n", investimentos[i].data_aplicacao.dia,
                    investimentos[i].data_aplicacao.mes, investimentos[i].data_aplicacao.ano);
            printf("- Valorizacao ate hoje: %.2f\n",rendimento_investimento(investimentos[i]));
            printf("-----------------------------------\n");
        }
    }

    free(investimentos);
}

float patrimonio_investidor(int codigo_investidor, FILE *investimento)
{
    float patrimonio = 0;
    struct dados_investimento investimentos;

    fseek(investimento,0,SEEK_SET);

    while(fread(&investimentos, sizeof(struct dados_investimento), 1, investimento) == 1)
    {
        if(codigo_investidor == investimentos.codigo_investidor && investimentos.codigo_investimento[0] != '\0')
            patrimonio = patrimonio + rendimento_investimento(investimentos);
    }

    return patrimonio;
}