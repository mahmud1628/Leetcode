# [LeetCode 433 - Minimum Genetic Mutation](https://leetcode.com/problems/minimum-genetic-mutation/)
***
## Solution 1: 

```cpp
class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        queue<pair<string, int>> q;
        q.push({startGene, 0});

        unordered_set<string> set_bank;
        for(string s : bank) set_bank.insert(s);

        unordered_set<string> visited;

        while(!q.empty()) {
            auto [currentGene, cost] = q.front();
            q.pop();
            visited.insert(currentGene);
            if(currentGene == endGene) return cost;
            for(int i = 0; i < 8; i++) {
                char ch = currentGene[i];
                if(ch != 'A') {
                    string temp = currentGene;
                    temp[i] = 'A';
                    if(set_bank.find(temp) != set_bank.end() && visited.find(temp) == visited.end()) q.push({temp, cost + 1});
                }
                if(ch != 'C') {
                    string temp = currentGene;
                    temp[i] = 'C';
                    if(set_bank.find(temp) != set_bank.end() && visited.find(temp) == visited.end()) q.push({temp, cost + 1});
                }
                if(ch != 'G') {
                    string temp = currentGene;
                    temp[i] = 'G';
                    if(set_bank.find(temp) != set_bank.end() && visited.find(temp) == visited.end()) q.push({temp, cost + 1});
                }
                if(ch != 'T') {
                    string temp = currentGene;
                    temp[i] = 'T';
                    if(set_bank.find(temp) != set_bank.end() && visited.find(temp) == visited.end()) q.push({temp, cost + 1});
                }
            }

        }
        return -1;
    }
};
```
### Idea:
The problem asks for the shortest sequence of valid gene mutations from a starting gene to an ending gene, given a bank of valid genes. This is a classic shortest path problem on a graph. We can model each valid gene as a node in the graph, and an edge exists between two genes if they differ by exactly one character (a single mutation). The algorithm uses Breadth-First Search (BFS) to find the shortest path from the `startGene` to the `endGene`. BFS naturally finds the shortest path in terms of the number of edges (mutations) because it explores the graph level by level.

### Algorithm:
1.  **Initialization**:
    *   Create a queue `q` to store pairs of `(gene_string, mutation_count)`.
    *   Push the `startGene` with a mutation count of 0 into the queue.
    *   Create an `unordered_set` called `set_bank` from the `bank` vector. This allows for efficient O(1) average time lookups to check if a gene is valid.
    *   Create an `unordered_set` called `visited` to keep track of genes that have already been processed to avoid cycles and redundant work.

2.  **BFS Traversal**:
    *   While the queue is not empty:
        *   Dequeue the front element, which is a pair `(currentGene, cost)`.
        *   Add `currentGene` to the `visited` set.
        *   If `currentGene` is equal to `endGene`, we have found the shortest path, so return `cost`.
        *   Generate all possible one-mutation neighbors of `currentGene`:
            *   Iterate through each of the 8 positions in `currentGene`.
            *   For each position, try changing the character to 'A', 'C', 'G', and 'T'.
            *   For each potential new gene (`temp`):
                *   Check if `temp` is present in `set_bank` (i.e., it's a valid gene).
                *   Check if `temp` has not been `visited` yet.
                *   If both conditions are true, enqueue the pair `{temp, cost + 1}` into the queue.

3.  **No Path Found**:
    *   If the loop finishes and `endGene` was not reached, it means there is no valid mutation path. Return -1.

### Time Complexity:
The time complexity is roughly O(N * L^2 * C), where N is the number of genes in the bank, L is the length of a gene string (which is 8 in this problem), and C is the number of possible characters ('A', 'C', 'G', 'T').
*   Each gene from the bank is enqueued and dequeued at most once.
*   When processing a gene, we iterate through its 8 positions.
*   For each position, we try 4 possible characters.
*   Generating the `temp` string takes O(L).
*   Set lookups (`set_bank.find`, `visited.find`) take O(L) in the worst case for strings (due to hashing and comparison), but on average O(1) if we consider average hash performance. However, if we consider string comparisons within hash lookups, it becomes O(L).
*   The number of possible mutations from any given gene is at most L * (C-1) which is 8 * 3 = 24.
*   So, the overall complexity is dominated by the number of states (genes that can be reached) and the transitions from each state. The maximum number of reachable genes is N. From each gene, we explore up to L * (C-1) potential mutations. String operations (creation, comparison in sets) take O(L).
*   Therefore, a more precise bound is O(N * L * (C-1) * L) if we consider string operations, or O(N * L) if we consider set operations as O(1) average for well-distributed hashes and assume string comparisons are implicit in the hash function or not the bottleneck. Given L=8, C=4, N is the bank size, it's effectively O(N * 8^2 * 4), which is dominated by N and the fixed gene length.

### Space Complexity:
The space complexity is O(N * L) in the worst case, where N is the number of genes in the bank and L is the length of a gene string. This is due to:
*   The `queue` storing gene strings. In the worst case, all valid genes in the bank could be in the queue simultaneously.
*   The `set_bank` storing all valid genes from the bank.
*   The `visited` set storing visited gene strings.
Each of these can store up to N gene strings, each of length L. Given L=8, it's effectively O(N * 8), which is dominated by N.

### Improving the space requirement:

```cpp
class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        queue<pair<string, int>> q;
        q.push({startGene, 0});

        unordered_set<string> set_bank;
        for(string s : bank) set_bank.insert(s);

        while(!q.empty()) {
            auto [currentGene, cost] = q.front();
            q.pop();
            set_bank.erase(currentGene);
            if(currentGene == endGene) return cost;
            for(int i = 0; i < 8; i++) {
                char ch = currentGene[i];
                if(ch != 'A') {
                    string temp = currentGene;
                    temp[i] = 'A';
                    if(set_bank.find(temp) != set_bank.end()) q.push({temp, cost + 1});
                }
                if(ch != 'C') {
                    string temp = currentGene;
                    temp[i] = 'C';
                    if(set_bank.find(temp) != set_bank.end()) q.push({temp, cost + 1});
                }
                if(ch != 'G') {
                    string temp = currentGene;
                    temp[i] = 'G';
                    if(set_bank.find(temp) != set_bank.end()) q.push({temp, cost + 1});
                }
                if(ch != 'T') {
                    string temp = currentGene;
                    temp[i] = 'T';
                    if(set_bank.find(temp) != set_bank.end()) q.push({temp, cost + 1});
                }
            }

        }
        return -1;
    }
};
```

### Improvement: 
Use the `set_bank` set only. As only the genes that are in the vector `bank` can be valid, and so can be visited, we don't need the `visited` set. When we pop one gene from queue, we also remove it from `set_bank` as it is visited and can never be visited in the future.
