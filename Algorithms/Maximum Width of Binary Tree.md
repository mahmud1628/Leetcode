# LeetCode 662 - Maximum Width of Binary Tree
***
## Problem Description:
  Given the root of a binary tree, return the maximum width of the given tree.
  
  The maximum width of a tree is the maximum width among all levels.
  
  The width of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that level are also counted into the length calculation.
  
  It is guaranteed that the answer will in the range of a 32-bit signed integer.

 

Example 1:
  Input: root = [1,3,2,5,3,null,9]
  Output: 4
  Explanation: The maximum width exists in the third level with length 4 (5,3,null,9).

Example 2:
  Input: root = [1,3,2,5,null,null,9,6,null,7]
  Output: 7
  Explanation: The maximum width exists in the fourth level with length 7 (6,null,null,null,null,null,7).

Example 3:
  Input: root = [1,3,2,5]
  Output: 2
  Explanation: The maximum width exists in the second level with length 2 (3,2).
 
Constraints:
 * The number of nodes in the tree is in the range [1, 3000].
 * -100 <= Node.val <= 100

## Solutions: 

### Approach 1 : [Status : Memory limit exceeded]

This solution uses a **Level-Order Traversal (Breadth-First Search)** to determine the maximum width of the binary tree. The core idea is to treat the binary tree as if it were a complete binary tree, keeping track of all the `null` nodes between the leftmost and rightmost nodes at each level.

1.  **Initialization**: A queue is initialized, and the `root` node is added to it.
2.  **Level-by-Level Traversal**: The algorithm enters a loop that processes the tree one level at a time.
3.  **Node Processing**:
    * For each level, it iterates through all the elements currently in the queue.
    * For every node it dequeues (even if it's `null`), it enqueues its two children. If a child does not exist, a `nullptr` is explicitly enqueued to act as a placeholder.
    * A boolean vector `is_null` is used to record whether the node at each position in the current level is `null` or a valid node.
4.  **Width Calculation**:
    * After processing a level, the algorithm scans the `is_null` vector to find the index of the first non-null node (`first_node_index`) and the last non-null node (`last_node_index`).
    * The width for the current level is calculated as `last_node_index - first_node_index + 1`.
    * The overall `max_width` is updated if the current level's width is greater.
5.  **Termination**: The process continues until it encounters a level that consists entirely of `nullptr`s, at which point the loop terminates and the `max_width` is returned.

The main challenge with this method is that by enqueuing `nullptr`s, the queue size can grow exponentially, potentially leading to performance issues on skewed or very deep trees.

---

### Complexity Analysis

#### Time Complexity: $O(2^H)$
* Let $H$ be the height of the binary tree.
* The algorithm traverses every node in the conceptual complete binary tree that contains the given tree.
* In the worst-case scenario (a skewed tree where nodes form a long chain), the height $H$ can be close to $N$ (the number of nodes). The last level could conceptually have up to $2^H$ nodes (most of which would be `null`).
* Since the algorithm processes every one of these `null` placeholders, the number of operations is proportional to the width of the lowest level of the complete tree, which is $O(2^H)$. This can be very inefficient and is likely to cause a "Time Limit Exceeded" error on certain test cases.

#### Space Complexity: $O(2^H)$
* The space complexity is determined by the maximum number of elements stored in the queue at any given time.
* Similar to the time complexity, the queue must hold all nodes (including `null` placeholders) at the widest level.
* In the worst-case scenario of a skewed tree with height $H$, the last level being processed could contain up to $O(2^H)$ `nullptr`s.
* Therefore, the space required is also $O(2^H)$.

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
public:
    int widthOfBinaryTree(TreeNode* root) {
        if(!root) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int max_width = -1;
        bool all_null = false;
        while(1) {
            all_null = true;
            int current_length = q.size();
            vector<bool> is_null;
            while(current_length--) {
                TreeNode * node = q.front();
                q.pop();
                if(!node) {
                  q.push(nullptr);
                  q.push(nullptr);
                  is_null.push_back(true);
                }
                else {
                  if(node->left) q.push(node->left);
                  else q.push(nullptr);
                  if(node->right) q.push(node->right);
                  else q.push(nullptr);
                  is_null.push_back(false);
                  all_null = false;
                }
            }
            if(all_null) break;
            int first_node_index = 0, last_node_index = 0;
            for(int i = 0; i < is_null.size(); i++) {
              if(!is_null[i]) {
                first_node_index = i;
                break;
              }
            }
            
            for(int i = is_null.size() - 1; i >= 0; i--) {
              if(!is_null[i]) {
                last_node_index = i;
                break;
              }
            }
            int current_width = last_node_index - first_node_index + 1;
            max_width = max(max_width, current_width);
        }
        return max_width;
    }
};
```

### Slight improvement in approach 1 : [Status : Memory limit exceeded]

This solution uses a **Level-Order Traversal (Breadth-First Search)** to find the maximum width of the tree. It conceptualizes the tree as a complete binary tree, including `null` nodes, to measure the width at each level.

1.  **Initialization**: A queue is initialized with the `root` node. A `max_width` variable is initialized to track the maximum width found so far.
2.  **Level-by-Level Traversal**: The algorithm enters a `while` loop that processes the tree one level at a time. The loop continues as long as there are non-null nodes to process.
3.  **Level Processing**: For each level, the algorithm iterates through all nodes currently in the queue (`current_length`).
    * It keeps track of the `first_node_index` and `last_node_index` of non-null nodes for the current level.
    * For each node dequeued, if it's not `null`, its `left` and `right` children (which can be `null`) are enqueued for the next level. The algorithm then updates `first_node_index` (if it's the first non-null node seen on this level) and `last_node_index`.
    * If the node is `null`, two `nullptr`s are enqueued to maintain the tree's structure in the queue.
4.  **Width Calculation**: After a level is fully processed, the width for that level is calculated as `last_node_index - first_node_index + 1`. This width is then compared with `max_width`, and `max_width` is updated if the current level is wider.
5.  **Termination**: A flag `all_null` checks if an entire level consists of only `null` nodes. If it does, it signifies the end of the tree, and the loop terminates.

This approach is more memory-efficient in its implementation than the previous one as it avoids using an extra vector, but it still relies on enqueuing `null` nodes, which can lead to performance issues.

---

### ## Complexity Analysis

#### Time Complexity: $O(2^H)$
* Let $H$ be the height of the binary tree.
* The algorithm's performance is tied to the maximum number of nodes at any level in the conceptual complete binary tree.
* In a worst-case scenario, such as a skewed tree, the height $H$ can be close to $N$ (the number of nodes). To correctly calculate the width at the lowest level, the algorithm must process up to $2^H$ nodes, most of which will be `null` placeholders pushed onto the queue.
* Therefore, the time complexity is dominated by the processing of the potentially massive last level, resulting in $O(2^H)$.

#### Space Complexity: $O(2^H)$
* The space complexity is determined by the maximum size of the queue.
* Similar to the time complexity, the queue must hold all nodes for the widest level of the conceptual complete tree.
* In the worst case of a skewed tree with height $H$, the queue's size can grow to hold up to $O(2^H)$ `null` pointers representing the lowest level.
* Thus, the space complexity is also $O(2^H)$.

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
public:
    int widthOfBinaryTree(TreeNode* root) {
        if(!root) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int max_width = -1;
        bool all_null = false;
        while(1) {
            all_null = true;
            int current_length = q.size();
            int first_node_index = -1, last_node_index = -1;
            for(int index = 0; index < current_length; index++) {
                TreeNode * node = q.front();
                q.pop();
                if(!node) {
                  q.push(nullptr);
                  q.push(nullptr);
                }
                else {
                  if(node->left) q.push(node->left);
                  else q.push(nullptr);
                  if(node->right) q.push(node->right);
                  else q.push(nullptr);
                  all_null = false;
                  if(first_node_index == -1) first_node_index = index;
                  last_node_index = index;
                }
            }
            if(all_null) break;
            int current_width = last_node_index - first_node_index + 1;
            max_width = max(max_width, current_width);
        }
        return max_width;
    }
};
```

