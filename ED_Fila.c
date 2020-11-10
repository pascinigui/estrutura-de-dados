#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define LIM 5
#define FALSE 0
#define TRUE 1
 
#define FIM 0
#define INSERIR 1
#define RETIRAR 2
#define LISTAR 3
   
int obterOpcao(void)
{
    int opcao;
    system("cls");
    printf("Menu de Op��es!\n");
    printf("Op��o %2d: - FIM\n", FIM);
    printf("Op��o %2d: - Inserir item na Fila\n", INSERIR);
    printf("Op��o %2d: - Retirar item da Fila\n", RETIRAR);
    printf("Op��o %2d: - Listar conte�do na Fila\n", LISTAR);
    printf("\nInforma a op��o desejada: ");
    scanf("%d", &opcao);
    return opcao;
}
   
int vazia(int inicio)
{
    return inicio == -1;
}
   
int esgotada(int inicio, int fim)
{
    if (vazia(inicio)) return FALSE;
    return (fim + 1) % LIM == inicio;
}
   
int inserir(int valor, int *pInicio, int *pFim, int fila[])
{
    if (esgotada(*pInicio, *pFim)) return FALSE;
    if (vazia(*pInicio)) *pInicio = *pFim = 0;
    else *pFim = (*pFim + 1) % LIM;
    fila[*pFim] = valor;
    return TRUE;
}
   
int retirar(int *pValor, int *pInicio, int *pFim, int fila[])
{
    if (vazia(*pInicio)) return FALSE;
    *pValor = fila[*pInicio];
    if (*pInicio == *pFim) *pInicio = -1; // lista vazia apos retirada
    else *pInicio = (*pInicio + 1) % LIM;
    return TRUE;
}
   
int listar(int inicio, int fim, int fila[])
{
    int i;
    if (vazia(inicio)) return FALSE;
    printf("< ");
    for (i = inicio; i != fim; i = (i + 1) % LIM)
        printf("%d ", fila[i]);
    printf("%d ", fila[fim]);
    printf("<\n");
    return TRUE;
}
   
int main(void)
{
	setlocale(LC_ALL, "Portuguese");
    int inicio, fim, fila[LIM], opcao, valor;
    inicio = -1; // fila vazia
    while ((opcao = obterOpcao()) != FIM)
    {
        switch (opcao)
        {
        case INSERIR:
            printf("Valor a ser inserido na fila: ");
            scanf("%d", &valor);
            if (inserir(valor, &inicio, &fim, fila))
                printf("Operacao concluida com sucesso\n");
            else printf("Operacao frustrada - fila esgotada...\n");
            break;
        case RETIRAR:
            if (retirar(&valor, &inicio, &fim , fila))
                printf("Valor %d retirado da fila\n", valor);
            else printf("Operacao frustrada - fila vazia...\n");
            break;
        case LISTAR:
            if (listar(inicio, fim, fila)) putchar('\n');
            else printf("Operacao frustrada - fila vazia...\n");
            break;
            Sleep(3000);
        }
        putchar('\n');
    }
    return 0;
}
