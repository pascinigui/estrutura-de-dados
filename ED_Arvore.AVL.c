#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct tNo {
	struct tNo *esq;
	int dado;
	struct tNo *dir;
};

int menu(void) {
	int op;
    
    printf("Menu de Execução...\n\n");
	printf("\t1. Inserir Produto\n");
	printf("\t2. Consultar os Dados\n");
    printf("\t3. Caminhamento - Preorder\n");
    printf("\t4. Caminhamento - Inorder\n");
    printf("\t5. Caminhamento - Posorder\n");
    printf("\t6. Listagem dos Dados\n");
	printf("\t7. Exclusão dos Dados\n");
	printf("\t8. Representar\n");

   
    printf("\t0. Sair do Menu\n\n");
    printf("Escolha o que deseja fazer: ");
    scanf("%d", &op);
    return op;
}

void rotacaoD(struct tNo **pai){
	struct tNo *filho = (*pai)->esq;
	(*pai)->esq = filho->dir;
	filho->dir = (*pai);
	(*pai) = filho;
}

void rotacaoE(struct tNo **pai){
	struct tNo *filho = (*pai)->dir;
	(*pai)->dir = filho->esq;
	filho->esq = (*pai);
	(*pai) = filho;
}

void balanceamento(struct tNo **raiz){
	int fat = fatorBal(*raiz);
	if((fat != 2) && (fat != -2))
		return;
	if((fat == 2) && (fatorBal((*raiz)->dir) == 1))	//simples esquerda
		rotacaoE(raiz);
	else {
		if((fat == -2) && (fatorBal((*raiz)->esq) == -1))	//simples direita
			rotacaoD(raiz);
		else {
			if((fat == 2) && (fatorBal((*raiz)->dir) == - 1)) { //dupla esquerda
				rotacaoD(&((*raiz)->dir));
				rotacaoE(raiz);
			} else { //dupla direita
				rotacaoE(&((*raiz)->esq));
				rotacaoD(raiz);
			}
		}
	}
}

//*** Inclusao *****************************************************************
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
	balanceamento(raiz);
}

//*** Consultar ****************************************************************
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



//*** Listagem *****************************************************************
void listar(struct tNo *raiz) {
	if (raiz == NULL)
		return;
		listar(raiz->esq);
		printf("%d ", raiz->dado);
		listar(raiz->dir);	
}

//*** Caminhamento Preorder ****************************************************
void caminharPreorder(struct tNo *raiz) {
	if (raiz == NULL)
		return;
	printf("%d, ", raiz->dado);
	caminharPreorder(raiz->esq);
	caminharPreorder(raiz->dir);
}

//*** Caminhamento Inorder *****************************************************
void caminharInorder(struct tNo *raiz) {
	if (raiz == NULL)
		return;
	caminharInorder(raiz->esq);
	printf("%d, ", raiz->dado);
	caminharInorder(raiz->dir);
}

//*** Caminhamento Posorder ****************************************************
void caminharPosorder(struct tNo *raiz) {
	if (raiz == NULL)
		return;
	caminharPosorder(raiz->esq);
	caminharPosorder(raiz->dir);
	printf("%d, ", raiz->dado);
}

void calcAlt(struct tNo *raiz, int *altura){
	if(raiz == NULL)
		return;
	*altura = *altura+1;
	if(raiz->esq != NULL)
		calcAlt(raiz->esq, altura);
	if(raiz->dir != NULL)
		calcAlt(raiz->dir, altura);
}

int fatorBal(struct tNo *raiz){
	int alturaD = 0, alturaE = 0;
	if(raiz == NULL)
		return;
	calcAlt(raiz->dir, &alturaD);
	calcAlt(raiz->esq, &alturaE);
	return alturaD - alturaE;
}

/*
void altFB(struct tNo *raiz, int valorFB, int altura){
	printf("-------------------------\n");
	printf("Codigo->%d\n", raiz->dado.codigo);
	printf("Altura->%d\n", altura);
	printf("Fator de Balanceamento->%d\n", valorFB);
	printf("-------------------------\n");
}
*/

