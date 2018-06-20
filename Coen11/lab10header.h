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

//Global Pointer
extern NODE *tail;
extern NODE *head;

//Global Functions
void insert(char [20], int);
void delete();
void list();
void search();
int check(char[20]);
void read_all(char*,char);
void save_all(char*, char);
void nameback();
void backwards();
void deleteall();
void display();
void *autosave(void*);
extern pthread_mutex_t mutex;