### Approach 2 : [Status : Signed integer overflow]

This solution provides an optimized approach using **Level-Order Traversal (BFS)** combined with a clever indexing strategy to avoid the performance pitfalls of the previous methods. Instead of storing `null` pointers, it assigns a unique index to each node as if it were part of a complete binary tree.

1.  **Initialization**: A queue is initialized to store pairs of `(TreeNode*, long long int)`, where the second element is the node's index. The `root` is enqueued with an initial index of `0`.
2.  **Indexing Scheme**: The indexing follows the standard heap/complete binary tree representation:
    * A node at index `i` will have its left child at index `2 * i + 1`.
    * Its right child will be at index `2 * i + 2`.
    This allows us to calculate the width of any level without needing to store the `null` nodes that lie between the two endpoints.
3.  **Level-by-Level Traversal**: The algorithm iterates through the tree one level at a time.
    * For each level, it captures the size of the queue (`current_length`) to ensure it only processes nodes from that specific level.
    * It keeps track of the index of the first node (`first_node_index`) and the last node (`last_node_index`) encountered on that level.
4.  **Node Processing**:
    * When a node is dequeued, its non-null children are enqueued for the next level, each with its correctly calculated new index.
    * By only enqueuing actual nodes, the queue's size is kept proportional to the number of nodes in the tree, not the potential size of a complete tree.
5.  **Width Calculation**: After each level is processed, the width is calculated as `last_node_index - first_node_index + 1`. The `max_width` is updated if this value is larger than the current maximum. The `long long int` type is used for indices to prevent integer overflow on very deep and skewed trees.
6.  **Termination**: The loop terminates naturally when the queue becomes empty, meaning all nodes have been visited.

This approach is highly efficient because it visits each node only once and avoids the exponential growth of the queue.



---

### Complexity Analysis

#### Time Complexity: $O(N)$
* The algorithm performs a single pass over all the nodes in the tree.
* Each node is enqueued and dequeued exactly once. The operations performed for each node (index calculation, pushing children) are constant time operations.
* Therefore, the time complexity is linear with respect to the number of nodes, $N$.