int grau(struct tNo *raiz){
	if((raiz->esq == NULL) && (raiz->dir == NULL))
		return 0;
	if((raiz->esq != NULL) && (raiz->dir != NULL))
		return 2;
	return 1;
}

struct tNo *menor (struct tNo *raiz){
	if((raiz == NULL) || (raiz->esq == NULL))
		return raiz;
	menor(raiz->esq);
}

//*** Exclusao *****************************************************************
int excluir(struct tNo **raiz, int chave) {
	int resp;
	struct tNo *p;
	if((*raiz) == NULL)
		return 0;
	if((*raiz)->dado == chave){
		if(grau(*raiz) == 0){
			free(*raiz);
			*raiz = NULL;
		}else{
			if(grau(*raiz) == 1){
				p = (*raiz);
				if((*raiz)->esq != NULL)
					(*raiz) = (*raiz)->esq;
				else
					(*raiz) = (*raiz)->dir;
				free(p);
			}else{
				p = menor((*raiz)->dir);
				(*raiz)->dado = p->dado;
				excluir(&((*raiz)->dir), p->dado);
			}
		}
		return 1;
	}
	if(chave < (*raiz)->dado)
		resp = excluir(&((*raiz)->esq), chave);
		resp = excluir(&((*raiz)->dir), chave);
		balanceamento(raiz);
		return resp;
}

//*** Destruir *****************************************************************
void destruir(struct tNo *raiz) {
	if (raiz == NULL)
		return;
		destruir(raiz->esq);
		destruir(raiz->dir);
		free(raiz);
}

void representar(struct tNo *raiz) {
	if (raiz == NULL)
		return;
	printf("(%d, ", raiz->dado);
	representar(raiz->esq);
	representar(raiz->dir);
	printf(")");
}

//*** Bloco Principal **********************************************************
int main(void) {
	setlocale (LC_ALL, "Portuguese");
	struct tNo *arvore=NULL, *p;
	int opcao, codigo, q, altura = 0, alturaD = 0, alturaE = 0, valorFB;
	
	do {
		altura = 0;
		alturaD = 0;
		alturaE = 0;
        opcao = menu();
		system("cls");
        switch (opcao) {
            case 1: 
            	printf("Inclusão na Árvore...\n");
                p = (struct tNo *)malloc(sizeof(struct tNo));
                printf("Digite um valor: ");
                scanf("%d", &(p->dado));
                incluir(&arvore, p);
	            break;
        	case 2: 
            	printf("Consulta na Árvore...\n");
                printf("Digite o codigo: ");
                scanf("%d", &codigo);
                p = consultar(arvore, codigo);
                if (p != NULL)
	        		printf("Achei\n");
	            else
	            	printf("Nao encontrado!\n");
	            Sleep(2000);
	            break;
	        case 3: 
                printf("Caminhamento - PreOrder...\n");
                caminharPreorder(arvore);
	            Sleep(2000);
	        	break;
            case 4: 
                printf("Caminhamento - InOrder...\n");
                caminharInorder(arvore);
	            Sleep(2000);
	            break;
            case 5: 
            	printf("Caminhamento - PosOrder...\n");
                caminharPosorder(arvore);
	            Sleep(2000);
	            break;
            case 6: 
                printf("Listagem da Árvore...\n");
                listar(arvore);
	            Sleep(2000);
	            break;
            case 7: 
                printf("Exclusão da Árvore...\n");
                printf("Digite o codigo: ");
            	scanf("%d", &codigo);
                q = excluir(&arvore, codigo);
                if (q == 1)
	            	printf("Excluido com sucesso!!!\n");
	            else
	            	printf("Exclusao falhou!!!\n");
	            break;
	        case 8: 
                printf("Representação da Árvore...\n");
                representar(arvore);
 	            Sleep(2000);
        }
        system("cls");
    } while (opcao != 0);
    destruir(arvore);
	return 0;
}
