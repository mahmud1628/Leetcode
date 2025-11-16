# [LeetCode 127 - Word Ladder](https://leetcode.com/problems/word-ladder/)
***
## Solution 1:

```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        queue<pair<string, int>> q;
        q.push({beginWord, 0});
        unordered_set<string> words(wordList.begin(), wordList.end());

        while(!q.empty()) {
            auto [currentWord, count] = q.front();
            q.pop();
            if(currentWord == endWord) return count + 1;
            words.erase(currentWord);

            for(int i = 0; i < currentWord.size(); i++) {
                char currentChar = currentWord[i];

                for(char ch = 'a'; ch <= 'z'; ch++) {
                    if(ch == currentChar) continue;
                    string temp = currentWord;
                    temp[i] = ch;
                    if(words.find(temp) != words.end()) q.push({temp, count + 1});
                }
            }
        }
        return 0;
    }
};
```

### Idea:
The problem asks for the shortest path in a graph where words are nodes and an edge exists between two words if they differ by a single character. This is a classic shortest path problem on an unweighted graph, which can be efficiently solved using Breadth-First Search (BFS). We start BFS from the `beginWord` and explore words that are one character different. We keep track of the "level" or the number of transformations made to reach a word. The first time we encounter the `endWord`, we have found the shortest transformation sequence.

### Algorithm:
1.  **Initialization:**
    *   Create a queue `q` to store pairs of `(word, count)`, where `word` is the current word and `count` is the number of transformations to reach it from `beginWord`.
    *   Push the `beginWord` into the queue with a count of 0.
    *   Create an `unordered_set` called `words` from the `wordList` for efficient lookup (O(1) average time).
2.  **BFS Traversal:**
    *   While the queue is not empty:
        *   Dequeue the front element `(currentWord, count)`.
        *   **Check for End Word:** If `currentWord` is equal to `endWord`, we have found the shortest path. Return `count + 1` (since `count` represents transformations, and the sequence length is transformations + 1).
        *   **Remove Visited Word:** Remove `currentWord` from the `words` set to avoid revisiting it and creating cycles.
        *   **Generate Neighbors:** For each character position `i` in `currentWord`:
            *   Store the original character at `currentWord[i]` in `currentChar`.
            *   Iterate through all possible lowercase letters `ch` from 'a' to 'z'.
            *   If `ch` is different from `currentChar`:
                *   Create a temporary string `temp` by replacing `currentWord[i]` with `ch`.
                *   **Check in Dictionary:** If `temp` exists in the `words` set (meaning it's a valid word in the dictionary and hasn't been visited yet in this path):
                    *   Enqueue `(temp, count + 1)` into the queue.
3.  **No Path Found:** If the loop finishes and `endWord` is not found, it means no transformation sequence exists. Return 0.

### Time Complexity:
The time complexity is roughly O(N * L^2 * 26), where N is the number of words in the `wordList`, and L is the length of each word.
*   Each word is enqueued and dequeued at most once.
*   When processing a word, we iterate through its L characters.
*   For each character, we try replacing it with 25 other characters (from 'a' to 'z').
*   Checking if a generated word is in the `unordered_set` takes O(L) on average due to string hashing and comparison.
*   So, for each word, we do L * 26 * L work. In the worst case, all words might be processed.
*   However, a tighter bound is O(N * L^2) because once a word is visited (removed from the set), it won't be processed again. The '26' factor comes from trying all possible character substitutions, which is a constant for a fixed alphabet.

### Space Complexity:
The space complexity is O(N * L), where N is the number of words in the `wordList` and L is the length of each word.
*   The `unordered_set` stores all words from the `wordList`, taking O(N * L) space.
*   The queue can, in the worst case, store a significant portion of the words, also contributing O(N * L) space.
