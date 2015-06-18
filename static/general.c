#include <stdio.h>
#include <stdlib.h>

#define CLEAR "clear || cls"
#define SIZE 10
//metodos > insert, search, edit step
/*

Foi convencionado que o indice de totalmente vazio é -1, assim como também o espaço vazio.

*/
typedef struct {
	int elements[SIZE];
	int last_index;
} queue;

typedef struct {
	int elements[SIZE]
	int last_index;
} stack;

typedef struct {
	int elements[SIZE]
	int first_index, last_index;
} deque;

typedef union {
	queue q;
	stack s;
	deque d;
} data_struct;

//limpar stdin
void clear(void){
	char c;
	while((c = getchar()) != '\n' && c != EOF);
}
//recebe uma string, imprime e pausa
void pause(const char* string){
	puts(string);
	clear();
}


//iniciar fila
void start(queue *q){
	int i;
	//convenção>todas posições do vetor iniciam com -1 e seu índice também;
	q->last_index = -1;
	for(i = 0; i < SIZE; i++)
		q->elements[i] = -1;
}


/*
 *Modo complicado, modo inicial. Não funciona quando houver mais de um segmento
 *
 *
 *Ex funcional ->[-1, -1, -1, 3, 5, -1, 1] -> [3, 5, -1, -1, -1, -1, -1]
 *Ex não-funcional -> [30, -1, -1, 40, -1, 20] -> [30, -1, -1, -1, -1, -1] (rearranjamento incorreto)
 *
 */
//obsoleta
void rearrange(queue *q){

	//comportamento misterioso, output limits: [1, 10] | [0, 9]
	// pega o limite esquerdo¸ex.: [-1, -1, 3, 4, -1, -1] indice 2 
	int limit_left = 0;
	while(q->elements[limit_left] ==  -1) limit_left++;
	
	// pega o limite direito¸ex.: [-1, -1, 3, 4, -1, -1] indice 3
	int limit_right = limit_left;
	while(q->elements[limit_right] != -1 && limit_right < SIZE - 1) limit_right++;

	//tamanho da faixa 
	int range = limit_right - limit_left;


	//debug: :-> print_list limites de rearrajamento
	printf("Limites:[%d, %d)\n", limit_left, limit_right);

	//deslocamento
	//preencher inicio
	int i;
	for(i = 0; i <= range; i++)
		q->elements[i] = q->elements[limit_left + i];
	
	//verificar se restará cabeça vazia ou não
	int rest;
	if(range == 0)
		rest = 0;
	else
		rest = i;

	//preencher final
	for(i = rest; i < SIZE; i++)
		q->elements[i] = -1;

	//definindo nova cauda
	q->last_index = range -1;
 
}

//versão optimizada e mais simples
void rearrangeplus(queue *q){
	//ignorando espaços vazios e rearrajando vetor
	int i, j;
	for(i = 0, j = 0; i < SIZE; i++){
		if (q->elements[i] != -1){
			q->elements[j] = q->elements[i];
			j++;
		}
	}
	//atribuindo o resto do vetor como vazio
	for(i = j; i < SIZE; i++) q->elements[i] = -1;

	q->last_index = j - 1;
}

void del(queue *q, int index){
	q->elements[index] = -1;
	rearrange(q);
}


//step na fila
int step(queue *q){
	printf("Cauda: %d\n", q->elements[0]);
	

	if(q->last_index == -1)
		return -1;
	else
		del(q, 0);

	return 0;
}

int generate(const char *message){
	int num;
	puts(message);
	scanf("%d", &num);
	clear();

	return num;
}

void new_element(queue *q, int index){
	printf("Insira um valor: ");
	scanf("%d", &q->elements[index]);
	clear();
}

 
//insere um valor no final da fila;
int insert(queue *q){
	//se tiver cheia tal fila
	if (q->last_index == SIZE -1)
		return -1;

	q->last_index++;
	new_element(q, q->last_index);

	return 0;
}



int search(queue *q, int num){
	int i;
	
	for(i = 0; i < SIZE; i++)
		if(q->elements[i] == num)
			return i;
	return -1;
}

int erase(queue *q, int num){
	int index = search(q, num);

	if(index != -1)
		del(q, index);
	else
		return -1;

	return 0;
	
}

int edit(queue *q, int index){
	if(!(index >= 0 && index <= SIZE))
		return -1;

	new_element(q, index);

	return 0;
}

void print_list(queue *q){
	//valores na fila:
	int i, value;
	printf("Fila: [ ");
	for(i = 0; i < SIZE; i++){
		value = q->elements[i];
		if (value != -1)
			printf(" (%d) ", q->elements[i]);
		else
			printf(" () ");
	}
	printf("]\n");
}

void menu(queue *fila){
	int command, status, num_key;
	do{	
		system(CLEAR);
		puts("Implementation of type queue in the class list!");
		printf("0.Exit\n1.Insert\n2.Step\n3.PrintVector\n4.Search\n5.Edit\n6.Erase\n7.Rearrange+\n\n");
		printf("Digite um comando:");
		scanf("%d", &command);
		clear();
		switch(command){
			case 1:
				status = insert(fila);
				if (status == -1) puts("Fila cheia!");
				break;
			case 2:
				status = step(fila);
				if (status == -1) puts("Fila vazia!");
				break;
			case 3:
				print_list(fila);
				break;
			case 4:
				num_key = generate("Pesquisar: ");
				status = search(fila, num_key);
				if (status != -1)
					printf("Encontrado elemento %d na posição %d\n", num_key, status);
				else
					printf("Não encontrado!\n");
				break;
			case 5:
				num_key = generate("Alterar(indice): ");
				status = edit(fila, num_key);
				if(status == -1)
					printf("Não encontrado!\n");
				break;
			case 6:
				num_key = generate("Apagar: ");
				status = erase(fila, num_key);
				if (status != -1)
					printf("Apagado elemento %d na posição %d\n", num_key, status);
				else
					printf("Não encontrado!\n");
				break;
			case 7:
				rearrangeplus(fila);
				break;
			case 0:
				printf("Saindo do programa...\n");
				break;
			default:
				printf("Comando inválido tente novamente!\n");
				break;
		}
		pause("Pressione enter para continuar...\n");
	}while(command != 0);
}

int main(void){
	queue fila;
	
	start(&fila);
	menu(&fila);

	return 0;
}