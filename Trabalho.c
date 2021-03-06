#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //biblioteca de linguagem.

typedef struct{
  int coluna;
  float valor;
}EntradaMatriz;

typedef struct{
  EntradaMatriz **m;
  int num_linhas, num_colunas;
}MatrizEsparsa;

int main(int argc, char const *argv[]) {
	setlocale(LC_ALL, "Portuguese"); /*inser??o de acentos, e outros caracteres.*/
	int opcao, sair = 0, escolha_me, i;
	MatrizEsparsa me1, me2, me3;
	int l1=0, c1=0, l2=0, c2=0, l=0, c=0, valor=0;
	do{
	//	printf("struct %i         variavel %i",me1.num_linhas,l1);
		printf("\n\n	Escolha a op??o desejada:\n	1. Inicializar uma matriz.\n	2. Carregar matriz do arquivo. \n	3. Visualizar uma matriz\n	4. Modificar uma matriz, dadas as coordenadas (linha e coluna)\n	5. Soma entre matrizes\n	6. Subtra??o entre matrizes\n	7. Multiplica??o entre matrizes\n	8. Salvar matriz.\n	9. Sair do programa\n\n	");
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
						printf("\n	Matriz 2 inicializada.");
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
				printf("\n	Escolha a matriz desejada: 1 ou 2? ");
				scanf("%i",&escolha_me);
				switch(escolha_me){
					case 1:
						matriz_arquivo(&me1,escolha_me);
						l1=me1.num_linhas;
						c1=me1.num_colunas;
						break;
					case 2:
						matriz_arquivo(&me2,escolha_me);
						l2=me2.num_linhas;
						c2=me2.num_colunas;
						break;
				}
				break;
			case 3:
				printf("\n	Escolha a matriz a ser visualizada: 1 ou 2? ");
				scanf("%i",&escolha_me);
				switch(escolha_me){
					case 1:
						mostra_m(&me1,escolha_me);
						break;
					case 2:
						mostra_m(&me2,escolha_me);
						break;
				}
				break;
			case 4:
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
						modifica_matriz(&me1, l, c, valor,escolha_me);
						break;
					case 2:
						printf("\n	Informe a linha: ");
						scanf("%i",&l);
						printf("\n	Informe a coluna: ");
						scanf("%i",&c);
						printf("\n	Informe o valor: ");
						scanf("%i",&valor);
						modifica_matriz(&me2, l, c, valor,escolha_me);
						break;
				}
				break;
			case 5:
				me3.m=malloc(sizeof(EntradaMatriz*));
				soma_matriz(&me1,&me2,&me3);
				escolha_me=3;
				mostra_m(&me3,escolha_me);
				break;
			case 8:
				printf("\n	Escolha a matriz a ser salva: 1 ou 2? ");
				scanf("%i",&escolha_me);
				switch(escolha_me){
					case 1:
						salva_matriz(&me1,escolha_me);
						break;
					case 2:
						salva_matriz(&me2,escolha_me);
						break;
					}
				break;	
			case 9:
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
				printf("\n	Codigo inv?lido.");
			}
		}
	}while(sair!=1);
  return 0;
}

void modifica_matriz(MatrizEsparsa *me, int l, int c, int valor,int escolha_me){
	
	//system("cls"); //Limpa a tela.
	
	int i=0;
	if(checa_me_inicializou(*me)){
		int tam_entrada;
		if((me->num_linhas)<l){
			me->m = realloc (me->m,sizeof(EntradaMatriz*)*(l+1));
			for(i=me->num_linhas;i<l;i++){
				me->m[i]=NULL;
			}
			me->num_linhas=l+1;
		}
		
		if(me->m[l] == NULL){
			tam_entrada = 2;
			me->m[l] = malloc(sizeof(EntradaMatriz)*(tam_entrada));
			me->m[l][tam_entrada-2].valor=valor;
			me->m[l][tam_entrada-2].coluna=c;
			me->m[l][tam_entrada-1].coluna = -1;
		}else{
			tam_entrada = conta_entrada(me->m[l]);
			if((me->num_colunas)<c){
				tam_entrada++;
				me->m[l] = realloc(me->m[l],sizeof(EntradaMatriz)*(tam_entrada));
				me->m[l][tam_entrada-1].coluna = -1;
				me->m[l][tam_entrada-2].coluna = c;
				me->m[l][tam_entrada-2].valor = valor;
				me->num_colunas = c+1;
			}else{
				me->m[l][c].valor = valor;
			}
		}			
		
		mostra_m(*me,escolha_me);
		printf("l %i c %i num_linhas %i num_colunas %i",l,c,me->num_linhas,me->num_colunas);
				
	}else{
		printf("\n	Matriz n?o inicializada.");
	}
}

int conta_entrada(EntradaMatriz *m){
	int i = 0, cont = 1;
	while(m[i].coluna != -1){
		cont++;
		i++;
	}
	return cont;
}

void inicializa_matrizesp(MatrizEsparsa *me, int l, int c){
  me->num_linhas=l;
  me->num_colunas=c;
  me->m = calloc(sizeof(EntradaMatriz*),l); //Aloca??o din?mica com calloc (j? inicializa os valores com 0).
  //system("cls"); //Limpa a tela.
}


void mostra_m(MatrizEsparsa *me,int escolha_me){
	//system("cls"); //Limpa a tela.
	
	if(checa_me_inicializou(*me)){
		int i,j;
		printf("\n\n	Matriz %i:\n",escolha_me); //Coloquei pra mostrar qual matriz foi modificada (Kenny). tem um erro que quero arrumar na modifica matriz o ESCOLHA_ME n?o ta funcionando!!!!!
  		for(i=0;i<(me->num_linhas);i++){
	    	if((me->m[i])==NULL){
		    	for(j=0;j<(me->num_colunas);j++){
		    		printf("	0");
				}
    		}else{
    			int k = 0;
    			for(j=0;j<(me->num_colunas);j++){
		    		if(me->m[i][k].coluna==j){
		    			printf("	%.2f",me->m[i][k].valor);
		    			k++;
					}else{
						printf("	0");
					}
				}
			}
			printf("\n");
		}
	}else{
		printf("\n\n	Matriz n?o inicializada.");
	}
}

