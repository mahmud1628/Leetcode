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
 * Traverse the tree rooted at **`root`**.
    * For each of the node, match the tree rooted at this node with the tree rooted at **`subRoot`**.
        * If the matches, return true.
        * Otherwise, return false.

#### Time Complexity: O(n * m), 
where n and m are the number of nodes in the trees rooted at **`root`** and **`subRoot`**.
#### Space Complexity: O(1)

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

    void preOrder(TreeNode* root, TreeNode* subroot, bool &isSubTree) {

        if(root == nullptr) return;

        if(match(root,subroot)) {
            isSubTree = true;
            return;
        }

        preOrder(root->left, subroot,isSubTree);
        preOrder(root->right, subroot,isSubTree);
    }

public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(root == subRoot) return true; // tree could also be coonsidered a subtree of itself

        bool isSubTree = false;

        preOrder(root,subRoot,isSubTree);

        return isSubTree;

    }
};
```