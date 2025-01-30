/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I		            **/
/**   EACH-USP - Segundo Semestre de 2024			                **/
/**								                                    **/
/**   Segundo Exercicio-Programa	                  			    **/
/**								                                    **/
/**   <Flavio Augusto Faustino de Caravlho>		  <15452444>   <94> **/
/**				                                   				    **/
/*********************************************************************/


#include <stdlib.h>
#include <stdio.h>

#define false 0
#define true 1

#define LETRAS 26

#define VALOR_a 97

typedef int bool;


/*
A estrutura NO foi projetada para armazenar os nos de nossa trie. Ela e composta por dois campos:
  - contador: valor numerico que indica quantas copias da respectiva palavra estao armazenadas;
  - filhos: campo do tipo ponteiro para ponteiros de NOs que tem por objetivo armazenar o endereco 
  do arranjo de filhos do respectivo no ou NULL se o no nao possuir filhos.
*/
typedef struct aux {
	int contador;
	struct aux** filhos;
} NO, * PONT;


/*
Funcao usada em testes da correcao automatica
   NAO APAGAR OU MODIFICAR 
*/
void print123(){

}


/*
Funcao que recebe como parametro o endereco da raiz de uma trie e realiza a inicializacao da estrutura. Isto e, 
atribui o valor 0 (zero) para o campo contador e o valor NULL para o campo filhos. */
void inicializar(PONT raiz){
	raiz->contador = 0;
	raiz->filhos = NULL;
}

/*
Funcao que aloca memoria para um novo no, inicializa seus campos (valor zero para contador e NULL para filhos) e 
retorna o endereco do novo no.
*/
PONT criarNo(){
	PONT novo = (PONT)malloc(sizeof(NO));
	novo->contador = 0;
	novo->filhos = NULL;
	return novo;
}


/*
Funcao recursiva que recebe o endereco de um no e retorna o numero de nos da trie a partir do no atual. 
Se a funcao for chamada a partir da raiz, retornara o numero total de nos na trie.
*/
int contarNos(PONT atual){
	if (!atual) return 0;
	int res = 1;
	int i;
	if (atual->filhos) 
		for (i=0;i<LETRAS;i++)
			if (atual->filhos[i])
				res += contarNos(atual->filhos[i]);
	return res;
}


/*
Funcao recursiva que recebe o endereco de um no e retorna o numero de arranjos de ponteiros para filhos da trie a 
partir do no atual, ou seja, retorna a quantidade de nos internos (nos que nao sao folha) da trie. Se a funcao for 
chamada a partir da raiz, retornara o numero total de arranjos na trie.
*/
int contarArranjos(PONT atual){
	if (!atual) return 0;
	int res = 0;
	int i;
	if (atual->filhos){
		res++; 
		for (i=0;i<LETRAS;i++)
			if (atual->filhos[i])
				res += contarArranjos(atual->filhos[i]);
	}
	return res;
}


/*
Funcao recursiva que recebe o endereco de um no e retorna o numero de palavras diferentes da trie a partir do no atual. 
Palavras diferentes significa que cada palavra sera contada uma unica vez. Se a funcao for chamada a partir da raiz, 
retornara o numero total de palavras diferentes na trie.
*/
int contarPalavrasDiferentes(PONT atual){
	if (!atual) return 0;
	int res = 0;
	if (atual->contador>0) res = 1;
	int i;
	if (atual->filhos) 
		for (i=0;i<LETRAS;i++)
			if (atual->filhos[i])
				res += contarPalavrasDiferentes(atual->filhos[i]);
	return res;
}



/*
Funcao recursiva que recebe o endereco de um no e retorna o numero de palavras da trie a partir do no atual. 
Uma palavra sera contada mais de uma vez, caso o campo contador seja maior do que 1. Se a funcao for chamada a 
partir da raiz, retornara o numero total de palavras na trie.
*/
int contarPalavras(PONT atual){
	if (!atual) return 0;
	int res = atual->contador;
	int i;
	if (atual->filhos) 
		for (i=0;i<LETRAS;i++)
			if (atual->filhos[i])
				res += contarPalavras(atual->filhos[i]);
	return res;
}



