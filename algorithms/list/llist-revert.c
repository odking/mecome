/*
 * =====================================================================================
 *
 *       Filename:  llist-revert.c
 *
 *    Description: k 
 *
 *        Version:  1.0
 *        Created:  05/28/2020 02:13:41 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "link-list.h"
#include <stdlib.h>

LinkList* revert(LinkList* head)
{
    if (head == NULL || head->next == NULL)
        return head;

    LinkList *nh = revert(head->next);
    head->next->next = head;
    head->next = NULL;
    return nh;
}

