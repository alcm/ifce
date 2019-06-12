#include "ordena.h"

/**************************MÉTODOS AUXILIARES**************************/
int *make_list(const unsigned int style){
	int *l = NULL, i;	

	l = (int *)malloc(sizeof(int)*f.list_size);
	if(l != NULL){		
		switch(style){
			case 1: 
				f.list_style = "Aleatorio";
				srand(time(NULL));
				for(i = 0; i < f.list_size; i++)
					l[i] = rand() % (10*f.list_size); 
      break;

			case 2: 
        f.list_style = "Crescente";
        for(i = 0; i < f.list_size; i++)
          l[i] = i;
        break;

			case 3: 
        f.list_style = "Decrescente";   
        for(i = 0; i < f.list_size; i++)
          l[i] = (f.list_size-i);
        break;
		}		
	}
	else
		fprintf(stderr, "Erro ao criar a lista!Pouca memória disponível.");

	return l;
}

void print(int *l){
	int i;
	
	for(i = 0; i < f.list_size; i++)
		printf("%d ", l[i]);
	puts("\n");
}

void generate_file(int *l, int size){
	int i, j, aux[f.list_size];	
	FILE *output_file = NULL;
	char buffer[10];

	output_file = fopen("saida.txt", "w");
	vectcpy(aux, l);
	if(output_file != NULL){	
		for(i = 0; i < size; i++){			
			f.p[i](l, 0, (f.list_size-1));					
			fputs(f.method_name, output_file);		
			fputs("\nAntes: ", output_file);	

			for(j = 0; j < f.list_size; j++){
				sprintf(buffer, "%d ", aux[j]);
				fputs(buffer, output_file);
				fputs(" ", output_file);
			}
			fputs("\nDepois: ", output_file);
	
			for(j = 0; j < f.list_size; j++){
				sprintf(buffer, "%d ", l[j]);
				fputs(buffer, output_file);
				fputs(" ", output_file);
			}
			fputs("\n\n", output_file);
			vectcpy(l, aux);	
			f.elapsed_time = 0;
			f.mov = 0;
			f.comp = 0;		
		}
		fclose(output_file);
	}
	else
		fprintf(stderr, "Erro ao criar o arquivo.");
}

void run(int *l){
	int aux[f.list_size], i, size;	
	clock_t t1, t2;		
	void (*m[12])(int *, int, int) = {shellsort, mergesort, countingsort, probabilistic_quicksort, deterministic_quicksort, heapsort,
																    bucketsort, cs_radixsort, flag_bubblesort, insertionsort, selectionsort, cocktailsort};	
	
	f.p = m;	
	size = (f.list_size > 50000)?((sizeof(m)/4)-4):(sizeof(m)/4);//Se a lista tiver mais de 50000 elementos, os ultimos 4 métodos do vetor 'm' não serão executados	
	if(f.list_size >= 100){		
		vectcpy(aux, l);//copia o vetor 'l' em 'aux' para ser recuperado no fim da execução do método	
		for(i = 0; i < size; i++){		
			t1 = clock();				
			f.p[i](l, 0, (f.list_size-1));//executa o método 'i' 		
			t2 = clock();
			#if defined(_WIN32) || defined(_WIN64)
      	f.elapsed_time = ((float)(t2-t1)); 
    	#else
      	f.elapsed_time = ((float)(t2-t1)/1000.0);
			#endif
    	printf("%s (%d - %s)\nComparações: %d Movimentações: %d Tempo: %f ms\n\n", f.method_name, f.list_size, f.list_style, f.comp, f.mov, f.elapsed_time);
			vectcpy(l, aux);//copiar o vetor em desordem para a proxima ordenação
			f.elapsed_time = 0;
			f.mov = 0;
			f.comp = 0;
		}
	}
	else
		generate_file(l, size);
}

void swap(int *n1, int *n2){
	int aux;

	aux = *n1;
	*n1 = *n2;
	*n2 = aux;
	f.mov++;
}

int get_bigger(int *l){
	int i, bigger = 0;

	for(i = 0; i < f.list_size; i++){		
		if(bigger < l[i])
			bigger = l[i];
	}

	return bigger;
}

void vectcpy(int *v1, int *v2){
	int i;

	for(i = 0; i < f.list_size; i++)
		v1[i] = v2[i];
}
/**************************MÉTODOS AUXILIARES**************************/



/******************************QUICKSORT*******************************/
int d_partition(int *l, int start_pos, int end_pos){
	int pivot = l[start_pos];
	int i = (start_pos+1), j = end_pos;

	while(i <= j){
		while((i <= j) && (l[i] <= pivot)){
			i++;
			f.comp++;
		}

		while(l[j] > pivot){
			j--;
			f.comp++;
		}

		if(i <= j){		
			swap(&l[i], &l[j]);
			i++;
			j--;
			f.comp++;	
			f.mov++;
		}
	}
	swap(&l[start_pos], &l[j]);
	f.comp++;
	f.mov++;

	return j;
}

