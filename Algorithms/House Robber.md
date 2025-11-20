# [LeetCode 198 - House Robber](https://leetcode.com/problems/house-robber/)
***
## Solution 1:

```cpp
class Solution {
    int helper(int house, vector<int> & nums, vector<int> & mem) {
        if(house >= nums.size()) return 0;
        if(mem[house] == -1)
            mem[house] = max(nums[house] + helper(house + 2, nums, mem), helper(house + 1, nums, mem));
        return mem[house];
    }
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];
        vector<int> mem(nums.size(), -1);
        return helper(0, nums, mem);
    }
};
```

### Idea:
The core idea is to decide for each house whether to rob it or not. If we rob a house, we cannot rob the next one. If we don't rob a house, we can potentially rob the next one. We want to maximize the total money. This problem has overlapping subproblems and optimal substructure, suggesting a dynamic programming or recursive approach with memoization. The recursive function `helper` calculates the maximum money that can be robbed starting from a given `house` index.

### Algorithm:
1.  **`rob(nums)` function:**
    *   Handles the base case: if there's only one house (`nums.size() == 1`), return the money from that house.
    *   Initializes a memoization table `mem` of the same size as `nums`, filled with -1. This table will store the maximum money that can be robbed starting from each house to avoid recomputing.
    *   Calls the `helper` function starting from the first house (index 0) and returns its result.

2.  **`helper(house, nums, mem)` function:**
    *   **Base Case:** If `house` is out of bounds (i.e., `house >= nums.size()`), it means there are no more houses to rob, so return 0.
    *   **Memoization Check:** If `mem[house]` is not -1, it means the result for this `house` has already been computed, so return the stored value.
    *   **Recursive Step:** If the result is not memoized, calculate it by considering two options:
        *   **Option 1: Rob the current `house`:** The total money would be `nums[house]` plus the maximum money that can be robbed starting from `house + 2` (skipping the next house). This is `nums[house] + helper(house + 2, nums, mem)`.
        *   **Option 2: Don't rob the current `house`:** The total money would be the maximum money that can be robbed starting from the next house (`house + 1`). This is `helper(house + 1, nums, mem)`.
    *   The maximum of these two options is the optimal solution for the current `house`. Store this result in `mem[house]` before returning it.

### Time Complexity:
O(N), where N is the number of houses. Each house's maximum rob amount is computed only once due to memoization. The `helper` function is called for each house at most once.

### Space Complexity:
O(N), where N is the number of houses. This is due to the recursion stack depth in the worst case (when we always choose to skip a house) and the `mem` vector used for memoization, which stores results for each house.
