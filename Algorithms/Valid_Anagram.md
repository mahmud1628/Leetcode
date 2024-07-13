# Leetcode 242 - Valid Anagram
***
## Problem Description : 
Given two strings s and t, return true if t is an anagram of s, and false otherwise.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
typically using all the original letters exactly once.

### Constraints
 * 1 <= s.length, t.length <= 5 * 104
 * s and t consist of lowercase English letters.


## Approach 1 (Sorting) : [Accepted]

 We can sort the two strings and then match all the characters one by one


## Code :

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

## Time complexity : O(nlogn)


## Approach 2 (Count frequency) : [Accepted]
 Count the frequency of the characters in both strings,
 if the frequency count is same in both of the strings then return true else return false.


 ## Code : 

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

## Time complexity : O(n)

## Approach 3 (Using hash table) : [Accepted]
 The idea is to store the count of each character in one string using a map where key is the character itself and value is the count of appearance of that character.
 Then we traverse the second string and if we don't find a character in the map we return false immediately, and if we find a character in the map then we decrease the count of that character.
 At last, if the map is empty then we return true, otherwise false.
 ## Code : 
#include<bits/stdc++.h>
using namespace std;

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

 ## Time complexity : O(n)





