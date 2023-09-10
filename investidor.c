#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "investidor.h"
#include "investimento.h"

#define TAMANHO_DOS_NOMES 255
#define TAMANHO_DOS_ENDERECOS 255
#define TAMANHO_DO_CPF 255
#define TAMANHO_DO_CODIGO 255
#define TAMANHO_DA_DATA 255
#define TAMANHO_SALARIO 255
#define TAMANHO_CHAR 255

void limpar_buffer()
{
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }

}

void inserir_novo_investidor(FILE *f,FILE *g)
{
        struct dados_investidor investidor;
        int nome_cpf_inseridos = 0;

            int nome_valido,cpf_valido;
            int cpf_existente = 0;

            do
            {
                char nome[TAMANHO_DOS_NOMES];
                nome_valido = 0;

                printf("Digite o nome do investidor:\n");
                fgets(nome,TAMANHO_DOS_NOMES, stdin);
                nome[strcspn(nome, "\n")] = '\0';

                for (int i = 0; i < strlen(nome); i++)
                {
                    if (i == 0 || (nome[i - 1] == ' ' && nome[i] != ' '))
                    {
                        nome[i] = toupper(nome[i]);
                    }
                    else
                    {
                        nome[i] = tolower(nome[i]);
                    }
                }

                if(nome[0] == '\0')
                    printf("O nome do investidor eh obrigatorio!\n");
                else
                {
                    strcpy(investidor.nome, nome);
                    nome_valido = 1;
                }

            }while(nome_valido == 0);
            
            char cpf[TAMANHO_DO_CPF];

            do
            {
                int cpf_existente = 0;
                int cpf_contem_letra = 0;
                cpf_valido = 0;

                printf("Digite o CPF do investidor (Sem pontos):\n");
                fgets(cpf,TAMANHO_DO_CPF, stdin); //11 digitos + 1 caractere nulo
                cpf[strcspn(cpf, "\n")] = '\0';

                //VERIFICAR SE TEM LETRA NO CPF:
                for(int i=0 ; cpf[i] != 0 ; i++)
                {
                    if(isdigit(cpf[i]) == 0)
                    {
                        cpf_contem_letra = 1;
                        break;
                    }
                }

                if(cpf[0] == '\0')
                {
                    printf("O CPF do investidor eh obrigatorio!\n");
                }
                else if(cpf_contem_letra == 1)
                {
                    printf("O CPF nao pode conter letras!\n");
                }
                else if(strlen(cpf) != 11)
                {
                    printf("O CPF deve conter 11 digitos!\n");
                }
                else
                {
                    cpf_valido = 1;
                }

            }while(cpf_valido == 0);

            //LOOP PARA LER TODOS OS STRUCTS DO ARQUIVO.BIN:
            fseek(f,0,SEEK_SET); //COLOCAR O PONTEIRO NO INÍCIO DO ARQUIVO

            do
            {
                struct dados_investidor alguem;

                fread(&alguem,sizeof(struct dados_investidor),1,f);

                if (strcmp(cpf, alguem.cpf) == 0)
                {
                            char resposta_usuario[2];

                            printf("\nJa existe investidor com esse CPF!\n");
                            cpf_existente = 1;
                            break;   
                }

            }while(!feof(f));

                if(cpf_existente == 0)
                {
                    strcpy(investidor.cpf, cpf);
                    nome_cpf_inseridos = 1;
                }

            ////////////////////////////////////////////////////////////////////////////////////////////////////////

            if(nome_cpf_inseridos == 1)
            {
                // INSERIR O ENDEREÇO DO INVESTIDOR:

                char endereco[TAMANHO_DOS_ENDERECOS];
                int tamanho_endereco;
                int usuario_deletado_encontrado;
                
                printf("Digite o endereco do investidor:\n");
                fgets(endereco, TAMANHO_DOS_ENDERECOS, stdin);
                endereco[strcspn(endereco, "\n")] = '\0';

                tamanho_endereco = strlen(endereco);

                if (endereco[0] != '\0')
                {
                    for (int i = 0; i < tamanho_endereco; i++)
                    {
                        if (i == 0 || (endereco[i - 1] == ' ' && endereco[i] != ' '))
                        {
                            endereco[i] = toupper(endereco[i]);
                        }
                        else
                        {
                            endereco[i] = tolower(endereco[i]);
                        }
                    }

                    strcpy(investidor.endereco, endereco);

                }
                ////////////////////////////////////////////////////////////////////////////////////////////

                // INSERIR DATA DE NASCIMENTO DO INVESTIDOR:

                char data[TAMANHO_DA_DATA];
                int data_inserida;
                
                do
                {
                    char dia[3],mes[3],ano[5];
                    data_inserida = 0;

                    printf("Preencha data de nascimentos do investidor (dd/mm/yyyy):\n");

                    printf("Dia: ");
                    fgets(dia,3,stdin);
                    dia[strcspn(dia,"\n")]='\0';

                    limpar_buffer();

                    printf("Mes: ");
                    fgets(mes,3,stdin);
                    mes[strcspn(mes,"\n")]='\0';

                    limpar_buffer();

                    printf("Ano: ");
                    fgets(ano,5,stdin);
                    ano[strcspn(ano,"\n")]='\0';

                    sprintf(data,"%02d/%02d/%04d",atoi(dia),atoi(mes),atoi(ano));
                
                    if(strlen(dia) == 0 || strlen(mes) == 0 || strlen(ano) == 0)
                    {
                        printf("E obrigatorio preencher completamente a data de nascimento!\n");
                    }
                    else if(strlen(data) != 10)
                    {
                        printf("A data de nascimento eh invalida!\n");
                    }
                    else
                    {
                        strcpy(investidor.data_nascimento,data);
                        data_inserida = 1;
                        limpar_buffer();
                    }

                }while(data_inserida == 0);
                ////////////////////////////////////////////////////////////////////////////////////////////

                //INSERIR O SALARIO DO INVESTIDOR:

                char salario[TAMANHO_SALARIO];
                int salario_inserido = 0;

                do
                {
                    salario_inserido = 0;

                    printf("Digite o salario do investidor (R$):\n");
                    fgets(salario,TAMANHO_SALARIO, stdin);
                    salario[strcspn(salario, "\n")] = '\0';

                    //TROCAR O A VIRGULA POR PONTO:
                    salario[strcspn(salario,",")] = '.';

                    if(salario[0] == '\0')
                    printf("O salario do investidor eh obrigatorio!\n");
                    else
                    {
                    investidor.salario = atof(salario);
                    investidor.acumulador_codigo_investimento = 0;
                    salario_inserido = 1;

                    //PROCESSO REFERENTE AO CODIGO DO INVESTIDOR://///////////////////////////////////////////////

                    //LER O CÓDIGO.BIN
                    int acumulador;

                    fseek(g,0,SEEK_SET);
                    fread(&acumulador, sizeof(int),1,g);
                    acumulador = acumulador + 1;

                    //ESCREVER NA STRUCT
                    investidor.codigo = acumulador;

                    //ESCREVER NO CÓDIGO.BIN O NOVO VALOR DO ACUMULADOR
                    fseek(g,0,SEEK_SET);
                    fwrite(&acumulador, sizeof(int),1,g);
                    fflush(g);
                    
                    /////////////////////////////////////////////////////////////////////////////////////////////
                    }

                }while(salario_inserido == 0);

                //ENCONTRAR UM INVESTIDOR DELETADO NO ARQUIVO P/ SOBRESCREVER:

                    usuario_deletado_encontrado = 0;

                    fseek(f,0,SEEK_SET);

                    while(!feof(f))
                    {
                        struct dados_investidor alguem;

                        fread(&alguem,sizeof(struct dados_investidor),1,f);

                        if(strcmp(alguem.nome,"\0")==0)
                        {
                            fseek(f,-sizeof(struct dados_investidor),SEEK_CUR);
                            fwrite(&investidor, sizeof(struct dados_investidor),1,f);

                            usuario_deletado_encontrado = 1;
                            break;
                        }
                    }
                /////////////////////////////////////////////////////////////////

                //ESCREVER NO FINAL DO ARQUIVO, CASO NÃO ENCONTRE USUÁRIO DELETADO:

                    if(usuario_deletado_encontrado == 0)
                    {
                        fseek(f,0,SEEK_END);
                        fwrite(&investidor, sizeof(struct dados_investidor),1,f);
                    }

                ////////////////////////////////////////////////////////////////
           }
}

