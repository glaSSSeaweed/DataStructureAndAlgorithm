/**
  * Definition of Doubly-ListNode
 * class DoublyListNode {
 * public:
 *     int val;
 *     DoublyListNode *next, *prev;
 *     DoublyListNode(int val) {
 *         this->val = val;
 *         this->prev = this->next = NULL;
 *     }
 * } * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */

class Solution {
public:
    void merge(TreeNode* node, DoublyListNode*& end)
    {
    	if (node == nullptr)
    		return;
    	merge(node->left, end);
    	DoublyListNode* tmp = new DoublyListNode(node->val);
    	end->next = tmp;
    	tmp->prev = end;
    	end = tmp;
    	merge(node->right, end);
    }
     
    DoublyListNode * bstToDoublyList(TreeNode * root) {
        DoublyListNode* end = new DoublyListNode(0);
	    DoublyListNode* first = end;
	    merge(root, end);
	    return first->next;
    }
};