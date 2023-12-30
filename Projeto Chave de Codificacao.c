// Projeto: Chave de Codifica��o;
// Aluno: Lucas Azevedo da Silva;
// Mat�ria: Programa��o Estruturada;

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <ctype.h>
#define lim 300

struct frase{
	char fraseOrig[lim], fraseCod[lim], **arrayDecod;
};

void imprimirArray(struct frase frases, int a){ // Fun��o para imprimir a matriz da chave de codifica��o.
	int i;
	
	printf(" --- Decodificador ---\n\n");
	printf(" Frase original: %s", frases.fraseOrig);
	printf(" Frase codificada: %s \n", frases.fraseCod);
		
	
	printf(" --- Chave de Codifica��o ---\n\n");
	for(i = 0; i < a; i++){
		printf("	   %c -> ", frases.arrayDecod[0][i]);
		printf("%c \n", frases.arrayDecod[1][i]);
	}
}

void alocarArray(struct frase frases, int a){ // Aloca��o din�mica da matriz, chamada sempre que um novo par de caracteres for gerado.
	int i;
	for(i = 0; i < 2; i++){
		frases.arrayDecod[i] = (char*) realloc(frases.arrayDecod[i], (a + 1) * sizeof(char));
		if(frases.arrayDecod[i] == NULL){
			exit(3);
		}
	}
}

void ordenarArray(struct frase frases, int i, int j, int a, int b){
	//Algoritmo bubble sort: organiza os elementos em ordem alfab�tica de uma coluna, comparando-os em pares adjacentes at� que todos estejam ordenados.
	// i = 1� incremento; j = somador (caso necess�rio); a = 1� posi��o; b = 2� posi��o (caso necess�rio);	
	char temp;
	temp = frases.arrayDecod[a][i];
	frases.arrayDecod[a][i] = frases.arrayDecod[b][i +  j];
	frases.arrayDecod[b][i + j] = temp;
}

void organizarArray(struct frase frases, int a){ // Ordena os caracteres da chave de codifica��o alfabeticamente de cada linha.
	int i, j;
	
	for(i = 0; i < a; i++){
		if(frases.arrayDecod[0][i] > frases.arrayDecod[1][i]){
			ordenarArray(frases, i, 0, 0, 1);
		}
	}
	
	for(i = 0; i < a; i++){
		for(j = 0; j < a - i - 1; j++){
			if(frases.arrayDecod[0][j] > frases.arrayDecod[0][j + 1]){
				ordenarArray(frases, j, 1, 0, 0);
				ordenarArray(frases, j, 1, 1, 1);	
			}
		}
	}
}

void buscarChar(struct frase frases, int a, int *index){ // Fun��o que verifica as condi��es para o armazenamento dos caracteres na matriz final.
	 int i, j, contArray;
	 
	 for(i = 0; i < a; i++){
	 	contArray = 0;
	 	if(frases.fraseOrig[i] != frases.fraseCod[i]){
		 	for(j = 0; j < i; j++){
		 		
				// Comparar se o caracter j� n�o est� inserido mais de uma vez na string, para impedir repeti��es na chave de codifica��o.
				
		 		if(frases.fraseOrig[i] == frases.fraseOrig[j] && i != j || frases.fraseOrig[i] == frases.fraseCod[j] && frases.fraseCod[i] == frases.fraseOrig[j]){
		 			contArray++;
		 				
		 			if(contArray > 0){
		 				break;
					}
				}
			}
			
			if(contArray == 0 && !isspace(frases.fraseOrig[i]) && !ispunct(frases.fraseOrig[i])){ // If para impedir entrada de caracteres de pontua��o e backspaces.
				alocarArray(frases, *index);
				frases.arrayDecod[0][*index] = frases.fraseCod[i];
				frases.arrayDecod[1][*index] = frases.fraseOrig[i];
				(*index)++;
			}
		}
	}
}

void verificarTam(struct frase frases, int *teste){ // Fun��o que retorna verdadeiro caso ambas strings possuam a mesma quantidade de caracteres.
	*teste = strlen(frases.fraseCod) == strlen(frases.fraseOrig) ? 1 : 0;
	*teste == 0 ? printf(" Frases com tamanhos diferentes! Insira novamente.\n\n") : 1;
}

int main(){
	struct frase frases;
	int teste = 0, tamFrase, cont = 0, i;
	
	setlocale(LC_ALL, "Portuguese");

	frases.arrayDecod = (char**) calloc(2, sizeof(char*)); // Aloca��o din�mica da matriz da chave 
	if(frases.arrayDecod == NULL){
		exit(1);
	}

	while(teste == 0){
		printf(" --- Decodificador ---\n\n");
		
		printf(" Insira uma frase: "); // Entrada de dados da frase padr�o;
		fgets(frases.fraseOrig, lim, stdin);
		
		printf(" Insira a frase codificada: "); // Entrada de dados da frase codificada;
		fgets(frases.fraseCod, lim, stdin);
		
		system("cls");
		verificarTam(frases, &teste); // Verifica��o se ambas strings possuem o mesmo tamanho.
	}
	tamFrase = strlen(frases.fraseOrig) - 1; // Armazena o tamanho da string.
	for(i = 0; i < tamFrase; i++){
			frases.fraseOrig[i] = toupper(frases.fraseOrig[i]); // Torna todos os caracteres da string em caixa alta.
			frases.fraseCod[i] = toupper(frases.fraseCod[i]);
	}
	
	buscarChar(frases, tamFrase, &cont);
	organizarArray(frases, cont);
	imprimirArray(frases, cont);
	
	for(i = 0; i < 2; i++){ // Libera��o de mem�ria.
		free(frases.arrayDecod[i]);
	}
	free(frases.arrayDecod);
	
	return 0;
}