void deterministic_quicksort(int *l, int start_pos, int end_pos){
	int j;

	f.method_name = "Quicksort deterministico";	
	if(start_pos < end_pos){
		j = d_partition(l, start_pos, end_pos);
		if(start_pos < (j-1)){
			deterministic_quicksort(l, start_pos, (j-1));
			f.comp++;
		}

		if((j+1) < end_pos){
			deterministic_quicksort(l, (j+1), end_pos);
			f.comp++;
		}
		f.comp++;
	}			
}

int r_partition(int *l, int start_pos, int end_pos){
  srand(time(NULL));
  int i = (start_pos-1), j, pivot, pivot_id;
    
  pivot_id = (start_pos+rand()%(end_pos-start_pos+1));//posição do pivo escolhida aleatoriamente
	pivot = l[pivot_id];
	swap(&l[pivot_id], &l[end_pos]); // troca o pivot com o ultimo elemento da lista
  pivot_id = end_pos; 
  for(j = start_pos; j <= (end_pos-1); j++){
    if(l[j] <= pivot){
      i++;
      swap(&l[i], &l[j]);
    }
  }
  swap(&l[i+1], &l[pivot_id]);
  
	return (i+1);
}
 
void probabilistic_quicksort(int *l, int start_pos, int end_pos){
	int j;  
	
	f.method_name = "Quicksort probabilistico";
	if(start_pos < end_pos){
		j = r_partition(l, start_pos, end_pos);
		if(start_pos < (j-1)){
			probabilistic_quicksort(l, start_pos, (j-1));
			f.comp++;
		}

		if((j+1) < end_pos){
			probabilistic_quicksort(l, (j+1), end_pos);
			f.comp++;
		}
		f.comp++;
	}			
}
/******************************QUICKSORT*******************************/



/******************************MERGESORT*******************************/
void merge(int *l, int start_pos, int middle, int end_pos){
	int i = start_pos, j = (middle+1), k = 0;
	int aux[end_pos];	

	while((i <= middle) && (j <= end_pos)){
		if(l[i] <= l[j])
			aux[k] = l[i++];
		else
			aux[k] = l[j++];
		k++;
		f.mov++;
		f.comp++;
	}
	if(i <= middle){		
		for(j = middle; j >= i; j--){
			l[end_pos-middle+j] = l[j];
			f.mov++; 		
		}
	}

	for(i = 0; i < k; i++){
		l[i+start_pos] = aux[i];
		f.mov++;
	} 
}

void mergesort(int *l, int start_pos, int end_pos){
	int middle;	
	
	f.method_name = "Mergesort";	
	if(start_pos < end_pos){
		middle = (start_pos+end_pos)/2;
		if(start_pos < middle)
			mergesort(l, start_pos, middle);

		if((middle+1) < end_pos)
			mergesort(l, (middle+1), end_pos);
		merge(l, start_pos, middle, end_pos);
	}
}
/******************************MERGESORT*******************************/



/******************************HEAPSORT********************************/
struct hbc_t *new_hbc(void){
	struct hbc_t *h = NULL;

	h = (struct hbc_t *)malloc(sizeof(struct hbc_t));
	h->heap_size = f.list_size;
	h->l = (int *)malloc(sizeof(int)*(h->heap_size+1));
	h->last_position = 0;	

	return h;
}

void insert_hbc(struct hbc_t *hbc, int item){
	int i;	

	if(hbc->heap_size == hbc->last_position)//se não existir posições disponíveis
		return;
		
	++hbc->last_position;
	i = hbc->last_position;
	while((i > 1) && (item < hbc->l[i/2])){
		hbc->l[i] = hbc->l[i/2];
		i = i/2;
		f.mov++;
	}
	hbc->l[i] = item;
}

void heapsort(int *l, int param1, int param2){
	struct hbc_t *h = NULL;
	int i;
	
	f.method_name = "Heapsort";
	h = new_hbc();
	if(h != NULL){
		for(i = 0; i < h->heap_size; i++)
			insert_hbc(h, l[i]);

		for(i = 0; i < h->heap_size; i++) 
			l[i] = remove_smallest(h);
	}
	else
		fprintf(stderr, "Erro.");
}

