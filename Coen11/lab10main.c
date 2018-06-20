
#include "lab10header.h"

NODE *tail=NULL;
NODE *head=NULL;
pthread_mutex_t mutex;

//Main Function
int main(int argc, char *argv []){
	int option;
	int nums;
	char nams [20];
	char key=(char)atoi(argv[3]);
	pthread_t thread;
	NODE *bby;
	if (argc == 1)
	{
		printf("Name of file is missing.\n");
		return 1;
	}
	pthread_mutex_init (&mutex, NULL);

	read_all(argv[1], key);

	if(argc == 4)
	{
	pthread_create(&thread, NULL, autosave, (void *) argv[2]);
	}
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
				save_all(argv[1], key);
				break;
			case 9:
				//End
				save_all(argv[1], key);
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
