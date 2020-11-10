#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

// Structs
struct tProduto {
	int cod; 
	char descricao[30];
};

struct tNo {
	struct tProduto dados;
	struct tNo *next;
	struct tNo *prev;
};

struct tDescritor {
	struct tNo *ini, *fim;
	int qtd;
};
//

// Menu
int menu(void) {
   int op;
    
    printf("Menu de Execução...\n\n");
	printf("\t1. Inclusão de um novo Produto\n");
    printf("\t2. Listagem dos Produtos disponíveis\n");
    printf("\t3. Consulta de informações sobre o Produto\n");
    printf("\t4. Alteração dos dados dos Produtos\n");
    printf("\t5. Exclusão dos Produtos do Estoque\n\n");
    printf("\t0. Sair do Menu\n\n");
    printf("Escolha o que deseja fazer: ");
    scanf("%d", &op);
    return op;
}
//

// Inicialização da Lista
void inicializar (struct tDescritor *lista) {
	(*lista).ini = (*lista).fim = NULL;
	(*lista).qtd = 0;
}
//

// Inclusão de Produtos
void incluir(struct tDescritor *lista, struct tNo *novo) {
	struct tNo *p = (*lista).ini;
	struct tNo *q;
	
	if ((*lista).ini == NULL) { // Lista vazia
		novo->next = NULL;
		novo->prev = NULL;
		(*lista).ini = novo;		
		(*lista).fim = novo;
	}
	
	else { // inicio, fim ou meio
		if (novo->dados.cod < (*lista).ini->dados.cod) { // inicio
			novo->next = (*lista).ini;
			novo->prev = NULL;
			(*lista).ini->prev = novo;
			(*lista).ini = novo;
		}
		else { // fim ou meio
			while (p->next != NULL)
				p = p->next;
			if (novo->dados.cod > p->dados.cod) { // fim
				p->next = novo;
				novo->next = NULL;
				novo->prev = p;
				(*lista).fim = novo;
			}
			else { // meio
				p = (*lista).ini;
				while (p->dados.cod < novo->dados.cod) {
					q = p;
					p = p->next;
				}
				q->next = novo;
				novo->next = p;
				novo->prev = p->prev;
				q->prev = novo;
			}
		}
	}
	(*lista).qtd++;
}
//

// Void de Listagem.
void listagemProdutos (struct tDescritor lista) {
	
	struct tNo *p = lista.ini;
	
	while (p != NULL) {
		printf("Código do Produto: %d\n", p->dados.cod);
		printf("Descrição do Produto: %s\n\n", p->dados.descricao); 
		p = p->next;
	}
	printf("\n\n\nPressione qualquer tecla para sair...");
	getche();
	system("cls");
}
// 

// Limpeza da memória Alocada.
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

// Exclusão do Produto do Sistema.
void exclusaoProdutos(struct tDescritor *lista, struct tNo *vitima) {

	struct tNo *p = (*lista).ini;

	if ((lista->ini == vitima) && (vitima->next == NULL)) {
		lista->ini = NULL;
		lista->fim = NULL;
		lista->qtd = 0;
	}else 
	// Primeiro, último e meio
		if ((*lista).ini == vitima) {// primeiro
			(*lista).ini = vitima->next;
			(*lista).ini -> prev = NULL;
		}
		else { // ultimo, meio
			while (p->next != vitima) // elemento = no anterior ao vitima
				p = p->next;
			if (vitima->next == NULL) { // ultimo
				p->next = NULL;
				(*lista).fim = p;
			}
			else {// meio
				p->next = vitima->next;
				(p->next)->prev = p;
			}
		}
	free(vitima);
	(*lista).qtd--;
}
//

// Void de Consulta.
void consultaProdutos(struct tDescritor lista, int codigo) {
	
	struct tNo *p = lista.fim;
	int flag=0;

	while ((p != NULL) && (p->dados.cod <= codigo)) {
		if (codigo == p->dados.cod) {
			printf("Descrição do Produto: %s\n\n", p->dados.descricao);
			flag=1; 
		}
		p = p->next;			
	}	
	if (flag==0)
    	printf("Código do Produto não foi encontrado!\n");
	flag=0;	
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
                printf("Inclusão de Produtos ao Estoque...\n\n");
			    p = (struct tNo *)malloc(sizeof(struct tNo));

				printf("Informe qual o código do Produto: ");
                scanf("%d", &(p->dados.cod));
     
	            printf("Informe a descrição do Produto: ");
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

				printf("Informe o código que deseja Consultar: ");
                scanf("%d", &codigo);
            
			    consultaProdutos(lista, codigo);
	            
				printf("\n\n\nPressione qualquer tecla para voltar ao Menu...");
				getche();
				break;
            case 4: 
                printf("Alteração de Produtos...\n\n");
                printf("Informe o código que deseja Consultar: ");
                scanf("%d", &codigo);
            
			    consultaProdutos(lista, codigo);

				if (p != NULL) {
			    	printf("Informe qual será a nova Descrição: ");
	        		fflush(stdin);
	                gets(p->dados.descricao);
	            }else
	                printf("Código do Produto não foi encontrado!\n");
	            break;
			case 5: 
                printf("Exclusão de Produtos....\n\n");
                printf("Informe o código do Produto que deseja excluir: ");
                scanf("%d", &codigo);

			    consultaProdutos(lista, codigo);

                if (p != NULL) {
                	exclusaoProdutos(&lista, p);
				}else{
					printf("\n\nCódigo do Produto não foi encontrado!\n");
					printf("\nPressione qualquer tecla para prosseguir... \n\n\n");
					getche();
				}
				break;
				getche();
        }
        system("cls");
    }while (opcao != 0);
	limpaAlocacao(&lista);
	return 0;
}
//	
