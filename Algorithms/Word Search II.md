# [LeetCode 212 - Word Search II](https://leetcode.com/problems/word-search-ii/)
***
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

## Solution 2 : [Accepted]
```cpp
struct Node {
    unordered_map<char, Node *> children;
    bool isCompleteWord;
    string word;
    Node() {
        isCompleteWord = false;
    }
};
class Solution {
    Node * root;
    void insert(string word, int index, Node * current_root) {
        if(index == word.size()) {
            current_root->isCompleteWord = true;
            current_root->word = word;
            return;
        }

        char current_char = word[index];

        if(current_root->children.find(current_char) == current_root->children.end()) {
            Node * node = new Node();
            current_root->children[current_char] = node;
        }

        insert(word, index + 1, current_root->children[current_char]);
    }

    void search(vector<vector<char>> & board, int row, int column, Node * current_root, vector<string> & result) {
        if(current_root->isCompleteWord) {
            result.push_back(current_root->word);
            current_root->isCompleteWord = false;
        }
        if(row < 0 || column < 0 || row >= board.size() || column >= board[0].size() || board[row][column] == '#') {
            return;
        }

        char current_char = board[row][column];

        if(current_root->children.find(current_char) == current_root->children.end()) return;

        board[row][column] = '#';
        Node * next_root = current_root->children[current_char];
        search(board, row + 1, column, next_root, result);
        search(board, row - 1, column, next_root, result);
        search(board, row, column + 1, next_root, result);
        search(board, row, column - 1, next_root, result);
        board[row][column] = current_char;
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        root = new Node();
        // build the trie using the strings in the words vector
        for(string word : words) 
            insert(word, 0, root);

        vector<string> res;

        //search in the trie starting from each cell of the board
        for(int i = 0; i < board.size(); i++)
            for(int j = 0; j < board[0].size(); j++)
                search(board, i, j, root, res);
        
        return res;
    }
};
```

## Idea:
> Initially i thought that building a trie on all possible words from the board and then searching each word from the words vector would work, but building the trie will all possible words from the board is not feasible. Instead, we can build the trie using the strings in the words vector and then search in the trie starting from each cell of the board(DFS backtracking).

### Time complexity:
> Building the trie: O(W x L)
> One DFS call : O(3^L)
> Total time complexity: O(W x L + m x n x 3^L)

### Space complexity:
> Building the trie: O(W x L) considering the alphabet size is constant (26)
> Searching : O(L)
> Total space complexity: O(W x L)

Where `m` and `n` are the dimensions of the `board`, `W` is the number of words in the `words` vector and `L` is the length of the longest word.