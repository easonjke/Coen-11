#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Joseph Sindelar

//Define my Node
#define NODE struct node
struct node
{
	char name[20];
	int number;
	NODE *next;
	NODE *prev;
};

//Global Pointers
NODE *tail=NULL;
NODE *head=NULL;

//Global Functions
void insert();
void delete();
void list();
void search();
int check();
void read_all();
void save_all();

//Main Function
int main(int argc, char *argv []){
	int option;
	read_all();
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
				save_all();
				return 1;
			default:
				printf("Inv`alid\n");
		}
	}
}

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

void insert()
{
	int num;
	char tempname[20];	
	printf("Type in Groupsize and Name.\n");
	scanf("%d",&num);
	scanf("%s", tempname);
	NODE *current;
	if (check(tempname)==1) //Checks for duplicate
	{
		printf("Already signed up.\n");
		return;
	}
	if ((current = malloc(sizeof(NODE))) == NULL) //To catch bugs
	{
			printf("error of malloc\n");
	}
	
	strcpy(current->name, tempname); //Writes in inputs
	current->number = num;
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

int check(char tempname [20])//Checks for duplicate
{
	NODE *current = head;
	while (current != NULL)
	{
		if (strcmp(current->name, tempname)== 0)
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
		printf("\n%d\n",temp->number);
		printf("%s\n",temp->name);
		temp=temp->next;
		}
}
