# LeetCode 572 - Subtree of another tree
***
## Problem Description:
    Given the roots of two binary trees root and subRoot, return true if there is a subtree of root with the same structure and node values of subRoot and false otherwise.

    A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants. The tree tree could also be considered as a subtree of itself.

### Constraints:
 * The number of nodes in the root tree is in the range [1, 2000].
 * The number of nodes in the subRoot tree is in the range [1, 1000].
 * -104 <= root.val <= 104
 * -104 <= subRoot.val <= 104

## Solutions: 

### Approach 1 - Brute Force : [Accepted]
 * Check if two trees are identical (**`match`** function)

    * If both trees are empty, they match, so return true.
    * If one tree is empty but the other isn’t, they don’t match, so return false.
    * If the values of the current nodes don’t match, return false.
    * Otherwise, check if both the left subtrees and right subtrees match.
    * If both sides match, return true, otherwise return false.

 * Check if **`subRoot`** is a subtree of **`root`** (**`isSubtree`** function)

    * If **`root`** is empty, return false (an empty tree can’t contain another tree).
    * If **`root`** and **`subRoot`** are the same **`TreeNode`**, return true.
    * If **`root`** and **`subRoot`** are identical (**`match`** function returns true), return true.
    * Otherwise, search in the left and right subtrees of **`root`**.
    * If either side contains **`subRoot`**, return true, otherwise return false.

#### Time Complexity: O(n * m), 
where n and m are the number of nodes in the trees rooted at **`root`** and **`subRoot`**.
#### Space Complexity: O(n + m),
where n and m are the number of nodes in the trees rooted at **`root`** and **`subRoot`**.

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

    bool match(TreeNode* root, TreeNode* subroot) {
        if(!root && !subroot) return true;
        if((root && !subroot) || (!root && subroot)) return false;
        if(root->val == subroot->val) return match(root->left, subroot->left) && match(root->right,subroot->right);
        return false;
    }


public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(!root) return false;
        if(root == subRoot) return true; // tree could also be coonsidered a subtree of itself
        if(match(root,subRoot)) return true;
        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }
};
```