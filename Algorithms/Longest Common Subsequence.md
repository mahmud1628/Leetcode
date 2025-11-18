# [LeetCode 1143 - Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/description/)
***

## Solution 1 : (Time limit exceeded)

```cpp
class Solution {
    int recursiveLongestCommonSubsequence(int index1, int index2, string text1, string text2) {
        if(index1 == text1.size() || index2 == text2.size()) return 0;

        if(text1[index1] == text2[index2]) return 1 + recursiveLongestCommonSubsequence(index1 + 1, index2 + 1, text1, text2);

        return max(recursiveLongestCommonSubsequence(index1 + 1, index2, text1, text2), recursiveLongestCommonSubsequence(index1, index2 + 1, text1, text2));
    }
public:
    int longestCommonSubsequence(string text1, string text2) {
        return recursiveLongestCommonSubsequence(0,0,text1,text2);
    }
};
```
### Idea:
The problem asks for the longest common subsequence between two strings. A subsequence maintains the relative order of characters but can skip characters. This recursive approach breaks down the problem by considering characters from the beginning of both strings. If the current characters match, we count them as part of the common subsequence and move to the next characters in both strings. If they don't match, we explore two possibilities: either the longest common subsequence doesn't include the current character from the first string (so we advance in the first string and keep the second string's current character), or it doesn't include the current character from the second string (so we advance in the second string and keep the first string's current character). We take the maximum of these two possibilities. The base case is when we reach the end of either string, meaning there are no more characters to compare, so the common subsequence length from that point is 0.

### Algorithm:
1. **`longestCommonSubsequence(text1, text2)`:** This is the main function that initiates the recursive process. It calls a helper function `recursiveLongestCommonSubsequence` starting from the beginning of both strings (index 0 for `text1` and index 0 for `text2`).

2. **`recursiveLongestCommonSubsequence(index1, index2, text1, text2)`:**
   - **Base Case:** If `index1` reaches the end of `text1` (`text1.size()`) or `index2` reaches the end of `text2` (`text2.size()`), it means we've exhausted one of the strings. No further common characters can be found, so return 0.
   - **Matching Characters:** If the character at `text1[index1]` is equal to the character at `text2[index2]`, this character is part of a common subsequence. We add 1 to the count and recursively call the function for the next characters in both strings: `recursiveLongestCommonSubsequence(index1 + 1, index2 + 1, text1, text2)`.
   - **Non-Matching Characters:** If the characters at `text1[index1]` and `text2[index2]` do not match, we have two choices:
     - Ignore `text1[index1]` and find the longest common subsequence starting from `index1 + 1` in `text1` and `index2` in `text2`: `recursiveLongestCommonSubsequence(index1 + 1, index2, text1, text2)`.
     - Ignore `text2[index2]` and find the longest common subsequence starting from `index1` in `text1` and `index2 + 1` in `text2`: `recursiveLongestCommonSubsequence(index1, index2 + 1, text1, text2)`.
     - We return the maximum of these two recursive calls, as we want the longest possible common subsequence.

### Time Complexity:
The time complexity is exponential, specifically O(2^(m+n)), where m and n are the lengths of `text1` and `text2`, respectively. This is because in the worst case (when characters don't match frequently), each recursive call can branch into two, leading to a large number of repeated subproblems.

### Space Complexity:
The space complexity is O(m + n) in the worst case due to the recursion depth. The call stack can grow up to the sum of the lengths of the two strings in a scenario where characters are not matched and the recursion goes deep.

## Improvement to solution 1: (Accepted)

```cpp
class Solution {
    int recursiveLongestCommonSubsequence(int index1, int index2, string & text1, string & text2, vector<vector<int>> & mem) {
        if(index1 == text1.size() || index2 == text2.size()) return 0;

        if(mem[index1][index2] == -1) {
            if(text1[index1] == text2[index2]) mem[index1][index2] = 1 + recursiveLongestCommonSubsequence(index1 + 1, index2 + 1, text1, text2, mem);

            else mem[index1][index2] = max(recursiveLongestCommonSubsequence(index1 + 1, index2, text1, text2, mem), recursiveLongestCommonSubsequence(index1, index2 + 1, text1, text2, mem));
    
        }

        return mem[index1][index2];

    }
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> mem(text1.size(), vector<int>(text2.size(), -1));
        return recursiveLongestCommonSubsequence(0,0,text1,text2, mem);
    }
};
```

### Idea:
The algorithm uses a recursive approach with memoization to find the longest common subsequence (LCS). It explores possibilities by considering whether the current characters of both strings match or not. If they match, it means we've found one character of a common subsequence, so we add 1 and move to the next characters in both strings. If they don't match, we have two choices: either skip the current character in the first string and compare with the second string, or skip the current character in the second string and compare with the first string. We take the maximum of these two choices. Memoization is used to store the results of subproblems to avoid redundant calculations.

### Algorithm:
1.  **`longestCommonSubsequence(text1, text2)` Function:**
    *   Initializes a 2D vector `mem` of size `text1.size()` x `text2.size()`, filled with -1. This `mem` table will store the results of `recursiveLongestCommonSubsequence` for each pair of indices `(index1, index2)`.
    *   Calls `recursiveLongestCommonSubsequence` starting from the beginning of both strings (index 0 for both).
    *   Returns the result of the recursive call.

2.  **`recursiveLongestCommonSubsequence(index1, index2, text1, text2, mem)` Function:**
    *   **Base Case:** If `index1` reaches the end of `text1` or `index2` reaches the end of `text2`, it means we have exhausted one of the strings, so there are no more common subsequences to find from this point. Return 0.
    *   **Memoization Check:** If `mem[index1][index2]` is not -1, it means the result for this subproblem has already been computed and stored. Return the stored value `mem[index1][index2]`.
    *   **Recursive Step:**
        *   **If `text1[index1]` equals `text2[index2]`:** This means the current characters match. This character can be part of the LCS. So, we add 1 (for the current matching character) to the LCS of the remaining substrings (`text1` from `index1 + 1` and `text2` from `index2 + 1`). Store this result in `mem[index1][index2]` and return it.
        *   **If `text1[index1]` does not equal `text2[index2]`:** The current characters don't match. We have two options:
            1.  Exclude `text1[index1]` and find the LCS of `text1` from `index1 + 1` and `text2` from `index2`.
            2.  Exclude `text2[index2]` and find the LCS of `text1` from `index1` and `text2` from `index2 + 1`.
            We take the maximum of these two recursive calls. Store this maximum value in `mem[index1][index2]` and return it.

### Time Complexity:
O(m*n), where m and n are the lengths of text1 and text2 respectively. This is because each subproblem (defined by a pair of `index1` and `index2`) is computed only once due to memoization. There are m*n possible subproblems.

### Space Complexity:
O(m*n) for the memoization table `mem`. Additionally, there is O(m + n) space for the recursion call stack in the worst case.
