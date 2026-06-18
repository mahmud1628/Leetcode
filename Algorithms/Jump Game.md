## Solution 1: [Accepted]
```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        vector<bool> v(n, false); // ith value indicates whether we can go from index i to the end
        v[n - 1] = true;

        for(int i = n - 2; i >= 0; i--) {
            int max_jump_len = nums[i];

            for(int jump_len = max_jump_len; jump_len > 0; jump_len--) {
                if(i + jump_len < n && v[i + jump_len]) {
                    v[i] = true;
                    break;
                }
            }
        }

        return v[0];
    }
};
```

### Idea:
> First we take a boolean array(`v`) of size `n` where `v[i]` indicates whether we can go to the end from index `i`.
> Clearly `v[n-1]` is always true.
> Now, we start from index `i = n - 2`. We look at `nums[i]`, which gives the maximum jump length from index `i`. We check all possible jumps (from `1` to `nums[i]`) and if we find a jump that leads to an index `j` such that `v[j]` is true, we set `v[i]` to true and break the inner loop.
> Finally, we return `v[0]`.

### Time Complexity: O(n * l)

### Space Complexity: O(n)

where `n` is the size of the input array and `l` is the maximum value in the input array.

## Solution 2: [Accepted]
```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int farthest_reach = 0;
        int target = nums.size() - 1;

        for(int i = 0; i <= farthest_reach; i++) {
            farthest_reach = max(farthest_reach, i + nums[i]);
            if(farthest_reach >= target) return true;
        }

        return false;
    }
};
```

### Idea:
> Here we keep track of the farthest index we can reach (`farthest_reach`) starting from the 0th index. 
> We iterate through the array, and for each index `i` we update `farthest_reach` to be the maximum of its current value and `i + nums[i]`. 
> If at any point `farthest_reach` is greater than or equal to the target index, we return true. 
> The loop terminates when `i` exceeds `farthest_reach`. Because if `i` exceeds `farthest_reach`, it means we can't reach the current index `i` from any of the previous indices and eventually we can't reach the end too. So we return false.

### Time Complexity: O(n)

### Space Complexity: O(1)
