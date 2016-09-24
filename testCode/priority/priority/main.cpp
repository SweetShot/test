#include<stdio.h>

typedef struct heap
{
	int element[16];
	int count;
}Heap;

void swap(Heap * heaptr, int i, int j)
{
	heaptr->element[0] = heaptr->element[i];
	heaptr->element[i] = heaptr->element[j];
	heaptr->element[j] = heaptr->element[0];
}
void enqueue(Heap *heaptr, int data)
{
	int i;
	// i element for switiching
	heaptr->element[heaptr->count + 1] = data;
	heaptr->count++;
	i = heaptr->count;
	while (i != 1)
	{
		if (heaptr->element[i] > heaptr->element[i / 2])
		{
			swap(heaptr, i, i / 2);
		}
		else
			break;
		i = i / 2;
	}
}

int dequeue(Heap *heaptr)
{
	int del;
	int i, index;
	del = heaptr->element[1];
	i = 1;
	heaptr->element[1] = heaptr->element[heaptr->count--];
	while (1)
	{
		if (2 * i < heaptr->count) // if left child exists , right child must exist
		{

			if (heaptr->element[2 * i] >heaptr->element[2 * i + 1]){ // which child is greater 
				index = 2 * i;
			} else {
				index = 2 * i + 1;
			}
			if (heaptr->element[index] > heaptr->element[i]) // compare greater child with parent
				swap(heaptr, i, index);
			else 
				break;
			i = index;

		}

		else if (2 * i == heaptr->count) // only 1 child
		{

			if (heaptr->element[2 * i] > heaptr->element[1]){ // comparing with only child
				swap(heaptr, i, 2 * i);
				i = 2 * i; // dont have child after this 
			}else break;

		}
		else 
			break; // when no child
	}

	return del;

}
void main()
{
	Heap heap;
	heap.count = 0;
	enqueue(&heap, 50);
	enqueue(&heap, 90);
	enqueue(&heap, 10);
	enqueue(&heap, 60);
	enqueue(&heap, 78);
	enqueue(&heap, 80);
	printf(" dequeue element is %d \n", dequeue(&heap));
	printf(" dequeue element is %d \n", dequeue(&heap));
	printf(" dequeue element is %d \n", dequeue(&heap));
	printf(" dequeue element is %d \n", dequeue(&heap));
	printf(" dequeue element is %d \n", dequeue(&heap));
	printf(" dequeue element is %d \n", dequeue(&heap));
}