/*
Funcao recursiva que recebe o endereco de um no, o endereco de um arranjo de caracteres e a posicao da letra 
atual da palavra. Caso o no atual corresponda a letra final de uma palavra (contador maior que zero) imprime 
a palavra atual. Se o no atual possuir filhos, realiza uma chamada recursiva para cada um de seus filhos 
adicionando a letra correspondente ao seu filho no arranjo palavra.
*/
void exibirAux(PONT atual, char* palavra, int pos){
    if (!atual) return;
    if (atual->contador > 0){
        palavra[pos] = '\0'; // Termina a palavra corretamente
        printf("%3i %s [%i]\n", atual->contador, palavra, pos);
    }
    int i;
    if (atual->filhos) 
        for (i = 0; i < LETRAS; i++)
            if (atual->filhos[i]) {
                palavra[pos] = (char)(VALOR_a + i);
                exibirAux(atual->filhos[i], palavra, pos + 1);
            }
}



/*
Funcao que recebe o endereco da raiz de uma trie e o endereco de um arranjo de caracteres e imprime na tela, em 
ordem alfabetica, todas as palavras da trie (utilizando a funcao exibirAux). O arranjo de caracteres, chamado 
palavra, e usado para  compor cada palavra a partir da raiz e entao imprimir essas palavras.
*/
void exibir(PONT raiz, char* palavra){
	exibirAux(raiz, palavra, 0);
}



/*
Funcao que recebe o endereco do no raiz de uma trie (raiz), o endereco de um arranjo de caracteres (palavra) 
e o tamanho da palavra presente no arranjo de caracteres (n) e retorna o numero de copias dessa palavra na trie. 
Provavelmente voce desejara realizar a busca chamando uma funcao auxiliar recursiva (desenvolvida por voce) que 
tenha, ao menos, um parametro adicional para indicar qual a letra atual da busca. Caso a palavra nao exista na 
trie, sua funcao devera retornar 0 (zero), caso contrario, devera retornar o valor do campo contador do no 
correspondente a ultima letra da palavra.
*/
int quantiPalavra(PONT noAtual, char* palavra, int indi, int tamanho){
	if(!noAtual) return 0; //validacao da existencia do nó
	if(indi == tamanho) return noAtual->contador; //retorna a quantidade de vzs q a palavra foi digitada

	int indiLetra = palavra[indi] - 'a'; // calculo pra saber o indice da letra na trie
	if(indiLetra < 0 || indiLetra	> 25) return 0; // validacao da existencia do indice

	return quantiPalavra(noAtual->filhos[indiLetra], palavra, indi+1, tamanho);
}
int buscarPalavra(PONT raiz, char* palavra, int tamanho){
	if(!raiz || !palavra || tamanho < 1) return 0; //validacao

 	int resposta = quantiPalavra(raiz, palavra, 0, tamanho);
	return resposta;
}

/*
Funcao que recebe o endereco do no raiz de uma trie (raiz), o endereco de um arranjo de caracteres (palavra) e o 
tamanho da palavra presente no arranjo de caracteres (n) e insere essa palavra na trie. Provavelmente voce desejara 
realizar a insercao chamando uma funcao auxiliar recursiva (desenvolvida por voce) que tenha, ao menos, um parametro 
adicional para indicar qual a letra atual da chamada recursiva (assumindo que a cada chamada recursiva uma letra sera 
inserida/processada). Voce pode assumir que todos os parametros desta funcao terao valores validos e a palavra a ser inserida 
(presente no arranjo de caracteres) possuira apenas letras m e atribuir o endereco dele no campo filhos do no atual;
     (b) criar o no correspondente ao proximo caractere, acertar seus campos (se voce usar a funcao criarNo ela ja acerta 
     esses valores) e colocar o endereco dele na posicao correspondente do arranjo filhos; e
     (c) continuar recursivamente com o processo sendo que, se voce acabou de criar o ultimo caractere da palavra, o 
     campo contador deve receber o valor 1 e a insercao foi concluida.
  (ii) se ainda falta inserir caractere(s) e o no atual possui o arranjo de filhos: caso o no correspondente ao proximo 
  caractere ja exista no arranjo de filhos, basta prosseguir a insercao (recursivamente) a partir dele, caso contrario e 
  necessario prosseguir de acordo com o processo (i.b).
  (iii) se voce chegou ao ultimo caractere da palavra e ele ja existe na trie, e necessario incrementar seu campo contador em uma unidade.
*/

