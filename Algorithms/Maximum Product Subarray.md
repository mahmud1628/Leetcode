# [LeetCode 152 - Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/description/)
***
## Solution 1: [Accepted on Neetcode, TLE on Leetcode]
```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int max_product = INT_MIN;

        for(int i = 0; i < nums.size(); i++) {
            int current_product = 1;
            for(int j = i; j < nums.size(); j++) {
                current_product *= nums[j];
                max_product = max(max_product, current_product);
            }
        }

        return max_product;
    }
};
```

### Idea:
> A brute-force approach to solve this problem is to iterate through all possible subarrays of the given array `nums` and calculate the product of each subarray. Then, we keep track of the maximum product found so far and return it at the end.

### Time Complexity:
> $O(n^2)$  

### Space Complexity:
> $O(1)$  

where $n$ is the length of the array `nums`.

## Solution 2: [Accepted]
```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int max_product = nums[0];
        int running_max = max_product;
        int running_min = max_product;

        for(int i = 1; i < nums.size(); i++) {
            int n = nums[i];
            int a = running_max * n;
            int b = running_min * n;
            running_max = max(max(a, b), n);
            running_min = min(min(a, b), n);

            max_product = max(max_product, running_max);
        }

        return max_product;
    }
};
```

### Idea:
> This is known as Kadane's algorithm. The key idea is to keep track of the maximum and minimum product of the subarrays ending at the current index. This is because the maximum product can be obtained by multiplying the current number with the previous maximum product (if the current number is positive) or the previous minimum product (if the current number is negative). Similarly, the minimum product can be obtained by multiplying the current number with the previous maximum product (if the current number is negative) or the previous minimum product (if the current number is positive).

### Time Complexity:
> $O(n)$

### Space Complexity:
> $O(1)$

where `n` is the length of the array `nums`.    