# [LeetCode 300 - Longest Increasing Subsequnce](https://leetcode.com/problems/longest-increasing-subsequence/description/)
***
## Solution 1:

```cpp
class Solution {
    int recursiveLIS(int index, int prev_index, vector<int> & nums, vector<vector<int>> & mem) {
        if(index == nums.size()) return 0;
        if(mem[index + 1][prev_index + 1] != -1) return mem[index + 1][prev_index + 1];
        int len = recursiveLIS(index + 1, prev_index, nums, mem);
        if(prev_index == -1 || nums[index] > nums[prev_index]) len = max(len, 1 + recursiveLIS(index + 1, index, nums, mem));
        return mem[index + 1][prev_index + 1] = len;
    }
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<vector<int>> mem(nums.size() + 1, vector<int>(nums.size() + 1, -1));

        return recursiveLIS(0, -1, nums, mem);
    }
};
```

### Idea:
The algorithm uses a recursive approach with memoization (dynamic programming) to find the longest increasing subsequence. It explores two possibilities at each element: either include the current element in the subsequence (if it's greater than the previous element included) or exclude it. The memoization table stores the results of subproblems to avoid redundant calculations.

### Algorithm:
1.  **`lengthOfLIS(nums)` function:**
    *   Initializes a 2D memoization table `mem` of size `(n+1) x (n+1)` with all values set to -1. `n` is the size of the input array `nums`. The table is used to store results of `recursiveLIS(index, prev_index)` where `index` and `prev_index` are mapped to `index+1` and `prev_index+1` for 0-based indexing convenience.
    *   Calls the `recursiveLIS` helper function starting from index 0 and a `prev_index` of -1 (indicating no previous element).
    *   Returns the result of `recursiveLIS`.

2.  **`recursiveLIS(index, prev_index, nums, mem)` function:**
    *   **Base Case:** If `index` reaches the end of the `nums` array (`index == nums.size()`), it means we have processed all elements, and the length of the subsequence from this point is 0.
    *   **Memoization Check:** If the result for the current `(index, prev_index)` pair is already computed and stored in `mem[index + 1][prev_index + 1]`, return the stored value.
    *   **Recursive Steps:**
        *   **Exclude Current Element:** Calculate the length of the longest increasing subsequence by excluding the current element `nums[index]`. This is done by recursively calling `recursiveLIS(index + 1, prev_index, nums, mem)`. Let this length be `len`.
        *   **Include Current Element (if possible):** If `prev_index` is -1 (meaning this is the first element being considered) or if the current element `nums[index]` is strictly greater than the element at `nums[prev_index]`, then we can potentially include `nums[index]` in the subsequence. In this case, calculate the length by including `nums[index]` (which adds 1 to the length) and recursively calling `recursiveLIS(index + 1, index, nums, mem)` to find the longest increasing subsequence from the next element, considering the current element `nums[index]` as the new previous element. Update `len` with the maximum of its current value and this new length.
    *   **Store and Return:** Store the computed `len` in `mem[index + 1][prev_index + 1]` and return `len`.

### Time Complexity:
The time complexity is O(n^2), where n is the length of the input array `nums`. This is because the `recursiveLIS` function has two parameters that can take on n+1 values each (index and prev\_index). Due to memoization, each unique state `(index, prev_index)` is computed only once.

### Space Complexity:
The space complexity is O(n^2) due to the memoization table `mem` which stores the results for all possible `(index, prev_index)` states. The recursion depth can also contribute up to O(n) to the space complexity in the worst case, but this is dominated by the memoization table.
