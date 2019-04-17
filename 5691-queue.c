#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 * Item: An item that is being enqueued to or dequeued from the queue
 *       It is a pointer to the process
 */
typedef struct
{
    char *name;
    int remaining_time;
} Process, *Item;
/*
 *
 */
typedef struct
{
    char *name;
    int rt;
    int bt;
} Itemes;
/*
*
*/
typedef struct Node
{
    Item data;
    struct Node* next;
} Node;
/*
 *
 */
typedef struct
{
    Node *head,*tail;
} Queue;
/*
 *
 */
void init(Queue *q)
{
    q->head=(Node*)malloc(sizeof(Node));
    q->tail=(Node*)malloc(sizeof(Node));
    q->head = q->tail= NULL;
}
/*
 *
 */
int isEmpty(Queue *q)
{
    if (q->head==NULL)
        return 1;
    else
        return 0;
}
/*
 *
 */
Item dequeue(Queue *q)
{
    Item b=(Item*)malloc(sizeof(Item));
    b->name=NULL;
    b->remaining_time=NULL;
    if (q->head == NULL)
        return b;
    else{
    Node* temp= q->head;
    q->head = q->head->next;
    if (q->head == NULL)
        q->tail = NULL;

    return temp->data;
        }

}

/*
 *
 */
void enqueue(Queue *q, Item val)
{
    Node *temp=(Node*)malloc(sizeof(Node));
    temp->data=val;
    temp->next= NULL;

    if (q->tail == NULL)
    {
        q->head = q->tail = temp;
 //        printf("**%s** ",q->tail->data->name);
               /* printf("%d\n",q->tail->data->remaining_time);
        */
        return;
    }
    else
    {
        q->tail->next = temp;
        q->tail = temp;
   //      printf("**%s** ",q->tail->data->name);
        /* printf("%d\n",q->tail->data->remaining_time);
        */
    }

}
/*
 *
 */
void destroy(Queue *q)
{
    free(q);
}

/*
 * RoundRobin Scheduling
 */
void RoundRobin(char* filename)
{
    FILE *fb;
    Queue q;
    init(&q);
    Process* proc=(Process*)malloc(20*sizeof(Process));
    Process enqProc;
    int i=0,x=0;
    int st[20];
    int rt[20];
    int count=0;
    int startTime;
    fb = fopen(filename, "r");

    if (fb == NULL)
    {
        printf("Cannot open file \n");
        exit(1);
    }
    else
    {
        while (!feof(fb))
        {
            fscanf(fb,"%s %d %d",&(proc+i)->name, &st[i], &(proc+i)->remaining_time);
            i++;
        }

    }
    fclose(fb);
    startTime=st[0];
    for(int h=0; h<i; h++)
    {
        if(st[h]<startTime)
        {
            startTime=st[h];
        }
    }


    for(int y=0; y<i; y++)
    {
        if(st[y]==startTime)
        {
            Item h=(Item*)malloc(sizeof(Item));
            h->name=&proc[y];
            h->remaining_time=proc[y].remaining_time;
            enqueue(&q,h);
            x++;
        }
    }
// printprocess(&q,i,startTime,st,proc);



    int w=st[i-1]+(proc+(i-1))->remaining_time;
    for(int j=0; j<w; j++)
    {
        if(isEmpty(&q))
        {
            printf("idel (%d-->%d)\n",j,j+1);
        }
     else{
            Item p=(Item*)malloc(sizeof(Item));
            p=dequeue(&q);
            p->remaining_time--;
            printf("%s (%d-->%d)",p->name,j,j+1);
             if((j+2>st[x]))
                {
                   // printf("%d\t\t%d\n\n\n",j,st[e]);
                    Item o=(Item*)malloc(sizeof(Item));
                    o->name=&(proc+x)->name;
                    o->remaining_time=(proc+x)->remaining_time;
                    enqueue(&q,o);
                    x++;
            }
            if(p->remaining_time<1)
            {
                printf("halts\n");
            }
            else
            {

                printf("\n");
                enqueue(&q,p);
            }
        }

    }
}
/*
 *
 */
int main(int argc, char**argv) {
	if(argc!=2) {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}

	RoundRobin(argv[1]);

	return 0;
}
