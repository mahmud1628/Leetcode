# Leetcode 1 - Two Sum
***
## Problem Description: 
    Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.<br>
    You may assume that each input would have exactly one solution, and you may not use the same element twice.<br>
    You can return the answer in any order.
    
    
    Example 1:
    
    Input: nums = [2,7,11,15], target = 9
    Output: [0,1]
    Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
    Example 2:
    
    Input: nums = [3,2,4], target = 6
    Output: [1,2]
    Example 3:
    
    Input: nums = [3,3], target = 6
    Output: [0,1]
 

### Constraints:

 * 2 <= nums.length <= 104
 * -109 <= nums[i] <= 109
 * -109 <= target <= 109
 * Only one valid answer exists.
 

### Follow-up: Can you come up with an algorithm that is less than O(n^2) time complexity?

## Solutions:

### Approach 1 [using hash table]: [Accepted]
   * Take an unordered map mp.
   * Iterate through the array.<br>
     In each iteration, take one number n = target - nums[i] and find n in the map.<br>
     If n is found in the map then return {mp[n],i}.<br>
     Else insert {nums[i],i} to the map.

``` cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> mp;
        for(int i=0;i<nums.size();i++) {
            int n=target-nums[i];
            if(mp.find(n)==mp.end()) {
                mp[nums[i]]=i;
            }
            else 
                return {mp[n],i};
        }
        return {-1,-1};
    }
};
```
#### Time Complexity: O(n)