void alterar_nome(FILE *f,char *novo_nome)
{
    char nome[TAMANHO_DOS_NOMES];
    struct dados_investidor alguem;
    int nome_inserido;

                    do
                    {
                    nome_inserido = 0;

                    printf("Digite o novo nome do investidor:\n");
                    fgets(nome,TAMANHO_DOS_NOMES, stdin);
                    nome[strcspn(nome, "\n")] = '\0';

                    int tamanho_nome = strlen(nome);

                    for (int i = 0; i < tamanho_nome; i++)
                        {
                            if (i == 0 || (nome[i - 1] == ' ' && nome[i] != ' '))
                            {
                                nome[i] = toupper(nome[i]);
                            }
                            else
                            {
                                nome[i] = tolower(nome[i]);
                            }
                        }

                    if(nome[0] == '\0')
                    {
                        printf("O nome do investidor eh obrigatorio!\n");
                    }
                    else
                    {
                       //ESCREVER NA STRUCT
                        strcpy(novo_nome, nome);
                        nome_inserido = 1;
                    }

                    } while(nome_inserido == 0);
}

void alterar_cpf(FILE *f,char* novo_cpf)
{
                //INSERIR O CPF DO INVESTIDOR:

                int cpf_existente;
                int cpf_inserido;
                int cpf_contem_letra = 0;
                struct dados_investidor alguem;
                char cpf[TAMANHO_DO_CPF];

                cpf_existente = 0;
                cpf_inserido = 0;
                cpf_contem_letra = 0;

                printf("Digite o novo CPF do investidor (Sem pontos):\n");
                fgets(cpf,TAMANHO_DO_CPF, stdin); //11 digitos + 1 caractere nulo
                cpf[strcspn(cpf, "\n")] = '\0';

                //VERIFICAR SE TEM LETRA NO CPF:
                for(int i=0 ; cpf[i] != 0 ; i++)
                {
                    if(isdigit(cpf[i]) == 0)
                    {
                        cpf_contem_letra = 1;
                        break;
                    }
                }

                if(cpf[0] == '\0')
                {
                    printf("O CPF do investidor eh obrigatorio!\n");
                }
                else if(cpf_contem_letra == 1)
                {
                    printf("O CPF nao pode conter letras!\n");
                }
                else if(strlen(cpf) != 11)
                {
                    printf("O CPF deve conter 11 digitos!\n");
                }
                else
                {
                    //LOOP PARA LER TODOS OS STRUCTS DO ARQUIVO.BIN:
                    fseek(f,0,SEEK_SET); //COLOCAR O PONTEIRO NO INÍCIO DO ARQUIVO

                    do
                    {
                        fread(&alguem,sizeof(struct dados_investidor),1,f);
                        
                        if (strcmp(cpf, alguem.cpf) == 0)
                        {
                            printf("\nJa existe investidor com esse CPF!\n");
                            cpf_existente = 1;
                            break;
                        }

                    }while(!feof(f));
                }

                if (cpf[0] != '\0' && strlen(cpf) == TAMANHO_DO_CPF-1 && cpf_existente == 0 && cpf_contem_letra == 0)
                {
                    strcpy(novo_cpf, cpf);
                    cpf_inserido = 1;
                }
}

