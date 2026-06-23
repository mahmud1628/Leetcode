# [LeetCode 417 - Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/)
## Solution 1: [Accepted]
```cpp
class Solution {
    void dfs(int row, int col, vector<vector<int>> & heights, vector<vector<bool>> & flow, int prev) {
        if(row < 0 || col < 0 || row >= heights.size() || col >= heights[0].size() || heights[row][col] < prev || flow[row][col]) return;

        flow[row][col] = true;
        int curr = heights[row][col];
        dfs(row + 1, col, heights, flow, curr);
        dfs(row - 1, col, heights, flow, curr);
        dfs(row, col + 1, heights, flow, curr);
        dfs(row, col - 1, heights, flow, curr);
    }
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int rows = heights.size();
        int cols = heights[0].size();
        vector<vector<bool>> pac(rows, vector<bool>(cols, false));
        vector<vector<bool>> atl(rows, vector<bool>(cols, false));

        for(int i = 0; i < cols; i++) {
            dfs(0, i, heights, pac, 0);
            dfs(rows - 1, i, heights, atl, 0);
        }

        for(int i = 0; i < rows; i++) {
            dfs(i, 0, heights, pac, 0);
            dfs(i, cols - 1, heights, atl, 0);
        }

        vector<vector<int>> result;

        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                if(pac[i][j] && atl[i][j])
                    result.push_back({i, j});
        
        return result;
    }
};
```

### Idea:
> We invert the idea of the flow. Instead of checking flow from any cell to the ocean, we check the flow from the ocean to a cell.
> The first row and the first column are connected to the pacific ocean. We find all the cells that can flow water to the cells of the first row and the first column. Similarly, the last row and the last column are connected to the Atlantic ocean. We find all the cells that can flow water to the cells of the last row and the last column.
> As we have inverted the idea of the flow here we need to check the flow from the ocean to a cell if the height of the current cell is greater than or equal to the height of the previous cell.
> Finally, we find the intersection of the two sets of cells.

### Time Complexity: O(M*N)
### Space Complexity: O(M*N)

where `M` is the number of rows and `N` is the number of columns.
