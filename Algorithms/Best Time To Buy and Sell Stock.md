# LeetCode 121 - Best Time to Buy and Sell Stcok
*** 
## Problem description:
    You are given an array prices where prices[i] is the price of a given stock on the ith day.

    You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

    Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

    
    Example 1:
    Input: prices = [7,1,5,3,6,4]
    Output: 5
    Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
    Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

    Example 2:
    Input: prices = [7,6,4,3,1]
    Output: 0
    Explanation: In this case, no transactions are done and the max profit = 0.

### Constraints:
 * 1 <= prices.length <= 105
 * 0 <= prices[i] <= 104

## Solutions:

### Approach 1 [Brute force] : [Time limit exceeded]
 * Compare each pair of prices to get the maximum profit

#### Time complexity: O(n^2)
#### Space complexity: O(1)

``` cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int max = 0;
        for(int i = 0;i<prices.size();i++) {
            int a = prices[i];
            for(int j = i+1;j<prices.size();j++) {
                if(prices[j] > a) {
                    max = max > prices[j] - a ? max : prices[j] - a;
                }
            }
        }
        return max;
    }
};
```

### Approach 2 [Using auxiliary array] : [Accepted]
 * Take an array temp of size of the given array.This will store the maximum number that appears at the right of a number in the given array including itself.
 * Compute the values of array temp
 * profit = 0.
 * Compute maximum profit using a for loop, take maximum of profit and temp[i] - prices[i] in each iteration.

#### Time complexity: O(n)
#### Space complexity: O(n)

``` cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int temp[n]; // array to store the maximum number that appears at the right of an index
        int max_right = prices[n-1];
        for(int i=n-1;i>=0;i--) {
            temp[i] = max_right = max(prices[i],max_right);
        }
        int profit = 0;
        for(int i = 0;i<n;i++) {
            profit = max(profit,temp[i] - prices[i]);
        }
        return profit;
    }
};
```


### Approach 3[Two pointers] : [Accepted]
 * Take three variables buy = 0 (left pointer), sell = 1 (right pointer), profit = 0.
 * Iterate through the array while sell is less than the size of the array
    * If prices[buy] is not less than prices[sell]. then it is not a profitable transaction. All the numbers at the left of sell are now greater than or equal to prices[sell], so no need to check them anymore as buying day because we won't find any profitable transaction in this way. Thus update buy = sell.
    * Otherwise take the maximum of profit and (prices[sell] - prices[buy]).
    * Always update sell = sell + 1.
 * Return profit.

#### Time complexity: O(n)
#### Space complexity: O(1)

``` cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int buy = 0, sell = 1; 
        int profit = 0;
        while(sell < n) {
            if(prices[buy] >= prices[sell]) {
                buy = sell;
            }
            else {
                profit = max(profit,prices[sell] - prices[buy]);
            }
            sell++;
        }
        return profit;
    }
};
```


### Approach 4[Using minimum price so far] : [Accepted]
 * min_so_far = prices[o]. This stores the minimum price of the stock so far.
 * max_profit = 0
 * Iterate through the array.
    * Update min_so_far if needed.
    * Compute maximum possible profit of current day by subtracting min_so_far from prices[i]
    * Take maximum of max_profit and (prices[i] - min_so_far) 
 * Retrun max_profit

#### Time complexity: O(n)
#### Space complexity: O(1)

``` cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int min_so_far = prices[0];
        int max_profit = 0;
        for(int i=1;i<n;i++) {
            min_so_far = min(min_so_far,prices[i]);
            max_profit = max(max_profit,prices[i] - min_so_far);
        }
        return max_profit;
    }
};
```