void alterar_endereco(FILE *f,char *novo_endereco)
{

    char endereco[TAMANHO_DOS_ENDERECOS];

                int tamanho_endereco;
                
                printf("Digite o novo endereco do investidor:\n");
                fgets(endereco, TAMANHO_DOS_ENDERECOS, stdin);
                endereco[strcspn(endereco, "\n")] = '\0';

                tamanho_endereco = strlen(endereco);

                if (endereco[0] != '\0')
                {
                    for (int i = 0; i < tamanho_endereco; i++)
                    {
                        if (i == 0 || (endereco[i - 1] == ' ' && endereco[i] != ' '))
                        {
                            endereco[i] = toupper(endereco[i]);
                        }
                        else
                        {
                            endereco[i] = tolower(endereco[i]);
                        }
                    }

                    strcpy(novo_endereco, endereco);
                }

}

void alterar_data_nascimento(FILE *f, char *nova_data)
{
                char data[TAMANHO_DA_DATA];
                int data_inserida;
                
                do
                {
                    char dia[3],mes[3],ano[5];
                    data_inserida = 0;

                    printf("Preencha de nascimentos do investidor (dd/mm/yyyy):\n");

                    printf("Dia: ");
                    fgets(dia,3,stdin);
                    dia[strcspn(dia,"\n")]='\0';

                    limpar_buffer();

                    printf("Mes: ");
                    fgets(mes,3,stdin);
                    mes[strcspn(mes,"\n")]='\0';

                    limpar_buffer();

                    printf("Ano: ");
                    fgets(ano,5,stdin);
                    ano[strcspn(ano,"\n")]='\0';

                    sprintf(data,"%02d/%02d/%04d",atoi(dia),atoi(mes),atoi(ano));
                
                    if(strlen(dia) == 0 || strlen(mes) == 0 || strlen(ano) == 0)
                    {
                        printf("E obrigatorio preencher completamente a data de nascimento!\n");
                    }
                    else if(strlen(data) != 10)
                    {
                        printf("A data de nascimento eh invalida!\n");
                    }
                    else
                    {
                        strcpy(nova_data,data);
                        data_inserida = 1;
                    }

                }while(data_inserida == 0);
}