#### Space Complexity: $O(W)$ or $O(N)$
* The space complexity is determined by the maximum number of nodes stored in the queue at any given time.
* This corresponds to the maximum width, $W$, of the binary tree (the maximum number of nodes at any single level).
* In the worst-case scenario of a complete or full binary tree, the last level can contain up to $\lceil N/2 \rceil$ nodes.
* Therefore, the space complexity is $O(W)$, which in the worst case is $O(N)$.

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
public:
    int widthOfBinaryTree(TreeNode* root) {
        if(!root) return 0;
        queue<pair<TreeNode*, int>> q; 
        q.push(make_pair(root, 0));
        int max_width = -1;
        while(!q.empty()) {
            int current_length = q.size();
            int first_node_index = -1, last_node_index = -1;
            int min_index_of_current_level;
            for(int index = 0; index < current_length; index++) {
                auto entry = q.front();
                TreeNode * node = entry.first;
                int node_index = entry.second;
                if(index == 0) min_index_of_current_level = node_index;
                q.pop();
                if(node->left) q.push(make_pair(node->left, 2 * (node_index - min_index_of_current_level) + 1));
                if(node->right) q.push(make_pair(node->right, 2 * (node_index - min_index_of_current_level) + 2));
                if(first_node_index == -1) first_node_index = node_index;
                last_node_index = node_index;
            }
            int current_width = last_node_index - first_node_index + 1;
            max_width = max(max_width, current_width);
        }
        return max_width;
    }
};
```


### Preventing overflow : [Status : Accepted]

This solution refines the optimized BFS-with-indexing approach to solve a critical edge case: **integer overflow**. While the previous method was efficient, its indexing scheme (`2 * i + 1`) could generate enormous index numbers for deep, skewed trees, eventually overflowing even a `long long int`. This solution prevents that by re-calibrating the indices at every level.

1.  **Core Logic**: The foundation is still a Level-Order Traversal (BFS) using a queue that stores pairs of `(TreeNode*, index)`.

2.  **Overflow Prevention (Index Normalization)**: The key innovation is how child indices are calculated.
    * At the beginning of each level, the index of the first node is recorded as `min_index_of_current_level`.
    * When a node with index `node_index` is processed, the indices for its children are not calculated from `node_index` directly. Instead, the index is first "normalized" relative to the start of the level: `node_index - min_index_of_current_level`.
    * The new indices are then calculated from this normalized value: `2 * (normalized_index) + 1` and `2 * (normalized_index) + 2`.
    * This ensures that the indices being pushed to the queue for the next level always start from a small number (like 1, 2, ...), effectively resetting the count for each level and preventing the numbers from growing uncontrollably.

3.  **Width Calculation**: The width of the *current* level is still calculated using the original, un-normalized indices (`last_node_index - first_node_index + 1`). This is crucial because these original indices correctly represent the positions of the nodes relative to each other on that level. The normalization only applies to the indices being prepared for the *next* level.



By resetting the index base at each level, this algorithm remains robust and correct even for the most extreme tree structures allowed by the problem constraints.

---

### Complexity Analysis

#### Time Complexity: $O(N)$
* The algorithm traverses each node of the tree exactly once.
* The index normalization step (`node_index - min_index_of_current_level`) is a constant-time arithmetic operation performed for each node.
* Since the core logic remains a single pass over $N$ nodes, the time complexity is linear, or $O(N)$.

#### Space Complexity: $O(W)$ or $O(N)$
* The space complexity is dictated by the maximum number of elements held in the queue at one time.
* This corresponds to the maximum width ($W$) of the tree, which is the greatest number of nodes found at any single level.
* In the worst-case scenario (a complete binary tree), the last level can contain approximately $N/2$ nodes.
* Therefore, the space complexity is $O(W)$, which simplifies to $O(N)$ in the worst case. The index normalization does not change the number of nodes stored per level.

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
public:
    int widthOfBinaryTree(TreeNode* root) {
        if(!root) return 0;
        queue<pair<TreeNode*, long long int>> q; 
        q.push(make_pair(root, 0));
        long long int max_width = -1;
        while(!q.empty()) {
            long long int current_length = q.size();
            long long int first_node_index = -1, last_node_index = -1;
            long long int min_index_of_current_level;
            for(long long int index = 0; index < current_length; index++) {
                auto entry = q.front();
                TreeNode * node = entry.first;
                long long int node_index = entry.second;
                if(index == 0) min_index_of_current_level = node_index;
                q.pop();
                if(node->left) q.push(make_pair(node->left, 2 * (node_index - min_index_of_current_level) + 1));
                if(node->right) q.push(make_pair(node->right, 2 * (node_index - min_index_of_current_level) + 2));
                if(first_node_index == -1) first_node_index = node_index;
                last_node_index = node_index;
            }
            long long int current_width = last_node_index - first_node_index + 1;
            max_width = max(max_width, current_width);
        }
        return max_width;
    }
};
```
