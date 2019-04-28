#include <stdio.h>
#include <stdlib.h>

/* хэш таблица для строк, хэш-функция возвращает сумму кодов-аски от строки*/

struct node
{
	struct node *next;
	char *data;
};

int hash(char *data)
{
	int i = 0;
	int res = 0;
	
	while (data[i])
	{
		res += data[i];
		i++;	
	}

	return res;
}

struct node* insertnode(char *data, struct node **hashTable)
{
	struct node *p, *p0;
	int bucket;
	
	bucket = hash(data);
	p = (struct node *)malloc(sizeof(struct node));
	p0 = hashTable[bucket];
	hashTable[bucket] = p;
	p->next = p0;
	p->data = data;
	
	return p;
}

void deletenode(char *data, struct node **hashTable)
{
	struct node *p0, *p;
	int bucket;
	p0 = 0;
	bucket = hash(data);
	p = hashTable[bucket];
	
	while (p && (p->data != data))
	{
		p0 = p;
		p = p->next;
	}
	
	if (!p) return;
	if (p0) p0->next = p->next;
	else hashTable[bucket] = p->next;
	free(p);
}

struct node *findnode(char *data, struct node **hashTable)
{
	struct node *p;
	p = hashTable[hash(data)];
	while (p && (p->data != data))
	{
		p = p->next;
	}
	
	return p;
}

int main()
{
	const int hashTableSize = 100;
	struct node **hashTable = (struct node**)malloc(hashTableSize * sizeof(struct node*));
	
//	printf("input hashTableSize");
//	scanf("%d", &hashTableSize);
	
	char sym[] = "!2";
	char symq[] = "2!";
	
	struct node *p = insertnode(sym, hashTable);
	struct node *p1 = insertnode(symq, hashTable);
	
	printf("%s + hash code:%d\n", p1->data, hash(symq));
	printf("%s + hash code:%d\n", p->data, hash(sym));
	
	printf("result of hash find\n");
	printf("%s\n", hashTable[hash(sym)]->data);
	printf("%s\n", hashTable[hash(symq)]->data);
	
	if (findnode("!2", hashTable))
	{
		printf("YES\n");
	}
	
	else 
	{
		printf("NO\n");
	}
	
	return 0;
}

