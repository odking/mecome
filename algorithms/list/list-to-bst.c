/*
 * =====================================================================================
 *
 *       Filename:  list-to-bst.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/03/2020 01:21:05 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "list-to-bst.h"
#include <stdlib.h>

ListNode* GetMNode(ListNode* head, ListNode* tail) {
    ListNode* fast = head;
    ListNode* slow = head;
    while (fast != tail && fast->next != tail) {
        fast = fast->next->next;
        slow = slow->next;
    }

    return slow;
}

TreeNode* buildBalanceTree(ListNode* head, ListNode *tail) {
    if (head == tail) return nullptr;
    if (head->next == tail) {
        TreeNode* inode = malloc(sizeof(struct TreeNode*));
        inode->val = head->data;
        inode->left = inode->right = nullptr;
        return inode;
    }

    ListNode* mnode = GetMNode(head, tail);
    TreeNode* root = malloc(sizeof(struct TreeNode*));
    root->val = mnode->data;
    root->left = buildBalanceTree(head, mnode);
    root->right = buildBalanceTree(mnode->next, tail);
    return root;
}


TreeNode* sortedListToBST(ListNode* head) {
    return buildBalanceTree(head, nullptr);
}

