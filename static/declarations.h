typedef union{
	int *integer;
	char *character;
	float *real;
} metatype;

typedef struct {
	void *elements;
	char *type;
	int last_index;
	int size;
} queue;



void clear(void);
void pause(const char* string);
int type(queue *q, int size);
void start(queue *q);
void random_values(queue *q);
void rearrange(queue *q);
void rearrangeplus(queue *q);
void del(queue *q, int index);
int step(queue *q);
int generate(const char *message);
void new_element(queue *q, int index);
int insert(queue *q);
int search(queue *q, int num);
int erase(queue *q, int num);
int edit(queue *q, int index);
void print_list(queue *q);
void menu(queue *fila);