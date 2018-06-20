#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Joseph Sindelar
//Global Variables
int groups[10];
int total=0;
char lessons[10][20];
//Functions
void request();
void cancel();
void list();
int main(){
	int option;
	while(1){
		printf("Option 1 is to Add, Option 2 is to Cancel, Option 3 is to list, and Option 9 is to exit\n");
		scanf("%d",&option);
		switch (option){
			case 1:
				//Adds a class
				printf("Write your name and group size.\n");
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
		scanf("%d",&tempsize);
		for (i=0;i<total;i++)
			{
			if (strcmp(lessons[i],tempname)==0)
				{
				printf("Already signed up under this name.\n");
				return;
				}
			}
		strcpy(lessons[total], tempname);
		groups[total]=tempsize;
		total++;
		}
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
			if (tempsize>=groups[i])
			{
				printf("Moved, %s off the list.\n", lessons[i]);
				tempsize-=groups[i];
				for (j=i;j<total-1;j++)
				{
					strcpy (lessons[j],lessons[j+1]);
					groups[j]=groups[j+1];
				}
				lessons[total-1][0]='\0';
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
	for (i=0;i<10;i++)
		if(lessons[i][0]=='\0')
			printf("%dpm-free\n",i+1);
		else
			printf("%s has a reservation at %dpm and their group size is %d\n", lessons[i],i+1,groups[i]);
	}




			
