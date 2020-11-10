#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

struct Pilha {

	int topo; /* posi��o elemento topo */
	int capa;
	float *pElem;

};

void criarpilha( struct Pilha *p, int c ){

   p->topo = -1;
   p->capa = c;
   p->pElem = (float*) malloc (c * sizeof(float));

}
int estavazia ( struct Pilha *p ){

   if( p-> topo == -1 )

      return 1;   // true

   else

      return 0;   // false

}

int estacheia ( struct Pilha *p ){

	if (p->topo == p->capa - 1)

		return 1;

	else

		return 0;

}

void empilhar ( struct Pilha *p, float v){

	p->topo++;
	p->pElem [p->topo] = v;

}

float desempilhar ( struct Pilha *p ){

   float aux = p->pElem [p->topo];
   p->topo--;
   return aux;

}

float retornatopo ( struct Pilha *p ){

   return p->pElem [p->topo];

}

int main(){
	setlocale (LC_ALL, "Portuguese");
	struct Pilha minhapilha;
	int capacidade, op;
	float valor;

	printf( "\nCapacidade da pilha? " );
	scanf( "%d", &capacidade );

	criarpilha (&minhapilha, capacidade);

	while( 1 ){ /* loop infinito */
		system("cls");
		printf("\nOp��o 1: Empilhar (Push)\n");
		printf("Op��o 2- Desempilhar (POP)\n");
		printf("Op��o 3- Mostrar o topo \n");
		printf("Op��o 4- sair\n");
		printf("\nQual a op��o desejada? ");
		scanf("%d", &op);

		switch (op){

			case 1: //push

				if( estacheia( &minhapilha ) == 1 )

					printf("\nA pilha est� cheia! \n");

				else {

					printf("\nQual o valor que deseja empilhar? ");
					scanf("%f", &valor);
					empilhar (&minhapilha, valor);
					system("cls");
				}
				break;

			case 2: //pop
				if ( estavazia(&minhapilha) == 1 )

					printf( "\nA pilha est� vazia! \n" );

				else{

					valor = desempilhar (&minhapilha);
					printf ( "\nN�mero: %.1f desempilhado!\n", valor );
					Sleep(3000);
				}
				break;

			case 3: // mostrar o topo
				if ( estavazia (&minhapilha) == 1 )

					printf( "\nA pilha est� vazia!\n" );

				else {

					valor = retornatopo (&minhapilha);
					printf ( "\nTopo da Pilha: %.1f\n", valor );
					Sleep(3000);
				}
				break;

			case 4: 
				exit(0);

			default: printf( "\nOp��o Inv�lida! \n" );
		}
	}
	
}
