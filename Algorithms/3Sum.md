# LeetCode 15 - 3Sum
***
## Problem Description:
    Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

    Notice that the solution set must not contain duplicate triplets.


    Example 1:
    Input: nums = [-1,0,1,2,-1,-4]
    Output: [[-1,-1,2],[-1,0,1]]
    Explanation: 
    nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
    nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
    nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
    The distinct triplets are [-1,0,1] and [-1,-1,2].
    Notice that the order of the output and the order of the triplets does not matter.

    Example 2:
    Input: nums = [0,1,1]
    Output: []
    Explanation: The only possible triplet does not sum up to 0.

    Example 3:
    Input: nums = [0,0,0]
    Output: [[0,0,0]]
    Explanation: The only possible triplet sums up to 0.

### Constraints:
 * 3 <= nums.length <= 3000
 * -105 <= nums[i] <= 105

## Solutions: 

### Approach 1 : [Accepted]
 * Sort the array.
 * Take an unordered map. Insert all the numbers in the map. Take the number as key and the index as value.
 * Create an empty 2D vector, res, to store the triplets.
 * Iterate through the sorted array.
    * To avoid duplicates, check if nums[i] is equal to nums[i-1], if so, then continue to next iteration.
    * Take n = nums[i] and target = 0 - n. Now we will use the "two sum" algorithm with this target.
    * Take another loop to iterate through the array
        * Again to avoid duplicates, check if nums[j] is equal to nums[j-1].
        * Find t = target - nums[j] in the map.
            * If found, and if the index of that found number is greater than j, then add {n,nums[j],t} to the res vector.
 * At last, return res.

#### Time Complexity: O(n^2)
#### Space Complexity: O(n)

``` cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        unordered_map<int,int> m;
        for(int i = 0;i<nums.size();i++) {
            m[nums[i]] = i;
        }
        vector<vector<int>> res;
        for(int i = 0;i<nums.size();i++) {
            if(i > 0 && nums[i] == nums[i-1]) continue;
            int n = nums[i];
            int target = 0 - n;
            for(int j = i+1;j<nums.size();j++) {
                if(j > i + 1 && nums[j] == nums[j-1]) continue;
                int t = target - nums[j];
                if(m.find(t) == m.end()) {
                    continue;
                }
                else {
                    if(m[t] <= j) {
                        continue;
                    }
                    else {
                        res.push_back({n,nums[j],t});
                    }
                }
            }
        }
        return res;
    }
};
```


### Approach 2 : [Accepted]
 * Sort the array.
 * Take a 2D vector to store the triplets.
 * Iterate through the sorted array.
    * To avoid duplicates, check if nums[i] is equal to nums[i-1].
    * Take target = 0 - nums[i].
    * Take two variables left = i + 1 and right = nums.size() - 1.
    * Take another two variables per1 and pre2 and initialize them with a number that is not in the array. These will be used to avoid duplicates.
    * Take a while loop 
        * sum = nums[left] + nums[right]
        * If sum is equal to target,
            * Check if pre1 is equal to nums[left] and pre2 is equal to nums[right]. If so, then these are duplicate results. So ignore them and continue to next iteration.
            * Otherwise push {nums[i],nums[left],nums[right]} to the vector res.
        * If sum is less than target, then increase left by 1.
        * If sum is greater than target, then decrease right by 1.
 * After iterating the whole array, return res.

#### Time complexity: O(n^2)
#### Space complexity: O(1)

``` cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        for(int i = 0;i<nums.size();i++) {
            if(i > 0 && nums[i] == nums[i-1]) continue;
            int target = 0 - nums[i];
            int left = i + 1;
            int right = nums.size() - 1;
            int pre1 = nums[0] - 1;
            int pre2 = pre1;
            while(left < right) {
                int sum = nums[left] + nums[right];
                if(sum == target) {
                    if(left <= i) {
                        left++;
                        continue;
                    }
                    if(pre1 == nums[left] && pre2 == nums[right]) {
                        left++;
                        right--;
                        continue;
                    }
                    res.push_back({nums[i],nums[left],nums[right]});
                    pre1 = nums[left];
                    pre2 = nums[right];
                    left++;
                    right--;
                }
                else if(sum < target) {
                    left++;
                }
                else {
                    right--;
                }

            }
        }
        return res;
    }
};
```