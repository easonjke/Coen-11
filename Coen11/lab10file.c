#include "lab10header.h"

void save_all(char *file, char key)
{
	FILE *fp;
	NODE *current;
	char temp[20];
	current=head;
	int i=0;
	int flag=0;
	fp=fopen(file, "w");
	if (fp==NULL)
	{
		printf("Error in memory.");
		fclose(fp);
		return;
	}
	while (current!=NULL)
	{
		sprintf(temp, "%s %d\n", current->name, current->number);
		i=0;
		while (temp[i]!='\n')
		{
			temp[i]^=key;
			i++;
		}
		fprintf(fp, "%s", temp);
		current=current->next;
	}
	fclose(fp);
}

void read_all(char *file,char key)
{
	//read from the file to the nodes, use a loop like while
	FILE *fp;
	int nums;
	char nams [20];
	char temp_enc[200];
	int i=0;
	fp=fopen(file, "r");
	if (fp==NULL)
	{
		printf("File is empty.\n");
		return;
	}
	while((fgets(temp_enc,200,fp))!=NULL)
	{
		i=0;
		while(temp_enc[i]!='\n')
		{
			temp_enc[i]^=key;
			i++;
		}
		sscanf(temp_enc, "%s %d\n", nams, &nums);
		{
			printf("In insert");
			insert(nams, nums);
		}
	}
	printf("Copied\n");
	fclose(fp);
	return;
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