int remove_smallest(struct hbc_t *hbc){
	int value, i = 1, smallest;		

	if(hbc->last_position == 0)//o heap está vazio
		return -1;
	
	value = hbc->l[1];	
	hbc->l[1] = hbc->l[hbc->last_position];
	f.mov++;
	hbc->last_position--;//atualiza a ultima posição
	while(((2*i) <= hbc->last_position && hbc->l[i] > hbc->l[2*i]) || ((2*i) < hbc->last_position && hbc->l[i] > hbc->l[2*1+1])){
		smallest = (2*i);
		f.comp++;
		if((2*i) < hbc->last_position && hbc->l[2*i+1] <= hbc->l[2*i])
			smallest++;	
		swap(&hbc->l[i], &hbc->l[smallest]);
		i = smallest;
	}
	return value;
}		
/******************************HEAPSORT********************************/



/*****************************BUCKETSORT*******************************/
struct node_t *ll_insertionsort(struct node_t *list){	
	struct node_t *k = NULL, *node_list = NULL, *ptr = NULL, *tmp = NULL;
	
	if(list == NULL || list->next == NULL){//se a lista for vazia 
		return list; 
	}

	node_list = list; 
	k = list->next; 
	node_list->next = NULL; 
	while(k != NULL){	
		if(node_list->info > k->info){ 
			tmp = k;  
			k = k->next; 
			tmp->next = node_list;
			node_list = tmp; 
			continue;
		}

		for(ptr = node_list; ptr->next != NULL; ptr = ptr->next){
			if(ptr->next->info > k->info) 
			break;
		}

		if(ptr->next != NULL){  
			tmp = k;  
			k = k->next; 
			tmp->next = ptr->next;
			ptr->next = tmp; 
			continue;
		}
		else{
			ptr->next = k;  
			k = k->next;  
			ptr->next->next = NULL; 
			continue;
		}
	}

	return node_list;
}

void bucketsort(int *l, int param1, int param2){	
	int i, j, pos;
	struct node_t **buckets, *current = NULL, *node = NULL;  
	
	f.method_name = "Bucketsort";
	buckets = (struct node_t **)malloc(sizeof(struct node_t *)*f.list_size);///alocação de memória para os buckets  
	for(i = 0; i < f.list_size;++i){//inicialização dos buckets  
		buckets[i] = NULL;
		f.mov++;
	}

	for(i = 0; i < f.list_size; ++i){//colocando os valores em seus respectivos buckets 	
		pos = l[i]/f.list_size;
		current = (struct node_t *)malloc(sizeof(struct node_t));
		current->info = l[i]; 
		current->next = buckets[pos];  
		buckets[pos] = current;
		f.mov++;
	}

	for(i = 0; i < f.list_size; ++i)//ordenação dos buckets usando o insertionsort  
		buckets[i] = ll_insertionsort(buckets[i]); 

	for(j =0, i = 0; i < f.list_size; ++i){//colocando os valores no vetor original	
		node = buckets[i];
		while(node){
			l[j++] = node->info;
			node = node->next;
			f.mov++;
		}
	}
	free(buckets); 
}
/*****************************BUCKETSORT*******************************/

void cocktailsort(int *l, int param1, int param2){
  int bottom = 0, top = (f.list_size-1), swapped = 0, i;
    
	f.method_name = "Cocktailsort";  
	while((swapped == 0) && (bottom < top)){                                  
    swapped = 1; 
  	for(i = bottom; i < top; i++){
      if(l[i] > l[i + 1]) {   
        swap(&l[i], &l[i+1]);        
        swapped = 0;
				f.comp++;
        f.mov++;
      }
			f.comp++;
    }
    top--;

    for(i = top; i > bottom; i--){  
			if(l[i] < l[i-1]){
        swap(&l[i], &l[i-1]);
        swapped = 0;
				f.comp++;
        f.mov++;
      }
    } 
    bottom++;  
		f.comp++;
  } 
}

void insertionsort(int *l, int param1, int param2){
	int i = 1, j, pivot;
	
	f.method_name = "Inserção";	
	for(; i < f.list_size; i++){
		pivot = l[i]; 
		j = i-1;
		while((j >= 0) && (l[j] > pivot)){
		l[j+1] = l[j];
			j--;
			f.mov++;
			f.comp++;
		}
		l[j+1] = pivot;
		f.mov++;
		f.comp++;
	}
}

void flag_bubblesort(int *l, int param1, int param2){
	int i = 0, j, aux;
	bool flag;	
	
	f.method_name = "Bolha com flag";
	do{
		flag = false;
		for(j = 0; j < (f.list_size-1-i); j++){
			if(l[j] > l[j+1]){ 
			  swap(&l[j], &l[j+1]);
				flag = true;
			}	
			f.comp++;
		}
		i++;
	}
	while(flag == true);	
}