int checa_me_inicializou(MatrizEsparsa *me){
	//system("cls"); //Limpa a tela.
	return (me->num_colunas)!=NULL;
}


EntradaMatriz le_entrada_m(int c,float valor){
	//system("cls"); //Limpa a tela.
  	EntradaMatriz e;
  	e.coluna=c;
 	e.valor=valor;
 	return e;
}

EntradaMatriz finaliza_entrada_m(){
	//system("cls"); //Limpa a tela.
 	EntradaMatriz e;
	e.coluna=-1;
 	return e;
}

void matriz_arquivo(MatrizEsparsa *me, int escolha_me){
	int i,j;
	FILE *arq;
	float checar=0;
	switch(escolha_me){
		case 1:
			arq=fopen("matriz1.txt", "rt");
			if(arq==NULL){
				printf("\n\n Arquivo n?o encontrado!");
			}else{
				fscanf(arq,"%i %i ",&me->num_linhas,&me->num_colunas);
				me->m=malloc(sizeof(EntradaMatriz*)*me->num_linhas);
				for(i=0;i<me->num_linhas;i++){
					int ind=0;
		            me->m[i]=malloc(sizeof(EntradaMatriz));
					for(j=0;j<me->num_colunas;j++){
						fscanf(arq,"%f",&checar);
						if(checar != 0){
		                    ind++;
		                    me->m[i]=realloc(me->m[i],sizeof(EntradaMatriz)*ind);
							me->m[i][ind-1].valor=checar;
							me->m[i][ind-1].coluna=j;
						}
					}
					me->m[i][ind].coluna = -1;
				}
			fclose(arq);
			printf("\n\n	Matriz %i carregada com sucesso!\n",escolha_me);
		}
		break;
		case 2:
			arq=fopen("matriz2.txt", "rt");
			if(arq==NULL){
				printf("\n\n Arquivo n?o encontrado!");
			}else{
				fscanf(arq,"%i %i ",&me->num_linhas,&me->num_colunas);
				me->m=malloc(sizeof(EntradaMatriz*)*me->num_linhas);
				for(i=0;i<me->num_linhas;i++){
					int ind=0;
		            me->m[i]=malloc(sizeof(EntradaMatriz));
					for(j=0;j<me->num_colunas;j++){
						fscanf(arq,"%f",&checar);
						if(checar != 0){
		                    ind++;
		                    me->m[i]=realloc(me->m[i],sizeof(EntradaMatriz)*ind);
							me->m[i][ind-1].valor=checar;
							me->m[i][ind-1].coluna=j;
						}
					  }
					me->m[i][ind].coluna = -1;
				}
			fclose(arq);
			printf("\n\n	Matriz %i carregada com sucesso!\n",escolha_me);
		}
		break;
}
}

void salva_matriz(MatrizEsparsa *me, int escolha_me){
	FILE *arq;
	int i,j,k=0;
	switch(escolha_me){
		case 1:
			arq=fopen("matriz1.txt","w");
			fprintf(arq,"%i %i\n",me->num_linhas,me->num_colunas);
			for(i=0;i<me->num_linhas;i++){
				for(j=0;j<me->num_colunas;j++){
					if (j == me->m[i][k].coluna){
						fprintf(arq,"%d ",me->m[i][k].valor);
						k++;
					}else{
						fprintf(arq, "0 ");
					}
				}
				fprintf(arq,"\n");
				k=0;
			}
			fclose(arq);
			break;
		case 2:
			arq=fopen("matriz2.txt","w");
			fprintf(arq,"%i %i\n",me->num_linhas,me->num_colunas);
			for(i=0;i<me->num_linhas;i++){
				for(j=0;j<me->num_colunas;j++){
					if (j == me->m[i][k].coluna){
						fprintf(arq,"%d ",me->m[i][k].valor);
						k++;
					}else{
						fprintf(arq, "0 ");
					}
				}
				fprintf(arq,"\n");
				k=0;
			}		
			fclose(arq);
			break;
}
}


void soma_matriz(MatrizEsparsa *me1,MatrizEsparsa *me2,MatrizEsparsa *me3){
	int i,j,k,cont=0;
	float x=0;
	if((me1->num_linhas==me2->num_linhas) && (me1->num_colunas==me2->num_colunas)){
		me3->num_linhas=me1->num_linhas;
		me3->num_colunas=me1->num_colunas;
		me3->m=malloc(sizeof(EntradaMatriz*)*me3->num_linhas);
		for(i=0;i<me3->num_linhas;i++){
			me3->m[i]=NULL;
			
			for(j=0;j<me3->num_colunas;j++){	
			
				for(k=0;me1->m[i][j].coluna!=-1;j++){
					
					if(me1->m[i][k].coluna==k){
						x=me1->m[i][j].valor;
					}
						
					if(me2->m[i][k].coluna==k){
						x=x+me2->m[i][j].valor;
					}	
					
					if(x!=0){
						me3->m[i]=realloc(me3->m[i],sizeof(EntradaMatriz)*(j+1));
						me3->m[i][j].coluna=j;
						me3->m[i][j].valor=x;
					}
				x=0;	
				}
			me3->m[i][j+1].coluna=-1;
			}
		}
	}else{
		printf("\n	As matrizes n�o possuem o mesmo tamanho!\n");
	}
}
	

	
	
	
