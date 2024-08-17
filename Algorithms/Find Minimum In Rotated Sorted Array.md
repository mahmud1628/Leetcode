# LeetCode 153 - Find Minimum in Rotated Sorted Array
***
## Problem description:
    Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, the array nums = [0,1,2,4,5,6,7] might become:

    [4,5,6,7,0,1,2] if it was rotated 4 times.
    [0,1,2,4,5,6,7] if it was rotated 7 times.
    Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

    Given the sorted rotated array nums of unique elements, return the minimum element of this array.

    You must write an algorithm that runs in O(log n) time.

    

    Example 1:
    Input: nums = [3,4,5,1,2]
    Output: 1
    Explanation: The original array was [1,2,3,4,5] rotated 3 times.

    Example 2:
    Input: nums = [4,5,6,7,0,1,2]
    Output: 0
    Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.

    Example 3:
    Input: nums = [11,13,15,17]
    Output: 11
    Explanation: The original array was [11,13,15,17] and it was rotated 4 times. 

### Constraints:
 * n == nums.length
 * 1 <= n <= 5000
 * -5000 <= nums[i] <= 5000
 * All the integers of nums are unique.
 * nums is sorted and rotated between 1 and n times.

## Soltuions:

### Approach 1 [Binary search] : [Accepted]
 * Take two variables left = 0 and right = nums.size() - 1.
 * Take a while loop 
    * compute mid.
    * If left is equal to right or (right - 1), then return the minimum of nums[left] and nums[right]
    * If nums[mid] is greater than nums[left] and nums[right], then minimum wil be between mid and right, so update left = mid + 1.
    * If nums[mid] is less than nums[left] and nums[mid - 1], then minimum will be between mid and right, so update left = mid (in this case, mid can be the minimum number too, so set left equal to mid instead of mid + 1)
    * In all other cases, minimum will be between left and mid. So set right = mid - 1.

#### Time complexity: O(logn)
#### Space complexity: O(1)
``` cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        while(left <= right) {
            int mid = (left + right)/2;
            if(left == right - 1 || left == right) {
                return min(nums[left],nums[right]);
            }
            if(nums[mid] > nums[left] && nums[right] < nums[mid]) {
                left = mid + 1;
            }
            else if(nums[mid] < nums[left] && nums[mid] < nums[mid - 1]) {
                left = mid;
            }
            else {
                right = mid - 1;
            }
        }
        return 0;
    }
};
```