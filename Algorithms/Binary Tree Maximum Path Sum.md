# [LeetCode 124 - Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/)
*** 

## Solution 1: [Accepted]

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
    /*
        This function returns the maximum possible path sum obtained from the current node if we don't split from current node, that is, we can take either the left subtree or the right subtree in the path
    */
    int MPS(TreeNode* root, int & max_path_sum) {
        int l = 0, r = 0;
        if(root->left) l = MPS(root->left, max_path_sum); // take the max path sum from left subtree considering the left subtree won't be splitted
        if(root->right) r = MPS(root->right, max_path_sum); // take the max path sum from right subtree considering the right subtree won't be splitted
        int spliting_path_sum = root->val + l + r; // path sum considering we are spliting from current node
        if(spliting_path_sum > max_path_sum) max_path_sum = spliting_path_sum;
        int non_spliting_path_sum = root->val + max(max(l, r), 0); // path sum considering we are not spliting from current node
        if(non_spliting_path_sum > max_path_sum) max_path_sum = non_spliting_path_sum;
        return non_spliting_path_sum;
    }
public:
    int maxPathSum(TreeNode* root) {
        int max_path_sum = INT_MIN;
        MPS(root, max_path_sum);
        return max_path_sum;
    }
};
```

### Idea:
To make a path, we need to ensure that we don't split from a node unless that is the topmost node in that path. Here, splitting means that we are taking both the left and right subtree of a node.

At each node, we have two possibilities for having max path sum.

First, we can take the current node as the splitting node, so it must be the top most node in the path, then we calculate the max path sum for that node including both the left and right sub tree. 

Second, we don't split from the current node. Thus this may not be the top most node in the path. Now we calculate the max path sum by including either the left or the right sub tree. 

Between these two possibilities, the one with the maximum value will be the result for that node.

However, for the second case, this node may not be the top most node. So we need to pass the value (obtained in the second case) to the parent.

### Time Complexity:
The time complexity is O(n), where n is the number of nodes in the tree.

### Space Complexity:
The space complexity is O(h), where h is the height of the tree.
