#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Joseph Sindelar

#define NODE struct node
struct node
{
	char name[20];
	int number;
	NODE *next;
	NODE *prev;
};

typedef struct list
{
	NODE *tail;
	NODE *head;
}LIST;

LIST lists[4];

void insert();
void delete();
void list();
void search();
int check();

int main(){
	int i;
	for (i=0;i<4;i++)
		{
		lists[i].head=lists[i].tail=NULL;
		}
	int option;
	while(1){
		printf("Option 1 to Add, 2 to cancel, 3 to list, 4 to search for less than entered size, and 9 to exit\n");
		scanf("%d",&option);
		switch (option){
			case 1:
				//Adds
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

void delete()
{
	int num;
	int i;
	int lim;
	int counter=1;
	NODE *current, *del;
	printf("Enter in the size you want to delete.\n");
	scanf("%d",&num);
	if (num>=1 && num<=2)
		lim=1;
	if (num>2 && num<=4)
		lim=2;
	if (num>4 && num<=6)
		lim=3;
	if (num>=7)
		lim=4;
	for (i=0;i<lim;i++)
	{
		current=del=lists[i].head;
		while (del!=NULL)
		{
			if(del->number<=num)
			{
			num-=del->number;
				if (lists[i].head->next==NULL) //Only head
				{
					printf("%s deleted size was %d.\n", del->name, del->number);
					free (lists[i].head);
					del=lists[i].head=NULL;
				}
				else if (del==lists[i].head) //Head
				{
					lists[i].head=lists[i].head->next;
					lists[i].head->prev=NULL;
					printf("%s deleted size %d.\n", del->name, del->number);
					free (del);
					del=lists[i].head;
					current=lists[i].head;
				}
				else if (del->next==NULL) //End
				{
					lists[i].tail=del->prev;
					printf("%s deleted size was %d.\n", del->name, del->number);
					lists[i].tail->next=NULL;
					free (del);
					return;
				}
				else if (del->next != NULL && del != lists[i].head) //Middle
				{
					del->prev->next=del->next;
					del->next->prev=del->prev;
					printf("%s deleted, size was %d.\n", del->name, del->number);
					free (del);
					del=current->next;
				}
			}
			else
			{
				current=del;
				del=del->next;
			}
			counter++;
		}
	}
}

void insert()
{
	int i;
	int num;
	char tempname[20];	
	printf("Type in Groupsize and Name.\n");
	scanf("%d",&num);
	scanf("%s", tempname);
	if (num>=1 && num<=2)
		i=0;
	if (num>2 && num<=4)
		i=1;
	if (num>4 && num<=6)
		i=2;
	if (num>=7)
		i=3;
	NODE *current = lists[i].head;
	if (check(tempname)==1)
	{
		printf("Already signed up.\n");
		return;
	}
	if ((current = malloc(sizeof(NODE))) == NULL)
	{
			printf("error of malloc\n");
	}
	strcpy(current->name, tempname);
	current->number = num;
	current->next = NULL;
	if (lists[i].head == NULL)
	{
		lists[i].head = current;
		lists[i].tail = current;
	}	
	else
	{		
		lists[i].tail->next = current;
		current->prev=lists[i].tail;
		lists[i].tail = current;
	}
}

void search()
{
	int i;
	int lim;
	int value;
	printf("Enter size to search for.\n");
	scanf("%d",&value);
	if (value>=1 && value<=2)
		lim=0;
	if (value>2 && value<=4)
		lim=1;
	if (value>4 && value<=6)
		lim=2;
	if (value>7)
		lim=3;
	for (i=0;i<lim;i++)
	{
		NODE *current = lists[i].head;
		while (current != NULL)
		{
			if (current->number <= value)
			{
				printf("\n%s\n",current->name);
				printf("%d\n",current->number);
			}
			current=current->next;
		}
	}	
}

int check(char tempname [20])
{
	int i;
	for (i=0;i<4;i++)
	{
		NODE *current = lists[i].head;
		while (current != NULL)
		{
			if (strcmp(current->name, tempname)== 0)
			{
				printf("Found\n");
				return 1;
			}
			current=current->next;
		}
	}
printf("Signed up.\n");
return 0;
}

void list()
{
	int i;
	for(i=0;i<4;i++)
	{
		struct node *temp;
		temp=lists[i].head;
		while(temp!=NULL)
		{
			printf("name = %s \tgroup size =  %d\n", temp->name, temp->number);
			temp=temp->next;
		}
	}
}



	
