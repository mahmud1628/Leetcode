# LeetCode - Minimum Window Substring
*** 
## Problem description:
    Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".

    The testcases will be generated such that the answer is unique.

    

    Example 1:

        Input: s = "ADOBECODEBANC", t = "ABC"
        Output: "BANC"
        Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

    Example 2:

        Input: s = "a", t = "a"
        Output: "a"
        Explanation: The entire string s is the minimum window.

    Example 3:

        Input: s = "a", t = "aa"
        Output: ""
        Explanation: Both 'a's from t must be included in the window.
        Since the largest window of s only has one 'a', return empty string.

### Constraints:
 * m == s.length
 * n == t.length
 * 1 <= m, n <= 105
 * s and t consist of uppercase and lowercase English letters.

## Solutions:

### Approach 1 : [Accepted]
 * Take an unordered map t_map. This will map the characters in t to their frequency in t.
 * left = 0, right = 0. left is the starting of the current substring amd right is the end of the current substring.
 *  res_left = 0, res_right = 0, min_length = 0.
 * map_initial_size = t_map.size(). In our implementation, when we found any character that is present in t and also in the substring, we will decrese its frequency in t. If a characters frequency becomes zero, we will not erase it from the map, rather we will decrease map_initial_size, implying that we have found a particluar character in the substring same number of time that the character appear in t.
 * Iterate through s while right is less than m.
    * If s[right] is not found in t_map, simply ignore it and increase right by 1.
    * If s[right] is found in t_map,
        * We have found a character in the current substring that is also in t. Decrease this characters frequency in the map.
        * If the characters frequency becomes zero, then we have found that character the same number of time that it appears in t. Now decrease map_initial_size.
        * If map_initial_size becomes zero, then it means that we have found all the characters the same number of time that they appear in t. So we have found a possible candidate for our result.
            * Now we need to increase left to get the minimum length. While s[left] is not found in the map, increase left. When s[left] is found, check its frequency. If it is negative, then it means that the character has been found more than its initial frequency in current substring. So, we can again increase left because we can have a valid substring without this index. So again increase left, and before increaseing left, inceraese the characters frequncey too.
            Do this until frequency of s[left] is not negative.
            * Now we have found a valid substring. Compare its length with min_length. If min_length is bigger, than update res_left, res_right and min_length.
            * Now to find more valid substrings, we need to update left. Increase the frequency of s[left] in the map and update left. If frequency of s[left] becomes 1, then update map_initial_size too.
            * Now to ignore some characters that can't be part of a valid minimum length substring, keep updating left while s[left] is not found in the map.
 * Return the substring that starts at res_left and ends at res_right.

#### Time complexity: O(n)
#### Space complexity: O(m)


``` cpp
class Solution {
public:
    string minWindow(string s, string t) {
        if(s.size() < t.size()) return "";
        unordered_map<char,int> t_map;
        for(char c : t) {
            if(t_map.find(c) == t_map.end()) {
                t_map[c] = 1;
            }
            else {
                t_map[c]++;
            }
        }
        int left = 0, right = 0;
        int map_initial_size = t_map.size();
        int res_left = 0, res_right = 0;
        int min_length = INT_MAX;
        while(right < s.size()) {
            if(t_map.find(s[right]) == t_map.end()) {
                right++;
            }
            else {
                t_map[s[right]]--;
                if(t_map[s[right]] == 0) {
                    map_initial_size--;
                }
                if(!map_initial_size) {
                    again:
                    while(t_map.find(s[left]) == t_map.end()) {
                        left++;
                    }
                    if(t_map[s[left]] < 0) {
                        t_map[s[left]]++;
                        left++;
                        goto again;
                    }
                    if(min_length > right - left + 1) {
                        res_left = left;
                        res_right = right;
                        min_length = right - left + 1;
                    }
                    t_map[s[left]]++;
                    if(t_map[s[left]] == 1)
                        map_initial_size++;
                    left++;
                    while(left < s.size() && t_map.find(s[left]) == t_map.end()) {
                        left++;
                    }
                }
                right++;
            }
        }
        if(res_left == res_right) {
            if(t.size() > 1 || t[0] != s[res_left]) {
                return "";
            }
        }
        return s.substr(res_left,min_length);
    }
};
```