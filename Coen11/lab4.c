#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Joseph Sindelar
//Global Variables
//Union
typedef union info
{
	char phone [12];
	int minage;
	float avg;
}INFO;

typedef struct entry
{
	int size;
	char name [20];
	int age;
	INFO extra;
} ENTRY; 
ENTRY waitlist [10];

int total=0;

//Functions

void request();
void cancel();
void list();
void sizefunc();
int duplicate(char name [20]);

int main(){
	int option;
	while(1){
		printf("Option 1 is to Add, Option 2 is to Cancel, Option 3 is to list, Option 4 is to search for any group less thanentered size,  and Option 9 is to exit\n");
		scanf("%d",&option);
		switch (option){
			case 1:
				//Adds a class
				printf("Write your name.\n");
				request();
				break;
			case 2:
				//Cancels a class
				cancel();
				break;
			case 3:
				//Lists the reservations
				list();
				break;
			case 4:
				//Searches for groupsizes
				sizefunc();
				break;
			case 9:
				//Just end me fam
				return 1;
			default:
				printf("Invalid option\n");
		}
	}
}
void request()
	{
	//Adds a class
	char tempname [20];
	int i;
	int tempsize;

	if (total==10)
		{
		printf("Full\n");
		}
	else
		{
		scanf("%s",tempname);
		if(duplicate(tempname)==1) 
			return;
		printf("Now groupsize and maximum age.");
		scanf("%d",&tempsize);
		scanf("%d",&waitlist[total].age);
		if (waitlist[total].age<18)
			{
			printf("Type in your phone number please.\n");
			scanf("%s",waitlist[total].extra.phone);
			}
		else if (waitlist[total].age>60)
			{
			printf("Type in the age of the youngest member in your group please.\n");
			scanf("%d",&waitlist[total].extra.minage);
			}
		else
			{
			printf("Type in average age please.\n");
			scanf("%f",&waitlist[total].extra.avg);
			}
		strcpy(waitlist[total].name, tempname);
		waitlist[total].size=tempsize;
		total++;  
		}
	}

int duplicate(char tempname[20])
//Checks for duplicate names
	{
	int i;
	for (i=0;i<total;i++)
		{
		if (strcmp(waitlist[i].name, tempname)==0)
			{
			printf("Already signed up under this name.\n");
			return 1;
			}
		}
	return 0;
	}

void cancel()
	{
	//Cancels a class
	int i;
	int j;
	int tempsize;
	printf("How many spaces do you want to cancel?\n");
	if (total!=0)
	{
		scanf("%d",&tempsize);
		for (i=0;i<total;i++)
		{
			if (tempsize>=waitlist[i].size)
			{
				printf("Moved, %s off the list.\n", waitlist[i].name);
				tempsize-=waitlist[i].size;
				for (j=i;j<total-1;j++)
				{
					waitlist[j]=waitlist[j+1];
				}
				total--;
				i--;
			}
		}
	}
	else
		printf("Nothing to cancel.\n");
	}

void list()
	{
	//Lists the Reservations
	int i;
	ENTRY *p;
	p=waitlist;
	for (i=0;i<total;i++,p++)
		{	
		printf("%s has a reservation, their group size is %d, and their max age is %d.\n", p->name,p->size,p->age);
		if (waitlist[i].age<18)
			printf("Phone number is %s\n", waitlist[i].extra.phone);
		else if(waitlist[i].age>60)
			printf("Minimum age in group is %d\n", waitlist[i].extra.minage);
		else
			printf("Average age in group is %f\n", waitlist[i].extra.avg);
		}
	printf("\n");
	}

void sizefunc()
{
//Searches for the size of the group
	int i;
	int flag=0;
	ENTRY *p;
	p=waitlist;
	int search_size;

	printf("Type the group size\n");
	scanf("%d",&search_size);
	printf("Matches:\n");
	for (i=0;i<total;i++,p++)
		if (search_size>=p->size)
			{
			printf("%s has a group size of %d\n",p->name,p->size);
			flag++;
			}
	if (flag==0)
		printf("None\n");
}





	


















