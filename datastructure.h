#ifndef DATASTRUCTURE_H_INCLUDED
#define DATASTRUCTURE_H_INCLUDED
#endif // DATASTRUCTURE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define dirname "data"
#define filename "leaderboard.txt"

int count;

// Struct Basic
struct node {
   char name[16];
   int point;
   struct node *next;
}*rear, *temp, *front_temp;

// Generate Node pointer
struct node *head = NULL;
struct node *current = NULL;

//Create Linked List
void insert(char *user, int point)
{
   // Allocate memory for new node;
   struct node *link = (struct node*) malloc(sizeof(struct node));

	// Set value
   strcpy(link->name, user);
   link->point = point;
   link->next = NULL;

   // If head is empty, create new list
   if(head==NULL)
    {
      head = link;
      return;
   }

   current = head;

   // move to the end of the list
   while(current->next!=NULL)
      current = current->next;

   // Insert link at the end of the list
   current->next = link;
}

void push(int item)
{
	struct node* newdata = (struct node*) malloc(sizeof(struct node));
	newdata->point = item;
	newdata->next = head;
	head = newdata;
}

void pop()
{
	struct node *ptr = head;
	head = ptr->next;
	free(ptr);
}

//Import Files to Data Structure
void initData()
{
    FILE *fp;
    //Specify path
    char filepath[128];
    sprintf(filepath, "%s/%s", dirname, filename);

    //Importing File
    fp = fopen(filepath, "r");
    if (fp != NULL)
    {
        char temp[32], *name, *num;
        int score;
        fscanf(fp, "%s", temp);
        //Print Data Structure
        while(getc(fp) != EOF)
        {
            name = strtok(temp, "<|>");
            num = strtok(NULL, "<|>");
            sscanf(num,"%d",&score);
            insert(name, score);
            fscanf(fp, "%s", temp);
        }
    }
    fclose(fp);
}

void display()
{
    struct node* ptr = head;
    while (ptr!=NULL)
    {
        printf("%d | ", ptr->point);
        ptr = ptr->next;
    }
    free(ptr);
    printf("\n");
}

void eksportData()
{
    mkdir(dirname);
    FILE *fp;
    //Specify path
    char filepath[128];
    sprintf(filepath, "%s/%s", dirname, filename);

    //Exporting File
    fp = fopen(filepath, "w");
    //Print Data Structure
    struct node *ptr = head;
    while(ptr != NULL)
    {
        char temp[32];
        sprintf(temp, "<%s|%d>\n", ptr->name, ptr->point);
        fprintf(fp, temp);
        ptr = ptr->next;
    }
    free(ptr);
    fclose(fp);
    printf("Data Saved to : %s", filepath);
}

void sorting()
{
    struct node* ptr = (struct node*) malloc(sizeof(struct node));
    struct node* ptr2 = (struct node*) malloc(sizeof(struct node));

    int temp_p;
    char temp_n[16];

    ptr = head;
    if (ptr == NULL)
        return;

    ptr2 = ptr->next;
    if (ptr2 == NULL)
        return;

    int i, j;
    calculate();

    for(i = 0 ; i < count*count; i++)
    {
        //Apabila Data Pertama lebih kecil dari Data Setelahnya
        if (ptr->point < ptr2->point)
        {
            //Simpan ptr(1st) ke Temp
            temp_p = ptr->point;
            strcpy(temp_n, ptr->name);

            //Masukkan data ptr(2nd) ke ptr(1st)
            ptr->point = ptr2->point;
            strcpy(ptr->name, ptr2->name);

            //Masukan ptr(1st) yang telah disimpan ke ptr(2nd)
            ptr2->point = temp_p;
            strcpy(ptr2->name, temp_n);

            //Lanjut looping untuk data selanjutntya
            ptr = ptr->next;
            ptr2 = ptr2->next;

            //Apabila Data selanjutnya kosong, ulangi dari awal proses sorting.
            if (ptr2 == NULL)
            {
                ptr = head;
                ptr2 = ptr->next;
            }
        }
        //Lanjutkan Pengecekan ke Data Selanjutnya
        else
        {
            ptr = ptr->next;
            if (ptr==NULL)
            {
                ptr = head;
                ptr2 = ptr->next;
            }
            ptr2 = ptr2->next;
            if (ptr2==NULL)
            {
                ptr = head;
                ptr2 = ptr->next;
            }
        }
    }
    count=0;
}

void calculate()
{
    struct node *ptr = head;
    while (ptr != NULL)
    {
        count++;
        ptr = ptr->next;
    }
    printf("Data Counted : %d\n", count);
}
