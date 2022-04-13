#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct ListNode {
    int data;
    struct ListNode *next;
}List;

void init_list(List **head)
{
    *head=(List*)malloc(sizeof(List));
    (*head)->next=NULL;
}
List *createlist()
{
    int num;
   List *q=NULL,*head=NULL,*p;
   printf("输入非递减有序的数,以输入-1截至:\n");
    do{
        scanf("%d",&num);
        if(num!=-1)
        {
            p=(List*)malloc(sizeof(List));
            p->data=num;
            p->next=NULL;
            if(head){
                q->next=p;
            }else{
                head=p;
            }q=p;
        }
    }while(num!=-1);
    if(q) q->next=head;
    return head;
}
List *Delete( List *head, ElementType minK, ElementType maxK )
{
    List *p=head,*q=NULL;
    ElementType Con=0;
    if(!p) return head;
    do{
        if(p->data<maxK&&p->data>minK)
        {
            if(q){
                q->next=p->next;
                free(p);
                p=q;
            }else{
                Con=1;
                q=p;
            }
        }else q=p;
        p=p->next;
    }while(p!=head);
    if(Con==1)
    {
        if(p==q) return NULL;
        q->next=p->next;
        head=p->next;
        free(p);
    }
    return head;
}
void Printlist(List *head)
{
     if(!head||!head->next){
         printf("NULL\n");
         return;}
     List *p = head;
     while (p->next!=head) {
           printf("%d ", p->data);
           p = p->next;
     }
     printf("%d\n",p->data);
}
void Decompose(List *head,List *L1_head,List *L2_head)
{
    List *p=head,*i=NULL,*j=NULL;
    if(head==NULL) return;
    do{
        if(p->data%2==1){
            if(i){
                i->next=p;
                i=i->next;
            }else{
                *L1_head=*p;
                i=L1_head;
            }
        }else{
            if(j){
                j->next=p;
                j=j->next;
            }else{
                *L2_head=*p;
                j=L2_head;
            }
        }
        p=p->next;
    }while(p!=head);
    if(i) i->next=L1_head;
    if(j) j->next=L2_head;
}
int main()
{
    List *L=NULL,*L1=NULL,*L2=NULL;
    init_list(&L1);
    init_list(&L2);
    ElementType minK, maxK;
    L = createlist();
    printf("依次输入minK与maxK:\n");
    scanf("%d %d", &minK, &maxK);
    printf("原链表返回：\n");
    Printlist( L );
    L = Delete( L, minK, maxK );
    printf("删除后链表返回：\n");
    Printlist( L );
    Decompose( L , L1 , L2 );
    printf("奇数链表L1返回：\n");
    Printlist( L1 );
    printf("偶数链表L2返回：\n");
    Printlist( L2 );
    return 0;
}
