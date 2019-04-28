#include <stdio.h>
#include <stdlib.h>

struct Node
{
    void *key;
    struct Node *next;
    struct Node *prev;
};

struct List
{
    size_t size;
    struct Node *head;
    struct Node *tail;
};

struct List* create_List();
void del_List(struct List *list);

void pushFront(struct List *list, void *key);
void* popFront(struct List *list);
void pushBack(struct List *list, void *key);
void* popBack(struct List *list);

struct Node* get_N_elem(struct List *list, size_t index);
void* del_N_elem(struct List *list, size_t index);

void insert(struct List *list, size_t index, void *key);

void print_List(struct List *list, void (*print)(void*));
void print_int(void *key);
struct List* make_from_mass(void *mass, size_t n, size_t i);

void sort(struct List *list, size_t n);



int main()
{
	struct List *list = create_List();
	struct List *ll;
	
	int mass[] = {9, 3, 4, 8, 7};
    int num1_pf, num2_pf, num3_pf, num4_pb, num5_pb, num6_pb, num7_ins;
    
    num1_pf = 120;
    num2_pf = 201;
    num3_pf = 303;
    num4_pb = 430;
    num5_pb = 5670;
    num6_pb = 960;
    num7_ins = 470;
    
    pushFront(list, &num1_pf);
    pushFront(list, &num2_pf);
    pushFront(list, &num3_pf);
    pushBack(list, &num4_pb);
    pushBack(list, &num5_pb);
    pushBack(list, &num6_pb);
    pushFront(list, &num5_pb);
    pushFront(list, &num4_pb);
    
    printf("result after pushing: ");
    print_List(list, print_int);
    
    printf("current length: %d\n", list->size);
    printf("current 3th elem: %d\n", *((int*)(get_N_elem(list, 3))->key));
    printf("current 4th elem: %d\n", *((int*)(get_N_elem(list, 4))->key));
    printf("result popFront: %d\n", *((int*)popFront(list)));
    printf("result popFront: %d\n", *((int*)popFront(list)));
    printf("current head: %d\n", *((int*)(list->head->key)));
    printf("current tail: %d\n", *((int*)(list->tail->key)));
    printf("result popBack: %d\n", *((int*)popBack(list)));
    printf("result popBack: %d\n", *((int*)popBack(list)));
    printf("current length: %d\n", list->size);
    
    printf("current list: ");
    print_List(list, print_int);
    insert(list, 1, &num7_ins);
    printf("insert result: ");
    print_List(list, print_int);
    printf("del_N_elem result: ");
    del_N_elem(list, 0);
    print_List(list, print_int);
    
    ll = make_from_mass(mass, 5, sizeof(int));
    printf("make_from_mass result: ");
    print_List(ll, print_int);
    
    
    printf("result sort: ");
    sort(ll, ll->size);
    print_List(ll, print_int);
    printf("\n");
    
    del_List(ll);
    del_List(list);
    
	return 0;
}

struct List* create_List()
{
	struct List* list = (struct List*)malloc(sizeof(struct List));
	list->head = list->tail = NULL;
	list->size = 0;
	
	return list;
}

void del_List(struct List *list)
{
	struct Node *val = list->head;
	struct Node *next_val = NULL;
	
	while (val)
	{
		next_val = val->next;
		free(val);
		val = next_val;
	}
	free(list);
	list = NULL;
}

void pushFront(struct List *list, void *key)
{
	struct Node *val = (struct Node*)malloc(sizeof(struct Node));
	
	if (val == NULL)
	{
		printf("pushFront Error!\n");
	}
	
	val->key = key;
	val->next = list->head;
	val->prev = NULL;
	
	if (list->head)
	{
		list->head->prev = val;
	}
	
	list->head = val;
	
	if (list->tail == NULL)
	{
		list->tail = val;
	}
	
	list->size++;
}

