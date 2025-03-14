# LeetCode 235 - Lowest Common Ancestor of a Binary Search Tree
***
## Problem Description:
    Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.

    According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

### Constraints:
 * The number of nodes in the tree is in the range [2, 105].
 * -109 <= Node.val <= 109
 * All Node.val are unique.
 * p != q
 * p and q will exist in the BST.

## Solutions: 

### Approach 1 : [Accepted]
 * In a BST, the values of all nodes in the left subtree of a node is less than the node's value, and the values of all noeds in the right subtree the node is greater than the node's value.
 * Here, the term **`lowest`** is used in terms of depth, not value.
 * We traverse the tree rooted at **`root`** in the following way:
    * If the values of both **`p`** and **`q`** are less than the value of the value of **`root`**, then the LCA will be in the left subtree of root.
    * If the values of both **`p`** and **`q`** are greater than the value of the value of **`root`**, then the LCA will be in the right subtree of root.
    * In other cases, for example, value of **`p`** or value of **`q`** is equal to the value of **`root`**, **`p`** and **`q`** is in different subtrees(left and right) of **`root`**, then the LCA is simply the **`root`**.

#### Recursive implementation:

``` cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(p->val < root->val && q->val < root->val) return lowestCommonAncestor(root->left,p,q);
        if(p->val > root->val && q->val > root->val) return lowestCommonAncestor(root->right,p,q);
        return root;
    }
};
```

#### Time Complexity: O(h)
#### Space Complexity: O(h)
where h is the height of the BST rooted at **`root`**

#### Iterative implementation:

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while(root) {
            if(p->val < root->val && q->val < root->val) root = root->left;
            else if(p->val > root->val && q->val > root->val) root = root->right;
            else return root;
        }
        return nullptr; // not needed actually because p and q are guranteed to exist
    }
};
```

#### Time complexity: O(h)
#### Space complexity: O(1)



