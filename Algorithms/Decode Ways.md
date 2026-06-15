# [LeetCode 91 - Decode Ways](https://leetcode.com/problems/decode-ways/description/)
***
## Solution 1: [Accepted]
```cpp
class Solution {
    int numDecodings(string & s, int index, vector<int> & mem) {
        if(index < s.size() && s[index] == '0') return 0;
        if(index >= s.size() - 1) {
            return 1;
        }
        if(mem[index] != -1) return mem[index];

        char ch = s[index];
        char next_ch = s[index + 1];
        int a = numDecodings(s, index  + 1, mem);
        int b = 0;
        if((ch == '2' && next_ch < '7') || ch == '1') {
                b = numDecodings(s, index + 2, mem);
        }
        mem[index] = a + b;
        return mem[index];
    }
public:
    int numDecodings(string s) {
        if(s[0] == '0') return 0;
        vector<int> mem(s.size(), -1);
        return numDecodings(s, 0, mem);
    }
};
```

### Idea:
> This is a dynamic programming problem. We can solve it using recursion with memoization. We can define a function `numDecodings(string & s, int index, vector<int> & mem)` which returns the number of ways to decode the substring starting from index. 

> At each index $i$ we can either take a single digit or two digits. There are several conditions.

> If we find a `0` at the current index, we can't make any decoding from it as `0` is not a valid code for any character and return 0.

> Otherwise, we have two parallel paths or branches. In one branch we take the single digit `s[index]` and make a function call for `index + 1`. In the other branch we check if we can take two digits `s[index]` and `s[index + 1]` as a valid code for a character. If we can, we make a function call for `index + 2`. The result is the sum of the results of these two branches. 

### Time Complexity:
> $O(n)$ 

### Space Complexity:
> $O(n)$
 
where `n` is the size of the input string `s`.