void* popFront(struct List *list)
{
	struct Node *prev;
	void *val;
	
	if (list->head == NULL)
	{
		printf("popFront Eror!\n");
	}
	
	prev = list->head;
	list->head = list->head->next;
	
	if (list->head)
	{
		list->head->prev = NULL;
	}
	
	if (prev == list->tail)
	{
		list->tail = NULL;
	}
	
	val = prev->key;
	free(prev);
	
	list->size--;
	
	return val;
}

void pushBack(struct List *list, void *key)
{
	struct Node *val = (struct Node*)malloc(sizeof(struct Node));
	
	if (val == NULL)
	{
		printf("pushBack Eror!\n");
	}
	
	val->key = key;
	val->prev = list->tail;
	val->next = NULL;
	
	if (list->tail)
	{
		list->tail->next = val;
	}
	
	list->tail = val;
	
	if (list->head == NULL)
	{
		list->head = val;
	}
	
	list->size++;
}

void* popBack(struct List *list)
{
	struct Node *next_val;
	void *key;
	
	if (list->tail == NULL)
	{
		printf("popBack Eror!\n");
	}
	
	next_val = list->tail;
	list->tail = list->tail->prev;
	
	if (list->tail)
	{
		list->tail->next = NULL;
	}
	
	if (next_val == list->head)
	{
		list->head = NULL;
	}
	
	key = next_val->key;
	free(next_val);
	
	list->size--;
	
	return key;
}

struct Node* get_N_elem(struct List *list, size_t index)
{
	struct Node *val = list->head;
	size_t i = 0;
	
	while (i < index)
	{
		val = val->next;
		i++;	
	}
	
	return val;
}

void* del_N_elem(struct List *list, size_t index)
{
	struct Node *val = NULL;
	void *key = NULL;
	
	val = get_N_elem(list, index);
	
	if (val == NULL)
	{
		printf("del_N_elem Eror!\n");
	}
	
	if (val->prev)
	{
		val->prev->next = val->next;
	}
	
	if (val->next)
	{
		val->next->prev = val->prev;
	}
	
	if (val->next == NULL)
	{
		list->tail = val->prev;
	}
	
	if (val->prev == NULL)
	{
		list->head = val->next;
	}
	
	free(val);
	
	list->size--;
	
	return key;
}

void insert(struct List *list, size_t index, void *key)
{
	struct Node *val = NULL;
	struct Node *neew = NULL;
	
	val = get_N_elem(list, index);
	
	if (val == NULL)
	{
		printf("insert Eror!\n");
	//	printf("%d\n", list->size);
	}
	
	neew = (struct Node*)malloc(sizeof(struct Node));
	neew->key = key;
	neew->prev = val;
	neew->next = val->next;
	
	if (val->next)
	{
		val->next->prev = neew;
	}
	
	val->next = neew;
	
	if (val->prev == NULL)
	{
		list->head = val;
	}
	
	if (val->next == NULL)
	{
		list->tail = val;
	}
	
	list->size++;
}

void print_List(struct List *list, void (*print)(void*))
{
	struct Node *val = list->head;
	
	while (val)
	{
		print(val->key);
		val = val->next;
	}
	printf("\n");
}

void print_int(void *key)
{
	printf("%d ", *((int*)key));
}

struct List* make_from_mass(void *mass, size_t n, size_t size)
{
	struct List *list = NULL;
	size_t i = 0;
	
	if (mass == NULL)
	{
		printf("make_from_mass Eror!");	
	}
	
	list = create_List();
	
	while (i < n)
	{
		pushBack(list, ((char*)mass + i * size));
		i++;
		list->size++;
	}
	
	return list;
}

void sort(struct List *list, size_t n)
{
	struct Node *cur = list->head;
	void* elem;
	
	size_t i = 0;
	size_t j = 0;
	
	
	while (i < n + 1)
	{
		while (j < n + 1)
		{
			if (cur->next)
			{
				if (*((int *)cur->key) > *((int *)cur->next->key))
				{
					elem = cur->key;
					cur->key = cur->next->key;
					cur->next->key = elem;
					
					cur = cur->next;
				}
			}
			j++;
		}
		i++;
	}
}
