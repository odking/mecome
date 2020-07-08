/*
 * =====================================================================================
 *
 *       Filename:  list-to-bst.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/03/2020 01:03:56 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef LIST_TO_BST_H
#define LIST_TO_BST_H


#define nullptr 0
#define new malloc

#include "link-list.h"
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

typedef LinkList ListNode;

TreeNode* sortedListToBST(ListNode* head);

#endif
