# LeetCode 11 - Container With Most Water
***
## Problem description: 
    You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

    Find two lines that together with the x-axis form a container, such that the container contains the most water.

    Return the maximum amount of water a container can store.

    Notice that you may not slant the container.

 

    Example 1:
    Input: height = [1,8,6,2,5,4,8,3,7]
    Output: 49
    Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.

    Example 2:
    Input: height = [1,1]
    Output: 1

### Constraints: 
 * n == height.length
 * 2 <= n <= 105
 * 0 <= height[i] <= 104

## Solutions:

### Approach 1 : [Time limit exceeded]
 * Compute the area for each pair of vertical lines. And the take the maximum of them.

#### Time complexity: O(n^2)
#### Space complexity: O(1)

``` cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int max = 0;
        for(int i = 0;i<height.size();i++) {
            for(int j = 0;j<height.size();j++) {
                int h = height[i] < height[j] ? height[i] : height[j];
                int t = i < j ? j - i : i - j;
                int temp = h * t;
                max = max > temp ? max : temp;
            }
        }
        return max;
    }
};
```


### Approach 2 : [Accepted]
 * Take two pointers left = 0, right = height.size() - 1
 * max_area = 0.
 * Take a while loop 
    * Compute area for current heights whixh are indexed at leftand right and update max_area if needed.
    * Update left or right. If height[left] is less than height[right], then increase left. Otherwise decrease right. 
        We are updating the pointer that have the lower height. Because while computing the area, we used the lower height and if we update the pointer with the bigger height now, then we will never find any area greater than the previous one computed. So we need to update the pointer with the lower height.
 * Return max_area.

#### Time complexity: O(n)
#### Space complexity: O(1)

``` cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int max_area = 0;
        while(left < right) {
            int h = min(height[left],height[right]);
            max_area = max(max_area, h * (right - left));
            height[left] <= height[right] ? left++ : right--;
        }
        return max_area;
    }
};
```

