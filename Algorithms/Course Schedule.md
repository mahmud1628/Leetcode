# [LeetCode 207 - Course Schedule](https://leetcode.com/problems/course-schedule/description/)
## Solution 1: [Accepted on Neetcode, TLE on Leetcode]
```cpp
class Solution {
    bool dfs(int node, vector<vector<int>> & neighbors, vector<bool> & visited) {
        if(visited[node]) return false;

        visited[node] = true;
        for(int neighbor : neighbors[node]) {
            bool b = dfs(neighbor, neighbors, visited);
            if(!b) return false;
        }
        visited[node] = false;

        return true;
    }
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> neighbors(numCourses, vector<int>());

        for(int i = 0; i < prerequisites.size(); i++) {
            neighbors[prerequisites[i][0]].push_back(prerequisites[i][1]);
        }

        vector<bool> visited(numCourses, false);

        for(int i = 0; i < numCourses; i++) {
           bool b = dfs(i, neighbors, visited);
           if(!b) return false;
           visited = vector<bool>(numCourses, false);
        }

        return true;
    }
};
```

### Idea:
> Construct a graph, if the graph has a cycle, return false, otherwise return true.
> In the code, we can detect a cycle by using DFS from each node. If we visit a node that has already been visited, then there is a cycle.

### Time Complexity: O(E + V * (V + E))
### Space Complexity: O(E + V)

## Solution 2: [Accepted]
```cpp
class Solution {
    bool dfs(int node, vector<vector<int>> & neighbors, vector<int> & state) {
        if(state[node] == 1) { // ifwe find something that has been visited on the current path, we have a cycle
            return false;
        }
        if(state[node] == 2) { // if we find some thing that has already been processed, no need to process it anymore 
            return true;
        }

        state[node] = 1; // 1 means it is on the current path
        for(int neighbor : neighbors[node]) {
            bool b = dfs(neighbor, neighbors, state);
            if(!b) {
                return false;
            }
        }
        state[node] = 2; // 2 means the node and its descendants are fully processed and there is no cycle

        return true;
    }
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> neighbors(numCourses, vector<int>());

        for(int i = 0; i < prerequisites.size(); i++) {
            neighbors[prerequisites[i][0]].push_back(prerequisites[i][1]);
        }

        vector<int> state(numCourses, 0);

        for(int i = 0; i < numCourses; i++) {
           bool b = dfs(i, neighbors, state);
           if(!b) return false;
        }

        return true;
    }
};
```

### Idea:
> We can optimize the previous solution by using a state array to keep track of the nodes that have been fully processed or that are on the current path. This way we don't have to run DFS on the same node multiple times.
> When we are traversing from a node, we mark it as 1 (visiting). If we encounter a node that is already marked as 1, it means we have a cycle. If we encounter a node that is marked as 2, it means we have already processed it and there is no cycle, so we can return true. Otherwise we recursively call DFS on the neighbors. If any of the DFS calls return false, we return false. Finally, we mark the current node as 2 (processed). 
> If all the DFS calls return true, we return true.

### Time Complexity: O(V + E)
### Space Complexity: O(V + E)
