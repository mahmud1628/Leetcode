# [LeetCode 133 - Clone Graph](https://leetcode.com/problems/clone-graph/description/)
## Solution 1: [Accpeted]
```cpp
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(!node) return node;

        unordered_map<Node *, Node *> copies; // original node -> cloned node 

        copies[node] = new Node(node->val); // copy the root node 

        queue<Node *> q; // stores original nodes for bfs
        q.push(node);

        while(!q.empty()) {
            Node * curr = q.front();
            q.pop();

            // check the neighbors
            for(Node * neighbor : curr->neighbors) {
                // check if this neighbor is already cloned or not 
                if(copies.find(neighbor) == copies.end()) {
                    Node * copy = new Node(neighbor->val); // copy it
                    copies[neighbor] = copy;

                    q.push(neighbor); 
                }

                // add the copy of the neighbor to the neighbor set of the copy of the curr  
                copies[curr]->neighbors.push_back(copies[neighbor]);
            }
        }

        return copies[node];
    }
};
```

### Idea:
The problem requires creating a deep copy of a connected, undirected graph. To achieve this, we must traverse the entire graph while ensuring two things:
- Every node is cloned exactly once.
- The original connections (edges) between nodes are perfectly replicated in the clone.

#### The solution utilizes a graph traversal algorithm (such as Breadth-First Search (BFS) or Depth-First Search (DFS)) combined with a Hash Map for tracking and deduplication. 

#### The Hash Map (unordered_map<Node*, Node*>): 
This is the key to the solution. It maps each original node to its corresponding cloned node. It serves a dual purpose:
- Lookup Table: Allows us to easily wire up connections between cloned nodes.
- Visited Set: Prevents infinite loops caused by cycles in the graph. If an original node is already in the map, it means it has already been cloned.

#### Traversal & Cloning: 
1. We start at the given input node, clone it, and add the original-to-clone pair to our map.
2. As we visit each node's neighbors during the traversal:
    - If a neighbor has not been cloned yet (not in the map), we create its clone, register it in the map, and add it to our traversal queue.
    - If a neighbor has already been cloned (exists in the map), we skip creating a new node.
    - In both cases, we safely link the current cloned node to the cloned neighbor.
    
### Time Complexity: $\mathcal{O}(V + E)$
 where $V$ is the number of vertices (nodes) and $E$ is the number of edges. We visit every node and every edge exactly once.
 ### Space Complexity: $\mathcal{O}(V)$
  needed for the hash map to store the mapping of all nodes and the queue used for traversal.