void alterar_investidor_existente(FILE *f)
{

struct dados_investidor investidor;
int investidor_alterado;
int codigo_existente;
char resposta_usuario[2];
int sair;

do{
    char codigo[TAMANHO_DO_CODIGO];
    investidor_alterado = 0;
    codigo_existente = 0;
    sair = 0;

    printf("Digite o codigo do investidor cujo os dados deseja alterar:\n");
    fgets(codigo, TAMANHO_DO_CODIGO, stdin);
    codigo[strcspn(codigo,"\n")] = '\0';

    if(codigo[0] == '\0')
    {
        printf("Voce precisa digitar algo!\n");
    }
    else if(atoi(codigo) == 0)
    {
        printf("\nNao existe investidor com esse codigo!\n");
        sair = 1;
    }
    else
    {
        //LOOP PARA LER TODOS OS STRUCTS DO ARQUIVO.BIN:

        fseek(f,0,SEEK_SET); //COLOCAR O PONTEIRO NO INÍCIO DO ARQUIVO

        do
        {
            fread(&investidor,sizeof(struct dados_investidor),1,f);

            char codigo_algum_investidor[TAMANHO_CHAR];
            sprintf(codigo_algum_investidor, "%d", investidor.codigo);
                        
            if (strcmp(codigo,codigo_algum_investidor)==0)
            {
                printf("Quais dados voce deseja alterar do investidor?\n\n");
                do
                {
                    printf("- Nome (Digite 1)\n");
                    printf("- CPF (Digite 2)\n");
                    printf("- Endereco (Digite 3)\n");
                    printf("- Data de nascimento (Digite 4)\n");
                    printf("- Salario (Digite 5)\n");
                    printf("- Sair (Digite 6)\n\n");

                    fgets(resposta_usuario, 2, stdin);
                    resposta_usuario[strcspn(resposta_usuario,"\n")] = '\0';

                    limpar_buffer();

                    if(resposta_usuario[0] == '1')
                        alterar_nome(f,investidor.nome);
                    if(resposta_usuario[0] == '2')
                        alterar_cpf(f,investidor.cpf);
                    if(resposta_usuario[0] == '3')
                        alterar_endereco(f,investidor.endereco);
                    if(resposta_usuario[0] == '4')
                        alterar_data_nascimento(f,investidor.data_nascimento);
                    if(resposta_usuario[0] == '5')
                    {
                        char salario[TAMANHO_SALARIO];
                        int salario_inserido = 0;

                        do
                        {
                        salario_inserido = 0;

                        printf("Digite o salario do investidor (R$):\n");
                        fgets(salario,TAMANHO_SALARIO, stdin);
                        salario[strcspn(salario, "\n")] = '\0';
                        
                        //TROCAR O A VIRGULA POR PONTO:
                        salario[strcspn(salario,",")] = '.';

                        if(salario[0] == '\0')
                        printf("O salario do investidor eh obrigatorio!\n");
                        else
                        {
                        investidor.salario = atof(salario);
                        salario_inserido = 1;
                        }

                        }while(salario_inserido == 0);
                    }

                    if(resposta_usuario[0] == '6')
                    {
                        fseek(f,0,SEEK_SET);

                        do{ //REPOSICIONAR O PONTEIRO
                        
                            struct dados_investidor alguem;

                            fread(&alguem,sizeof(struct dados_investidor),1,f);

                            sprintf(codigo_algum_investidor, "%d", alguem.codigo);

                            if(strcmp(codigo,codigo_algum_investidor)==0)
                            {
                                fseek(f,-sizeof(struct dados_investidor), SEEK_CUR); //COLOCAR O PONTEIRO UMA POSIÇÃO ANTES DA POSIÇÃO QUE DESEJO SOBRESCREVER
                                fwrite(&investidor, sizeof(struct dados_investidor),1,f);
                                investidor_alterado = 1;
                                break;
                            }

                        }while(!feof(f));
                    }

                }while(!(resposta_usuario[0] == '6'));

                    codigo_existente = 1;
                    break;
            }

        }while(!feof(f));

        if(codigo_existente == 0 && codigo[0] != '\0')
        {
            printf("\nNao existe investidor com esse codigo!\n");
            sair = 1;
        }
    }

}while(investidor_alterado == 0 && sair == 0);

}

