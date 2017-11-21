#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int coluna;
  float valor;
}EntradaMatriz;

typedef struct{
  EntradaMatriz **m;
  int num_linhas, num_colunas;
}MatrizEsparsa;

int main(int argc, char const *argv[]) {
	int opcao, sair = 0, escolha_me, i;
	MatrizEsparsa me1, me2;
	int l1, c1, l2, c2, l, c, valor;
	do{
		printf("\n\n\n	Escolha a op��o desejada:\n	1. Carregar uma matriz do arquivo\n	2. Visualizar uma matriz\n	3. Modificar uma matriz, dadas as coordenadas (linha e coluna)\n	4. Salvar uma matriz\n	5. Soma entre matrizes\n	6. Subtra��o entre matrizes\n	7. Multiplica��o entre matrizes\n	8. Sair do programa\n	");
		scanf("%i",&opcao);
		switch(opcao){
			case 1:
				printf("\n	Escolha a matriz a ser inicializada: 1 ou 2? ");
				scanf("%i",&escolha_me);
				switch(escolha_me){
					case 1:
						printf("\n	Informe o numero de linhas: ");
						scanf("%i",&l1);
						printf("\n	Informe o numero de colunas: ");
						scanf("%i",&c1);
						inicializa_matrizesp(&me1,l1,c1);
						printf("\n	Matriz 1 inicializada.");
						break;
					case 2:
						printf("\n	Informe o numero de linhas: ");
						scanf("%i",&l2);
						printf("\n	Informe o numero de colunas: ");
						scanf("%i",&c2);
						inicializa_matrizesp(&me2,l2,c2);
						printf("\n	Matriz 2 inicializada.");
						break;
				}
				break;
			case 2:
				printf("\n	Escolha a matriz a ser visualizada: 1 ou 2? ");
				scanf("%i",&escolha_me);
				switch(escolha_me){
					case 1:
						mostra_m(&me1);
						break;
					case 2:
						mostra_m(&me2);
						break;
				}
				break;
			case 3:
				printf("\n	Escolha a matriz a ser modificada: 1 ou 2? ");
				scanf("%i",&escolha_me);
				switch(escolha_me){
					case 1:
						printf("\n	Informe a linha: ");
						scanf("%i",&l);
						printf("\n	Informe a coluna: ");
						scanf("%i",&c);
						printf("\n	Informe o valor: ");
						scanf("%i",&valor);
						modifica_matriz(&me1, l, c, valor);
						break;
					case 2:
						printf("\n	Informe a linha: ");
						scanf("%i",&l);
						printf("\n	Informe a coluna: ");
						scanf("%i",&c);
						printf("\n	Informe o valor: ");
						scanf("%i",&valor);
						modifica_matriz(&me2, l, c, valor);
						break;
				}
				break;
			case 8:
				if(checa_me_inicializou(&me1)){
					for(i=0;i<me1.num_colunas;i++){
						free(me1.m[i]);
					}
					free(me1.m);
				}
				if(checa_me_inicializou(&me2)){
					for(i=0;i<me1.num_colunas;i++){
						free(me2.m[i]);
					}
					free(me2.m);
				}
				sair = 1;
				break;
			default:{
				printf("\n	Codigo invalido.");
			}
		}
	}while(sair!=1);
  return 0;
}

void modifica_matriz(MatrizEsparsa *me, int l, int c, int valor){
	if(checa_me_inicializou(*me)){
		int tam_entrada = sizeof(me->m[l])/sizeof(EntradaMatriz);
		if(tam_entrada==0){
			me->m[l] = malloc(sizeof(EntradaMatriz));
		}
		tam_entrada++;
		me->m[l] = realloc(me->m[l], sizeof(EntradaMatriz)*tam_entrada);
		me->m[l]->coluna = c;
		me->m[l]->valor = valor;
		mostra_m(*me);
	}else{
		printf("\n	Matriz nao inicializada.");
	}
}

void inicializa_matrizesp(MatrizEsparsa *me, int l, int c){
  me->num_linhas=l;
  me->num_colunas=c;
  me->m = malloc(sizeof(EntradaMatriz*)*l);
  int i;
  for(i=0;i<l;i++){
    me->m[i]=NULL;
  }
}


void mostra_m(MatrizEsparsa *me){
	if(checa_me_inicializou(*me)){
		int i,j;
  		for(i=0;i<(me->num_linhas);i++){
	    	if((me->m[i])==NULL){
		    	for(j=0;j<(me->num_colunas);j++){
		    		printf(" 0");
				}
    		}else{
    			int k = 0;
    			for(j=0;j<(me->num_colunas);j++){
		    		if(me->m[i][k].coluna==j){
		    			printf(" %.2f",me->m[i][k].valor);
		    			k++;
					}else{
						printf(" 0");
					}
				}
			}
			printf("\n");
		}
	}else{
		printf("\n	Matriz nao inicializada.");
	}
}

int checa_me_inicializou(MatrizEsparsa *me){
	return (me->num_colunas)!=NULL;
}


EntradaMatriz le_entrada_m(int c,float valor){
  EntradaMatriz e;
  e.coluna=c;
  e.valor=valor;
  return e;
}

EntradaMatriz finaliza_entrada_m(){
  EntradaMatriz e;
  e.coluna=-1;
  return e;
}
