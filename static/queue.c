#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CLEAR "clear || cls"
#define SIZE 10
//metodos > insert, search, erase, edit


/**
 *
 *	Foi convencionado que o indice de totalmente vazio é -1, assim como também o espaço vazio.
 *
**/

typedef struct {
	int elements[SIZE];
	int last_index;
	int size;
} queue_struct;

//limpar stdin
void clear(void){
	char c;
	while((c = getchar()) != '\n' && c != EOF);
}
//recebe uma string, imprime e faz uma pausa até capturar alguma tecla.
void pause(const char* string){
	printf("%s", string);
	clear();
}


//iniciar queue
void start(queue_struct *queue){
	int i;
	//convenção>todas posições do vetor iniciam com -1 e seu índice também;
	queue->last_index = -1;
	for(i = 0; i < SIZE; i++)
		queue->elements[i] = -1;
}

void random_values(queue_struct *queue){
	int i;
	time_t t;
	srand((unsigned) time(&t));

	for(i = 0; i < SIZE; i++)
		queue->elements[i] = rand() % 100;
	queue->last_index = i;
}


//versão optimizada e mais simples
void rearrange(queue_struct *queue){
	//ignorando espaços vazios e rearrajando vetor
	int i, j;
	for(i = 0, j = 0; i < SIZE; i++){
		if (queue->elements[i] != -1){
			queue->elements[j] = queue->elements[i];
			j++;
		}
	}
	//atribuindo o resto do vetor como vazio
	for(i = j; i < SIZE; i++) queue->elements[i] = -1;

	queue->last_index = j - 1;
}

void del(queue_struct *queue, int index){
	queue->elements[index] = -1;
	rearrange(queue);
}


//step na queue
int step(queue_struct *queue){
	printf("Pop Head: %d\n", queue->elements[0]);
	

	if(queue->last_index == -1)
		return -1;
	else
		del(queue, 0);

	return 0;
}

int generate(const char *message){
	int num;
	puts(message);
	scanf("%d", &num);
	clear();

	return num;
}

void new_element(queue_struct *queue, int index){
	printf("Insert a value: ");
	scanf("%d", &queue->elements[index]);
	clear();
}

 
//insere um valor no final da queue;
int insert(queue_struct *queue){
	//se tiver cheia tal queue
	if (queue->last_index == SIZE -1)
		return -1;

	queue->last_index++;
	new_element(queue, queue->last_index);

	return 0;
}



int search(queue_struct *queue, int num){
	int i;
	
	for(i = 0; i < SIZE; i++)
		if(queue->elements[i] == num)
			return i;
	return -1;
}

int erase(queue_struct *queue, int num){
	int index = search(queue, num);

	if(index != -1)
		del(queue, index);
	else
		return -1;

	return index;
	
}

int edit(queue_struct *queue, int index){
	if(!(index >= 0 && index <= SIZE))
		return -1;

	new_element(queue, index);

	return 0;
}

void print_list(queue_struct *queue){
	//valores na queue:
	int i, value;
	printf("Queue: [ ");
	for(i = 0; i < SIZE; i++){
		value = queue->elements[i];
		if (value != -1)
			printf(" (%d) ", queue->elements[i]);
		else
			printf(" () ");
	}
	printf("]\n");
}

void menu(queue_struct *queue){
	int command, status, num_key;
	do{	
		system(CLEAR);
		puts("Implementation of type queue_struct in the class list!");
		printf("0.Exit\n1.Insert\n2.Step\n3.PrintVector\n4.Search\n5.Edit\n6.Erase\n7.Rearrange\n8.RandomValues\n\n");
		printf("Type a command: ");
		scanf("%d", &command);
		clear();
		switch(command){
			case 1:
				status = insert(queue);
				if (status == -1) puts("Full queue_struct!");
				break;
			case 2:
				status = step(queue);
				if (status == -1) puts("Empty queue_struct!");
				break;
			case 3:
				print_list(queue);
				break;
			case 4:
				num_key = generate("Search for: ");
				status = search(queue, num_key);
				if (status != -1)
					printf("Found element %d on position %d\n", num_key, status);
				else
					printf("Error 404: Not found!\n");
				break;
			case 5:
				num_key = generate("Edit value in index: ");
				status = edit(queue, num_key);
				if(status == -1)
					printf("Index out of the range!\n");
				break;
			case 6:
				num_key = generate("Erase element: ");
				status = erase(queue, num_key);
				if (status != -1)
					printf("Deleted element %d on position %d\n", num_key, status);
				else
					printf("Error 404: Not found!\n");
				break;
			case 7:
				rearrange(queue);
				break;
			case 8:
				random_values(queue);
				break;
			case 0:
				printf("Leaving the universe...\n");
				break;
			default:
				printf("Command invalid, try again.!\n");
				break;
		}
		pause("Press enter to continue...");
	}while(command != 0);
}

int main(void){
	queue_struct queue;
	start(&queue);
	menu(&queue);

	return 0;
}