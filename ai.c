#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

typedef struct Node
{
   int id;
   char name[50];
   struct Node *next;
}node;


typedef struct Q
{
 int data[MAX];
 int R,F;
}Q;

node **G;
int n,x;
char dest[30];

void insert(node *p, node *q)
{
    node *temp=(node*)malloc(sizeof(node));
    temp->id=q->id;
    strcpy(temp->name,q->name);
    temp->next=NULL;
    while(p->next!=NULL)
       p=p->next;
    p->next=temp;
}

int empty(Q *P)
{
 if(P->R==-1)
  return 1;
 return 0;
}

int full(Q *P)
{
 if(P->R==MAX-1)
  return 1;
 return 0;
}

void enqueue(Q *P,int x)
{
 if(P->R==-1)
 {
  P->R=P->F=0;
  P->data[P->R]=x;
 }
 else
 {
  P->R=P->R+1;
  P->data[P->R]=x;
 }
}

int dequeue(Q *P)
{
 int x;
 x=P->data[P->F];
 if(P->R==P->F)
 {
  P->R=-1;
  P->F=-1;
 }
 else
  P->F=P->F+1;
 return x;
}


void BFS(int v)
{
 int w,i,visited[MAX];
 Q q;
 node *p;
 q.R=q.F=-1;              
 for(i=0;i<n;i++)
  visited[i]=0;
 enqueue(&q,v);
 printf("\n%s",G[v]->name);
 visited[v]=1;
 while(!empty(&q))
 {
  v=dequeue(&q);
  //insert all unvisited,adjacent vertices of v into queue
  for(p=G[v];p!=NULL;p=p->next)
  {
     w=p->id;
     if(visited[w]==0)
   {
     enqueue(&q,w);
     visited[w]=1;
     printf("-->%s",p->name);
     if(p->id==x)
     {
       printf("\n");
       exit(0);
     }  
   }
  }
 }
}

int search(char *str)
{
   int i;
   for(i=0;i<n;i++)
   {
      if(strcmp(G[i]->name,str)==0)
        return G[i]->id;
   }
}

void main()
{
   int i,vi,vj,no_of_edges;
   printf("Enter the number of people: ");
   scanf("%d",&n);
   G=(node**)malloc(n*sizeof(node*));
   for(i=0;i<n;i++)
   {  
      G[i]=(node*)malloc(sizeof(node));
      G[i]->id=i;
      printf("Enter name: ");
      scanf("%s",G[i]->name);
      G[i]->next=NULL;
   }
  /* for(i=0;i<n;i++)
   {
      printf("%d %s\n",G[i]->id,G[i]->name);
   }*/
   char str[30],str1[30];
   printf("\nEnter the number of connections: ");
   scanf("%d",&no_of_edges);
   for(i=0;i<no_of_edges;i++)
   {
      printf("\nEnter 2 friends: ");
      
      scanf("%s%s",str,str1);
      vi=search(str);
      vj=search(str1);
      insert(G[vi],G[vj]);
      insert(G[vj],G[vi]);
      printf("%s is now friends with %s!\n",str,str1);
   }
   printf("\nEnter your profile: ");
   scanf("%s",str);
   i=search(str);
   printf("\nEnter the profile you are looking for: ");
   scanf("%s",str1);
   x=search(str1);
   printf("Link between %s and %s:\n",str,str1);
   BFS(i);
}
