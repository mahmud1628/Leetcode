# [LeetCode 39 - Combination Sum](https://leetcode.com/problems/combination-sum)
***
## Solution 1:
```cpp
class Solution {
    void recursiveCombinationSum(vector<int> & nums, int index, int target, vector<int> & current_combination, vector<vector<int>> & combinations) {
        if(target == 0) {
            combinations.push_back(current_combination);
            return;
        }
        if(index == nums.size() || target < 0) {
            return;
        }

        int n = nums[index];
        // pick n
        current_combination.push_back(n);
        recursiveCombinationSum(nums, index, target - n, current_combination, combinations);

        // doesn't pick n
        current_combination.pop_back();
        recursiveCombinationSum(nums, index + 1, target, current_combination, combinations);
    }
public:
    vector<vector<int>> combinationSum(vector<int>& nums, int target) {
        vector<vector<int>> combinations;
        vector<int> current_combination;
        recursiveCombinationSum(nums, 0, target, current_combination, combinations);
        return combinations;
    }
};
```

### Idea:
    At each index, we have two options. We either pick the element on that index, or we don't pick it.
    If we pick it, index doesn't change and target decreases.
    If we don't pick it, index increases and target remains the same.
