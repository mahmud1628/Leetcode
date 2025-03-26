# Leetcode 98 - Validate Binary Search Tree
***
## Problem Description: 
    Given the root of a binary tree, determine if it is a valid binary search tree (BST).

    A valid BST is defined as follows:

    The left subtree of a node contains only nodes with keys less than the node's key.
    The right subtree of a node contains only nodes with keys greater than the node's key.
    Both the left and right subtrees must also be binary search trees.

### Constraints
 * The number of nodes in the tree is in the range [1, 104].
 * -231 <= Node.val <= 231 - 1  

## Solutions: 

### Approach 1 : [Accepted]

 Inorder traversal of a BST gives a sorted array.
 * Traverse the tree and push the node values in a vector.
 * Check if the vector is sorted or not

#### Time complexity : O(n)
#### Space complexity : O(n)

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

    void inorder(TreeNode* root, vector<int> & arr) {
        if(!root) return;
        inorder(root->left,arr);
        arr.push_back(root->val);
        inorder(root->right,arr);
    }
public:
    bool isValidBST(TreeNode* root) {
        // inorder traversal gives a sorted sequence in a BST
        vector<int> arr;
        inorder(root,arr);
        for(int i=0;i<arr.size()-1;i++) {
            if(arr[i] >= arr[i+1]) return false;
        }
        return true;
    }
};
```