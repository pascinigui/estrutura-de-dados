#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Declaracoes de tipos
struct tNo {
	struct tNo *esq;
	struct tNo *dir;
	int dado;
};

// Menu
int menu(void) {
	int op;
    
    printf("Menu de Execução...\n\n");
	printf("\t1. Inserir Produto\n");
	printf("\t2. Listar os dados dos Produtos\n");
    printf("\t3. Consultar informações sobre o Produto\n");
	printf("\t4. Exclusão das informações sobre o Produto\n");
   
    printf("\t0. Sair do Menu\n\n");
    printf("Escolha o que deseja fazer: ");
    scanf("%d", &op);
    return op;
}
//

// Inclusao 
void incluir(struct tNo **raiz, struct tNo *novo) {
	if ((*raiz) == NULL) {
		(*raiz) = novo;
		novo->esq = novo->dir = NULL;
	}
	else {
		if (novo->dado < (*raiz)->dado)
			incluir(&(*raiz)->esq, novo);
		else
			incluir(&(*raiz)->dir, novo);
	}
}
//

// Consultar
struct tNo *consultar(struct tNo *raiz, int chave) {
	if (raiz == NULL)
		return NULL;
	if (raiz->dado == chave)
		return raiz;
	if (chave < raiz->dado)
		return consultar(raiz->esq, chave);
	else
		return consultar(raiz->dir, chave);
}
//

// Listagem (MODO ERD)
void imprime(struct tNo *raiz) {
	if (raiz == NULL)
		return;
	imprime(raiz->esq); 
	printf("%d ", raiz->dado); 
	imprime(raiz->dir); 
}
//

// Destruir
void destruir(struct tNo *raiz) {
	if (raiz == NULL) 
		return;
	destruir(raiz->esq); 
	destruir(raiz->dir); 
	free(raiz); 
}
//

// Menor
struct tNo *menor (struct tNo *raiz) {
    if((raiz == NULL) || (raiz->esq == NULL))
        return raiz;
    menor(raiz->esq);

}

// Grau
int grau (struct tNo *raiz) {
	if ((raiz->esq == NULL) && (raiz->dir == NULL))
		return 0;
	if ((raiz->esq != NULL) && (raiz->dir != NULL))
		return 2;
	return 1;
}
//

// Exclusao
int excluir(struct tNo **raiz, int chave) {
	struct tNo *p;
    
	if((*raiz) == NULL)
        return 0;
        
    if((*raiz)->dado == chave) {
        if(grau(*raiz) == 0) { //grau = 0
            free(*raiz);
            *raiz = NULL;
        } else {
            if(grau(*raiz) == 1) { //grau igual a 1
                p = (*raiz);
                if((*raiz)->esq !=NULL)
                    (*raiz) = (*raiz)->esq;
                else
                    (*raiz) = (*raiz)->dir;
                free(p);
            } else { //grau igual 2
                p = menor((*raiz)->dir);
                (*raiz)->dado = p->dado;
                excluir(&((*raiz)->dir), p->dado);
            }
        }
        return 1;
    }
    
    if(chave < (*raiz)->dado)
        return excluir(&((*raiz)->esq), chave);
    return excluir(&((*raiz)->dir), chave);
}
//

// Bloco Principal 
int main(void) {
	setlocale (LC_ALL, "Portuguese");
	struct tNo *arvore=NULL, *p;
	int q;
	int opcao, codigo;
	
	do {
        opcao = menu();
        system("cls");
        switch (opcao) {
				case 1: 
                    printf("Inclusão na Árvore...\n");
                    p = (struct tNo *)malloc(sizeof(struct tNo));
                    printf("\nDigite um valor: ");
                    scanf("%d", &(p->dado));
                    incluir(&arvore, p);
	                break;
                case 2: 
                    printf("Listagem da Árvore...\n");
                    imprime(arvore);
                    Sleep(2000);
					break;
                case 3: 
			    	printf("Consulta na Árvore...\n");
					printf("\nDigite o codigo: ");
                    scanf("%d", &codigo);
                    p = consultar(arvore, codigo);
                    if (p != NULL)
						printf("\nValor encontrado.\n");
					else
	            		printf("\nValor NÃO encontrado!\n");
	            	Sleep(3000);
	                break;
                case 4: 
                    printf("Exclusão de item Árvore...\n");
					printf("\nDigite o codigo que deseja excluir: ");
                    scanf("%d", &codigo);
	            	q = excluir(&arvore, codigo);
	            	if (q == 1)
						printf("\nValor REMOVIDO.\n");
					else
	            		printf("\nValor NÃO REMOVIDO ou NÃO ENCONTRADO!\n");
					Sleep(3000);
					break;
        }
        system("cls");
    }while (opcao != 0);
    destruir(arvore);
	return 0;
}

