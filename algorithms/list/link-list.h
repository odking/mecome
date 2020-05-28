/*
 * =====================================================================================
 *
 *       Filename:  link-list.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/28/2020 02:11:56 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */
typedef struct LinkList
{
    int data;
    struct LinkList *next;
}LinkList;


LinkList* sort_merge(LinkList *head1, LinkList *head2);
LinkList* revert(LinkList *head);


