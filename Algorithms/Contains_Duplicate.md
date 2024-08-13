# LeetCode 217 - Contains Duplicate
***
## Problem Description:
    Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.

    Example 1:

    Input: nums = [1,2,3,1]
    Output: true
    Example 2:

    Input: nums = [1,2,3,4]
    Output: false
    Example 3:

    Input: nums = [1,1,1,3,3,4,3,2,4,2]
    Output: true

### Constraints: 
 * 1 <= nums.length <= 105
 * -109 <= nums[i] <= 109

## Solutions: 

### Approach 1 [Using hash table]: [Accepted]
 * Take an unordered map.
 * Iterate through the array, find each number in the map.
 * If the number is already in the map (duplicate found), then return true.
 * At the end of the iteration (no duplicate found), return false.

``` cpp
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int,int> m;
        for(auto a: nums) {
            if(m.find(a) == m.end())
                m[a] = 1;
            else return true;
        }
        return false;
    }
};
```
#### Time Complexity: O(n)