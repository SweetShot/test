#include <stdio.h>
#include <stdlib.h>


void getAdjcencyMatrix(int *** matptr, int n)
{
	int ** mat = *matptr;
	char t = 'y';
	mat = (int **)malloc(sizeof(int*) * n);
	// When using for adjacency matrix 
	for (int i = 0; i < n; i++)
	{
		mat[i] = (int*)malloc(sizeof(int) * n);
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			mat[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++)
	{
		printf("You are adding connections of node %d \n", i);
		int j;
		do
		{
			printf("Do u have any connection ?(y/n)");
			scanf("%c", &t);
			fflush(stdin);
			if (t == 'n')
				break;

			scanf("%d", &j);
			fflush(stdin);
			mat[i][j] = 1;
			mat[j][i] = 1;
		} while (1);


		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				printf("%2d ", mat[i][j]);
			}
			printf("\n");
		}

	}

	*matptr = mat;
}

void getAdjacencyList(int *** matptr, int n)
{
	int ** mat = *matptr;
	char t = 'y';
	mat = (int **)malloc(sizeof(int*) * n);
	for (int i = 0; i < n; i++)
	{
		printf("You are adding connections of node %d \nHow many connections do u have?", i);
		int j, index;
		scanf("%d", &j);
		fflush(stdin);
		mat[i] = (int*)malloc(sizeof(int) * (j + 1));
		mat[i][j] = -1;
		for (int k = 0; k < j; k++)
		{
			scanf("%d", &index);
			fflush(stdin);
			mat[i][k] = index;
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; mat[i][j] >= 0; j++)
		{
			printf("%2d ", mat[i][j]);
		}
		printf("\n");
	}

	*matptr = mat;
}

void main(void)
{
	int ** mat = NULL;
	int n;
	scanf("%d", &n);
	fflush(stdin);
	//getAdjcencyMatrix(&mat, n);
	//getAdjacencyList(&mat, n);
	printf("\n");
}
