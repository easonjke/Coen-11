#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Joseph Sindelar

#define NODE struct node
typedef struct node
{
	char name[20];
	int number;
	NODE *next;
}NODE;

NODE *tail=NULL;
NODE *head=NULL;

void insert();
void delete();
void deletthis();
void list();
void search();

int main(){
	int option;
	while(1){
		printf("Option 1 to Add, 2 to cancel, 3 to list, 4 to search for less than entered size, and 9 to exit\n");
		scanf("%d",&option);
		switch (option){
			case 1:
				//Adds
				printf("Name and group size.\n");
				insert();
				break;
			case 2:
				//Cancels
				delete();
				break;
			case 3:
				//Lists
				list();
				break;
			case 4:
				//Search
				search();
				break;
			case 9:
				//End
				return 1;
			default:
				printf("Invalid\n");
		}
	}
}

void delete ()
{
	int num;
	NODE *p, *q;
	printf("Enter in the size you want to delete")
	scanf("%d",&num)
	if (head==NULL)
		return;
	p=q=head;
	while (p!=NULL)
	{
		if (p->number>=num)
			break;
		q=p;
		p=p->next;
	}
	if (p==NULL || p->number>num)
		return;
	if (p==head)
		head=head->next;
	else if (p->next==NULL)
		q->next=NULL;
	else
		q->next=p->next;
	free(p);
}

void insert()
{
	printf("Type in Groupsize and Name.");
	scanf("%d",&num);
	scanf("%s", tempname)
	if (search(tempname)==1);
		return;
	NODE *current = head;
	while (current->next != NULL) {
		current = current->next;
	}

	current->next = malloc(sizeof(NODE));
	current->next->number=num;
	current->next->name=tempname;
	current->->next = NULL;
}

void insertwrong ()
{
	printf("Type in group size and name.");
	int num;
	char tempname [20];
	scanf("%d",&num);
	scanf("s",tempname);
	int *p;
	int *q;
	NODE *temp;
	temp = malloc(sizeof(NODE));
	temp->name = tempname;
	temp->number = num;
	temp->next = *head;
	*head = temp;
	if ((temp=(NODE*)malloc(size of (NODE)))==NULL)
		return;
	temp->number=num;
	if (p==head) //before the list
	{
		temp->next=head
		temp->prev=NULL;
		head->prev=temp;
		head=temp;
	}
	else
	{
		temp->next=p;
		temp->prev=p->prev;
		p->prev->next=temp;
		q->prev=temp;
	}
	return;
}

void deletthis (NODE *p)
{
	if (p==NULL)
		return;
	if(head==tail)
	{
		if (p!=head)
			return;
		head=tail=NULL;
	}
	else(p==head)
	{
		head=head->next;
		head->prev=NULL;
	}
	else if(p==tail)
	{
		tail=tail->prev;
		tail->next=NULL;
	}
	else
	{
		p->prev->next=p->next;
		p->next->prev=p->prev;
	}
	free(p);
	return;
}

int search(tempname)
{
	while (head != NULL)
	{
		if (head->name == tempname)
		{
			printf("Found\n");
			return 1;
		}
		head=head->next;
	}
	printf("Not found\n");
}

void list()
{
	struct node *temp;
	temp=start;
	while(temp!=NULL)
		{
		printf("%d",temp->number);
		temp=temp->next;
		}
}












