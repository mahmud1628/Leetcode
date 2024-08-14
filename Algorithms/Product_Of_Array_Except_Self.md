# LeetCode 238 - Product of Array Except Self
***
## Problem Description:
    Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

    The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

    You must write an algorithm that runs in O(n) time and without using the division operation.

    

    Example 1:

    Input: nums = [1,2,3,4]
    Output: [24,12,8,6]
    Example 2:

    Input: nums = [-1,1,0,-3,3]
    Output: [0,0,9,0,0]

### Constraints:
 * 2 <= nums.length <= 105
 * -30 <= nums[i] <= 30
 * The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

### Follow up:
 Can you solve the problem in O(1) extra space complexity? 
 (The output array does not count as extra space for space complexity analysis.)

## Solutions:

### Approach 1[Using two array for prefix and suffix product]: [Accepted]
 * Take two arrays prefix and suffix.
 * Initialize prefix[0] = nums[0] and suffix[n-1] = nums[n-1].
 * Take a loop (starting from 1, ending at n - 1) and calculate prefix[i] = prefix[i-1] * nums[i]
 * Take another loop (starting from n-2, ending at 0) and calculate suffix[i] = suffix[i+1] * nums[i]
 * Now take an array answer. Initialize answer[0] = suffix[1] and answer[n-1] = prefix[n-2]
 * Take a loop and calculate answer[i] = suffix[i+1] * prefix[i-1]
 * Return the array answer.

``` cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefix(n,1);
        vector<int> suffix(n,1);
        prefix[0] = nums[0];
        suffix[n-1] = nums[n-1];
        for(int i=1;i<n;i++) {
            prefix[i] = prefix[i-1] * nums[i];
        }
        for(int i=nums.size() - 2;i>=0;i--) {
            suffix[i] = suffix[i+1] * nums[i];
        }
        vector<int> answer(n);
        answer[0] = suffix[1];
        answer[n-1] = prefix[n-2];
        for(int i=1;i<n-1;i++) {
            answer[i] = prefix[i-1] * suffix[i+1];
        }
        return answer;
    }
};
```
#### Time Complexity: O(n)
#### Auxiliary Space: O(n)


### Approach 2[Minimize auxiliary space]: [Accepted]
 * Take an array ans and a variable t.
 * Initialize t to 1.
 * Take a loop and calculate ans[i] = t and t = t * nums[i].
 * Again initialize t to 1.
 * Take another loop and calculate ans[i] *= t and t = t * nums[i].
 * Return the array ans.

``` cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        int t = 1;
        vector<int> ans(n);
        for(int i=0;i<n;i++) {
            ans[i] = t;
            t = t * nums[i];
        }
        t = 1;
        for(int i = n-1;i>=0;i--) {
            ans[i] *= t;
            t = t * nums[i];
        }
        return ans;
    }
};
```
#### Time Complexity: O(n)
#### Auxiliary space: o(1)


