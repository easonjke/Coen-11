#include "lab10header.h"

void delete()
{
	int num;
	int counter=1;
	NODE *current, *del;
	printf("Enter in the size you want to delete.\n");
	scanf("%d",&num);
	if (head==NULL)
		return;
	current=del=head;
	while (del!=NULL) //Checks the whole list
	{
		if (del==head && del->number<=num) //If it is the head node
		{
			head=head->next;
			num=(num-(del->number));
			printf("%s deleted size %d.\n", del->name, del->number);
			free (del);
			del=head;
			current=head;
		}
		//If it is the last node
		else if (del->next==NULL && del->number<=num)
		{
			tail=del->prev;
			printf("%s deleted size was %d.\n", del->name, del->number);
			tail->next=NULL;
			free (del);
			return;
		}
		// If it is a middle node
		else if (del->number<=num && del->next != NULL && del != head)
		{
			del->prev->next=del->next;
			del->next->prev=del->prev;
			printf("%s deleted, size was %d.\n", del->name, del->number);
			free (del);
			del=current->next;
		}
		//Moves the pointer if it did not end up deleting a node this time
		else
		{
			current=del;
			del=del->next;
		}
		counter++;
	}
}

void insert(char nams[20] , int nums)
{
	printf("Type in Groupsize and Name.\n");
	NODE *current;
	if (check(nams)==1) //Checks for duplicate
	{
		printf("Already signed up.\n");
		return;
	}
	if ((current =(NODE*)malloc(sizeof(NODE))) == NULL) //To catch bugs
	{
			printf("error of malloc\n");
	}
	strcpy(current->name, nams); //Writes in inputs
	current->number = nums;
	current->next = NULL;
	if (head == NULL)//First node
	{
		head = current;
		tail = current;
	}	
	else
	{		
		tail->next = current;//All subsequent nodes
		current->prev=tail;
		tail = current;
	}
}

void search()
{
	int value;
	printf("Enter size to search for.\n");
	scanf("%d",&value);
	NODE *current = head;
	while (current != NULL)//moves through the list
	{
		if (current->number <= value)//If match
		{
			printf("\n%s\n",current->name);
			printf("%d\n",current->number);
		}
		current=current->next;
	}
}

int check(char nams [20])//Checks for duplicate
{
	NODE *current = head;
	while (current != NULL)
	{
		if (strcmp(current->name, nams)== 0)
		{
			printf("Found\n");
			return 1;
		}
		current=current->next;
	}
	printf("Signed Up\n");
	return 0;
}

void list()//Lists all nodes
{
	struct node *temp;
	temp=head;
	while(temp!=NULL)
	{
		printf("\n%d\t",temp->number);
		printf("%s\n",temp->name);
		temp=temp->next;
	}
}


void backwards(NODE *p)
{
	if (p==NULL)
		return;
	backwards(p->next);
	printf("%s\t%d\n",p->name, p->number);
}

void nameback(char *p)
{
	if (*p == '\0')
		return;
	nameback(p+1);
	printf("%c",*p);
}

void deleteall(NODE *p)
{
	if (p==NULL)
		return;
	deleteall(p->next);
	printf("Good bye %s\n",p->name);
	free (p);
}
