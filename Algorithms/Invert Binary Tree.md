# LeetCode 226 - Invert Binary Tree
***
## Problem description:
    Given the root of a binary tree, invert the tree, and return its root.


    Example 1:
        Input: root = [4,2,7,1,3,6,9]
        Output: [4,7,2,9,6,3,1]

    Example 2:
        Input: root = [2,1,3]
        Output: [2,3,1]

    Example 3:
        Input: root = []
        Output: []
 

### Constraints:
 * The number of nodes in the tree is in the range [0, 100].
 * -100 <= Node.val <= 100

## Solutions:

### Approach 1 [Pre order traversal]: [Accepted]
 * Run pre_order traversal algorithm on the root of the tree.
    * If root is nullptr, then return.
    * Swap left and right child of root.
    * Run pre_order traversal algorithm on left child.
    * Run pre_order traversal algorithm on right child.

#### Time complexity: O(n) , n = number of nodes in the tree.
#### Space complexity: O(h) , h = height of the tree.

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
    void pre_order(TreeNode * root) {
        if(!root) return;
        swap(root->left,root->right);
        pre_order(root->left);
        pre_order(root->right);
    }
public:
    TreeNode* invertTree(TreeNode* root) {
        pre_order(root);
        return root;
    }
};
```
