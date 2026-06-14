## Solution 1: [Accepted]
```cpp
class Solution {
    // checks whether the subtring is a palindrome
    bool isPalindrome(string & s, int start, int end) {
        while(start <= end) {
            if(s[start] != s[end]) return false;
            start++;
            end--;
        }
        return true;
    }
public:
    string longestPalindrome(string s) {
        int max_length = -1;
        string longest = "";

        for(int i = 0; i < s.size(); i++) {
            for(int j = i; j < s.size(); j++) {
                if(isPalindrome(s, i , j)) {
                    if(j - i + 1 > max_length) {
                        max_length = j - i + 1;
                        longest = s.substr(i, max_length);
                    }
                }
            }
        }
        return longest;
    }
};
```

### Idea:
> We iterate through all possible substrings of the given string `s`. For each substring, we check if it is a palindrome using the helper function `isPalindrome`. If it is a palindrome, we compare its length with the maximum length found so far. If the current substring is longer than the maximum length found so far, we update the maximum length and the longest palindromic substring. Finally, we return the longest palindromic substring.
Leetcode showed Memory limit excedded when I passed the string `s` by value. But when I passed the string `s` by reference it passed successfully. I think this is because making a copy of a string of length n takes $O(n)$ time and $O(n)$ space.    

### Time Complexity:
> $O(n^3)$ 

### Space Complexity:
> $O(1)$

where $n$ is the length of the string `s`.  


## Solution 2: [Accepted]
```cpp
class Solution {
    // search odd palindromes considering the `middle` as the index of the center of a palindrome
    void searchOddPalindromes(string & s, int middle, int & max_length, string & longest) {
        int left = middle;
        int right = middle; // a chracter itself is a palindrome, so setting left and right at the same place so that at least we have a palindrome of length 1

        search(s, left, right, max_length, longest);
    }

    // search even palindromes considering the `middle_left` as the idnex of the left character as the center of a palindrome
    void searchEvenPalindromes(string & s, int middle_left, int & max_length, string & longest) {
        int left = middle_left;
        int right = middle_left + 1;

        search(s, left, right, max_length, longest);
    }

    void search(string & s, int left, int right, int & max_length, string & longest) {
        while(true) {
            if(left < 0) break;
            if(right == s.size()) break;
            if(s[left] != s[right]) break;
            left--;
            right++;
        }
        left++;
        right--;
        int length = right - left + 1;
        if(length > max_length) {
            max_length = length;
            longest = s.substr(left, length);
        }
    }
public:
    string longestPalindrome(string s) {
        int max_length = -1;
        string longest = "";
        for(int i = 0; i < s.size(); i++) {
            searchOddPalindromes(s, i, max_length, longest);
            searchEvenPalindromes(s, i, max_length, longest);
        }
        return longest;
    }
};
```

### Idea:
> Instead of checking every substring, we can use the concept of "Expand Around Center". We can think of each character (for odd length palindromes) and each pair of adjacent characters (for even length palindromes) as a potential center of a palindrome. Then, we expand outwards from each center to find all possible palindromes.

### Time Complexity:
> $O(n^2)$  

### Space Complexity:
> $O(1)$  

where $n$ is the length of the string `s`.      

### Shorter version:
```cpp
class Solution {
    void search(string & s, int left, int right, int & max_length, string & longest) {
        while(true) {
            if(left < 0) break;
            if(right == s.size()) break;
            if(s[left] != s[right]) break;
            left--;
            right++;
        }
        left++;
        right--;
        int length = right - left + 1;
        if(length > max_length) {
            max_length = length;
            longest = s.substr(left, length);
        }
    }
public:
    string longestPalindrome(string s) {
        int max_length = -1;
        string longest = "";
        for(int i = 0; i < s.size(); i++) {
            search(s, i, i, max_length, longest); // search odd ones
            search(s, i, i + 1, max_length, longest); // search even ones
        }
        return longest;
    }
};
```