# Leetcode 49- Group Anagrams
***
## Problem Description : 
Given an array of strings strs, group the anagrams together. You can return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

 

Example 1:

Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
Example 2:

Input: strs = [""]
Output: [[""]]
Example 3:

Input: strs = ["a"]
Output: [["a"]]
 

### Constraints:

 * 1 <= strs.length <= 104
 * 0 <= strs[i].length <= 100
 * strs[i] consists of lowercase English letters.

## Solutions: 

### Approach 1 (Brute force) : [TLE]
 Repeatedly Take two strings and check if they are anagram.

``` cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        int index = -1;
        vector<bool> flag(strs.size(),false);
        for(int i = 0;i<strs.size();i++) {
            if(flag[i]) continue;
            res.push_back({});
            index++;
            res[index].push_back(strs[i]);
            flag[i] = true;
            for(int j= i+1 ;j<strs.size();j++) {
                if(flag[j]) continue;
                if(strs[i].size() != strs[j].size()) continue;
                vector<int> a(26,0);
                vector<int> b(26,0);
                for(int k=0;k<strs[i].size();k++)
                    a[strs[i][k]-'a']++;
                for(int l=0;l<strs[j].size();l++)
                    b[strs[j][l]-'a']++;
                bool f = true;
                for(int k=0;k<strs[i].size();k++)
                        if(a[strs[i][k]-'a']!=b[strs[i][k]-'a'])
                            {
                                f = false;
                                break;
                            }
                if(f) {
                    res[index].push_back(strs[j]);
                    flag[j] = true;
                }
            }
        }
        return res;
    }
};
```
#### Time Complexity : O(n^3)


### Approach 2 (Using map) : [Accepted]
 Take a vector<int> as the key to store character frequency.
 All the strings with the same frequency will be mapped to the same key.

``` cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<vector<int>,vector<string>> m;
        for(string s : strs) {
            vector<int> a(26,0);
            for(auto ch : s)  {
                a[ch - 'a']++;
            }
            if(m.find(a) == m.end()) {
                m[a] = {};
                m[a].push_back(s);
            }
            else {
                m[a].push_back(s);
            }
        }
        map<vector<int>,vector<string>> :: iterator it ;
        it = m.begin();
        vector<vector<string>> res;
        while(it!= m.end()) {
            res.push_back(it->second);
            it++;
        }
        return res;

    }
};
```

### Approach 3 (using hash table) : [Accepted]
Iterate through the vector of strings.
Sort the string and push it to the hash table.

``` cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>> u_map;
        for(auto s : strs) {
            string t = s;
            sort(t.begin(),t.end());
            if(u_map.find(t) == u_map.end()) {
                u_map[t] = {};
                u_map[t].push_back(s);
            }
            else {
                u_map[t].push_back(s);
            }
        }
        vector<vector<string>> res;
        auto it = u_map.begin();
        while(it!=u_map.end()) {
            res.push_back(it->second);
            it++;
        }
        return res;
    }
};
```

## Approach 4 (Using hash table but more efficient) : [Accepted]

 Take one string and sort it. Now instead of pushing it to the hash table, store it directly in the result vector.

``` cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,int> u_map;
        vector<vector<string>> res;
        int index = 0;
        for(auto s : strs) {
            string t = s;
            sort(t.begin(),t.end());
            if(u_map.find(t) == u_map.end()) {
                u_map[t] = index;
                res.push_back({});
                res[index].push_back(s);
                index++;
            }
            else {
                res[u_map[t]].push_back(s);
            }
        }
        return res;
    }
};
```

