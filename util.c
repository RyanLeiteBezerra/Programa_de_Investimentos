#include <stdio.h>

void iniciar_arquivos(FILE **investidor,FILE **codigo,FILE **investimento)
{
////////////////////////////////////////////////////////////////////////////////
    //INICIAR O INVESTIDOR.BIN:
    *investidor = fopen("investidor.bin","rb+");
    if (*investidor == NULL) 
    {
        printf("Arquivo investidor.bin nao existe!\n");
        *investidor = fopen("investidor.bin", "wb+");
        if (*investidor == NULL) 
        {
            printf("Não conseguiu criar o arquivo investidor.bin!\n");
            return;
        }
    }

    //INICIAR O CÓDIGO.BIN:
    *codigo = fopen("codigos.bin","rb+");
    if (*codigo == NULL) 
    {
        printf("Arquivo codigos.bin nao existe!\n");
        *codigo = fopen("codigos.bin", "wb+");

        if (*codigo == NULL) 
        {
            printf("Não conseguiu criar o arquivo codigos.bin!\n");
            return;
        }
        else 
        {
            int acumulador = 0;
            fwrite(&acumulador, sizeof(int), 1, *codigo);
        }
    }

    //INICIAR O INVESTIMENTO.BIN:
    *investimento = fopen("investimento.bin","rb+");
    if (*investimento == NULL) {
        printf("Arquivo investimento.bin nao existe!\n");
        *investimento = fopen("investimento.bin", "wb+");
        if (*investimento == NULL) {
            printf("Não conseguiu criar o arquivo investimento.bin!\n");
            return;
        }
    }
    ///////////////////////////////////////////////////////////////////////////////////////
}

void fechar_arquivos(FILE **investidor,FILE **codigo,FILE **investimento)
{
    fclose(*codigo);
    fclose(*investidor);
    fclose(*investimento);
}