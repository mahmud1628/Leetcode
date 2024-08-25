# LeetCode 206 - Reverse Linked List
***
## Problem description:
    Given the head of a singly linked list, reverse the list, and return the reversed list.


    Example 1:

        Input: head = [1,2,3,4,5]
        Output: [5,4,3,2,1]

    Example 2:

        Input: head = [1,2]
        Output: [2,1]

    Example 3:

        Input: head = []
        Output: []

### Constraints: 
 * The number of nodes in the list is the range [0, 5000].
 * -5000 <= Node.val <= 5000

## Solutions: 

### Approach 1 [Using stack] : [Accepted]
 * Take a stack
 * Push all the nodes of the list into the stack serially.
 * Now pop them and make a new list.

#### Time complexity: O(n)
#### Space complexity: O(n)

``` cpp
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
    ListNode* reverseList(ListNode* head) {
        if(head == nullptr) return nullptr;
        stack<ListNode*> st;
        ListNode * temp = head;
        while(temp->next != nullptr) {
            st.push(temp);
            temp = temp->next;
        }
        head = temp;
        while(!st.empty()) {
            temp = temp->next = st.top();
            st.pop();
        }
        temp->next = nullptr;
        return head;
    }
};
```

### Approach 2 [Recursion] : [Accepted]
 * If head or head->next is nullptr, then return head.
 * Call the function recursively for head->next and set the return value to temp.
 * Make head its succesors succesor and make heads successor nullptr.
 * At last, return temp.

#### Time complexity: O(n)
#### Space complexity: O(n)


``` cpp
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
    ListNode* reverseList(ListNode* head) {
        if(head == nullptr || head->next == nullptr) return head;
        ListNode * temp = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return temp;
    }
};
```

### Approach 3 [Three pointers] : [Accepted]
 * prev = nullptr, curr = head, next = nullptr
 * Iterate through the linked list until curr is nullptr
    * Set next to curr->next
    * Set curr->next to prev
    * Set prev to curr
    * Set curr to next
 * Return prev

#### Time complexity: O(n)
#### Space comeplexity: O(1)


``` cpp
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
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr, *curr = head, *next = nullptr;
        while(curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};
```