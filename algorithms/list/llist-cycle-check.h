/*
 * =====================================================================================
 *
 *       Filename:  llist-cycle-check.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/17/2020 09:02:22 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "link-list.h"

class CycleCheck {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return nullptr;
        ListNode *fast = head;
        ListNode *slow = head;

        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) break;
        }
        if (fast != slow) return NULL;

        ListNode* slow2 = head;
        while (slow2 != slow) {
            slow2 = slow2->next;
            slow = slow->next;
            cout << "slow2 " << (long)slow2 ;
        }

        return slow2;
    }
};
