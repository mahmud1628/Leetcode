# [LeetCode 53 - Maximum Subarray](https://leetcode.com/problems/maximum-subarray/description/)
## Solution 1: [Accepted]
```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {

        int s = nums[0];
        int max_sum = s;

        for(int i = 1; i < nums.size(); i++) {
            if(s < 0) {
                s = 0;
            }
            s += nums[i];

            max_sum = max(max_sum, s);
        }

        return max_sum;
    }
};
```

### Idea:
> Take a running sum, `s`.
> If `s` is ever negative, reset it to `0` (because including a negative prefix will only decrease the sum of any subarray starting from there).
> Keep track of the maximum sum encountered during this process, `max_sum`.

### Time Complexity: O(n)

### Space Complexity: O(1)