// Função auxiliar recursiva para inserção
void adicionarPalavra(PONT nodoAtual, char* termo, int posicao, int comprimento) {
    if (posicao == comprimento) { // Verifica se alcançou o final da palavra
        nodoAtual->contador++;   // Incrementa o contador (como na primeira função)
        return;
    }

    int indice = termo[posicao] - 'a'; // Determina o índice correspondente ao caractere atual

    // Garante que o array de filhos está alocado
    if (nodoAtual->filhos == NULL) {
        nodoAtual->filhos = (PONT*)malloc(LETRAS * sizeof(PONT)); // Aloca espaço para filhos
        for (int i = 0; i < LETRAS; i++) {
            nodoAtual->filhos[i] = NULL;  // Inicializa todos os filhos como NULL
        }
    }

    // Cria um novo nó, se necessário
    if (nodoAtual->filhos[indice] == NULL) {
        nodoAtual->filhos[indice] = criarNo(); // Cria um novo nó se não existir
    }

    // Chama recursivamente para o próximo caractere da palavra
    adicionarPalavra(nodoAtual->filhos[indice], termo, posicao + 1, comprimento);
}

// Função principal de inserção
void inserir(PONT raiz, char* palavra, int n) {
    adicionarPalavra(raiz, palavra, 0, n); // Inicia a inserção recursiva
}


/*
Funcao que recebe o endereco do no raiz de uma trie (raiz), o endereco de um arranjo de caracteres (palavra) e o 
tamanho da palavra presente no arranjo de caracteres (n) e exclui todas as copias dessa palavra da trie. Provavelmente 
voce desejara realizar a exclusao chamando uma funcao auxiliar recursiva (desenvolvida por voce) que tenha, ao menos,
um parametro adicional para indicar qual a letra atual da chamada recursiva (assumindo que cada chamada recursiva 
avancara uma letra na arvore). Adicionalmente, se a operacao de exclusao resultar na eliminacao de um no, pode ser 
necessario, recursivamente, apagar alguns dos nos anteriores, neste caso, voce pode precisar de mais um parametro 
adicional na sua funcao auxiliar recursiva ou ela pode ter um retorno (potencialmente booleano) para indicar que e 
necessario excluir nos na volta da chamada recursiva. Voce pode assumir que todos os parametros desta funcao terao 
valores validos e a palavra a ser excluida (presente no arranjo de caracteres) possuira apenas letras minusculas 
(sem acentos ou caracteres especiais). E possivel que a palavra nao exista na sua trie, entao a funcao de exclusao 
nao causara nenhuma mudanca na trie. A exclusao funciona da seguinte forma (potencialmente recursiva):
 Voce navegara na trie, caractere a caractere, ate passar por toda a palavra, isto e, chegar no caractere final da palavra. 
 (i) Se isto nao for possivel, isto e, se a sequencia de caracteres que forma a palavra nao esta presente na trie, sua 
 funcao devera encerrar sem realizar nenhuma mudanca na estrutura; caso contrario, ha duas possibilidades principais:
 (ii) A palavra nao existe na trie (isto e, apesar de suas letras estarem la, o campo contador da ultima letra e igual 
 a zero), neste caso, sua funcao deve encerrar sem modificar a estrutura;    
 (iii) A palavra existe na trie, neste caso ela dever ser excluida, considerando duas situacoes:
    (a) O no correspondente a ultima letra possui filhos, neste caso o contador dele devera ser zerado e nao 
    ha mais nada a ser feito pela funcao; 
    (b) Caso o no correspondente a ultima letra nao possua filhos ele devera ser excluido, e o ponteiro para ele 
    no arranjo de filhos de seu pai deve ser atualizado para NULL. Se apos essa exclusao, o pai desse no nao 
    possuir mais filhos, seu arranjo de filhos deve ser excluido (memoria liberada) e seu campo filhos deve 
    receber o valor NULL. Adicionalmente, se o campo contador do no pai valer zero este tambem deve ser apagado 
    (e o processo iii.b deve ser repetido enquanto cada no [na volta da recursao] nao possuir mais filhos e nao 
    for um no final de uma palavra).
Observacao: o no raiz nunca devera ser excluido, porem seu arranjo de filhos podera ser excluido caso este no 
nao possua filhos (trie sem nenhuma palavra) e, neste caso, seu campo filhos devera ser atualizado para NULL.
*/
// Função auxiliar recursiva para excluir todas as cópias da palavra
bool del(PONT atual, char* palavra, int loc, int n) {
    // Verifica se chegou ao fim da palavra
    if (loc == n) {
        if (atual->contador > 0) {
            atual->contador = 0; // Zera o contador
            if (!atual->filhos) return true; // Retorna true se não houver mais filhos
        }
        return false;
    }

    int i = palavra[loc] - 'a'; // Calcula o índice do caractere atual
    if (!atual->filhos || !atual->filhos[i]) return false; // Verifica se o caminho existe

    // Chamada recursiva para o próximo caractere
    if (del(atual->filhos[i], palavra, loc + 1, n)) {
        // Libera o nó filho se a exclusão for confirmada
        free(atual->filhos[i]);
        atual->filhos[i] = NULL;

        // Verifica se ainda existem outros filhos
        for (int f = 0; f < LETRAS; f++) {
            if (atual->filhos[f] != NULL) return false;
        }

        // Libera o array de filhos e verifica se o nó atual pode ser removido
        free(atual->filhos);
        atual->filhos = NULL;
        return atual->contador == 0;
    }

    return false;
}


