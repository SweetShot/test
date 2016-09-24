void dfs(int**mat, int n, int i)
{
	Stack s;
	push(&s, i); // push starting node to stack
	int visited[n];
	// set array to 0
	// set visited of starting 
	visited[i] = 1;
	while(!isEmpty(&s)) // while not empty stack
	{
		int curr = pop(&s); // pop stack
		printf("%d ", curr); // print
		for(int j=0;j < n;j++) // for each connection
		{
			if(mat[curr][j] == 1) 
			{
				// check if visited or not 
				if(visited[j] != 1)
				{
					visited[j] = 1;
					push(&s, j);
				}
			}
		}// end for
	}// end while
}

void bfs(int**mat, int n, int i)
{
	Queue s;
	push(&s, i); // push starting node to Queue
	int visited[n];
	// set array to 0
	// set visited of starting 
	visited[i] = 1;
	while(!isEmpty(&s)) // while not empty Queue
	{
		int curr = pop(&s); // pop Queue
		printf("%d ", curr); // print
		for(int j=0;j < n;j++) // for each connection
		{
			if(mat[curr][j] == 1) 
			{
				// check if visited or not 
				if(visited[j] != 1)
				{
					visited[j] = 1;
					push(&s, j);
				}
			}
		}// end for
	}// end while
}

void insertionsort(int * arr, int n)
{
	int i,j;
	int temp;
	for(i=0;i<n;i++)
	{
		for(j=i;j>=0;j--)
		{
			if(arr[j]>arr[j-1])
			{
				temp=arr[j];
				arr[j]=arr[j-1];
				arr[j-1]=temp;
			}
			else 
				break;
		}
	}
}
// priority queue insertion 
while(iter->next)
{
	if (iter->next->priority <= priority)
	{
		iter = iter->next;
	}
	else
		break;
}
//new node inserted after iter 

// Simulation using queue

// ask no people coming in per min 
// efficiency of counters 
// time for which simulation should work\
// max waiting per person
Queue q;
n = 0;
while(1)
{
	int flag = 0;
	n += 1; // no_people += 1 in case of finding people i can handle
	for (t = 0; t < time; t++) // simulation time 
	{
		// enqueue people 
		for (i = 0; i < no_people; i++)
		{
			enqueue(&q, t);
		}
		// process people for every counter
		for (i = 0; i < n; i++)
		{
			// people per counter
			for(int j = 0; j < efficiency; j++)
			{
				int time_joined = dequeue(&q);
				int diff = t - time_joined;
				if (diff > max_waiting)
				{
					flag = 1;
					break; // break per counter processing
				}
			}
			
			if (flag)
			{
				break; // break for every counter
			}
			
		}
		
		if (flag)
			break; // break time simulator loop
		
	}
	if (flag == 0)
		break; // break while infinite loop
	
}
// so my current n contains min counters required 
printf(" kejwfjfenfms,dmf,mds %n counters are required", jfjejeof,,,, n);














