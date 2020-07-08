/*
 * =====================================================================================
 *
 *       Filename:  llist-common-node.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/17/2020 08:32:13 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "LinkList.h"
typedef struct LinkList ListNode;

class SharedNode {
public:
    int length(ListNode* head) {
        int len = 1;
        while (head->next != NULL)
        {
            head = head->next;
            ++len;
        }
        return len;
    }

    ListNode* nstep(ListNode* head, int step) {
        while (step-- != 0)
         head = head->next;

        return head;
    }

    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == NULL || headB == NULL) return NULL;
        int len1 = length(headA);
        int len2 = length(headB);
        int delta = len1 < len2 ? (len2 - len1) : (len1-len2);

        if (len1 > len2) {
            headA = nstep(headA, delta);
        }else
            headB = nstep(headB, delta);

        while (headA != NULL && headB != NULL) {
            if (headA == headB) break;
            headA = headA->next;
            headB = headB->next;
        }

        if (headA == NULL || headB == NULL) return NULL;
        return headA;

    }
};
