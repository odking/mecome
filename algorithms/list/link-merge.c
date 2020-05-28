#include <stdlib.h>
#include "link-list.h"

#define null 0
LinkList * sort_merge2(LinkList *p1, LinkList *p2, LinkList *head, LinkList *tail)
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
        return sort_merge2(p1, p2, head, tail);
    }
}

LinkList* sort_merge(LinkList *head1, LinkList *head2)
{
    LinkList *head = null;
    if (head1 == NULL) return head2;
    else if (head2 == NULL ) return head1;
    else
    {
        LinkList *tail = null;
        if (head1->data > head2->data)
        {
            head = head2;
            head2=head2->next;
        }
        else
        {
            head = head1;
            head1=head1->next;
        }
        tail = head;
        return sort_merge2(head1, head2, head, tail);
    }
}


