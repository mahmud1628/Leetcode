# LeetCode - Remove nth node from end of list
***
## Problem description:
    Given the head of a linked list, remove the nth node from the end of the list and return its head.

    Example 1:
        Input: head = [1,2,3,4,5], n = 2
        Output: [1,2,3,5]
    
    Example 2:
        Input: head = [1], n = 1
        Output: []

    Example 3:
        Input: head = [1,2], n = 1
        Output: [1]


### Contraints:
 * The number of nodes in the list is sz.
 * 1 <= sz <= 30
 * 0 <= Node.val <= 100
 * 1 <= n <= sz

#### Follow up: Could you do this in one pass?

## Solutions:

### Approach 1 [Using stack] : [Accepted]
 * Take an empty stack
 * Push all the nodes to the stack
 * If there is only one node in the stack, then we have only one node in the list. So return nullptr, as after removing the only node we will get nullptr only.
 * If size of the stack is equal to n, then we need to remove the first node of the list. So return head->next.
 * Otherwise pop from the stack n - 1 times. Take the last popped node in a temporary variable.
 * Lastly pop again to pop the nth node from end. 
 * Now set the next of the node at top of the stack to the node stored in the temporary variable.
 * Now return head.

#### Time complexity: O(n)
#### Space complexity: O(n)

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        stack<ListNode*> st;
        ListNode* temp = head;
        while(temp) {
            st.push(temp);
            temp = temp->next;
        }
        if(st.size() == 1) return nullptr;
        if(st.size() == n) {
            return head->next;
        }
        n--;
        while(n--) {
            temp = st.top();
            st.pop();
        }
        st.pop();
        st.top()->next = temp;
        return head;
    }
};
```

### Approach 2 [Using vector] : [Accepted]
 * Take an empty vector
 * Push all the nodes to the vector.
 * If size of the vector is 1, then we have only one node in the list. So return nullptr.
 * If size of the vector is equal to n, then we need to remove the first node of the list. So return head->next.
 * Otherwise set the next pointer of the (n+1)th node(from end) to the (n-1)th node(from end). And return the first node in the vector.

#### Time complexity: O(n)
#### Space complexity: O(n)

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        vector<ListNode*> v;
        while(head) {
            v.push_back(head);
            head = head->next;
        }
        if(v.size() == 1) return nullptr;
        if(v.size() == n) return v[1];
        v[v.size()-1-n]->next = v[v.size()-n]->next;
        return v[0];
    }
};
```

### Approach 3 [Using total size of list] : [Accepted]
 * Iterate through the list once and calculate the size of the list.
 * If size is equal to 1, then there is only one node and after deleting it, there will be no node in the list, so return nullptr.
 * If size is equal to n, then we need to remove the first node actually. So return head->next.
 * Now again iterate through the list from start, reach at the previous node of the node to be deleted by iterating (size - n - 1) times.
 * Change next pointer of the previous node to the next node of the node to be deleted.
 * Return head.

#### Time complexity: O(n)
#### Space complexity: O(1)

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode * temp = head;
        int size = 0;
        while(temp) {
            size++;
            temp = temp->next;
        }
        if(size == 1) return nullptr;
        if(size == n) return head->next;
        n = size - n -1;
        temp = head;
        while(n--) {
            temp = temp -> next;
        }
        temp->next = temp->next->next;
        return head;
    }
};
```

### Appraoch 4 [Two pointers, solved in one pass] : [Accepted]
 * If head->next is nullptr, then there is only one node in the list. So return nullptr.
 * Take two ListNode pointers right and left and initialize them with head.
 * Now update the right pointer n times with its next.
 * If right becomes nullptr after updating, then it means that the size of the list and n are equal. So we need to remove the first node of the list. Thus return head->next.
 * Now update left and right with their respective next pointers until right->next becomes nullptr. Then left pointer will arrive at the node to be deleted.
 * Now set left->next = left->next->next.
 * Return head.

#### Time complexity: O(n)
#### Space complexity: O(1)

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(!head->next) return nullptr; 
        ListNode * right = head, * left = head;

        while(n--) {
            right = right->next;
        }
        if(!right) return head->next;
        while(right->next) {
            left = left->next;
            right = right->next;
        }
        left->next = left->next->next;
        return head;
    }
};
```