void excluirTodas(PONT raiz, char* palavra, int n) {
    del(raiz, palavra, 0, n);
}

/*
Funcao que recebe o endereco do no raiz de uma trie (raiz), o endereco de um arranjo de caracteres (palavra) 
e o tamanho da palavra presente no arranjo de caracteres (n) e exclui uma copia dessa palavra da trie (isto e,
caso a palavra exista na trie, diminui o contador correspondente a sua ultima letra em uma unidade). Observacoes: 
se a palavra nao existir na trie, nao ha nada a ser feito pela funcao; se a palavra existir e o contador valer 1 
(um) antes da exclusao, entao a exclusao tera o mesmo comportamento da funcao excluirTodas.
*/
bool del2(PONT noAtual, char* palavra, int indice, int comprimento) {
    // Caso base: chegou ao final da palavra
    if (indice == comprimento) {
        if (noAtual->contador > 0) {
            noAtual->contador -= 1; // Decrementa o contador
            // Retorna verdadeiro se não houver filhos e o contador for zero
            return noAtual->filhos == NULL && noAtual->contador == 0;
        }
        return false;
    }

    // Calcula o índice do caractere atual na palavra
    int posicao = palavra[indice] - 'a';

    // Verifica se o nó correspondente ao caractere atual existe
    if (noAtual->filhos == NULL || noAtual->filhos[posicao] == NULL) {
        return false;
    }

    // Continua a busca recursivamente pelo próximo caractere
    if (del2(noAtual->filhos[posicao], palavra, indice + 1, comprimento)) {
        // Libera o nó filho se ele puder ser removido
        free(noAtual->filhos[posicao]);
        noAtual->filhos[posicao] = NULL;

        // Verifica se ainda existem outros filhos
        for (int f = 0; f < 26; f++) {
            if (noAtual->filhos[f] != NULL) {
                return false;
            }
        }

        // Libera o array de filhos e verifica se o nó pode ser removido
        free(noAtual->filhos);
        noAtual->filhos = NULL;

        // Retorna verdadeiro apenas se o contador do nó for zero
        return noAtual->contador == 0;
    }

    return false;
}

