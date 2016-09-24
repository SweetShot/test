#include<stdio.h>
#include<conio.h>
long int hash_table[20]={0};
long int n,key,table_size;
//int collision;
long int j;
long int hash(long int key)
{
	long int i;
	i=key%table_size;
	return i;
}
long int rehash(long int oldi)
{
	long int i;
	i=(oldi+1)%table_size;
	return i;
}
long int rehashquad(long int key,long int j)
{
	long int i;
	i=(key+j*j)%table_size;
	return i;
}
int insert(long int key) //returns collision
{
	long int i;
	int collision=0;
	i=hash(key);
	if(hash_table[i] == 0)
	{
		hash_table[i] = key;
	}
	else
	{
		while(hash_table[i]!=0)
		{
			i = rehash(i);
			collision++;
		} //whenever rehash is called it increments collision
		hash_table[i]=key;
	}
	return collision;
}
int insertquad(long int key)//same as above
{
	long int i,j = 0;
	int collision= 0;
	i = hash(key);
	if(hash_table[i]==0)
		hash_table[i]=key;
	else
	{
		while(hash_table[i]!=0)
		{
			j++;
			collision++;    //same as above
			i = rehashquad(i,j);
		}
		//collision++;
		hash_table[i]=key;
	}
	return collision;
}

void main()
{
	long int n,i,ch,ch1;
	int coll,k=0;
	clrscr();
	printf("Enter no. of elements ");
	scanf("%lu",&n);
	printf("\nEnter table size ");
	scanf("%lu",&table_size);
	if(table_size>=n)
	{
	do{
	printf("\nEnter 1 for Linear probing 2 for Quadratic probing ");
	scanf("%lu",&ch);
	switch(ch)
	{
	case 1:
	{
	for(i=0;i<n;i++)
		{
		printf("\nEnter key ");
		scanf("%lu",&key);
		coll=insert(key);  //collision is returned and stored in coll
		//if(coll!=0)
		k+=coll;//since val of coll changes every time it is stored in k
		}
	printf("\nHash table is ");
	for(i=0;i<table_size;i++)
		{
		printf("%lu ",hash_table[i]);
		}
	printf("Collisions are %d",k);
	break;
	}

	case 2:
	{
	for(i=0;i<n;i++)
		{
		printf("\nEnter key ");
		scanf("%lu",&key);
		coll=insertquad(key);

		k+=coll;//since val of coll changes every time it is stored in k
		}
	printf("\nHash table is ");
	for(i=0;i<table_size;i++)
		{
		printf("%lu ",hash_table[i]);
		}
	printf("Collisions are %d",k);
	break;
	}
	default:
	{
	printf("\nInvalid ip ");
	break;
	}
	}
	printf("\nWant to continue 1: Yes 2: No ");
	scanf("%lu",&ch1);
	}
	while(ch1!=2);
	}
	else
	{
	printf("\nWrong input ");
	//scanf("%d",&table_size);
	}
	getch();
}