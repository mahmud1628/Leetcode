# LeetCode 3 - Longest Substring Without Repeating Characters
***
## Problem description:
    Given a string s, find the length of the longest substring without repeating characters.


    Example 1:
        Input: s = "abcabcbb"
        Output: 3
        Explanation: The answer is "abc", with the length of 3.

    Example 2:
        Input: s = "bbbbb"
        Output: 1
        Explanation: The answer is "b", with the length of 1.

    Example 3:
        Input: s = "pwwkew"
        Output: 3
        Explanation: The answer is "wke", with the length of 3.
        Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

### Constraints:
 * 0 <= s.length <= 5 * 104
 * s consists of English letters, digits, symbols and spaces.

## Solutions:

### Approach 1 : [Accepted]
 * Take an unordered map .
 * max_length = 0, length = 0, start_index = 0.
 * Iterate through the string
    * If a character is not found in the map, then increase length and push the character to the map.
    * Otherwise, update max_length and set length to 0 as we will start from a new substring now. Clear the map, increase start_index by 1. Start iterating from start_index again.
 * At last return the maximum of max_length and length.

#### Time complexity: O(n)
#### Space complexity: O(n)

``` cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.size()==0)
            return 0;
        unordered_map<char,int> a; 
        int max_length = 0;
        int length=0;
        int start_index = 0;
        for(int i=start_index;i<s.size();i++) {
            if(a.find(s[i])==a.end()) {
                length++;
                a[s[i]]=1;
            }
            else {
                max_length = max(max_length,length);
                length = 0;
                a.clear();
                i = ++start_index;
                i--;
            }
        }
        return max(max_length,length);
    }
};
```

### Approach 2 : [Accepted]
 * Take an unordered_map m.
 * start_index = -1 (The current substring starts at the right of this point)
 * max_length = 0
 * Iterath through the string
    * If a character is found in the map and its index is greater than start_index(check this because we will always check the characters at the right of start_index as the current substring started at the right of start_index), then it's a repeating character. So update start_index to the repeating characters previous index(by doing this we are eliminating all the characters before start_index, including the character at start_index, from our consideration).
    * Insert the character to the map(or update its value). The character will be the key and index will be the value.
    * Compute max_length in every step comparing previous max_length and the current length of the substring ,i.e, (i - start).
 * Return max_length

#### Time complexity: O(n)
#### Space complexity: O(n)

``` cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.size() <= 1) return s.size();
        unordered_map<char,int> m;
        int start = -1;
        int max_length = 0;
        int i;
        for(i = 0;i < s.size();i++) {
            if(m.find(s[i]) != m.end() && m[s[i]] > start) {
                start = m[s[i]];
            }
            m[s[i]] = i;
            max_length = max(max_length,i - start);
        }
        return max_length;
    }
};
```