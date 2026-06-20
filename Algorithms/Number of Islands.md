## Solution 1: [Accepted]
```cpp
class Solution {
    void dfs(vector<vector<char>> & grid, int row, int column) {
        if(row < 0 || column < 0 || row >= grid.size() || column >= grid[0].size() || grid[row][column] == '0') return;

        grid[row][column] = '0';
        dfs(grid, row + 1, column);
        dfs(grid, row - 1, column);
        dfs(grid, row, column + 1);
        dfs(grid, row, column - 1);
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int count = 0;

        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[0].size(); j++) {
                if(grid[i][j] == '1') {
                    count++;
                    dfs(grid, i, j);
                }
            }
        }

        return count;
    }
};
```
### Idea:
> We iterate through the grid and whenever we find a '1', we increment the count and then use DFS or BFS to find all the connected '1's and mark them as '0' to avoid counting them again as all the connected '1's are part of the same island.

### Time Complexity: O(m*n)
> The nested loops contribute O(m*n). 
> The dfs call visits all cell at most once as once visited, we mark that cell as `0`.
> Since every cell in the grid is visited at most a constant number of times (either by the main loops or by the DFS directional checks), the total number of operations is directly proportional to the total number of cells.

### Space Complexity: O(m*n)
> The space complexity is O(m*n) in the worst case due to the recursion stack depth during the DFS traversal. 
> In the worst case (e.g., a grid entirely filled with '1's), the DFS might need to explore all cells before returning, leading to a recursion depth proportional to the total number of cells.