void listar_investidores(FILE *f, FILE *investimento)
{
    struct dados_investidor investidor;

    // Reposiciona o ponteiro no início do arquivo
    fseek(f, 0, SEEK_SET);

    // Loop para ler todos os registros do arquivo
    while (fread(&investidor, sizeof(struct dados_investidor), 1, f) == 1)
    {
        if(strcmp(investidor.nome,"\0") != 0)
        {
        printf("-------------------------------------\n");
        printf("%s\n\n", investidor.nome);
        printf("- Codigo: %d\n", investidor.codigo);
        printf("- CPF: %s\n", investidor.cpf);
        printf("- Endereco: %s\n", investidor.endereco);
        printf("- Data de Nascimento: %s\n", investidor.data_nascimento);
        printf("- Salario: R$ %.2f\n", investidor.salario);
        printf("- Patrimonio: R$ %.2f\n", patrimonio_investidor(investidor.codigo,investimento));
        printf("-------------------------------------\n");
        }
    }
}

void excluir_investidor(FILE *f, FILE *investimento)
{
    char codigo[TAMANHO_DO_CODIGO];
    int codigo_existente = 0;

    printf("Digite o codigo do investidor que deseja deletar:\n");
    fgets(codigo, TAMANHO_DO_CODIGO, stdin);
    codigo[strcspn(codigo, "\n")] = '\0';

    if (codigo[0] == '\0')
    {
        printf("Voce precisa digitar algo!\n");
        return;
    }
    else if (atoi(codigo) == 0)
    {
        printf("\nNao existe investidor com esse codigo!\n");
        return;
    }

    // Leitura do arquivo de investidores
    fseek(f, 0, SEEK_SET);
    struct dados_investidor alguem;
    while (fread(&alguem, sizeof(struct dados_investidor), 1, f) == 1)
    {
        if (alguem.codigo == atoi(codigo))
        {
            // Colocar vazio nos dados do investidor
            strcpy(alguem.nome, "");
            strcpy(alguem.cpf, "");
            alguem.codigo = 0;
            fseek(f, -sizeof(struct dados_investidor), SEEK_CUR);
            fwrite(&alguem, sizeof(struct dados_investidor), 1, f);

            // Colocar vazio nos dados de todos os investimentos associados ao investidor
            fseek(investimento, 0, SEEK_SET);
            struct dados_investimento investimentos;
            while (fread(&investimentos, sizeof(struct dados_investimento), 1, investimento) == 1)
            {
                if (investimentos.codigo_investidor == atoi(codigo))
                {
                    strcpy(investimentos.codigo_investimento, "");
                    fseek(investimento, -sizeof(struct dados_investimento), SEEK_CUR);
                    fwrite(&investimentos, sizeof(struct dados_investimento), 1, investimento);
                }
            }

            codigo_existente = 1;
            break;
        }
    }

    if (codigo_existente == 0)
    {
        printf("\nNao existe investidor com esse codigo!\n");
    }
}


