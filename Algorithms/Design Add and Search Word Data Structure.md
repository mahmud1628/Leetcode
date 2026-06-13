# [LeetCode 211 - Design Add and Search Word Data Structure](https://leetcode.com/problems/design-add-and-search-words-data-structure/)
***
## Solution 1: [Accepted]
```cpp
struct Node {
    Node * children[26];
    bool isCompleteWord;
    Node() {
        isCompleteWord = false;
        for(int i = 0; i < 26; i++) 
            children[i] = nullptr;
    }
};

class WordDictionary {
    Node * root;

    void addWord(string word, int index, Node * current_root) {
        if(index == word.size()) {
            current_root->isCompleteWord = true;
            return;
        }

        char current_char = word[index];
        if(current_root->children[current_char - 'a'] == nullptr) {
            Node * node = new Node();
            current_root->children[current_char - 'a'] = node;
            addWord(word, index + 1, node);
        } else {
            addWord(word, index + 1, current_root->children[current_char - 'a']);
        }
    }

    bool search(string word, int index, Node * current_root) {
        if(current_root == nullptr) {
            return false;
        } 
        if(index == word.size()) {
            return current_root->isCompleteWord;
        }

        char current_char = word[index];

        if(current_char == '.') {
            for(int i = 0; i < 26; i++) {
                bool f = search(word, index + 1, current_root->children[i]);
                if(f) return true;
            }
            return false;
        } else if(current_root->children[current_char - 'a'] == nullptr) {
            return false;
        } else {
            return search(word, index + 1, current_root->children[current_char - 'a']);
        }
    }
public:
    WordDictionary() {
        root = new Node();    
    }
    
    void addWord(string word) {
        addWord(word, 0, root);
    }
    
    bool search(string word) {
        return search(word, 0, root);
    }
};
```

### Idea: 
> Use a Trie data structure

### Time Complexity:
> Add Word: O(L)
> Search: O(L) (At most 2 dots will be there, so the for loop in the search function doesn't contribute much to time complexity, if we consider worst case scenario, it would be O(L * 26^W) where W is the number of dots)

### Space Complexity:
> Add Word: O(L)
> Search: O(L)

**Here `L` is the length of the word, and `W` is the number of dots in the word.**
