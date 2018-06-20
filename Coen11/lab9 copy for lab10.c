#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
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
void insert(char [20], int);
void delete();
void list();
void search();
int check();
void read_all();
void save_all();
void nameback();
void backwards();
void deleteall();
void display();
void *autosave(void*);
pthread_mutex_t mutex;

//Main Function
int main(int argc, char *argv []){
	int option;
	int nums;
	char nams [20];
	pthread_t thread;
	NODE *bby;
	if (argc == 1)
	{
		printf("Name of file is missing.\n");
		return 1;
	}
	pthread_mutex_init (&mutex, NULL);

	pthread_create(&thread, NULL, autosave, (void *) argv[2]);

	read_all(argv[1]);
	while(1){
		printf(" 0 to save\n 1 to Add\n 2 to cancel\n 3 to list\n 4 to search for less than entered size\n 5 to list backwards\n 6 to reverse the names\n 7 to display\n 9 to save and exit\n");
		scanf("%d",&option);
		switch (option){
			case 1:
				//Adds
				pthread_mutex_lock(&mutex);
				printf("Type number and name.\n");
				scanf("%d",&nums);
				scanf("%s",nams);
				insert(nams, nums);
				pthread_mutex_unlock(&mutex);
				break;
			case 2:
				//Cancels
				pthread_mutex_lock(&mutex);
				delete();
				pthread_mutex_unlock(&mutex);
				break;
			case 3:
				//Lists
				pthread_mutex_lock(&mutex);
				list();
				pthread_mutex_unlock(&mutex);
				break;
			case 4:
				//Search
				pthread_mutex_lock(&mutex);
				search();
				pthread_mutex_unlock(&mutex);
				break;
			case 5:
				//List backwards
				backwards(head);
				break;
			case 6:
				//Name backwards
				bby=head;
				while (bby != NULL)
				{
					nameback(bby->name);
					printf("\n");
					bby=bby->next;
				}
				break;
			case 7:
				//Display
				display(argv[2]);
				break;
			case 0:
				//Just Save
				save_all(argv[1]);
				break;
			case 9:
				//End
				save_all(argv[1]);
				pthread_mutex_lock(&mutex);
				pthread_cancel(thread);
				pthread_mutex_unlock(&mutex);
				deleteall(head);
				return 1;
			default:
				printf("Invalid\n");
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

void save_all(char *file)
{
	FILE *fp;
	NODE *current;
	current=head;
	int flag=0;
	fp=fopen(file, "w");
	if (fp==NULL)
	{
		printf("Error in memory.");
		fclose(fp);
		return;
	}
	if (flag==0)
	{
		fprintf(fp, "Name\tGroup Size\n");
		fprintf(fp, "--------------------------------------------\n");
		flag++; 
	}
	while (current != NULL)
	{
		fprintf(fp,"%s\t%d\n", current->name, current->number);
		current=current->next;
	}
	fclose (fp);
}

void read_all(char *file)
{
	//read from the file to the nodes, use a loop like while
	FILE *fp;
	int nums;
	char nams [20];
	NODE *current;
	current=head;
	fp=fopen(file, "r");
	if (fp==NULL)
	{
		printf("File is empty.\n");
		fclose(fp);
		return;
	}
	fseek(fp, 61, SEEK_SET);
	while (fscanf(fp, "%s %d", nams, &nums)==2)
	{
		insert(nams, nums);
	}
	fclose(fp);
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

void display(char * filename)
{
	//Read Binary
	FILE *fp;
	NODE temp;
	
	fp = fopen(filename,"rb");
	while (fread(&temp,sizeof(NODE),1,fp) > 0)
	{
		printf("Name:%s\tSize:%d\n",temp.name, temp.number);
	}
	fclose (fp);
}

void* autosave(void* filename)
{
	//every 15 do stuff
	FILE *fp;
	NODE *p;
	int i;

	while (1)
	{
		printf("Autosaving...\n");
		pthread_mutex_lock(&mutex);
		fp = fopen(filename,"wb");
		p=head;
		while (p!=NULL)
		{
			fwrite(p, sizeof(NODE),1,fp);
			p = p->next;
		}
		fclose(fp);
		pthread_mutex_unlock(&mutex);
		printf("Saved");
		sleep(15);
	}

}





