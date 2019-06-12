#ifndef ORDENA_H
#define ORDENA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

struct order_t{
	void (**p)(int *, int, int);
	char *list_style;
	char *method_name;		
	unsigned int list_size;
	unsigned long int comp;
	unsigned long int mov;
	float elapsed_time;
};

/************************************************************************
order_t: estrutura que contém os dados da ordenação.

@p: ponteiro para um array que irá conter os métodos de ordenação.
@list_style: estilo da lista (aleatória, crescente ou decrescente).
@method_name: nome do método em execução.
@list_size: tamanho do vetor.
@comp: quantidade de comparações do método de ordenação executado.
@mov: quantidade de movimentações do método de ordenação executado.
@elapsed_time: tempo decorrido do método de ordenação em executado.
*************************************************************************/

struct node_t{
  struct node_t *next;
  int info;
};

/************************************************************************
node_t: estrutura que será utilizada na construção das listas ligadas.

@next: ponteiro para o proximo elemento da lista.
@info: dado contido em cada nó da lista.
*************************************************************************/

struct hbc_t{
	int *l;
	int heap_size;
	int last_position;
};

/************************************************************************
hbc_t: estrutura que será utilizada na construção do heap binário crescente.

@l:vetor do heap.
@heap_size: tamanho do heap.
@last_position: última posição da estrutura.
*************************************************************************/

struct order_t f;

int *make_list(const unsigned int style);
/************************************************************************
make_list: Gera um vetor de inteiros de acordos com as especificações.

@style: estilo da lista (1 = aleatório, etc...). 
@return: endereço do primeiro elemento do vetor preenchido.
*************************************************************************/

void swap(int *n1, int *n2);
/************************************************************************
swap: realiza a troca dos conteúdos apontados por n1 e n2.

@n1 = endereço do elemento 1.
@n2 = endereço do elemento 2. 
@return: ---
*************************************************************************/

void vectcpy(int *v1, int *v2);
/************************************************************************
vectcpy: realiza uma copia do vetor v2 em v1.

@v1: vetor vazio que recebera o conteúdo de v2.
@v2: vetor a ser copiado.
@return: ---
*************************************************************************/

void run(int *l);
/************************************************************************
run: executa os métodos de ordenação, contagem de tempo, etc...

@l: contém o endereço do primeiro elemento do vetor a ser ordenado
@return: ---
*************************************************************************/

void merge(int *l, int start_pos, int middle, int end_pos);
/************************************************************************
merge.

@l: vetor em possível desordem.
@start_pos: posição inicial do vetor l.
@middle: posição do meio do vetor l.
@end_pos: posição final do vetor l.
@return: ---
*************************************************************************/

int d_partition(int *l, int start_pos, int end_pos);
/************************************************************************
d_partition: partição determinística.

@l: vetor l.
@start_pos: posição inicial de l.
@end_pos: última posição de l.
@return: partição.
*************************************************************************/

int r_partition(int *l, int start_pos, int end_pos);
/************************************************************************
r_partition: partição probabilística.

@l: vetor l.
@start_pos: posição inicial de l.
@end_pos: última posição de l.
@return: partição
*************************************************************************/

void insert_hbc(struct hbc_t *hbc, int item);
/************************************************************************
insert_hbc: insere novo dado no heap.

@hbc: heap binário crescente.
@item: valor a ser colocado no heap
@return: ---
*************************************************************************/

int remove_smallest(struct hbc_t *hbc);
/************************************************************************
remove_smallest: remove o menor elemento do heap

@hbc: heap binário crescente
@return: menor elemento do heap.
*************************************************************************/

struct hbc_t *new_hbc(void);
/************************************************************************
new_hbc: constrói novo hbc

@return: novo hbc.
*************************************************************************/

void generate_file(int *l, int size);
/************************************************************************
generate_file: ordena o vetor para o caso de size < 100 e gera o arquivo
contendo o vetor l antes e após a execução de cada método de ordenação.

@l: vetor em possível desordem.
@size: quantidade de métodos a serem executados.
@return: ---
*************************************************************************/

struct node_t *ll_insertionsort(struct node_t *list);
/************************************************************************
ll_insertionsort: método de ordenação insertionsort adaptado para listas
ligadas.

@list: lista a ser ordenada.
@return: lista ordenada.
*************************************************************************/

void cs_radixsort(int *l, int param1, int param2);
/************************************************************************
cs_radixsort (radixsort + countingsort).

@l: vetor em possível desordem.
@param1: não utilizado.
@param2: não utilizado.
@return: ---
*************************************************************************/

void bucketsort(int *l, int param1, int param2);
/************************************************************************
bucketsort(utilizando o insertionsort como rótina de ordenação).

@l: vetor em possível desordem.
@param1: não utilizado.
@param2: não utilizado.
@return: ---
*************************************************************************/

void heapsort(int *l, int param1, int param2);
/************************************************************************
heapsort.

@l: vetor em possível desordem.
@param1: não utilizado.
@param2: não utilizado.
@return: ---
*************************************************************************/

void insertionsort(int *l, int param1, int param2);
/************************************************************************
insertionsort.

@l: vetor em possível desordem.
@param1: não utilizado.
@param2: não utilizado.
@return: ---
*************************************************************************/

void flag_bubblesort(int *l, int param1, int param2);
/************************************************************************
flag_bubblesort.

@l: vetor em possível desordem.
@param1: não utilizado.
@param2: não utilizado.
@return: ---
*************************************************************************/

void selectionsort(int *l, int param1, int param2);
/************************************************************************
selectionsort.

@l: vetor em possível desordem.
@param1: não utilizado.
@param2: não utilizado.
@return: ---
*************************************************************************/

void shellsort(int *l, int param1, int param2);
/************************************************************************
shellsort.

@l: vetor em possível desordem.
@param1: não utilizado.
@param2: não utilizado.
@return: ---
*************************************************************************/

void mergesort(int *l, int start_pos, int end_pos);
/************************************************************************
mergesort.

@l: vetor em possível desordem.
@start_pos: posição inicial do vetor l.
@end_pos: posição final do vetor l.
@return: ---
*************************************************************************/

void countingsort(int *l, int param1, int param2);
/************************************************************************
counting_sort.

@l: vetor em possível desordem.
@param1: não utilizado.
@param2: não utilizado.
@return: ---
*************************************************************************/

void cocktailsort(int *l, int param1, int param2);
/************************************************************************
cocktailsort.

@l: vetor em possível desordem.
@param1: não utilizado.
@param2: não utilizado.
@return: ---
*************************************************************************/

void deterministic_quicksort(int *l, int start_pos, int end_pos);
/************************************************************************
deterministic_quicksort.

@l: vetor em possível desordem.
@start_pos: posição inicial do vetor l.
@end_pos: posição final do vetor l.
@return: ---
*************************************************************************/

void probabilistic_quicksort(int *l, int start_pos, int end_pos);
/************************************************************************
probabilistic_quicksort.

@l: vetor em possível desordem.
@start_pos: posição inicial do vetor l.
@end_pos: posição final do vetor l.
@return: ---
*************************************************************************/

#endif