void excluir(PONT raiz, char* palavra, int tamanho) {
    del2(raiz, palavra, 0, tamanho);
}




/*
Funcao main que realiza ALGUNS testes nas funcoes implementadas.
Seu EP sera avaliado utilizando um conjunto distinto de testes.
*/
int main(){
	NO raiz1;
	char* temp = (char*)malloc(sizeof(char) * 1025);
    if (!temp) {
        printf("Erro ao alocar memória para temp.\n");
        return -1;
    }

	printf("\n### Inicializacao.\n");
	inicializar(&raiz1);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));

	printf("\n### Primeiras insercoes.\n");
	inserir(&raiz1, "teste", 5);
	inserir(&raiz1, "teste", 5);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));

	printf("\n### Mais insercoes.\n");
	inserir(&raiz1, "testemunha", 10);
	inserir(&raiz1, "testemunhe", 10);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));	

	printf("\n### Mais insercoes.\n");
	inserir(&raiz1, "testa", 5);
	inserir(&raiz1, "testamento", 10);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));

	printf("\n### Exclusoes.\n");
	excluir(&raiz1, "teste", 5);
	excluir(&raiz1, "teste", 5);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));

	printf("\n### Mais exclusoes.\n");
	excluir(&raiz1, "teste", 5);
	excluir(&raiz1, "testemunha", 10);
	excluir(&raiz1, "testemunhe", 10);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));

	printf("\n### Mais insercoes.\n");
	inserir(&raiz1, "abacate", 7);
	inserir(&raiz1, "abacaxi", 7);
	inserir(&raiz1, "abacaxi", 7);
	inserir(&raiz1, "abacaxi", 7);
	inserir(&raiz1, "abobora", 7);
	inserir(&raiz1, "banana", 6);
	inserir(&raiz1, "caju", 4);
	inserir(&raiz1, "melancia", 8);
	inserir(&raiz1, "melao", 5);
	inserir(&raiz1, "abacaxi", 7);
	inserir(&raiz1, "melao", 5);
	inserir(&raiz1, "melao", 5);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));

	printf("\n### Exclusoes (excluir todas as copias).\n");
	excluirTodas(&raiz1, "teste", 5);
	excluirTodas(&raiz1, "abacaxi", 7);
	excluirTodas(&raiz1, "testa", 5);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));

	printf("\n### Buscas.\n");
	printf("Foram encontradas %i copia(s) da palavra 'testa'.\n",buscarPalavra(&raiz1, "testa", 5));
	printf("Foram encontradas %i copia(s) da palavra 'mel'.\n",buscarPalavra(&raiz1, "mel", 3));
	printf("Foram encontradas %i copia(s) da palavra 'melao'.\n",buscarPalavra(&raiz1, "melao", 5));
	printf("Foram encontradas %i copia(s) da palavra 'melancia'.\n",buscarPalavra(&raiz1, "melancia", 8));
	
	printf("\n### Exclusoes adicionais (eliminando cada uma das palavras restantes).\n");
	excluirTodas(&raiz1, "abacate", 7);
	excluirTodas(&raiz1, "abobora", 7);
	excluirTodas(&raiz1, "banana", 6);
	excluirTodas(&raiz1, "caju", 4);
	excluirTodas(&raiz1, "melancia", 8);
	excluirTodas(&raiz1, "melao", 5);
	excluirTodas(&raiz1, "testamento", 10);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));

	
	printf("\n### Repetindo primeiras insercoes.\n");
	inserir(&raiz1, "teste", 5);
	inserir(&raiz1, "teste", 5);
	exibir(&raiz1, temp);
	printf("Numero de nos: %i\n", contarNos(&raiz1));
	printf("Numero de arranjos: %i\n", contarArranjos(&raiz1));
	printf("Numero de palavras: %i\n", contarPalavras(&raiz1));
	printf("Numero de palavras diferentes: %i\n", contarPalavrasDiferentes(&raiz1));

	
    free(temp);
    
	return 0;
}