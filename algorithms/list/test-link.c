/*
 * =====================================================================================
 *
 *       Filename:  test-link.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/28/2020 02:07:19 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "link-list.h"
#include "list-to-bst.h"
#include <stdio.h>
#include <stdlib.h>

void printList(LinkList* head)
{
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    LinkList *head1 = NULL;
    LinkList *head2 = NULL;


    head1 = (LinkList*)malloc(sizeof(LinkList));
    head1->data=5;
    head1->next=NULL;
    head2 = (LinkList*)malloc(sizeof(LinkList));
    head2->data=3;
    head2->next=NULL;
    LinkList *tmp = head1;
    LinkList *p = NULL;
    int i;
    for (i=0; i < 4; i++)
    {
        p = (LinkList*)malloc(sizeof(LinkList));
        p->data=head1->data+i;
        p->next=NULL;
        tmp->next=p;
        tmp=tmp->next;
    }

    p=NULL; tmp=head2;
    for (i=0; i < 4; i++)
    {
        p = (LinkList*)malloc(sizeof(LinkList));
        p->data=head2->data+i;
        p->next=NULL;
        tmp->next=p;
        tmp=tmp->next;
    }

    printf("merge two list\n");
    p = sort_merge(head1, head2);
    printList(p);

    printf("revert a list\n");
    p = revert(p);
    printList(p);

    printf("list to bst\n");
    printList(p);
    sortedListToBST(p);

    return 0;
}
