#include<stdio.h>
#include<stdlib.h>
#include "log.h"

struct Node
{
	struct Node *next;
	int data;
};

struct Node* new_node(int data)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->data = data;
	node->next = NULL;
	return node;
}
int is_empty(struct Node* root)
{
	return !root;	
}

int push(struct Node** root, int data)
{
	struct Node* node = new_node(data);
	node->next = *root;
	*root = node;
	printf("%d pushed to stack", data);	
}
int pop(struct Node** root)
{
	struct Node* temp = *root;
	*root = (*root)->next;
	int pop = temp->data;
	free(temp);

	return pop;
}
int peek(struct Node* root)
{
	return root->data;
}

int main();

int main()
{
	struct Node* head = (struct Node*)malloc(sizeof(struct Node));
	head->data = 10;
	push(&head, 20);
	printf("%d", peek(head));
	return 0;
}
