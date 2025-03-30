# Leetcode 215 - Kth Largest Element in an Array
***
## Problem description:
    Given an integer array nums and an integer k, return the kth largest element in the array.

    Note that it is the kth largest element in the sorted order, not the kth distinct element.

    Can you solve it without sorting?

    Example 1:

    Input: nums = [3,2,1,5,6,4], k = 2
    Output: 5

    Example 2:

    Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
    Output: 4
 

### Constraints:
 * 1 <= k <= nums.length <= 105
 * -104 <= nums[i] <= 104

## Solutions:

### Approach 1 [Sorting]: [Accepted]
 * Sort in descending order and return the kth item.

#### Time complexity: O(nlogn)
#### Space complexity: O(nlogn), n is the size of the array.

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.rbegin(),nums.rend());
        return nums[k-1];
    }
};
```

### Approach 2 : [Accepted]
 * Take a min heap.
 * Repeatedly push the elements of the array to the min heap.
 * If the size of the min heap gets larger than k , then pop one element (extract the min).
 * Thus, at the end, we will have the largest k elements in the min heap. And the minimum of the largest k elements is the kth largest element. Therefore, return the top of the min heap at the end.
 
#### Time complexity : O(nlogk)
#### Space complexity : O(k)

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> q;

        for(int i : nums) {
            q.push(i);
            if(q.size() > k) q.pop();
        }
        return q.top();
    }
};
```
