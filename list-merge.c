#include <stdio.h>
#include <stdlib.h>

#define null 0
typedef struct LinkList
{
    int data;
    struct LinkList *next;
}LinkList;

LinkList *head1 = null;
LinkList *head2 = null;

LinkList * revert2(LinkList *p1, LinkList *p2, LinkList *head, LinkList *tail)
{
    if (p1 == NULL)
    {
        tail->next = p2;
        return head;
    }
    else if (p2 == NULL)
    {
        tail->next = p1;
        return head;
    }
    else
    {
        if (p1->data >= p2->data)
        {
            tail->next = p2;
            p2 = p2->next;
        }
        else
        {
            tail->next = p1;
            p1 = p1->next;
        }
        tail = tail->next;
        return revert2(p1, p2, head, tail);
    }
}

LinkList* revert(LinkList *head1, LinkList *head2)
{
    LinkList *head = null;
    if (head1 == NULL) return head2;
    else if (head2 == NULL ) return head1;
    else
    {
        LinkList *tail = null;
        if (head1->data > head2->data)
            head = head2;
        else
            head = head1;
        tail = head;
        return revert2(head1, head2, head, tail);
    }
}


void main(int argc, char ** argv)
{
    head1 = (LinkList*)malloc(sizeof(LinkList));
    head1->data=5;
    head1->next=null;
    head2 = (LinkList*)malloc(sizeof(LinkList));
    head1->data=3;
    head1->next=null;
    LinkList *p, *tmp = head1;
    int i;
    for (i=0; i < 4; i++)
    {
        p = (LinkList*)malloc(sizeof(LinkList));
        p->data=head1->data+i;
        p->next=null;
        tmp->next=p;
        tmp=tmp->next;
    }

    p=null; tmp=head2;
    for (i=0; i < 4; i++)
    {
        p = (LinkList*)malloc(sizeof(LinkList));
        p->data=head2->data+i;
        p->next=null;
        tmp->next=p;
        tmp=tmp->next;
    }

    p = revert(head1, head2);
    while (p!= null)
    {
        printf("%d ", p->data);
    }
}
