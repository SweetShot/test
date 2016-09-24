void buildexprestree(char postfix[] , Node** rootptr)
{
 int  i ; // for iterating on exp
 struct  node  *pnode; 
 struct  stack  s ;
 s.top=-1 ;
 // for each char from left to right
 for(i=0 ; postfix[i]!='\0' ; i++)
  if(isoperand(postfix[i])) // if operand then push to stack
  {
   pnode= new_Node(postfix[i]);
   push(&s,pnode) ;
  }
  else // if operator then create node , right = pop then left = pop , and then push node to stack
  {
   pnode= new_Node(postfix[i]) ;
   pnode->right = pop(&s);
   pnode->left = pop(&s);
   push(&s,pnode);
  }
  // return root node
  *rootptr = pop(&s);
}

double eval(Node * root)
{
	if (!root->right && !root->left)
	{
		return root->data;
	}
	else 
	{ 
		return apply(eval(root->left),root->data,eval(root->right)); 
	}
}
double apply(double a, char op, double b)
{
	switch (op)
	{
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			return a/b;
		case '^':
			return pow(a,b);
		case '%':
			return a%b;
		default:
			return 0;
	}
}

