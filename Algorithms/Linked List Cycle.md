# LeetCode 141 - Linked List Cycle
***
## Problem description:
    Given head, the head of a linked list, determine if the linked list has a cycle in it.

    There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.

    Return true if there is a cycle in the linked list. Otherwise, return false.

    

    Example 1:
        Input: head = [3,2,0,-4], pos = 1
        Output: true
        Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).
    
    Example 2:
        Input: head = [1,2], pos = 0
        Output: true
        Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.

    Example 3:
        Input: head = [1], pos = -1
        Output: false
        Explanation: There is no cycle in the linked list.

### Constraints: 
 * The number of the nodes in the list is in the range [0, 104].
 * -10<sup>5</sup> <= Node.val <= 10<sup>5</sup>
 * pos is -1 or a valid index in the linked-list.

#### Follow up: Can you solve it using O(1) (i.e. constant) memory?

## Solutions:

### Approach 1 [Using hash set] : [Accepted]
 * Take an empty set.
 * Iterate through the list.
    * If head is found in the set, then there is a cycle. So return true.
    * Otherwise insert head to the set and update head.
 * After iterating the whole list, return false.

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
    bool hasCycle(ListNode* head) {
        unordered_set<ListNode*> s;
        while(head) {
            if(s.find(head) == s.end()) {
                s.insert(head);
                head = head->next;
            }
            else return true;
        }
        return false;
    }
};
```

### Approach 2 : [Accepted] 
 * Set the val of the head to 100001. From the given constraints, no node in the list has this value.
 * Now iterate through the list.
    * If next node of head has the value 100001, then we have visited that node already. So return true.
    * Otherwise update head = head->next and also update the val of current head to 100001.
 * After iterating the whole list, return false.

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
    bool hasCycle(ListNode* head) {
        if(!head) return false;
        head->val = 100001;
        while(head->next) {
            if(head->next->val == 100001) return true;
            else {
                head = head->next;
                head->val = 100001;
            }
        }
        return false;
    }
};
```
