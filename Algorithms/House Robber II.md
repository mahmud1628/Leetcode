# [LeetCode 213 - House Robber II](https://leetcode.com/problems/house-robber-ii/)
***
## Solution 1 :

```cpp
class Solution {
    int helper(int house, vector<int> & nums, vector<int> & mem, int limit) {
        if(house > limit) return 0;
        if(mem[house] == -1)
            mem[house] = max(nums[house] + helper(house + 2, nums, mem, limit), helper(house + 1, nums, mem, limit));
        return mem[house];
    }
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];
        vector<int> mem1(nums.size(), -1);
        vector<int> mem2 = mem1;
        return max(helper(0, nums, mem1, nums.size() - 2), helper(1, nums, mem2, nums.size() - 1));
    }
};
```

### Idea:
The problem is to find the maximum amount of money that can be robbed from houses arranged in a circle, with the constraint that no two adjacent houses can be robbed. Since the houses are in a circle, the first and last houses are considered adjacent. This circular arrangement makes it impossible to rob both the first and the last house simultaneously.

The core idea to solve this is to break down the circular problem into two linear problems. We can consider two scenarios:
1. Robbing houses from the first house up to the second-to-last house (excluding the last house).
2. Robbing houses from the second house up to the last house (excluding the first house).

The maximum amount of money that can be robbed will be the maximum of the results from these two linear subproblems.

For each linear subproblem, we can use dynamic programming. For a given house, we have two choices: either rob it or don't rob it.
- If we rob the current house, we cannot rob the next house. So, the total amount would be the money in the current house plus the maximum amount we can rob from the house two steps ahead.
- If we don't rob the current house, we can then consider robbing the next house. So, the total amount would be the maximum amount we can rob from the house one step ahead.
We take the maximum of these two choices.

Memoization is used to store the results of subproblems to avoid redundant calculations.

### Algorithm:
1.  **`rob(nums)` function:**
    *   **Base Case:** If there's only one house (`nums.size() == 1`), return the money in that house.
    *   **Initialization:** Create two memoization vectors, `mem1` and `mem2`, both initialized with -1 (indicating uncomputed values) and of the same size as `nums`.
    *   **Two Linear Subproblems:**
        *   Call the `helper` function for the first scenario: `helper(0, nums, mem1, nums.size() - 2)`. This calculates the maximum money robbed from house 0 up to house `nums.size() - 2`.
        *   Call the `helper` function for the second scenario: `helper(1, nums, mem2, nums.size() - 1)`. This calculates the maximum money robbed from house 1 up to house `nums.size() - 1`.
    *   **Return Maximum:** Return the maximum of the results from the two `helper` calls.

2.  **`helper(house, nums, mem, limit)` function:**
    *   **Base Case (Out of Bounds):** If the current `house` index is beyond the `limit`, it means we have considered all valid houses in this subproblem, so return 0.
    *   **Memoization Check:** If `mem[house]` is not -1, it means the result for this `house` has already been computed. Return the stored value `mem[house]`.
    *   **Dynamic Programming Calculation:** If the result is not memoized:
        *   **Option 1 (Rob current house):** `nums[house] + helper(house + 2, nums, mem, limit)`. We rob the current `house` and then recursively call `helper` for the house two steps ahead.
        *   **Option 2 (Don't rob current house):** `helper(house + 1, nums, mem, limit)`. We don't rob the current `house` and then recursively call `helper` for the next house.
        *   The result for the current `house` is the maximum of these two options: `max(nums[house] + helper(house + 2, nums, mem, limit), helper(house + 1, nums, mem, limit))`.
    *   **Store and Return:** Store the calculated maximum value in `mem[house]` and then return it.

### Time Complexity:
The `rob` function calls `helper` twice. The `helper` function uses memoization, meaning each subproblem (calculating the maximum robbable amount for a specific starting house index) is computed only once. Since there are `n` houses, and in the worst case, the `helper` function visits each house index at most once within its respective linear traversal, the time complexity is O(n), where n is the number of houses.

### Space Complexity:
Two memoization vectors, `mem1` and `mem2`, are used, each of size n. Therefore, the space complexity is O(n) due to the memoization arrays. The recursion depth in the `helper` function can also go up to O(n) in the worst case, contributing to the space complexity in terms of the call stack.
