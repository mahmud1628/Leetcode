## Solution 1 : [Accepted on Neetcode, TLE on Leetcode]
```cpp
class Solution {
        bool exist(vector<vector<char>> & board, string word, int row, int column, int index) {
        if(index >= word.size()) return true;
        if(row < 0 || column < 0 || row >= board.size() || column >= board[row].size() || board[row][column] == '#') return false;

        if(word[index] != board[row][column]) return false;

        char current = board[row][column];
        board[row][column] = '#'; // mark as visited

        bool found = exist(board, word, row, column + 1, index + 1) ||
                     exist(board, word, row + 1, column, index + 1) ||
                     exist(board, word, row, column - 1, index + 1) ||
                     exist(board, word, row - 1, column, index + 1);    

        board[row][column] = current; // remove visited mark

        return found;       
    }

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
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> res;
        for(string word : words) {
            if(exist(board, word)) res.push_back(word);
        }
        return res;
    }
};
```

### Idea:
> Use the `Word search` algorithm for each word in the `words` vector.

### Time complexity: 
> O(mnW.3^L)

### Space complexity:
> O(L)

Where `m` and `n` are the dimensions of the `board`, `W` is the number of words in the `words` vector and `L` is the length of the longest word.
