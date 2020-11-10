#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

// Structs
struct tProduto {
	int cod; // chave de ordena??o
	char descricao[30];
};

struct tNo {
	struct tProduto dados;
	struct tNo *next;
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

// Inclus�o de Produtos
void incluir(struct tDescritor *lista, struct tNo *novo) {
	struct tNo *p, *q;
	
	// Situa��o no caso de Lista Vazia receber o valor
	if (lista->ini == NULL) {
		novo->next = NULL;
		lista->ini = novo;
		lista->fim = novo;
	}else
		// Inicio da Lista
		if (lista->fim->dados.cod < lista->ini->dados.cod) {
			lista->fim->next = novo;
			lista->ini = novo;
		}else
			// Fim da Lista
			if (lista->fim->dados.cod < novo->dados.cod) {
				lista->fim->next = novo;
				lista->fim = novo;
				novo->next = NULL;
			}else{
				p= lista->ini;
				while (p->dados.cod < novo->dados.cod) {
					q=p;
					p=p->next;
				}
				q->next = novo;
				novo->next = p;
			}
			lista->qtd++;
}
//

// Void de Listagem.
void listagemProdutos (struct tDescritor lista) {
	
	struct tNo *p = lista.ini;
	
	while (p != NULL) {
		printf("C�digo do Produto: %d\n", p->dados.cod);
		printf("Descri��o do Produto: %s\n\n", p->dados.descricao); 
		p = p->next;
	}
	printf("\n\n\nPressione qualquer tecla para sair...");
	getche();
	system("cls");
}
// 

// Exclus�o do Produto do Sistema.
void exclusaoProdutos(struct tDescritor *lista, struct tNo *vitima) {
	
	struct tNo *p = lista->ini;
	
	if (lista == NULL)
		return;
	if ((lista->ini == vitima) && (vitima->next == NULL)) 
		lista = NULL;
	else { 
		if (lista->ini == vitima) 
			lista->ini = vitima->next;
		else { 
			while (p->next != vitima) 
				p = p->next;
			if (vitima->next == NULL) 
				p->next = NULL;
			else 
				p->next = vitima->next;
		}
	}
	free(vitima);
}
//


// Void de Consulta.
void consultaProdutos(struct tDescritor lista, int codigo) {
	
	struct tNo *p = lista.fim;
	int flag=0;

	while ((p != NULL) && (p->dados.cod <= codigo)) {
		if (codigo == p->dados.cod) {
			printf("Descri��o do Produto: %s\n\n", p->dados.descricao);
			flag=1; 
		}
		p = p->next;			
	}	
	if (flag==0)
    	printf("C�digo do Produto n�o foi encontrado!\n");
	flag=0;	
}
//

// Limpeza da mem�ria Alocada.
void limpaAlocacao (struct tDescritor *lista) {
    struct tNo *p = lista->ini, *q;
    while (p != NULL) {
    	q = p;
    	p = p->next;
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
                scanf("%d", &(p->dados.cod));
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
            
			    consultaProdutos(lista, codigo);
	            
				printf("\n\n\nPressione qualquer tecla para voltar ao Menu...");
				getche();
                break;
            case 4: 
                printf("Altera��o de Produtos...\n\n");
                printf("Informe o c�digo que deseja Consultar: ");
                scanf("%d", &codigo);
            
			    consultaProdutos(lista, codigo);

				if (p != NULL) {
			    	printf("Informe qual ser� a nova Descri��o: ");
	        		fflush(stdin);
	                gets(p->dados.descricao);
	            }else
	                printf("C�digo do Produto n�o foi encontrado!\n");
	            break;
            case 5: 
                printf("Exclus�o de Produtos....\n\n");
                printf("Informe o c�digo do Produto que deseja excluir: ");
                scanf("%d", &codigo);

			    consultaProdutos(lista, codigo);

                if (p != NULL)
                	exclusaoProdutos(&lista, p);
                else
	                printf("C�digo do Produto n�o foi encontrado!\n");
	            break;
        }
        system("cls");
    }while (opcao != 0);
    limpaAlocacao(&lista);
	return 0;
}
//
