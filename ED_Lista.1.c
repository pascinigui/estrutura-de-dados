#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

struct tProduto {
	int codigoProduto;
	char descProduto[30];
	float valor;
};

struct tNo {
	struct tProduto dado;
	struct tNo *prox;
};

int menu () {
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

// Void de Inclus�o (Professor, usei como base o inclus�o do Sr.);
void inclusaoProdutos(struct tNo **lst, struct tNo *novo) {
	
	struct tNo *p = (*lst), *q;
	
	if ((*lst) == NULL) { 
		novo->prox = NULL;
		(*lst) = novo;
	}
	
	else { // inicio, fim ou meio
		if (novo->dado.codigoProduto < (*lst)->dado.codigoProduto) { // inicio
			novo->prox = (*lst);
			(*lst) = novo;
		}
		else { // fim ou meio
			while (p->prox != NULL)
				p = p->prox;
				
			if (novo->dado.codigoProduto > p->dado.codigoProduto) { // fim
				p->prox = novo;
				novo->prox = NULL;
			}
			else { // meio
				p = (*lst);
				while (p->dado.codigoProduto < novo->dado.codigoProduto) {
					q = p;
					p = p->prox;
				}
				q->prox = novo;
				novo->prox = p;
			}
		}
	}
}
//

// Void de Consulta.
struct tNo *consultaProdutos(struct tNo *lst, int codigo) {
    
	struct tNo *p = lst;

    while (p != NULL) {
    	if (p->dado.codigoProduto == codigo)
    		return p;
    	p = p->prox;
	}
	return NULL;
}
//

// Void de Listagem.
void listagemProdutos (struct tNo *lst, struct tNo *n) {
	
	struct tNo *p = lst;
	
	while (p != NULL) {
		printf("C�digo do Produto: %d\n", p->dado.codigoProduto);
		printf("Descri��o do Produto: %s\n\n", p->dado.descProduto); 
		p = p->prox;
	}
	printf("\n\n\nPressione qualquer tecla para sair...");
	getche();
	system("cls");
}
// 

// Limpeza da mem�ria Alocada.
void limpaAlocacao (struct tNo **lst) {
    struct tNo *q, *p = *lst;
    while (p != NULL) {
    	q = p;
    	p = p->prox;
    	free(q);
	}
}
//

// Exclus�o do Produto do Sistema.
void exclusaoProdutos(struct tNo **lst, struct tNo *removeProduto) {
	
	struct tNo *p = (*lst), *q;
	
	if (((*lst) == removeProduto) && (removeProduto->prox == NULL)) 
		(*lst) = NULL;
	else { 
		if ((*lst) == removeProduto) 
			(*lst) = removeProduto->prox;
		else { 
			while (p->prox != NULL) {
				q = p;
				p = p->prox;
			}
			if (removeProduto == p) 
				q->prox = NULL;
			else { 
				p = (*lst);
				while (p != removeProduto) {
					q = p;
					p = p->prox;
				}
				q->prox = removeProduto->prox;
			}
		}
	}
	free(removeProduto);
}
//

int main(void) {
	setlocale (LC_ALL, "Portuguese");
	
	int opcao, codigoProduto, i, achei;
	struct tNo *p, *novo, *produtos=NULL;
	
	do {
        opcao = menu();
        system("cls");
        switch (opcao) {
			case 1: 
				printf("Inclus�o de Produtos no Sistema...\n\n");
                
				p= malloc(sizeof(struct tNo));
                    
                printf("Informe o c�digo do Produto: ");
                scanf("%d", &(p->dado.codigoProduto));
                printf("Informe a descri��o do Produto: ");
                fflush(stdin);
                gets(p->dado.descProduto);
                    
				inclusaoProdutos(&produtos, p); 
                    
				printf("\n\n\nDados incluidos...\n");
				printf("\n\n\nPressione qualquer tecla para voltar ao Menu!");
				getche();
	            break;
            case 2: 
				printf("Listagem de Produtos no Sistema...\n\n");
            	listagemProdutos(produtos, p);
	            break;
            case 3: 
				printf("Consulta de Produtos no Sistema...\n\n");
                printf("Informe o c�digo que deseja Consultar: ");
                scanf("%d", &codigoProduto);
            
			    p = consultaProdutos(produtos, codigoProduto);
                
				if (p != NULL) {
                	printf("Descri��o do Produto: %s\n\n\n", p->dado.descProduto);
				}else
	            	printf("C�digo do Produto n�o foi encontrado!\n");
	            	
	            printf("\n\n\nPressione qualquer tecla para voltar ao Menu...");
				getche();
				break;
            case 4: 
				printf("Altera��o de Produtos no Sistema...\n\n");
                printf("Informe o c�digo do Produto que deseja Alterar: ");
                
				scanf("%d", &codigoProduto);
                
				p = consultaProdutos(produtos, codigoProduto);
                
				if (p != NULL) {
                	printf("\nDescri��o do Produto: %s \n", p->dado.descProduto);
	            	printf("\n\n\nInforme qual ser� a nova Descri��o: ");
	            	fflush(stdin);
	                gets(p->dado.descProduto);
	            }else
	                printf("C�digo do Produto n�o foi encontrado!\n");
	            break;
	        case 5:
				printf("Exclus�o de Produtos no Sistema...\n\n");
                printf("Informe o c�digo do Produto que deseja excluir: ");
                scanf("%d", &codigoProduto);

				p = consultaProdutos(produtos, codigoProduto);

                if (p != NULL)
                	exclusaoProdutos(&produtos, p);
                else
	                printf("C�digo do Produto n�o foi encontrado!\n");
	            break;
		}
        system("cls");
    }while (opcao != 0);
    limpaAlocacao(&produtos);
	return 0;
}
