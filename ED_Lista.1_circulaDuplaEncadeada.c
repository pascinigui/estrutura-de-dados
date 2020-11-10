#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

// Structs
struct tProduto {
	int codigo; 
	char descricao[30];
};

struct tNo {
	struct tProduto dados;
	struct tNo *prox;
	struct tNo *ant;
};

struct tDescritor {
	struct tNo *ini, *fim;
	int qtd;
};
//

// Menu
int menu(void) {
   int op;
    
    printf("Menu de Execu��o...\n\n");
	printf("\t1. Inclus�o de um novo Produto\n");
    printf("\t2. Listagem dos Produtos dispon�veis\n");
    printf("\t3. Consulta de informa��es sobre o Produto\n");
    printf("\t4. Altera��o dos dados dos Produtos\n");
    printf("\t5. Exclus�o dos Produtos do Estoque\n\n");
    printf("\t0. Sair do Menu\n\n");
    printf("Escolha o que deseja fazer: ");
    scanf("%d", &op);
    return op;
}
//

// Inicializa��o da Lista
void inicializar (struct tDescritor *lista) {
	(*lista).ini = (*lista).fim = NULL;
	(*lista).qtd = 0;
}
//

// Inclus�o no La�o em formato Circular
void incluir(struct tDescritor *lista, struct tNo *novo) {
struct tNo *p = (*lista).ini;
    
    if ((*lista).ini == NULL) { // �nico
        novo->ant = novo->prox = novo;
        (*lista).ini = (*lista).fim = novo;
    }
    else { // Inicio
        if (novo->dados.codigo < (*lista).ini->dados.codigo) { 
        	
        	novo->prox = (*lista).ini;
			novo->prox->ant = novo;
			novo->ant = novo;
			(*lista).ini = novo;
	
        }else { // Fim
            if (novo->dados.codigo > (*lista).fim->dados.codigo) {
                
				novo->ant = (*lista).fim;
				novo->ant->prox = novo;
				novo->prox = (*lista).ini;
				(*lista).fim = novo;
				(*lista).ini->ant = novo;
				
            }else{ // Meio

                while (p->dados.codigo < novo->dados.codigo)
                    p = p->prox;
                    
                novo->ant = p->ant;
                novo->prox = p;
                novo->prox->ant = novo;
                novo->ant->prox = novo;
            }
        }
    }
    (*lista).qtd++;
}
//

// Exclus�o 
void excluir(struct tDescritor *lista, struct tNo *vitima) {
	if ((*lista).ini == vitima)
		(*lista).ini = vitima->prox;
		
	if ((*lista).fim == vitima)
		(*lista).fim = vitima->ant;
		
	if (vitima->ant != NULL)
		vitima->ant->prox = vitima->prox;
		
	if (vitima->prox != NULL)
		vitima->prox->ant = vitima->ant;
		
	free(vitima);
	(*lista).qtd--;
}
//

// Void de Listagem.
void listagemProdutos (struct tDescritor lista) {
	
	struct tNo *p = lista.ini;
	
	if (p != NULL) {
		do {
			printf("C�digo do Produto: %d\n", p->dados.codigo);
			printf("Descri��o do Produto: %s\n\n", p->dados.descricao); 
			p = p->prox;
		}while(p != (lista).ini);
	}
	printf("\n\n\nPressione qualquer tecla para sair...");
	getche();
	system("cls");
}
// 

// Consulta no La�o
struct tNo *consultar(struct tDescritor lista, int cod) {
	struct tNo *p = lista.ini;
	
	do {
		if (p->dados.codigo == cod)
			return p;
		p = p->prox;
	}while (p->dados.codigo <= cod && p != (lista).ini);
	return NULL;
}
//

// Limpeza da mem�ria Alocada.
void limpaAlocacao (struct tDescritor *lista) {
    struct tNo *p = lista->ini, *q;
    while (p != NULL) {
    	q = p;
    	p = p->prox;
    	free(q);
	}
	lista=NULL;
}
//

// Main
int main(void) {
	setlocale(LC_ALL, "Portuguese");

	struct tDescritor lista;
	struct tNo *p;
	int opcao, codigo;
		
	inicializar(&lista);
	do {
        opcao = menu();
        system("cls");
        switch (opcao) {
            case 1: 
                printf("Inclus�o de Produtos ao Estoque...\n\n");
			    p = (struct tNo *)malloc(sizeof(struct tNo));

				printf("Informe qual o c�digo do Produto: ");
                scanf("%d", &(p->dados.codigo));
     
	            printf("Informe a descri��o do Produto: ");
                fflush(stdin);
				gets(p->dados.descricao);
								
	            incluir(&lista, p);
                break;
            case 2: 
                printf("Listagem de Produtos ao Estoque...\n\n");
            	listagemProdutos(lista);
				break;
            case 3: 
                printf("Consulta de Produtos ao Estoque...\n\n");
            	printf("Informe o c�digo que deseja Consultar: ");
                scanf("%d", &codigo);
            
                p = consultar(lista, codigo);
                
                if (p == NULL)
                    printf("Produto n�o encontrado!\n");
                else
                    printf("Descri��o do Produto: %s\n", p->dados.descricao);
                printf("\n\n\nPressione qualquer tecla para voltar ao Menu...");
				getche();
				break;
            case 4: 
				printf("Altera��o de Produtos...\n\n");
                printf("Informe o c�digo que deseja Consultar: ");
                scanf("%d", &codigo);
                
				p = consultar(lista, codigo);
                
                if (p == NULL){
                    printf("Produto n�o encontrado!\n");
                }else{
                    printf("Descri��o do Produto: %s\n", p->dados.descricao);
                    printf("Digite a nova descricao: ");
                    fflush(stdin);
                    gets(p->dados.descricao);
				}
	            break;
			case 5: 
                printf("Exclus�o de Produtos....\n\n");
                printf("Informe o c�digo do Produto que deseja excluir: ");
                scanf("%d", &codigo);

				p = consultar(lista, codigo);
                
                if (p == NULL) {
                    printf("Produto n�o encontrado!\n");
				}else{
					excluir(&lista, p);
                    printf("Excluido com sucesso!!!\n");		
					printf("\nPressione qualquer tecla para prosseguir... \n\n\n");
					getche();
				}
				break;
		}
        system("cls");
    }while (opcao != 0);
	limpaAlocacao(&lista);
	return 0;
}
//	
