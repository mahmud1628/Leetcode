# Leetcode 242 - Valid Anagram
***
## Problem Description: 
Given two strings s and t, return true if t is an anagram of s, and false otherwise.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
typically using all the original letters exactly once.

### Constraints
 * 1 <= s.length, t.length <= 5 * 10<sup>4</sup>
 * s and t consist of lowercase English letters.  

## Solutions: 

### Approach 1 (Sorting) : [Accepted]

 We can sort the strings and then match all the characters one by one.
 ``` cpp
    class Solution {
    public:
        bool isAnagram(string s, string t) {
            if(s.size() != t.size()) return false;
            sort(s.begin(),s.end());
            sort(t.begin(),t.end());
            for(int i = 0 ;i<s.size();i++) {
                if(s[i] != t[i]) return false;
            }
            return true;
        }
    };
```

#### Time complexity : O(nlogn)  


### Approach 2 (Count frequency) : [Accepted]
 Count the frequency of the characters in both strings.<br>
 If the frequency count is same in both of the strings then return true else return false.<br>
 As both strings consist of lowercase english letters, we can take two array of size 26 to store frequency count.<br>

``` cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size() != t.size()) return false;
        vector<int> a(26,0);
        vector<int> b(26,0);
        for(int i=0;i<s.size();i++)
            a[s[i]-'a']++;
        for(int i=0;i<t.size();i++)
            b[t[i]-'a']++;
        for(int i=0;i<t.size();i++)
                if(a[t[i]-'a']!=b[t[i]-'a'])
                    return false;
        return true;
    }
};
```

#### Time complexity : O(n)

### Approach 3 (Using hash table) : [Accepted]
 Use a map to store the frequency count of each character in the first string where key is the character itself and value is the frequency count.<br>
 Then we traverse the second string and if we don't find a character in the map we return false immediately, and if we find a character in the map then we decrease the count of that character by 1.<br>
 At last, if the map is empty then we return true, otherwise false.<br>

``` cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size() != t.size()) return false;
        else {
            unordered_map<char,int> m;
            for(int i=0;i<s.size();i++) {
                if(m.empty()) m[s[i]] = 1;
                else if(m.find(s[i]) == m.end()) m[s[i]] = 1;
                else m[s[i]]++;
            }
            for(int i=0;i<t.size();i++) {
                if(m.find(t[i]) == m.end()) return false;
                else {
                    m[t[i]]--;
                    if(m[t[i]] == 0) m.erase(t[i]);
                }
            }
            return m.empty();
        }
        return true;
    }
};
```

#### Time complexity : O(n)





