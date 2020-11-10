#include<stdio.h>
#include<locale.h>
#include <stdlib.h>

#define TAM_MAX 100

struct tHash {
	float item;
	int ocupado;
};

int calcHash (float chave) {
	return abs(chave) % TAM_MAX;
}

void inicializa(struct tHash tabHash[]) {
	int i;
	
	for(i=0; i<TAM_MAX; i++) {
		tabHash[i].ocupado = 0; // falso
	}
}

int tabCheia (struct tHash tabHash[]) {
	int i, qtde=0;
	for (i=0; i<TAM_MAX; i++)
		if( tabHash[i].ocupado == 1)
			qtde++;
	if (qtde == TAM_MAX) return 1;
	else return 0;
}

int consulta(struct tHash tabHash[], float chave) { // Recuperando um elemento
	int pos = calcHash(chave);
	int iniciobusca = pos;
	if (tabHash[pos].ocupado == 1) { // se nessa posicao esta ocupado 
	
		if (tabHash[pos].item == chave) // Se item e chave são iguais	
			return pos; // saida imediata da função
		
		// INICIO ROTINA TRATAMENTO DE COLISAO	(se o item e chave nao sao iguais)
		while (pos < TAM_MAX) { // percorre proximas posições do vetor
			if (pos==TAM_MAX-1) pos=-1; // volta para o inicio da tabela
			pos++; // incremento mais um no indice
			if (tabHash[pos].ocupado == 1 && tabHash[pos].item == chave) 
			// se o campo esta ocupado e o item foi encontrado
				return pos; // saida imediata da função
			if (pos==iniciobusca) return -1; // se percorreu tudo e nao encontrou
		}
		// FIM ROTINA TRATAMENTO DE COLISAO
		
	}
	return -1; // Se nao existe essa chave
}


void inserir(struct tHash tabHash[], float chave, char desc[]) {
	if (tabCheia(tabHash)) { // Caso Tabela = Cheia, Imprime mensagem e sai.
		printf("\n\n!!! Tabela está CHEIA !!!\n\n");
		return; // Saida Imediata.
	}

	int pos = calcHash(chave); // Realiza o Calculo
	
	// INICIO ROTINA TRATAMENTO DE COLISAO
	if (tabHash[pos].ocupado == 1) { // se ocorreu colisao
		if (chave==tabHash[pos].item) { // se a chave ja existe
			puts("\n!!! AVISO !!! Este dado já foi cadastrado. \n\n");
			return; // saida imediata da função
		}
		printf("\n!!! Ocorreu uma colisação na %d° Posição. \n" ,pos);
		while (pos < TAM_MAX) {
			if (pos==TAM_MAX-1) pos=-1; // volta para o inicio da tabela
			pos++; // incremento mais um no indice
			if (tabHash[pos].ocupado == 0) // se a posição estiver livre
				break; // sai do loop com o indice na posicao correta (pos sem colisão)
		}
	}
	// FIM ROTINA TRATAMENTO DE COLISAO
	
	tabHash[pos].item=chave;
	tabHash[pos].ocupado = 1;
	printf("-> Inserido HASH [%d, %s] \n\n",pos,desc);
}

int menu(void) {
	int op;
    
    printf("Menu de Execução...\n\n");
	printf("\t1. Inserir Elemento\n");
	printf("\t2. Listar dos dados dos Produtos\n");
    printf("\t3. Consultar de informações sobre o Produto\n");

    printf("\t4. Deletar dos Produtos disponíveis\n");
   
    printf("\t0. Sair do Menu\n\n");
    printf("Escolha o que deseja fazer: ");
    scanf("%d", &op);
    return op;
}

void listagem(struct tHash tabHash[]) {
	int i;
	for (i=0; i<TAM_MAX; i++)
		if(tabHash[i].ocupado == 1)
			printf("\n[%d°] Campo --> Valor: %.2f",i,tabHash[i].item);
}

void deleta(struct tHash tabHash[], float chave) {
    int pos=consulta(tabHash,chave);
	if (pos!=-1) {
		tabHash[pos].ocupado=0;
		printf("Os dados HASH [%d] foram apagados. ",pos);
	}
	else printf("\nItem não encontrado.");
}

int main(void) {
	setlocale(LC_ALL, "Portuguese");
	
	int i, pos, opcao;
	float item;
	char desc[150];
	struct tHash tab[TAM_MAX];
	
	inicializa(tab);
	do {
        opcao = menu();
        system("cls");
        switch (opcao) {
            case 1: 
    			for (i=0; i<TAM_MAX; i++) {
					printf("Inserindo %d° elemento: \n\n", i+1);
					printf("Forneça um valor real: "); 
					scanf("%f", &item);
					printf("Forneça uma descrição real: ");
					fflush(stdin);
					gets(desc);
					fflush(stdin);
					inserir(tab,item,desc);
				} 
                break;
            case 2: 
                printf("Listando dados...\n");
				listagem(tab);
				Sleep(3000);
				break;
            case 3: 
            	printf("Forneça o valor para Consultar: ");
				scanf("%f",&item);
                pos=consulta(tab,item);
				if (pos!=-1)
					printf("\nItem: %.2f encontrado na %d° Posição. \n\n", tab[pos].item,pos);
				else 
					printf("\nItem não encontrado. \n\n");
				Sleep(2000);
				break;
            case 4: 
				printf("Remoção de dados...\nInforme o dado que deseja remover: ");
				scanf("%f",&item);
				deleta(tab,item);
	            break;
		}
        system("cls");
    }while (opcao != 0);
	return 0;
}
