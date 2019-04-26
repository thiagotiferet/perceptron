#include<stdlib.h>
#include<stdio.h>

#define TETA 0
#define ALFA 1

int ativacao(int y_in){
	if (y_in > TETA)
		return 1;
	else{
		if (y_in < -TETA)
			return -1;
		else
			return 0;
	}
}

int seleciona_alvo(int valor){
	int retorno;
	if((valor==0) || (valor==7) || (valor==14) || (valor==21) || (valor==28) || (valor==35))
		retorno = 0;
	else{
		if ((valor==1) || (valor==8) || (valor==15) || (valor==22) || (valor==29) || (valor==36))
			retorno = 1;
		else{
			if ((valor==2) || (valor==9) || (valor==16) || (valor==23) || (valor==30) || (valor==37))
				retorno = 2;
			else{
				if ((valor==3) || (valor==10) || (valor==17) || (valor==24) || (valor==31) || (valor==38))
					retorno = 3;
				else{
	   				if ((valor==4) || (valor==11) || (valor==18) || (valor==25) || (valor==32) || (valor==39))
						retorno = 4;
					else{
						if ((valor==5) || (valor==12) || (valor==19) || (valor==26) || (valor==33) || (valor==40))
							retorno = 5;
						else
							retorno = 6;
					}
				}	
			}	
		}	
	}
	return retorno;
}

char muda_para_letra(int valor){
	char letra;
	switch(valor){
		case 0:
			letra = 'A';
			break;
		case 1:
			letra = 'B';
			break;
		case 2:
			letra = 'C';
			break;
		case 3:
			letra = 'D';
			break;
		case 4:
			letra = 'E';
			break;
		case 5:
			letra = 'J';
			break;
		case 6:
			letra = 'K';
			break;
		default:
			break;
	}
	return letra;
}

void verifica_perceptron(FILE* saida,int entrada[42][64],int alvo[7][7],int pesos[7][64], int chave){
	int y[7]; 
	int y_in[7];
	int i, j, k, l, m, n, z;
	char letra;
	int c = 21;
	if (chave == 2)
		c = 42;	
	fprintf(saida,"RESULTADOS CLASSIFICACAO\n" );
	for(i=0;i<c;i++){
		k = seleciona_alvo(i);
		z = 0;
		while(z<7){
			y_in[z] = 0;
			z++;
		}
		for(j=0;j<7;j++){
			for(l=0;l<64;l++){
				y_in[j] = y_in[j] + entrada[i][l] * pesos[j][l];			
			}
			y[j] = ativacao(y_in[j]);
	    }
	    switch(i){
	    	case 0:
	    		fprintf(saida,"ENTRADA FONTE 1\n");
	    		break;
	    	case 7:
	    		fprintf(saida,"ENTRADA FONTE 2\n");
	    		break;
	    	case 14:
	    		fprintf(saida,"ENTRADA FONTE 3\n");
	    		break;
	    	case 21:
	    		fprintf(saida,"ENTRADA FONTE 4\n");
	    		break;
	    	case 28:
	    		fprintf(saida,"ENTRADA FONTE 5\n");
	    		break;
	    	case 35:
	    		fprintf(saida,"ENTRADA FONTE 6\n");
	    		break;
	    	default:
	    		break;
		}
	    for(m=0;m<7;m++){
	    	if(y[m] == -1)
	    		fprintf(saida,". ");
	    	else{
	    		letra = muda_para_letra(m);
	    		fprintf(saida,"%c ",letra);
	        }
	    }
	    fprintf(saida,"\n");
    }
    fprintf(saida,"\n\n\n");
}

void treina_perceptron(FILE* saida,int entradas[42][64],int alvo[7][7],int pesos[7][64], int chave){
	int y[7]; 
	int y_in[7];
	int epoca = 0;
	int i, j, k, l, m, n, z;
	int continua = 1;
	int altera;
	int c = 21;
	if (chave == 2)
		c = 42;
	while (continua == 1){
		altera = 0; 
		for(i=0;i<c;i++){
			k = seleciona_alvo(i);
			z = 0;
			while(z<7){
				y_in[z] = 0;
				z++;
			}
			for(j=0;j<7;j++){
				for(l=0;l<64;l++){
					y_in[j] = y_in[j] + entradas[i][l] * pesos[j][l];
						
				}
				y[j] = ativacao(y_in[j]);
				if (y[j] != alvo[k][j]){
					for(n=0;n<64;n++){
						pesos[j][n] = pesos[j][n] + ALFA * alvo[k][j] * entradas[i][n];
						altera++;
					}
				}			
			}		
	    }
		epoca++;
		if (altera == 0)
			continua = 0;		
	}
	fprintf(saida,"NUMERO DE EPOCA PARA TREINO = %d\n",epoca);
}

int main(){
	int valores_treino[42][64];
	int valores_classificacao[21][64];
	int alvos[7][7] = {{1,-1,-1,-1,-1,-1,-1},
						{-1,1,-1,-1,-1,-1,-1},
						{-1,-1,1,-1,-1,-1,-1},
						{-1,-1,-1,1,-1,-1,-1},
						{-1,-1,-1,-1,1,-1,-1},
						{-1,-1,-1,-1,-1,1,-1},
						{-1,-1,-1,-1,-1,-1,1}};
						
	int pesos[7][64];
	int d,e;	
	
	for(d=0;d<7;d++){
		for(e=0;e<64;e++)
			pesos[d][e] = 0;
    }
    
	FILE* entrada_treino = fopen("entrada_treino.txt","r");
	FILE* entrada_teste_classificacao = fopen("entrada_teste_classificacao.txt","r");
	FILE* entrada_novo_treino = fopen("entrada_novo_treino.txt","r");
	FILE* saida = fopen("saida.txt","w");
	
	for(d=0;d<21;d++){
		for(e=0;e<64;e++){
			if(e == 63){
				valores_treino[d][63] = 1;
				valores_classificacao[d][63] = 1;
		    }
			else{
				fscanf(entrada_treino,"%d",&valores_treino[d][e]);
				fscanf(entrada_teste_classificacao,"%d",&valores_classificacao[d][e]);
		    }
		}		
	}
	
	treina_perceptron(saida,valores_treino,alvos,pesos,1);
	verifica_perceptron(saida,valores_classificacao,alvos,pesos,1);
	
	for(d=0;d<42;d++){
		for(e=0;e<64;e++){
			if(e == 63)
				valores_treino[d][63] = 1;
			else
				fscanf(entrada_novo_treino,"%d",&valores_treino[d][e]);
		}		
	}
	
	for(d=0;d<7;d++){
		for(e=0;e<64;e++)
			pesos[d][e] = 0;
    }
	treina_perceptron(saida,valores_treino,alvos,pesos,2);
	verifica_perceptron(saida,valores_classificacao,alvos,pesos,2);
	
	printf("REDE TREINADA");
	
	close(entrada_treino);
	close(entrada_teste_classificacao);
	close(entrada_novo_treino);
	close(saida);
	return 0;
}
