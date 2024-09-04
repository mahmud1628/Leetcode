# LeetCode 23 - Merge k sorted lists
***
## Problem description:
    You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

    Merge all the linked-lists into one sorted linked-list and return it.


    Example 1:
        Input: lists = [[1,4,5],[1,3,4],[2,6]]
        Output: [1,1,2,3,4,4,5,6]
        Explanation: The linked-lists are:
        [
        1->4->5,
        1->3->4,
        2->6
        ]
        merging them into one sorted list:
        1->1->2->3->4->4->5->6

    Example 2:
        Input: lists = []
        Output: []
        
    Example 3:
        Input: lists = [[]]
        Output: []

### Constraints:
 * k == lists.length
 * 0 <= k <= 104
 * 0 <= lists[i].length <= 500
 * -104 <= lists[i][j] <= 104
 * lists[i] is sorted in ascending order.
 * The sum of lists[i].length will not exceed 104.

## Solutions:


### Aproach 1 [naive approach] : [Accepted]
 * Take a vector.
 * Push all the node values to the vector.
 * Sort the vector.
 * Make a new list using the values that are now sorted in the vector.
 * Return the new list.

#### Time complexity: O(NlogN) where N is the total number of nodes present in the lists.
#### Space complexity: O(N) where N is the total number of nodes present in the lists.

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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size() == 0) return nullptr;
        vector<int> v;
        for(auto node : lists) {
            while(node) {
                v.push_back(node->val);
                node = node->next;
            }
        }
        if(v.size() == 0) return nullptr;
        sort(v.begin(),v.end());
        ListNode * sorted_list = new ListNode(v[0]);
        ListNode * temp = sorted_list;
        for(int i = 1;i<v.size();i++) {
            temp = temp->next = new ListNode(v[i]);
        }
        temp->next = nullptr;
        return sorted_list;
    }
};
```

### Approach 2 [Using min heap] : [Accepted]
 * Take a min priority queue.
 * Push all the head nodes of the lists to the priority queue.
 * Take a new head for the merged list.
 * Take a while loop, do the following until the priority queue is empty.
    * Pop the top node from the priority queue and insert it to the merged list. If the next node of the top node in the lists is not nullptr then push the next node of the top node to the priority queue.
 * Return the new merged list.

#### Time complexity: O(N logk) where N is the number of total nodes present in the lists.
#### Space complexity: O(k) 

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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size() == 0) return nullptr;
        priority_queue<pair<int,ListNode*>,vector<pair<int,ListNode*>>,greater<pair<int,ListNode*>>> pq;
        for(auto node : lists) {
            if(node)
                pq.push(make_pair(node->val,node));
        }
        if(!pq.size()) return nullptr;

        ListNode * temp = new ListNode(-1);
        ListNode * sorted_list = temp;

        while(pq.size()) {
            temp = temp->next = pq.top().second;
            pq.pop();
            if(temp->next) {
                pq.push(make_pair(temp->next->val,temp->next));
            }
        }
        temp->next = nullptr;

        return sorted_list->next;
    }
};
```