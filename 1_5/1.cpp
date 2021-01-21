class Forward_List_iterator
{
public:
	Forward_List_iterator() : itPtr(nullptr)
	{ }
	Forward_List_iterator(ListNode* t)
		: itPtr(t) { }

	Forward_List_iterator& operator++()
	{
		itPtr = itPtr->next;
		return *this;
	}
	bool operator!=(Forward_List_iterator& other)
	{
		return !(itPtr == other.itPtr);
	}
	bool operator==(Forward_List_iterator& other)
	{
		return itPtr == other.itPtr;
	}
	Forward_List_iterator& operator=(const Forward_List_iterator& other)
	{
		itPtr = other.itPtr;
		return *this;
	}
	ListNode* operator->()
	{
		return itPtr;
	}
	ListNode* operator&()
	{
		return itPtr;
	}
	ListNode operator*()
	{
		return *itPtr;
	}
private:
	ListNode *itPtr;
};


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
class Solution {
public:

    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr)
            return head;
        typedef Forward_List_iterator iterator;
        ListNode  headerNode;
        headerNode.next = head;

        iterator current(head);
        iterator tmp(current->next);
        iterator next = current;
        iterator previous(&headerNode);

        int counter = 0;
        while (&(++next) != nullptr)
        {

            if (next->val == current->val) {
                counter += 1;
            }
            else {
                if (counter != 0)
                {
                    while (current != next)
                    {
                        delete &current;
                        current = tmp;
                        ++tmp;
                    }
                    previous->next = &next;
                    current = next;
                    counter = 0;
                }
                else
                {
                    previous = &current;
                    current = &next;
                    tmp = current->next;
                }
            }
        }
        if (&tmp != nullptr)
        {
            while (tmp != next)
            {
                tmp = current->next;
                delete &current;
                current = tmp;

            }
            previous->next = &next;
            current = next;
        }
        return headerNode.next;

    }
};