# LeetCode 143 - Reorder List
***
## Problem description:
    You are given the head of a singly linked-list. The list can be represented as:

    L0 → L1 → … → Ln - 1 → Ln
    Reorder the list to be on the following form:

    L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
    You may not modify the values in the list's nodes. Only nodes themselves may be changed.

    

    Example 1:
        Input: head = [1,2,3,4]
        Output: [1,4,2,3]

    Example 2:
        Input: head = [1,2,3,4,5]
        Output: [1,5,2,4,3]
 

### Constraints:
 * The number of nodes in the list is in the range [1, 5 * 104].
 * 1 <= Node.val <= 1000

## Solutions: 

### Approach 1 : [Accepted]
 * Take a vector of ListNode pointers.
 * Push all the nodes into the vector serially.
 * If leng th of the vector is 1, then return. Because there is only one node in the list.
 * Take a dummy node temp and set head equal to temp. temp will be used as the reordered list.
 * left = 0, right = length of vector - 1.
 * Take a while loop 
    * If left is equal to right, then only one node is left. So insert v[left] to the reordered list, i.e, temp and break the loop.
    * If left is greater than right, then all the nodes have been inserted. So break the loop.
    * Otherwise, insert v[left] and v[right] to the reordered list and increase left and decrease right.
 * As we need to modify the "head" node, so at last set head = head->next.

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
    void reorderList(ListNode* head) {
        vector<ListNode * > v;
        while(head) {
            v.push_back(head);
            head = head->next;
        }
        if(v.size() == 1) return;

        ListNode * temp = new ListNode(-1);
        head = temp;

        int left = 0, right = v.size() - 1;
        while(true) {
            if(left == right) {
                temp = temp->next = v[left];
                break;
            }
            else if(left > right) {
                break;
            }
            temp = temp->next = v[left];
            temp = temp->next = v[right];
            left++;
            right--;
        }
        temp->next = nullptr;
        head = head->next;
        
    }
};
```