# [LeetCode 269 - Alien Dictionary](https://leetcode.com/problems/alien-dictionary/description/)
## Solution 1: [Accepted]
```cpp
class Solution {
    // We only need the words to determine the edge.
    bool add_edge(string & a, string & b, unordered_map<char, vector<char>> & adj_list) {
        int l = min(a.size(), b.size());

        for (int t = 0; t < l; t++) {
            // Found the first difference, create a directed edge
            if (a[t] != b[t]) {
                adj_list[a[t]].push_back(b[t]);
                return true; 
            }
        }

        // If we didn't find any differences, but the first word is longer, 
        // it's an invalid dictionary order (e.g., "abcd" before "abc")
        if (a.size() > b.size()) {
            return false;
        }
        
        return true;
    }

    bool dfs(char c, unordered_map<char, vector<char>> & adj_list, unordered_map<char, int> & state, string & reverse_order) {
        if (state.find(c) != state.end()) {
            if (state[c] == 1) return false; // Already visited and safe
            if (state[c] == 2) return true;  // Cycle detected!
        }

        state[c] = 2; // Mark as currently visiting

        for (auto nei : adj_list[c]) {
            bool cycle = dfs(nei, adj_list, state, reverse_order);
            if (cycle) return true;
        }

        state[c] = 1; // Mark as fully visited
        reverse_order.push_back(c);
        return false;
    }

public:
    string foreignDictionary(vector<string>& words) {
        unordered_map<char, vector<char>> adj_list;

        // Initialize the graph with all unique characters first.
        // This ensures isolated letters (not involved in any edges) are still in our result.
        for (const string& word : words) {
            for (char c : word) {
                adj_list[c] = vector<char>();
            }
        }

        // Build the graph
        for (int i = 0; i < words.size() - 1; i++) {
            bool valid_order = add_edge(words[i], words[i + 1], adj_list);
            if (!valid_order) return "";
        }

        unordered_map<char, int> state; 
        string reverse_order = "";

        // Run DFS on every node in the graph
        for (auto i : adj_list) {
            if (state.find(i.first) == state.end()) {
                bool cycle = dfs(i.first, adj_list, state, reverse_order);
                if (cycle) return "";
            }
        }

        // Reverse the post-order to get the valid topological sort

        reverse(reverse_order.begin(), reverse_order.end());

        return reverse_order;
    }
};
```

### Time Complexity: $O(C)$
> The overall time complexity is entirely bound by the total number of characters across all words. 
> Here is the step-by-step breakdown:
> - Extracting Unique Characters:Looping through every character in every word to initialize the adjacency list takes $O(C)$ time.
> - Building the Graph: Compare adjacent words ($i$ and $i+1$). In the worst-case scenario (e.g., words that are identical or share very long prefixes), may inspect almost every character again. Therefore, the total time spent comparing prefixes across all $N-1$ word pairs is bounded by $O(C)$.
> - DFS (Topological Sort):A standard DFS traversal on a graph takes time proportional to the number of vertices ($V$) plus the number of edges ($E$).
> - - Vertices $V = U$.
> - - Edges $E \le N - 1$ (since you only add at most one edge per adjacent word pair).
> - - The DFS takes $O(U + E)$ time. Since $U \le C$ and $E < N \le C$, this step is strictly bounded by $O(C)$.
> - Reversing the String:Reversing the final string takes $O(U)$ time.
> - Adding these up: $O(C) + O(C) + O(U + E) + O(U) = O(C)$
### Space Complexity: $O(U + \min(U^2, N))$ or $O(1)$
> The space complexity depends on whether we treat the alphabet size as a constant (like 26 letters) or as an arbitrarily large variable. \
> - If we assume an arbitrarily large alphabet ($U$):
> - - Adjacency List (adj_list):It stores $U$ keys. The total number of edges is at most $N - 1$. However, in a directed graph, the maximum possible number of edges is $U^2$. Therefore, the space taken by the edges is $\min(U^2, N - 1)$. Total map space: $O(U + \min(U^2, N))$.
> - - State Map (state):Stores the visited status for up to $U$ characters, taking $O(U)$ space.
> - - DFS Call Stack:In the worst case (a single straight line graph like $a \to b \to c \dots$), the recursive call stack will go $U$ levels deep, taking $O(U)$ space.Result String (reverse_order):Takes $O(U)$ space.
> - - Total Space: $O(U + \min(U^2, N))$. \
> - If we assume a fixed standard alphabet (e.g., $U \le 26$):
> - - Because the maximum number of unique characters is capped at 26, the maximum number of nodes is 26, the maximum number of edges is $26^2 = 676$, and the maximum recursion depth is 26. Since these are all fixed upper bounds regardless of how massive the input array $N$ is, the space complexity simplifies to $O(1)$ auxiliary space.

here, 
- $N$ = Total number of words in the input array. 
- $C$ = Total length of all words combined (i.e., the total number of characters).
- $U$ = Total number of unique characters in the alien alphabet (typically bounded by 26 for English lowercase letters).