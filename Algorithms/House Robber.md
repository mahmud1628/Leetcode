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

## Solution 2:

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> money(nums.size());
        if(nums.size()==1) return nums[0];
        money[0] = nums[0];
        money[1] = max(nums[0],nums[1]);
        for(int i=2;i<nums.size();i++){
            money[i] = max(money[i-1],money[i-2]+nums[i]);
        }
        return money[nums.size()-1];
    }
};
```

### Idea:
The problem asks us to find the maximum amount of money a robber can steal from a row of houses, with the constraint that they cannot rob two adjacent houses. This problem can be solved using dynamic programming. The core idea is to build up the solution by considering the maximum money that can be robbed up to each house. For any given house `i`, the robber has two choices: either rob house `i` or not rob house `i`.

If the robber robs house `i`, they cannot have robbed house `i-1`. Therefore, the total money would be the money in house `i` plus the maximum money they could have robbed up to house `i-2`.

If the robber does not rob house `i`, then the maximum money they can have is simply the maximum money they could have robbed up to house `i-1`.

The algorithm chooses the option that yields the maximum amount of money.

### Algorithm:
1.  **Base Cases:**
    *   If there's only one house (`nums.size() == 1`), the robber can only rob that house, so return `nums[0]`.
    *   Create a DP array `money` of the same size as `nums`.
    *   `money[0]` is initialized to `nums[0]` (maximum money robbing up to the first house).
    *   `money[1]` is initialized to `max(nums[0], nums[1])` (maximum money robbing up to the second house, either robbing the first or the second).

2.  **Iteration:**
    *   Iterate from the third house (`i = 2`) up to the last house.
    *   For each house `i`, calculate `money[i]` as the maximum of two options:
        *   `money[i-1]`: The maximum money obtained without robbing house `i`.
        *   `money[i-2] + nums[i]`: The maximum money obtained by robbing house `i` (which means we couldn't have robbed `i-1`, so we add `nums[i]` to the max money up to `i-2`).

3.  **Result:**
    *   The final answer is `money[nums.size()-1]`, which represents the maximum money that can be robbed up to the last house.

**Space Optimized version for solution 2:**
1.  **Base Cases:**
    *   If there's only one house (`nums.size() == 1`), return `nums[0]`.
    *   If there are two houses (`nums.size() == 2`), return `max(nums[0], nums[1])`.
    *   Initialize `prev1` to `nums[0]` (representing `money[i-2]` in the iteration).
    *   Initialize `prev2` to `max(nums[0], nums[1])` (representing `money[i-1]` in the iteration).
    *   Initialize `maximum` to store the current maximum.

2.  **Iteration:**
    *   Iterate from the third house (`i = 2`) up to the last house.
    *   For each house `i`, calculate `maximum` as the max of two options:
        *   `prev1 + nums[i]`: Robbing the current house `i` (add its value to the max money two houses back).
        *   `prev2`: Not robbing the current house `i` (take the max money from the previous house).
    *   Update `prev1` to `prev2` for the next iteration.
    *   Update `prev2` to `maximum` for the next iteration.

3.  **Result:**
    *   The final answer is `maximum` after the loop finishes.

### Time Complexity:
Both solutions iterate through the `nums` array once. Therefore, the time complexity is **O(n)**, where `n` is the number of houses.

### Space Complexity:
*   **Solution 2:** Uses a DP array of size `n`. So, the space complexity is **O(n)**.
*   **Space optimized version of solution 2:** Uses only a few constant variables (`prev1`, `prev2`, `maximum`). So, the space complexity is **O(1)**.
