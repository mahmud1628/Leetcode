# [LeetCode 139 - Word Break](https://leetcode.com/problems/word-break/)
***
## Solution 1: [TLE]
```cpp
class Solution {
    bool wordBreak(string & s, int start, int end, unordered_set<string> & words) {
        string word = s.substr(start, end - start + 1);

        if(words.find(word) != words.end()) return true;

        int temp = end;

        while(start <= temp) {
            word.pop_back();
            temp--;
            if(words.find(word) != words.end()) {
                bool r = wordBreak(s, temp + 1, end, words);
                if(r) return true;
            }
        }

        return false;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> words;
        for(string word : wordDict) words.insert(word);

        return wordBreak(s, 0, s.size() - 1, words);
    }
};
```

### Idea:
> Start by considering the entire substring `s[start...end]`. If it exists in the dictionary, we have found a valid segmentation and can immediately return `true`.
>
> Otherwise, repeatedly shorten the substring from the end and check whether the resulting prefix exists in the dictionary. Whenever a valid prefix is found, recursively solve the remaining suffix of the string.
>
> If any recursive call successfully segments the remaining part, the whole string can be segmented, so we return `true`. If no valid split leads to a solution, we return `false`.
>
> This is a brute-force recursive approach that explores every possible way to partition the string.

### Time Complexity:
> **O(n · 2^n)**
>
> In the worst case, the algorithm explores every possible way to split the string. A string of length `n` has `2^(n-1)` possible partitions, which gives an exponential number of recursive calls.
>
> In each recursive call, `s.substr(start, end - start + 1)` creates a new string, which takes `O(n)` time in the worst case. Although `pop_back()` is `O(1)`, `unordered_set::find()` must hash the current string, which also takes `O(n)` time.
>
> Therefore, the overall time complexity is:
>
> `O(n · 2^n)`

### Space Complexity:
> **O(n²)**
>
> The recursion depth can reach `O(n)` in the worst case (for example, when the string is split one character at a time).
>
> Each recursive call stores its own `word` string, whose size can be up to `O(n)`. Since only one recursive path is active at a time, the total memory used by all active `word` strings is:
>
> `n + (n - 1) + (n - 2) + ... + 1`
>
> which sums to:
>
> `O(n²)`
>
> Therefore, the overall space complexity is:
>
> `O(n²)`

## Solution 2: [TLE]
```cpp
class Solution {
    bool wordBreak(string & s, int start, unordered_set<string> & words) {
        if(start == s.size()) return true;

        string prefix = "";
        for(int i = start; i < s.size(); i++) {
            prefix += s[i];
            if(words.find(prefix) != words.end()) {
                if(wordBreak(s, i + 1, words)) {
                    return true;
                }
            }
        }

        return false;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> words;
        for(string word : wordDict) words.insert(word);

        return wordBreak(s, 0, words);
    }
};
```

### Idea:
> Similar to the previous one, but now we start from the beginning of the string. From the beginning we repeatedly add one character to the `prefix` and find that in the dictionary. If it is there we recursively call the function for the remaining part of the string. If we don't find any `prefix` in the dictionary, we return false.

### Time Complexity:
> **O(n · 2^n)**
>
> In the worst case, the algorithm explores every possible way to split the string. A string of length `n` has `2^(n-1)` possible partitions, leading to an exponential number of recursive calls.
>
> In each recursive call, the loop iterates up to `O(n)` times while gradually building `prefix`. For every iteration, `unordered_set::find()` hashes the current `prefix`, which can take up to `O(n)` time in the worst case.
>
> Therefore, the overall time complexity is:
>
> `O(n · 2^n)`

### Space Complexity:
> **O(n²)**
>
> The recursion depth can reach `O(n)` in the worst case (for example, when the string is segmented one character at a time).
>
> Each recursive call stores its own `prefix` string, whose size can grow up to `O(n)`. Since only one recursive path is active at a time, the total memory used by all active `prefix` strings is:
>
> `n + (n - 1) + (n - 2) + ... + 1`
>
> which sums to:
>
> `O(n²)`
>
> Therefore, the overall space complexity is:
>
> `O(n²)`

## Solution 3: [Accepted]
```cpp
class Solution {
    bool wordBreak(string & s, int start, unordered_set<string> & words, vector<int> & visited) {
        if(start == s.size()) return true;
        if(visited[start] != -1) return visited[start];

        string prefix = "";
        for(int i = start; i < s.size(); i++) {
            prefix += s[i];
            if(words.find(prefix) != words.end()) {
                if(wordBreak(s, i + 1, words, visited)) {
                    return visited[start] = 1;
                }
            }
        }
        return visited[start] = 0;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> words;
        for(string word : wordDict) words.insert(word);
        vector<int> visited(s.size(), -1); // -1 unvisited, 1 true, 0 false

        return wordBreak(s, 0, words, visited);
    }
};
```

### Idea:
> Use memoization to store the results of the recursive calls. The `visited` array is used to store the results of the recursive calls. If `visited[start]` is not -1, it means that the result has already been computed, so we can return the stored result. Otherwise, we compute the result and store it in the `visited` array.

