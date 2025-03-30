# Leetcode 106 - Construct Binary Tree from Inorder and Postorder Traversal
***
## Problem Description: 
    Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree and postorder is the postorder traversal of the same tree, construct and return the binary tree.

### Constraints
 * 1 <= postorder.length <= 3000
 * inorder.length == postorder.length
 * -3000 <= postorder[i], inorder[i] <= 3000
 * **`postorder`** and **`inorder`** consist of unique values.
 * Each value of inorder also appears in postorder.
 * **`postorder`** is guaranteed to be the postorder traversal of the tree.
 * **`inorder`** is guaranteed to be the inorder traversal of the tree.

## Solutions: 

### Approach 1 : [Accepted]

We have a recursive solution here. We know that in the postorder traversl, the last element is the root. We do the following recursively:
 * Take the **`root`** from the last (postEnd) of **`postorder`**
 * Find the **`index`** of the **`root`** from **`inorder`**
 * All the elements to the left of this **`index`** will be in the left subtree of **`root`** and all the elements to the right of this **`index`** will be in the right subtree of **`root`**. Recursively call the function accordingly. Also update the starting and ending variables(postStart, postEnd, inStart, inEnd) for **`postorder`** and **`inorder`** while calling the function recursively.

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
    TreeNode * buildTree(vector<int> & postorder, int postStart, int postEnd, vector<int> & inorder, int inStart, int inEnd, map<int,int> & node_index) {
        if(postStart > postEnd || inStart > inEnd) return nullptr;

        TreeNode * root = new TreeNode(postorder[postEnd]);

        int index = node_index[postorder[postEnd]];

        int onTheLeftOfRoot = index - inStart;

        root->left = buildTree(postorder,postStart,postStart +  onTheLeftOfRoot - 1, inorder, inStart, index - 1, node_index);
        root->right = buildTree(postorder,postStart + onTheLeftOfRoot, postEnd - 1,inorder, index + 1, inEnd,node_index);

        return root;
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        map<int,int> node_index;
        for(int i = 0;i<inorder.size();i++) node_index[inorder[i]] = i;
        TreeNode * root = buildTree(postorder,0,postorder.size()-1,inorder,0,inorder.size()-1,node_index);
        return root;
    }
};
```