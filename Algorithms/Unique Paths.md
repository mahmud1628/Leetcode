# [LeetCode 62: Unique Paths](https://leetcode.com/problems/unique-paths/description/)

## Solution 1 : [TLE]
```cpp
class Solution {
    int uniquePaths(int m, int n, int curr_m, int curr_n) {
        if(curr_m == m && curr_n == n) return 1;
        if(curr_m > m || curr_n > n) return 0;

        int right = uniquePaths(m, n, curr_m, curr_n + 1);
        int down = uniquePaths(m, n, curr_m + 1, curr_n);

        return right + down;
    }
public:
    int uniquePaths(int m, int n) {
        return uniquePaths(m - 1, n - 1, 0, 0);
    }
};
```

### Idea:
> This is a brute-froce approach.
> * From any cell (curr_m, curr_n), we have only two choices - either we can move right to (curr_m, curr_n + 1) or down to (curr_m + 1, curr_n).
> * If we reach the target cell (m, n), it means we have found a unique path.
> * If we go out of bounds, it means we have not found a unique path.

### Time Complexity:
> O(2 ^ (m + n))
> * The time complexity of this approach is O(2^(m+n)) because at each step, we have two choices.

### Space Complexity:
> O(m + n)
> * The space complexity of this approach is O(m+n) because of the recursion stack.

## Solution 2: [Accepted]
```cpp
class Solution {
    int uniquePaths(int m, int n, int curr_m, int curr_n, vector<vector<int>> & mem) {
        if(curr_m == m && curr_n == n) return 1;
        if(curr_m > m || curr_n > n) return 0;

        if(mem[curr_m][curr_n] != -1) return mem[curr_m][curr_n];

        int right = uniquePaths(m, n, curr_m, curr_n + 1, mem);
        int down = uniquePaths(m, n, curr_m + 1, curr_n, mem);

        return mem[curr_m][curr_n] = right + down;
    }
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> mem(m, vector<int>(n, -1));
        return uniquePaths(m - 1, n - 1, 0, 0, mem);
    }
};
```

### Idea:
> We use memoization to store the results of the subproblems.

### Time Complexity:
> O(m * n)
> * The time complexity of this approach is O(m*n) because we are calculating for each cell only once.

### Space Complexity:
> O(m * n)
> * The space complexity of this approach is O(m*n) because of the memoization table.


## Solution 3: [Accepted]
```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> mem(m, vector<int>(n, 0));
        mem[m - 1][n - 1] = 1;
        for(int i = m - 1; i >= 0; i--) {
            for(int j = n - 1; j >= 0; j--) {
                int right = 0, down = 0;
                if(i != m - 1) down = mem[i + 1][j]; 
                if(j != n - 1) right = mem[i][j + 1];
                if(i != m - 1 || j != n - 1) mem[i][j] = right + down;
            }
        }

        return mem[0][0];
    }
};
```

### Idea: 
> The top-down dynamic programming approach is converted into a bottom-up dynamic programming approach here.
> * We are iterating from the bottom-right cell to the top-left cell.
> * For each cell, we are calculating the number of unique paths to reach the target cell.
> * The base case is the target cell, which has only one unique path to reach the target cell.

### Time Complexity:
> O(m * n)
> * The time complexity of this approach is O(m*n) because we are calculating for each cell only once.

### Space Complexity:
> O(m * n)
> * The space complexity of this approach is O(m*n) because of the memoization table.

## Solution 4: [Accepted]
```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> row(n, 0); // each row has n columns
        row[n - 1] = 1;
        for(int i = m - 1; i >= 0; i--) {
            for(int j = n - 1; j >= 0; j--) {
                int right = 0;
                int down = row[j];
                if(j != n - 1) right = row[j + 1];
                if(i != m - 1 || j != n - 1) row[j] = right + down;
            }
        }

        return row[0];
    }
};
```

### Idea:
> 1. The Two-Row Realization:\
> To compute any value in the current row `i`, we only depend on values from the row directly below it (`i + 1`) and the cell to its immediate right (`j + 1`). Because we have no dependency on rows `i + 2` or deeper, the older rows become dead weight in memory. So we can keep track of the row below the current one only.
> 2. In-Place Overwriting (The Single-Row Trick):\
> We can compress the space further into a single 1D array of size `n` by running our inner loop backward (from right to left: j = n - 1 down to 0).When processing column j, our single array row implicitly holds two distinct layers of time simultaneously:row[j] has not been overwritten yet for the current row `i`, so it still retains its value from the row below (`i + 1`). This acts perfectly as `down`. `row[j + 1]` was just updated in the previous iteration of the inner loop, meaning it already holds the fresh value for the current row `i`. This acts perfectly as `right`.By executing `row[j] = right + down`, we safely overwrite the old row's data with the current row's calculated sum. The single array functions as a rolling wave, dynamically updating itself row-by-row until the final answer settles at `row[0]`.

### Time Complexity:
> O(m * n)

### Space Complexity:
> O(n)

## Solution 5: [Accepted]
```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        int N = m + n - 2;
        int K = min(m - 1, n - 1);

        long long ans = 1;
        for(int i = 1; i <= K; i++) {
            ans = ans * (N - K + i) / i;
        }
        return ans;
    }
};
```

### Idea: Mathematical Optimization - The Combinatorics Approach

Instead of using Dynamic Programming to simulate the movement step-by-step, we can reframe the problem as a classic combinatorial puzzle.

#### 1. The Fixed Move Invariant
To travel from the top-left corner $(0, 0)$ to the bottom-right corner $(m-1, n-1)$ of an $m \times n$ grid, we are bound by a strict geometric invariant:
* We must move **Down ($D$)** exactly $m - 1$ times.
* We must move **Right ($R$)** exactly $n - 1$ times.

No matter which path we take, the total number of moves will *always* be exactly:
$$N = (m - 1) + (n - 1) = m + n - 2$$

#### 2. Reframing as a Combinations Problem
Every unique path is simply a unique permutation of these $N$ total moves. For example, in a $3 \times 3$ grid, one path might be $D \rightarrow R \rightarrow D \rightarrow R$, while another might be $R \rightarrow R \rightarrow D \rightarrow D$. 



Because the sequence always contains exactly $m - 1$ Down moves and $n - 1$ Right moves, the problem reduces to: 
*"Out of $m + n - 2$ available slots in our move sequence, in how many unique ways can we choose $m - 1$ slots to be Down moves or $n - 1$ slots to be Right moves?"*

This is the definition of a combination, mathematically expressed as $N\text{C}K$:

$$\binom{m + n - 2}{m - 1} = \frac{(m + n - 2)!}{(m - 1)!(n - 1)!}$$

#### 3. Algorithmic Advantage
By calculating this binomial coefficient using a single loop, we completely bypass arrays, matrices, and recursion stacks.

### Time Complexity:  $O(\min(m, n))$
> Computing the combination requires a single linear loop proportional to the number of moves.

### Space Complexity: $O(1)$
> Requires no extra memory, running purely on primitive numeric variables.