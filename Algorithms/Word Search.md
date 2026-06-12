## Solution 1: [Accepted]
```cpp
class Solution {
    bool exist(vector<vector<char>> & board, string word, int row, int column, int index) {
        if(index >= word.size()) return true;
        if(row < 0 || column < 0 || row >= board.size() || column >= board[row].size() || board[row][column] == '#') return false;

        if(word[index] != board[row][column]) return false;

        char current = board[row][column];
        board[row][column] = '#'; // mark as visited

        bool right = exist(board, word, row, column + 1, index + 1);
        if(right) return true;
        bool down = exist(board, word, row + 1, column, index + 1);        
        if(down) return true;
        bool left = exist(board, word, row, column - 1, index + 1);        
        if(left) return true;
        bool up = exist(board, word, row - 1, column, index + 1);    
        if(up) return true;

        board[row][column] = current; // remove visited mark

        return false;        
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        for(int row = 0; row < board.size(); row++) {
            for(int column = 0; column < board[row].size(); column++) {
                if(board[row][column] == word[0]) {
                    bool found = exist(board, word, row, column, 0);
                    if(found) return true;
                }
            }
        }
        return false;
    }
};
```

### Idea:
> Start recursive search from each cell of the `board` if that cell contains the first character from the `word`.
> In each recursive call, search in all four vertical and horizontal neighbours from the current cell. To avoid exploring duplicate cell, mark the current cell as visited when exploring the neighbours and after exploring, again mark as not visited.

### Time complexity: 
> In the worst case, the outer loops try every cell as a starting point which is O(mn).
> For each starting cell, the DFS can explore up to 4 directions initially and then at most 3 directions afterward (because the previous cell is marked visited and cannot be revisited).
> This is: O(4.3<sup>L - 1</sup>) or O(3<sup>L</sup>) for one DFS call.

> Overall O(mn.3<sup>L</sup>)

### Space complexity:
> The only extra space comes from the recursion stack.
> The maximum recursion depth is the length of the word:
> So O(L)

Here `m` is the length of the `board`, `n` is the width of the `board` and `L` is the size of the `word`
	​

## Solution 2: [Accepted]
```cpp
class Solution {
    bool exist(vector<vector<char>> & board, string word, int row, int column, int index) {
        if(index >= word.size()) return true;
        if(row < 0 || column < 0 || row >= board.size() || column >= board[row].size() || board[row][column] == '#') return false;

        if(word[index] != board[row][column]) return false;

        char current = board[row][column];
        board[row][column] = '#'; // mark as visited

        bool right = exist(board, word, row, column + 1, index + 1);
        if(right) return true;
        bool down = exist(board, word, row + 1, column, index + 1);        
        if(down) return true;
        bool left = exist(board, word, row, column - 1, index + 1);        
        if(left) return true;
        bool up = exist(board, word, row - 1, column, index + 1);    
        if(up) return true;

        board[row][column] = current; // remove visited mark

        return false;        
    }
public:
    bool exist(vector<vector<char>>& board, string word) {

        // a quick check whether the board contains enough charaters to make the word
        unordered_map<char, int> boardFreq;
        unordered_map<char, int> wordFreq;
        for(auto row : board) {
            for(auto ch : row) {
                boardFreq[ch]++;
            }
        }
        for(auto ch : word) {
            wordFreq[ch]++;

            if(wordFreq[ch] > boardFreq[ch]) return false;
        }


        for(int row = 0; row < board.size(); row++) {
            for(int column = 0; column < board[row].size(); column++) {
                if(board[row][column] == word[0]) {
                    bool found = exist(board, word, row, column, 0);
                    if(found) return true;
                }
            }
        }
        return false;
    }
};
```

### Idea:
> Same idea as before. Just add a quick check before running the algorithm whether the `board` contains enough characters to make the `word`.

### Time complexity: 
> Same as before.

### Space complexity:
> Same as before considering the alphabet size is fixed (52 here), so the `unordered_maps` are of a constant size at most.
