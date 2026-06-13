# [LeetCode 208 - Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/description/)
***
## Solution 1: [Accepted]
```cpp
struct Node {
    unordered_map<char, Node *> children;
    bool isCompleteWord;
    Node() {
        isCompleteWord = false;
    }
};

class Trie {
    Node * root;
    void insert(string word, int index, Node * current_root) {
        if(index == word.size()) {
            current_root->isCompleteWord = true;
            return;
        }
        char current_char = word[index];
        if(current_root->children.find(current_char) == current_root->children.end()) {
            Node * node = new Node();
            current_root->children[current_char] = node;
            insert(word, index + 1, node);
        } else {
            insert(word, index + 1, current_root->children[current_char]);
        }
    }

    bool search(string word, int index, Node * current_root) {
        if(index == word.size()) {
            return current_root->isCompleteWord;
        }

        char current_char = word[index];

        if(current_root->children.find(current_char) == current_root->children.end()) return false;

        return search(word, index + 1, current_root->children[current_char]);
    }

    bool startsWith(string prefix, int index, Node * current_root) {
        if(index == prefix.size()) {
            return true;
        }

        char current_char = prefix[index];

        if(current_root->children.find(current_char) == current_root->children.end()) return false;

        return startsWith(prefix, index + 1, current_root->children[current_char]);
    }
public:
    Trie() {
        root = new Node();
    }
    
    void insert(string word) {
        insert(word, 0, root);
    }
    
    bool search(string word) {
        return search(word, 0, root);
    }
    
    bool startsWith(string prefix) {
        return startsWith(prefix, 0, root);
    }
};
```

### Time Complexity:
> `insert` : O(n)
> `search` : O(n)
> `startsWith` : O(n) 

### Space Complexity:
> `insert` : O(n)
> `search` : O(n)
> `startsWith` : O(n) 

Here `n` is the length of the `word`.


## Solution 2 : [Accepted]
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

class Trie {
    Node * root;
    void insert(string word, int index, Node * current_root) {
        if(index == word.size()) {
            current_root->isCompleteWord = true;
            return;
        }
        char current_char = word[index];
        if(current_root->children[current_char - 'a'] == nullptr) {
            Node * node = new Node();
            current_root->children[current_char - 'a'] = node;
            insert(word, index + 1, node);
        } else {
            insert(word, index + 1, current_root->children[current_char - 'a']);
        }
    }

    bool search(string word, int index, Node * current_root) {
        if(index == word.size()) {
            return current_root->isCompleteWord;
        }

        char current_char = word[index];

        if(current_root->children[current_char - 'a'] == nullptr) return false;

        return search(word, index + 1, current_root->children[current_char - 'a']);
    }

    bool startsWith(string prefix, int index, Node * current_root) {
        if(index == prefix.size()) {
            return true;
        }

        char current_char = prefix[index];

        if(current_root->children[current_char - 'a'] == nullptr) return false;

        return startsWith(prefix, index + 1, current_root->children[current_char - 'a']);
    }
public:
    Trie() {
        root = new Node();
    }
    
    void insert(string word) {
        insert(word, 0, root);
    }
    
    bool search(string word) {
        return search(word, 0, root);
    }
    
    bool startsWith(string prefix) {
        return startsWith(prefix, 0, root);
    }
};


/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
 ```