void imprimir_investidor_pelo_codigo(FILE *f,FILE *investimento)
{
    struct dados_investidor investidor;
    char codigo[TAMANHO_DO_CODIGO];

    int codigo_existente;
    int investidor_imprimido;
    int continuar_procurando;

    do
    {
        codigo_existente = 0;
        investidor_imprimido = 0;
        continuar_procurando = 1;

        printf("Digite o codigo do investidor cujos os dados deseja imprimir:\n");
        fgets(codigo, TAMANHO_DO_CODIGO,stdin);
        codigo[strcspn(codigo,"\n")] = '\0';

        if(codigo[0] == '\0')
            printf("Voce precisa digitar algo!\n");
        else if(atoi(codigo) == 0)
        {
        printf("\nNao existe investidor com esse codigo!\n");
        continuar_procurando = 0;
        }
        else
        {
            fseek(f,0,SEEK_SET);

            do
            {
                fread(&investidor,sizeof(struct dados_investidor),1,f);

                char codigo_str[TAMANHO_CHAR];
                sprintf(codigo_str, "%d", investidor.codigo);

                if(strcmp(codigo,codigo_str)==0)
                {
                    printf("\n-----------------------------------------\n");
                    printf("%s | Codigo: %d\n", investidor.nome,investidor.codigo);
                    printf("- CPF: %s\n",investidor.cpf);
                    printf("- Endereco: %s\n",investidor.endereco);
                    printf("- Data de nascimento: %s\n",investidor.data_nascimento);
                    printf("- Salario: R$ %.2f\n",investidor.salario);
                    printf("- Patrimonio: R$ %.2f\n", patrimonio_investidor(investidor.codigo,investimento));
                    printf("-----------------------------------------\n");

                    codigo_existente = 1;
                    investidor_imprimido = 1;
                    break;
                }

            }while(!feof(f));
        }

        if(codigo[0] != '\0' && codigo_existente == 0 && atoi(codigo) != 0)
        {
            printf("\nNao existe investidor com esse codigo!s\n");
            continuar_procurando = 0;
        }
        
    }while(investidor_imprimido == 0 && continuar_procurando == 1);
}

