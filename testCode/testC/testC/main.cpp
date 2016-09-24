#include <stdio.h>
#include <stdlib.h>

// Queue
typedef struct Node
{
	int data;
	struct Node *left, *right;
} Node;

// Node structure
typedef struct node
{
	Node * nodeptr;
	struct node * nextNode;
} ListNode;



// Insert 
void insert(Node **rootptr, int value)
{
	Node *temp;
	if (*rootptr == NULL)
	{
		temp = (Node*)malloc(sizeof(Node));
		temp->data = value;
		temp->left = temp->right = NULL;
		*rootptr = temp;
	}
	else if ((*rootptr)->data < value)
	{
		insert(&((*rootptr)->right), value);
	}

	else if ((*rootptr)->data > value)
	{
		insert(&((*rootptr)->left), value);
	} 
}
// Inoreder Successor
int inorders(Node *traverse)
{ 
	while (traverse->left)
	{
		traverse = traverse->left;
	}
	return traverse->data;

}
// DeleteNode
void deleteNode(Node **rootptr, int value)
{
	Node *temp;
	int i;
	if (*rootptr == NULL)
	{
		printf("tanay does not exist");
	}
	else if ( (*rootptr)->data < value)
	{
		deleteNode(&((*rootptr)->right), value);
	}

	else if ((*rootptr)->data > value)
	{
		deleteNode( &((*rootptr)->left), value);
	}
	else
	{
		if ((*rootptr)->left == NULL && (*rootptr)->right == NULL)
		{
			free(*rootptr);
			*rootptr = NULL;
		}
		else if ((*rootptr)->left != NULL && (*rootptr)->right != NULL)
		{
			i = inorders((*rootptr)->right);

			(*rootptr)->data = i;
			deleteNode(&((*rootptr)->right), i);
		}
		else if ((*rootptr)->left)
		{
			temp = (*rootptr);
			*rootptr = (*rootptr)->left;
			free(temp);
		}
		else
		{
			temp = (*rootptr);
			*rootptr = (*rootptr)->right;
			free(temp);
		}
	}
}
// Simple List, go on implement simple list here , which we will use for BFS and DFS

void pushEnd(ListNode **f,Node *nodeptr) // will use as pushing to Queue, // i ll do normally, tell me if i have to make changes ok
{
	// now create a temp node
	ListNode *temp, *traverse;
	// first time front null hua toh 1st element is goin
	if (*f == NULL)
	{
		temp = (ListNode *)malloc(sizeof(ListNode));
		temp->nodeptr = nodeptr;// here i pass my pointr to the node of tree right?, n that well fill later.
		temp->nextNode = NULL;
		*f = temp; //  
	}
	else
	{
		traverse = *f;
		while (traverse->nextNode!= NULL)
		{
			traverse = traverse->nextNode;
		}
		pushEnd(&(traverse->nextNode),nodeptr);
	}
} // done with push end

void pushFront(ListNode **f,Node *nodeptr) // will use as pushing on Stac. why but ,ok
{
	ListNode *temp;
	temp = (ListNode *)malloc(sizeof(ListNode)); 
	temp->nodeptr = nodeptr;
	temp->nextNode = *f;
	*f = temp;
}
// pop from front
Node* pop(ListNode **f) // will pop front and will work for both Q and Stack
{
	Node *temp;
	ListNode *link;
	temp=(*f)->nodeptr;
	link=(*f)->nextNode;
	free(*f);
	*f = link;
	return temp;
}


// BFS , as we have already implemented BST , we will directly use BFS on BST , even though it doesnt make sence
Node * bfs(Node *root,int search)
{
	
	ListNode *queue = NULL; 
	Node * current;
	pushEnd(&queue, root); // root

	while (queue != NULL && (current = pop(&queue))->data != search)
	{
		if (current->left)
		{
			pushEnd(&queue, current->left);
		}
		if (current->right)
		{
			pushEnd(&queue, current->right);
		}
	}

	if (current->data == search)
	{
		return current;
	}
	else
	{
		return NULL;
	}
}

Node * dfs(Node *root, int search)
{

	ListNode *stack = NULL;
	Node * current;
	pushFront(&stack, root); // root

	while (stack != NULL && (current = pop(&stack))->data != search)
	{
		if (current->right)
		{
			pushFront(&stack, current->right);
		}
		if (current->left)
		{
			pushFront(&stack, current->left);
		}
	}

	if (current->data == search)
	{
		return current;
	}
	else
	{
		return NULL;
	}
}
// test functn 
void test()
{
	ListNode * list = NULL;
	Node a, b, c, d, e, f;
	Node * popped  = NULL;
	a.data = 12;
	b.data = 15;
	c.data = 20;
	d.data = 25;
	e.data = 2;
	f.data = 0;

	pushFront(&list, &a); // a
	pushEnd(&list, &b); // a b
	pushFront(&list, &c);// c a b
	pushFront(&list, &d); // d c a b
	pushEnd(&list, &e); // d c a b e

	popped = pop(&list); // d , c a b e
	popped = pop(&list); // c , a b e

}

// Printing
void postorderprint(Node *traverse)
{
	if (traverse != NULL)
	{
		postorderprint(traverse->left);
		postorderprint(traverse->right);
		printf("%d \n", traverse->data);
	}
}
void preorderprint(Node *traverse)
{
	if (traverse)
	{
		printf("%d \n", traverse->data);
		preorderprint(traverse->left);
		preorderprint(traverse->right);
	}
}
void inorderprint(Node *traverse)
{
	if (traverse)
	{
		inorderprint(traverse->left);
		printf("%d \n", traverse->data);
		inorderprint(traverse->right);
	}
}

// Testing
void main()
{
	Node *root = NULL;
	char i = ' ';
	root = NULL;

	test();

	insert(&root, 25);
	insert(&root, 50);
	insert(&root, 35);
	insert(&root, 75);
	insert(&root, 20);
	insert(&root, 10);
	insert(&root, 15);

	Node * searched = dfs(root, 20);
	////
	//printf("Tree generated \nPrinting inorder\n");
	//inorderprint(root);
	//deleteNode(&root, 15);
	//printf("deleted 15 \nPrinting inorder\n ");
	//inorderprint(root);
	//deleteNode(&root, 25);
	//printf("deleted 25 \nPrinting inorder\n ");
	//inorderprint(root);

	//printf("printing in all orders post then pre and last in");

	//postorderprint(root);
	//printf("\n");
	//preorderprint(root);
	//printf("\n");
	//inorderprint(root);

	scanf("%c", &i); // replacement for getch
}