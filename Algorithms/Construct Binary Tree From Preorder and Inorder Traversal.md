# Leetcode 105 - Construct Binary Tree from Preorder and Inorder Traversal
***
## Problem Description: 
    Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree, construct and return the binary tree.

### Constraints
 * 1 <= preorder.length <= 3000
 * inorder.length == preorder.length
 * -3000 <= preorder[i], inorder[i] <= 3000
 * **`preorder`** and **`inorder`** consist of unique values.
 * Each value of inorder also appears in preorder.
 * **`preorder`** is guaranteed to be the preorder traversal of the tree.
 * **`inorder`** is guaranteed to be the inorder traversal of the tree.

## Solutions: 

### Approach 1 : [Accepted]

We have a recursive solution here. We know that in the preorder traversl, the first element is the root. We do the following recursively:
 * Take the **`root`** from the start (preStart) of **`preorder`**
 * Find the **`index`** of the **`root`** from **`inorder`**
 * All the elements to the left of this **`index`** will be in the left subtree of **`root`** and all the elements to the right of this **`index`** will be in the right subtree of **`root`**. Recursively call the function accordingly. Also update the starting and ending variables(preStart, preEnd, inStart, inEnd) for **`preorder`** and **`inorder`** while calling the function recursively.

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
    TreeNode * buildTree(vector<int> & preorder, int preStart, int preEnd, vector<int> & inorder, int inStart, int inEnd, map<int,int> & node_index) {
        if(preStart > preEnd || inStart > inEnd) return nullptr;

        TreeNode * root = new TreeNode(preorder[preStart]);

        int index = node_index[preorder[preStart]];
        int onTheLeftOfRoot = index - inStart;

        root->left = buildTree(preorder,preStart+1, preStart + onTheLeftOfRoot, inorder,inStart,index - 1, node_index);
        root->right = buildTree(preorder,preStart + onTheLeftOfRoot + 1, preEnd, inorder, index + 1, inEnd, node_index);

        return root;

    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        map<int,int> node_index;
        for(int i=0;i<inorder.size();i++) node_index[inorder[i]] = i;
        TreeNode * root = buildTree(preorder,0,preorder.size() - 1,inorder,0,inorder.size() - 1, node_index);
        return root;
    }
};
```
