# LeetCode 128 - Longest Consecutive Sequence
***
## Problem Description:
    Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.

    You must write an algorithm that runs in O(n) time.

    Example 1:
    Input: nums = [100,4,200,1,3,2]
    Output: 4
    Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.

    Example 2:
    Input: nums = [0,3,7,2,5,8,4,6,0,1]
    Output: 9

### Constraints: 
 * 0 <= nums.length <= 105
 * -109 <= nums[i] <= 109

## Solutions:

### Approach 1 [Sorting] : [Accepted] (But time complexity is not expected according to question)
 * Sort the given array
 * Take two variables and initialize: temp = 1, max = 1.
 * Iterate through the sorted array (start from 1 and end at nums.size() - 1)
 * If the current number is equal to the previous number + 1, then increase temp by 1 and update max if needed.
 * If the number is equal to previous number, then do nothing and go to the next index.
 * Otherwise reset temp to 1.
 * At last, return max.

#### Time Complexity: O(nlogn)
#### Space Complexity: O(1)

``` cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        if(nums.size() == 1) return 1;
        sort(nums.begin(),nums.end());
        int temp = 1;
        int max = 1;
        for(int i=1;i<nums.size();i++) {
            if(nums[i] == nums[i-1] + 1) {
                temp++;
                max = max > temp ? max : temp;
            }
            else if(nums[i] == nums[i-1]) {
                continue;
            }
            else {
                temp = 1;
            }
        }
        return max;
    }
};
```

### Approach 2[Using hash table] : [Accepted]
 * Take an unordered set s.
 * Insert all the numbers of the array to the set.
 * Initialize an variable ans = 0.
 * Iterate through the array.
 * Find nums[i] - 1 in the set.
 * If it is not found in the set, then nums[i] can be the first element of a subsequence. Initialize a variable temp_ans to 0 and repeatedly find the next consecutive elements of that number in the set, if found, then increase temp_ans by 1. Stop finding when a consecutive element can't be found in the set and update ans if needed.
 * At last, return ans.

#### Time Complexity: O(n)
#### Space Complexity: O(n)

``` cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s;
        for(auto a : nums) 
            s.insert(a);
        int ans = 0;
        for(int i = 0;i<nums.size();i++ ) {
            if(s.find(nums[i] - 1) == s.end()) {
                int temp = nums[i];
                int temp_ans = 0;
                while(s.find(temp++) != s.end()) {
                    temp_ans++;
                }
                ans = ans > temp_ans ? ans : temp_ans;
            }
        }
        return ans;
    }
};
```
