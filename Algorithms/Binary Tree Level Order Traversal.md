# LeetCode 102 - Binary Tree Level Order Traversal
***
## Problem Description:
    Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).

    

    Example 1:

    Input: root = [3,9,20,null,null,15,7]
    Output: [[3],[9,20],[15,7]]

    Example 2:

    Input: root = [1]
    Output: [[1]]

    Example 3:

    Input: root = []
    Output: []

### Constraints:
 * The number of nodes in the tree is in the range [0, 2000].
 * -1000 <= Node.val <= 1000

## Solutions: 

### Approach 1 : [Accepted]
 * Apply BFS(Breadth First Search) on **`root`**

#### Time Complexity: O(n)
#### Space Complexity: O(n)

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root == nullptr) return {};

        queue<TreeNode*> q;

        vector<vector<int>> result;

        q.push(root);

        while(!q.empty()) {

            int size = q.size();
            result.push_back({});

            for(int i=0;i<size;i++) {
                TreeNode * node = q.front();
                q.pop();
                result[result.size()-1].push_back(node->val);
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }

        }

        return result;
    }
};
```