void imprimir_investidores_ordemcrescente_patrimonio(FILE *f,FILE *investimento)
{
    struct dados_investidor alguem;
    struct nome_patrimonio *investidores = NULL;
    int contador = 0;

    //ARMAZENAR NOME E PATRIMÔNIO DE TODOS OS INVESTIDORES NO PONTEIRO:
    
    fseek(f,0,SEEK_SET);

    while(fread(&alguem,sizeof(struct dados_investidor),1,f) == 1)
    {
        if(strcmp(alguem.nome,"\0") != 0)
        {
            investidores = realloc(investidores, (contador + 1) * sizeof(struct nome_patrimonio));
            strcpy(investidores[contador].nome_investidor,alguem.nome);
            investidores[contador].patrimonio = patrimonio_investidor(alguem.codigo,investimento);
            contador++;
        }
    }

    //ORDENAR ESSE PONTEIRO:

    for(int i=0 ; i<contador ; i++)
    {
        for(int j=i ; j<contador ; j++)
        {
            if(investidores[i].patrimonio > investidores[j].patrimonio)
            {
                struct nome_patrimonio aux = investidores[i];
                investidores[i] = investidores[j];
                investidores[j] = aux;
            }
        }
    }

    //IMPRIMIR O PONTEIRO ORDENADO:

    for(int i=0 ; i<contador ; i++)
    {
        {
            printf("%s | Patrimonio: R$ %.2f\n\n",investidores[i].nome_investidor,investidores[i].patrimonio);
        }
    }
    
    free(investidores);
}

void imprimir_investidores_pelo_tipo(FILE *f,FILE *investimento)
{
    struct dados_investimento algum;
    struct dados_investidor investidor;
    char tipo[TAMANHO_CHAR];

    int tipo_existente = 0;
    int investidores_imprimidos = 0;
    int continuar_procurando = 1;

    do
    {

        tipo_existente = 0;
        investidores_imprimidos = 0;
        continuar_procurando = 1;

        printf("Digite o tipo do investimento:\n");
        fgets(tipo, TAMANHO_CHAR, stdin);
        tipo[strcspn(tipo, "\n")] = '\0';

        for (int i = 0; i < strlen(tipo); i++)
        {
            tipo[i] = toupper(tipo[i]);
        }

        if(tipo[0] == '\0')
        {
            printf("Voce precisa digitar algo!\n");
        }
        else
        {
            fseek(f, 0, SEEK_SET);

            while (fread(&investidor, sizeof(struct dados_investidor), 1, f) == 1)
            {
                fseek(investimento,0,SEEK_SET);

                while(fread(&algum, sizeof(struct dados_investimento), 1, investimento) == 1)
                {
                    if(strcmp(tipo,algum.tipo)==0 && (algum.codigo_investidor == investidor.codigo) && (algum.codigo_investimento[0] != '\0'))
                    {   
                        printf("-------------------------------------\n");
                        printf("%s\n\n", investidor.nome);
                        printf("- Codigo: %d\n", investidor.codigo);
                        printf("- CPF: %s\n", investidor.cpf);
                        printf("- Endereco: %s\n", investidor.endereco);
                        printf("- Data de Nascimento: %s\n", investidor.data_nascimento);
                        printf("- Salario: R$ %.2f\n", investidor.salario);
                        printf("- Patrimonio: R$ %.2f\n", patrimonio_investidor(investidor.codigo,investimento));
                        printf("-------------------------------------\n");
                        tipo_existente = 1;
                        investidores_imprimidos = 1;
                        break;
                    }
                }
            } 

            if (tipo_existente == 0)
            {
                printf("\nNao existe investidores com esse tipo de investimento!\n");
                continuar_procurando = 0;
            }
        }

    }while(investidores_imprimidos == 0 && continuar_procurando == 1);
}
