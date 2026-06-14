# [LeetCode 70 - Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)
***
## Solution 1: [Accepted]
```cpp
class Solution {
    int climbStairs(int remaining_steps, vector<int> & mem) {
        if(remaining_steps == 0) return 1;
        if(remaining_steps < 0) return 0;

        if(mem[remaining_steps] == -1) {
            mem[remaining_steps] = climbStairs(remaining_steps - 1, mem) + climbStairs(remaining_steps - 2, mem);
        }

        return mem[remaining_steps];
    }
public:
    int climbStairs(int n) {
        vector<int> mem(n + 1, -1);
        return climbStairs(n, mem);
    }
};
```

### Idea:
> From each step, explore two paths. One using `1` step up and another using `2` steps up. Use memoization to store the results of the subproblems.

### Time Complexity:
> O(n)

### Space Complexity:
> O(n)

Where `n` is the number of stairs.

## Solution 2: [Accepted]
```cpp
class Solution {
public:
    int climbStairs(int n) {
        if(n <= 1) return 1;

        int prev2 = 1;
        int prev1 = 1;
        int current;

        for(int i = 2; i <= n; i++) {
            current = prev1 + prev2;
            prev2 = prev1;
            prev1 = current;
        }

        return current;
    }
};
```

### Idea: Optimizing the space
> An iterative approach that only stores the previous two values. Technically we only need the Fibonacci sequence to solve this problem.

### Time Complexity:
> O(n)

### Space Complexity:
> O(1)

Where `n` is the number of stairs.


