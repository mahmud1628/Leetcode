# LeetCode 100 - Same Tree
***
## Problem description:
    Given the roots of two binary trees p and q, write a function to check if they are the same or not.

    Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

    
    Example 1:
        Input: p = [1,2,3], q = [1,2,3]
        Output: true

    Example 2:
        Input: p = [1,2], q = [1,null,2]
        Output: false
    Example 3:
        Input: p = [1,2,1], q = [1,1,2]
        Output: false
    

Constraints:
 * The number of nodes in both trees is in the range [0, 100].
 * -104 <= Node.val <= 104

## Solutions:

### Approach 1 : [Accepted]
 * Check if root is null in both trees, if so, then return true. 
 * Otherwise if one of the root is null, then return false.
 * If above two cases fail, then no root is null. Then check their value and recursively do the same process for left subtree and right subtree of both trees.

#### Time complexity: O(n) where n is the number of nodes in the smalller tree
#### Space compelxity: O(h) where h is the height of the smaller tree.

``` cpp
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
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if( !p && !q) return true;
        if(!p || !q) return false;
        return (p->val == q->val && isSameTree(p->left,q->left) && isSameTree(p->right,q->right));
    }
};
```