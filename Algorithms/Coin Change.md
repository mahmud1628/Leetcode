# [LeetCode 322 - Coin Change](https://leetcode.com/problems/coin-change/description/)
***
## Solution 1: [Accepted on Neetcode, TLE on leetcode]
```cpp
class Solution {
    void searchCombinations(vector<int> & coins, int amount, int index, int  current_coins, int & min_coins) {
        if(amount == 0) {
            min_coins = min(min_coins, current_coins);
            return;
        }
        if(amount < 0 || index >= coins.size()) return;

        // pick current coin
        searchCombinations(coins, amount - coins[index], index, current_coins + 1, min_coins);

        // don't pick current coin
        searchCombinations(coins, amount, index + 1, current_coins, min_coins);
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        int min_coins = INT_MAX;
        searchCombinations(coins, amount, 0, 0, min_coins);
        if(min_coins == INT_MAX) return -1;
        return min_coins;
    }
};
```

### Idea: 
> Problem is similar to the `Combination Sum` problem. We use recursion to find all combinations of coins that sum up to the amount. We keep track of the minimum number of coins used in each combination. If the amount becomes 0, we update the minimum number of coins used. If the amount becomes negative or we reach the end of the coins array, we return.  

### Time Complexity: 
> $O(2^n)$

### Space Complexity: 
> $O(n)$

## Solution 2: [Accepted on Neetcode, TLE on leetcode]
```cpp
class Solution {
    void searchCombinations(vector<int> & coins, int amount, int index, int  current_coins, int & min_coins) {
        if(amount == 0) {
            min_coins = min(min_coins, current_coins);
            return;
        }
        if(amount < 0 || index >= coins.size()) return;

        // pick current coin
        searchCombinations(coins, amount - coins[index], index, current_coins + 1, min_coins);

        // don't pick current coin
        searchCombinations(coins, amount, index + 1, current_coins, min_coins);
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        int min_coins = INT_MAX;
        searchCombinations(coins, amount, 0, 0, min_coins);
        if(min_coins == INT_MAX) return -1;
        return min_coins;
    }
};
```

### Idea: 
> Problem is similar to the `Combination Sum` problem. We use recursion to find all combinations of coins that sum up to the amount. We keep track of the minimum number of coins used in each combination. If the amount becomes 0, we update the minimum number of coins used. If the amount becomes negative or we reach the end of the coins array, we return.  

### Time Complexity: 
> $O(2^n)$

### Space Complexity: 
> $O(n)$


## Solution 2: [Accepted]
```cpp
class Solution {
    int searchCombinations(vector<int> & coins, int amount, vector<int> & mem) {
        if(amount < 0) return -1;
        if(amount == 0) return 0;
        if(mem[amount] == -2) {
            int min_coins = INT_MAX;
            for(int coin : coins) {
                int res = searchCombinations(coins, amount - coin, mem);
                if(res != -1) min_coins = min(min_coins, 1 + res);
            }
            if(min_coins != INT_MAX) mem[amount] = min_coins;
            else mem[amount] = -1; // -1 denotes impossible to make the amount
        }

        return mem[amount];
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> mem(amount + 1, -2); // -2 denotes unvisited
        return searchCombinations(coins, amount, mem);
    }
};
```

### Idea:
> Instead of pick/not pick from each index approach, we can think in terms of the amount. For a given amount, we can try to make it by subtracting each coin from it and recursively call the function for the remaining amount. We take the minimum of all the results. Memoization is used to store the results of subproblems to avoid redundant calculations.

###  Time Complexity:
> $O(amount * n)$

### Space Complexity:
> $O(amount)$

where n is the number of coins and `amount` is the target amount.  

The second approach would not be very good for `Combination Sum` problem because in the second approach we are not bothered about duplicate combinations.We iterate through every coin in each call, that can make duplicate combinations. For example, if the `coins` array is [1,2] and amount is 3, we can have combinations (1,1,1) and (1,2) and (2, 1) - but we only want (1,1,1) and (1,2) in `Combination Sum`. Also memoization would not be that effective either because in `Combination Sum` we need to store the result for each combination, not a single integer like in this problem.   