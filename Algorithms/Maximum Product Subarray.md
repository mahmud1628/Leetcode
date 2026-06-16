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
> This is known as an extended version of Kadane's algorithm for product. The key idea is to keep track of the maximum and minimum product of the subarrays ending at the current index. This is because the maximum product can be obtained by multiplying the current number with the previous maximum product (if the current number is positive) or the previous minimum product (if the current number is negative). Similarly, the minimum product can be obtained by multiplying the current number with the previous maximum product (if the current number is negative) or the previous minimum product (if the current number is positive).

### Time Complexity:
> $O(n)$

### Space Complexity:
> $O(1)$

where `n` is the length of the array `nums`.   

## Solution 3: [Accepted]
```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int max_product = INT_MIN;
        int n = nums.size();

        int prefix_product = 1;
        int suffix_product = 1;

        for(int i = 0; i < n; i++) {
            if(nums[i] == 0) {
                max_product = max(max_product, 0);
                prefix_product = 1;
            } else {
                prefix_product = prefix_product * nums[i];
                max_product = max(max_product, prefix_product);
            }

            if(nums[n - i - 1] == 0) {
                max_product = max(max_product, 0);
                suffix_product = 1;
            } else {
                suffix_product = suffix_product * nums[n - i - 1];
                max_product = max(max_product, suffix_product);
            }
        }

        return max_product;
    }
};
```

### Idea:
> If there are no negative numbers in the array, the maximum product is simply the product of all the numbers.
> If there are even numbers of negative numbers, then the product of all the numbers is positive and hence the maximum product.
> If there are odd numbers of negative numbers, then the product of all the numbers is negative. This time we need to discard one negative number. If we discard one negative number, then the answer is the product of the previous numbers (prefix_product) or the product of the latter numbers (suffix_product). We take the maximum of the two.
> In case of 0, multiplying with 0 will give us 0. So we don't want to take 0 in our subarray. So we skip that index and reset the prefix_product and suffix_product to 1 as the start of our new sub array.


### Time Complexity: 
> $O(n)$

### Space Complexity: 
> $O(1)$    

where `n` is the length of the array `nums`.  