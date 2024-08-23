# LeetCode 424 - Longest Repeating Character Replacement
***
## Problem description:
    You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most k times.

    Return the length of the longest substring containing the same letter you can get after performing the above operations.

    

    Example 1:
        Input: s = "ABAB", k = 2
        Output: 4
        Explanation: Replace the two 'A's with two 'B's or vice versa.

    Example 2:
        Input: s = "AABABBA", k = 1
        Output: 4
        Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
        The substring "BBBB" has the longest repeating letters, which is 4.
        There may exists other ways to achieve this answer too.


### Constraints:
 * 1 <= s.length <= 105
 * s consists of only uppercase English letters.
 * 0 <= k <= s.length


## Solutions:

### Approach 1 : [Accepted]

#### Intuition:
    We take a substring, and then check the most frequent character in that substring. It's obvious that we do not replace the most frequnt character in a substring,rather we should replace the other characters to get maximum length. Now we check that if the other characters can't be replaced with k operations. Just check whether (length_of_substring - most_frequent_character_length) is less than or equal to k. If so, then we can replace them in k operations, otherwise not. If we can replace, then this substring is a possible candidate for our expected substring and we take the length of the substring as a candidate for our result.

#### Algorithm:
 * left = 0, right = 1
 * Take an unordered_map to store a character as key and its frequency as value
 * insert the character at the left into the map with value 1.
 * max_length = 0, max_frequency = 1
 * Take a while loop 
    * If the character at right is not found in the map, insert it.
    * Otherwise, increase its value by 1. And also update max_frequncy.
    * If length of the substring minus max_frequency is greater than k, then we have found a substring that is not valid according to our expectation but the previous substring was valid. So take maximum of max_length and length of the previous substring. Update left as we will no more find any valid substring if we start at current left and only increase right. Also we need to update the characters (which is at left currently) value in the map before updating left.
    * Increment right.
 * Return maximum of max_length and (right - left)

#### Time complexity: O(n)
#### Space complexity: O(n)
``` cpp
class Solution {
public:
    int characterReplacement(string s, int k) {
        if(s.size() <= 1) return s.size();
        int left = 0; // start of substring
        int right = 1; // end of substring
        int max_length = 0; // result
        int max_frequency = 1; // frequency of the most frequent character in substring
        unordered_map<char,int> m; // store character - frequency pair
        m[s[left]] = 1;
        while(right < s.size()) {
            if(m.find(s[right]) == m.end()) {
                m[s[right]] = 1;
            }
            else {
                m[s[right]]++;
                if(m[s[right]] > max_frequency) {
                    max_frequency = m[s[right]];
                }
            }
            if(right - left + 1 - max_frequency > k) {  //length of current substring = right - left + 1
                max_length = max(max_length,right - left); // length of previous substring = right - left
                m[s[left]]--;
                left++;
            }
            right++;
        }
        return max(max_length,right - left);
    }
};
```