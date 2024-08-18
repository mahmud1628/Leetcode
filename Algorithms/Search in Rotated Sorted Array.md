# LeetCode 33 - Search in Rotated Sorted Array
*** 
## Problem description:
    There is an integer array nums sorted in ascending order (with distinct values).

    Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].

    Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

    You must write an algorithm with O(log n) runtime complexity.

    

    Example 1:
    Input: nums = [4,5,6,7,0,1,2], target = 0
    Output: 4

    Example 2:
    Input: nums = [4,5,6,7,0,1,2], target = 3
    Output: -1

    Example 3:
    Input: nums = [1], target = 0
    Output: -1
 
### Constraints:
 * 1 <= nums.length <= 5000
 * -104 <= nums[i] <= 104
 * All values of nums are unique.
 * nums is an ascending array that is possibly rotated.
 * -104 <= target <= 104


## Solutions:

### Approach 1[binary search] : [Accepted]

#### Intuition:
 If we look at the array carefully, either half of the array is sorted in ascending order always (both may also be sorted). We need to find the sorted half first and then check if target is in that half.

#### Algorithm:
 * Take left = 0, right = nums.size() - 1.
 * Take a while loop 
    * compute mid.
    * If nums[left] is equal to target, then return left. Same goes for right and mid.
    * If nums[left] is less than nums[mid], then left half is sorted.
        * If target is in in this half, then update right = mid - 1.
        * Otherwise update left = mid + 1.
    * If nums[mid] is less than nums[right], then right half is sorted.
        * If target is in this half, then update left = mid + 1.
        * Otherwise update right = mid - 1.
 * If target is not found, then return -1.

#### Time complexity: O(log n) 
#### Space complexity: O(1)

``` cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        while(left <= right) {
            if(nums[left] == target) return left;
            if(nums[right] == target) return right;
            int mid = (left + right) / 2;
            if(nums[mid] == target) return mid;
            if(nums[left] < nums[mid]) {
                if(nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                }
                else {
                    left = mid + 1;
                }
            }
            else {
                if(nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};
```
