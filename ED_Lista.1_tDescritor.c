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
	struct tNo *p, *q;
	
	// Situação no caso de Lista Vazia receber o valor
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
		printf("Código do Produto: %d\n", p->dados.cod);
		printf("Descrição do Produto: %s\n\n", p->dados.descricao); 
		p = p->next;
	}
	printf("\n\n\nPressione qualquer tecla para sair...");
	getche();
	system("cls");
}
// 

// Exclusão do Produto do Sistema.
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

                if (p != NULL)
                	exclusaoProdutos(&lista, p);
                else
	                printf("Código do Produto não foi encontrado!\n");
	            break;
        }
        system("cls");
    }while (opcao != 0);
    limpaAlocacao(&lista);
	return 0;
}
//