void selectionsort(int *l, int param1, int param2){
	int i, j, min, aux;
	
	f.method_name = "Seleção";
	for(i = 0; i < (f.list_size-1); i++){
		min = i;

		for(j = (i+1); j < f.list_size; j++){
			if(l[j] < l[min]){
   			min = j;
				f.comp++;	
			}
			f.comp++;
		}

		if(i != min){
			swap(&l[i], &l[min]);
			f.mov++;
		}		
		f.comp++;	
	}
}

void shellsort(int *l, int param1, int param2){
  int i, j, pivot, h = 1;

	f.method_name = "Shellsort";
	while(h < f.list_size)//calculo de 'h' sugerido por Donald Knuth
    h = 3*h + 1;
  do{
    h /= 3;
    for(i = h; i < f.list_size; i++) {//ordenação do vetor l por meio do método da inserção
      pivot = l[i];
      j = (i-h);
      while(j >= 0 && pivot < l[j]) {
        l[j+h] = l[j];
        j -= h;
				f.mov++;
				f.comp++;
      }
      l[j+h] = pivot;
			f.mov++;
			f.comp++;
    }
	}
	while(h > 1);
}

void cs_radixsort(int *l, int param1, int param2){
  int aux[f.list_size], aux2[f.list_size], l_aux[f.list_size], less_significatives[f.list_size], *c = NULL, k, digit, i;
	char buffer[100];

	f.method_name = "Radixsort + countingsort";
	vectcpy(l_aux, l);
	k = get_bigger(l);
	sprintf(buffer, "%d", k);//converte o maior número para uma string para sabermos a quantidade de casas decimais pelo método strlen
  for(digit = 1; digit <= strlen(buffer); digit++){             
    for(i = 0; i < f.list_size; i++){
      less_significatives[i] = (l_aux[i]%10);//o digito menos significativo da posição k são guardados em less_significatives.
      l_aux[i] = (l_aux[i]-less_significatives[i])/10;//os digitos mais significativos (que não foram selecionados) são guardados em l_aux.
    }           

    c = (int *)malloc(sizeof(int)*((get_bigger(less_significatives)+1)));
    for(i = 0; i <= get_bigger(less_significatives); i++){//inicialização do vetor c
      c[i] = 0;
			f.mov++;
		}

    for(i = 0; i < f.list_size; i++){//contagem das ocorrências 
      c[less_significatives[i]] = c[less_significatives[i]]+1;
			f.mov++;
		}

    for(i = 1; i <= get_bigger(less_significatives); i++){//soma acumulada
      c[i] = c[i]+c[i-1];
			f.mov++;
		}

    for(i = f.list_size-1; i >= 0; i--){//ordenação
      c[less_significatives[i]] = c[less_significatives[i]]-1; 
      aux[c[less_significatives[i]]] = l[i]; //o vetor aux para recebe esse elemento de l[i] na posição correta.
      aux2[c[less_significatives[i]]] = l_aux[i]; //o vetor aux2 recebe esse elemento de l_aux[i] na posição correta.
			f.mov++;
    }

    for(i = 0; i < f.list_size; i++){
      l[i] = aux[i]; 
      l_aux[i] = aux2[i]; 
			f.mov++;
    }            
  }
	free(c);
}  

void countingsort(int *l, int param1, int param2){
  int aux[f.list_size], i, k , *c = NULL;

	f.method_name = "Countingsort";	
	k = get_bigger(l);//maior elemento de l
	c = (int *)malloc(sizeof(int)*(k+1));	
	for(i = 0; i < (k+1); i++){//inicialização do vetor c
		c[i] = 0;
		f.mov++;
	}

	for(i = 0; i < f.list_size; i++){//contagem das ocorrências 	
		c[l[i]] = c[l[i]] + 1;
		f.mov++;	
	}

	for(i = 1; i < (k+1); i++){//soma acumulada
		c[i] = c[i] + c[i-1];
		f.mov++;
	}

	for(i = (f.list_size-1); i > -1; i--){//ordenação
		c[l[i]] = c[l[i]] - 1;
		aux[c[l[i]]] = l[i];
		f.mov++;
	}

	for(i = 0; i < f.list_size; i++){
		l[i] = aux[i];
		f.mov++;
	}
	free(c);
}

int main(int argc, char **argv){
	int *l = NULL, list_style;

	if(argc == 3){			
		f.list_size = atoi(argv[1]);
		list_style = atoi(argv[2]);		
		l = make_list(list_style);
		if(l != NULL){				
			run(l);			
			free(l);
		}
	}
	else
		printf("usage: %s [list_size] [list_style]\n", argv[0]);	
	
	#if defined(_WIN32) || defined(_WIN64)
		system("pause");
	#endif
}