### Time Complexity:
> **O(n³)**
>
> Memoization ensures that each `start` index is solved only once, giving at most `n` unique states.
>
> For each state, the loop can iterate up to `n` times while gradually building `prefix`. During each iteration, `unordered_set::find()` hashes the current `prefix`, whose length can be up to `O(n)`.
>
> Therefore, the total time complexity is:
>
> `O(n × n × n)`
>
> `= O(n³)`

### Space Complexity:
> **O(n²)**
>
> The `visited` array requires `O(n)` space, and the recursion stack can grow up to `O(n)` deep in the worst case.
>
> Each recursive call stores its own `prefix` string. Since only one recursive path is active at a time, the total memory used by all active `prefix` strings is:
>
> `n + (n - 1) + (n - 2) + ... + 1`
>
> which sums to:
>
> `O(n²)`
>
> Therefore, the overall space complexity is:
>
> `O(n²)`

## Solution 4: [Accepted]
```cpp
class Solution {
    bool wordBreak(string & s, int start, unordered_set<string> & words, vector<int> & visited, int & max_len) {
        if(start == s.size()) return true;
        if(visited[start] != -1) return visited[start];

        string prefix = "";
        for(int i = start; i < s.size() && (i - start + 1) <= max_len; i++) {
            prefix += s[i];
            if(words.find(prefix) != words.end()) {
                if(wordBreak(s, i + 1, words, visited, max_len)) {
                    return visited[start] = 1;
                }
            }
        }
        return visited[start] = 0;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int max_len = 0;
        unordered_set<string> words;
        for(string word : wordDict) {
            words.insert(word);
            if(max_len < word.size())
                max_len = word.size();
        }
        vector<int> visited(s.size(), -1); // -1 unvisited, 1 true, 0 false

        return wordBreak(s, 0, words, visited, max_len);
    }
};
```

### Idea:
> Slight optimization to the previous one by making the `prefix` at most of size `max_len` (maximum length of a word in the dictionary).

### Time Complexity:
> **O(nL²)**
>
> Memoization ensures that each `start` index is solved only once, giving at most `n` unique states.
>
> Unlike the previous solution, the loop is limited to at most `L` iterations, where `L` is the maximum length of any word in the dictionary. During each iteration, `unordered_set::find()` hashes the current `prefix`, whose length is at most `L`, taking `O(L)` time.
>
> Therefore, the total time complexity is:
>
> `O(n × L × L)`
>
> `= O(nL²)`

### Space Complexity:
> **O(nL)**
>
> The `visited` array requires `O(n)` space, and the recursion stack can grow up to `O(n)` deep in the worst case.
>
> Each recursive call stores its own `prefix` string, whose length is bounded by `L`. Since only one recursive path is active at a time and the recursion depth can reach `O(n)`, the total memory used by all active `prefix` strings is:
>
> `O(n × L)`
>
> This dominates the `O(n)` space used by the memoization table and recursion stack.
>
> Therefore, the overall space complexity is:
>
> `O(nL)`

## Solution 5: [Accepted]
```cpp
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int max_len = 0;
        unordered_set<string> words;
        for(string word : wordDict) {
            words.insert(word);
            if(max_len < word.size())
                max_len = word.size();
        }
        vector<int> valid(s.size() + 1, false); // valid[i] denotes whether the prefix s[0...i-1] can be segmented or not
        valid[0] = true; // empty string is valid

        for(int i = 1; i < valid.size(); i++) {
            for(int len = 1; len <= max_len && len <= i; len++) {
                int j = i - len;
                if(valid[j] && words.find(s.substr(j, len)) != words.end()) {
                    valid[i] = true;
                    break;
                }
            }
        }

        return valid[valid.size() - 1];
    }
};
```

### Idea:
> Iterative dp approach of the same logic as Solution 4. 

### Time Complexity:
> **O(nL²)**
>
> The outer loop runs `n` times, where `n` is the length of the string.
>
> For each position, the inner loop checks at most `L` possible word lengths, where `L` is the maximum length of any word in the dictionary.
>
> In each iteration, `s.substr(j, len)` creates a substring of length at most `L`, and `unordered_set::find()` hashes that substring, both taking `O(L)` time.
>
> Therefore, the total time complexity is:
>
> `O(n × L × L)`
>
> `= O(nL²)`

### Space Complexity:
> **O(n + L)**
>
> The DP array `valid` stores `n + 1` boolean values, requiring `O(n)` space.
>
> The algorithm is iterative, so no recursion stack is used. During each iteration, `s.substr(j, len)` creates a temporary substring whose maximum size is `L`. Since only one temporary substring exists at a time, it contributes `O(L)` extra space.
>
> Therefore, the overall space complexity is:
>
> `O(n + L)`
>
> Since `L ≤ n`, this can also be simplified to:
>
> `O(n)`


Here, `n` = length of `s`, `L` = maximum length of a word in `wordDict`.