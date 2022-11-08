typedef struct uer
{
    char name[30];
    char pass[30];
    int status;
    char homepage[30];
   
}acc;

typedef acc listStudentType ;
void displayType(listStudentType user)
{
   printf("%-20s%d\n",user.name,user.status);
}

struct listNode
{
    listStudentType frt;
    struct listNode *next;
};
typedef struct listNode listNode;
typedef struct list
{
    listNode *root;
    listNode *cur;
}LIST;

listNode *searchList(LIST *list,char x[])
{
    listNode *p;
    for( p = list->root;p!=NULL;p= p-> next)
    {
        if(strcmp(p->frt.name,x)==0)
          {
            return p;
            break;
          }
    }
    return NULL;
}
void deleteHead(LIST *list)
{
    if(list->root!=NULL)
    {
        listNode *tmp = list->root->next;
        free(list->root);
        if(list->cur == list->root)    list->cur=tmp;
            list->root=tmp;
        
    }
}
void deleteAtPosition(LIST *list,int p)
{
    listNode *tmp=list->root;
    listNode *prev= NULL;
    if(p<0)
    {

    }
    else if(p==0)
    {
        deleteHead(list);
    }else 
    {
        int i;
        for (int i=0;i<p;i++)
        {
            if(tmp->next ==  NULL) break;
            prev = tmp;
            tmp = tmp->next;
        }
        if( i == p)
        {
            prev -> next = tmp -> next;
            free(tmp);
            list->cur= list->root;
        }
    }
}

void deleteNode(LIST * list,char x[])
{
    int i=0;
    listNode *p;
    for(p= list->root;p!=NULL;p=p->next, i++)
    {
      if(strcmp(p->frt.name,x)==0)
      {
        deleteAtPosition(list,i);
        break;
      }
    }
}
listStudentType registerAcc(LIST* list)
{
    listStudentType t;
    listNode *p;
    printf("Username: ");
    scanf("%s",t.name);
    p=searchList(list,t.name);
    if(p!=NULL)
     printf("Account existed\n");
    else
    {
        printf("Password: ");
        scanf("%s",t.pass);
        t.status=2;
        printf("Homepage: ");
        scanf("%s",t.homepage);
        printf("Successful registration. Activation required.\n");
    }
    return t;
}
LIST *newList()
{
    LIST *list = malloc(sizeof(LIST));
    list->root=NULL;
    list->cur=list->root;
    return list;
}

listNode *makeNewNode(listStudentType inf)
{
    listNode *new = (listNode*) malloc(sizeof(listNode));
    new->frt=inf;
    new ->next=NULL;
    return new;
}
void insertAtHead(LIST *list,listStudentType std)
{
 listNode *new = makeNewNode(std);
 new->next=list->root;
 list->root=new;
 list->cur=list->root;
}
void insertAfterCurrent(LIST *list,listStudentType std)
{
    listNode *new =makeNewNode(std);
    if ( list->root == NULL ) {
        list->root = new;
        list->cur = list->root;
    } else
    {
         new->next = list->cur->next;
        list->cur->next = new;
        list->cur = new;
    }
}