#include<stdio.h>
#include<stdlib.h>
typedef struct Pair
{
	int mob;
	char name;
}Pair;
// pairlist
typedef struct pairlist
{
	Pair pairptr;
	struct pairlist* next;
}PairList;

int hashfunction(unsigned int key,int bits)
{
	//in case of division method //return key % N;
	return (key * key) >> (32 - bits);
}
int add(int key,int N,char name,Pair **hash)
{
	int index = hashfunction(key, N);
	for (int i = 0; i < N; i++)
	{
		int realIndex = (index + i) % N;
		if (hash[realIndex] == NULL)
		{
			hash[realIndex] = (Pair *)malloc(sizeof(Pair));
			(hash[realIndex])->mob = key;
			(hash[realIndex])->name = name;
			return 0;
		}
	}
	return -1;
}
char search(int key, int N, Pair** hash)
{
	int index = hashfunction(key, N);
	for (int i = 0; i < N; i++)
	{
		int realIndex = (index + i) % N;
		if (hash[realIndex])
		{
			if (hash[realIndex]->mob == key)
			{
				return hash[realIndex]->name;
			}
		}
		else
		{
			return -1;
		}
	}
	return -1;
}
void main()
{
	Pair **hash=NULL;
	int N;
	scanf("%d", &N);
	fflush(stdin);
	hash = (Pair **)malloc(sizeof(Pair *)* N);
	for (int i = 0; i < N; i++)
	{
		hash[i] = NULL;
	}
	//inputing;
	//testing;
	add(12345, N, 'A', hash);
	add(1995, N, 'B', hash);
	add(1245, N, 'C', hash);
	add(345, N, 'D', hash);
	add(26354, N, 'V', hash);
	add(5678, N, 'U', hash);
	char n = search(9999, 5, hash);
}
