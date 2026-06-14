## Solution 1: [Accepted]
```cpp
class Solution {
    bool isPalindrome(string s, int start, int end) {
        while(start <= end) {
            if(s[start] != s[end]) return false;
            start++;
            end--;
        }
        return true;
    }
public:
    int countSubstrings(string s) {
        int count = 0;
        for(int i = 0; i < s.size(); i++) {
            for(int j = i; j < s.size(); j++) {
                if(isPalindrome(s, i, j)) count++;
            }
        }
        return count;
    }
};
```

### Idea:
> We iterate through all possible substrings of the given string s. For each substring, we check if it is a palindrome using the helper function isPalindrome. If it is a palindrome, we increment the count. Finally, we return the total count of palindromic substrings.

### Time Complexity:
> $O(n^3)$

### Space Complexity:
> $O(1)$

where n is the length of the string s.  

## Solution 2: [Accepted]
```cpp
class Solution {
    // This function finds all the odd length palindromes treating the the `middle` as the center of the palindrome
    int findOddPalindromes(string s, int middle) {
        int count = 1; // any character itself is a palindrome
        int left = middle - 1;
        int right = middle + 1;
        count += countPalindromes(s, left, right);
        return count;
    }

    // this function finds all the even length palindromes treating `middle_left` as the index of the left character at the center of the palindrme 
    int findEvenPalindromes(string s, int middle_left) {
        int left = middle_left;
        int right = middle_left + 1;
        return countPalindromes(s, left, right);
    }

    int countPalindromes(string s, int left, int right) {
        int count = 0;
        while(true) {
            if(left < 0) break;
            if(right >= s.size()) break;

            if(s[left] != s[right]) break;

            count++;
            left--;
            right++;
        }
        return count;
    }
public:
    int countSubstrings(string s) {
        int count = 0;
        for(int i = 0; i < s.size(); i++) {
            count += findOddPalindromes(s, i);
            count += findEvenPalindromes(s, i);
        }
        return count;
    }
};
```

### Idea:
> Instead of checking every substring, we can use the concept of "Expand Around Center". We can think of each character (for odd length palindromes) and each pair of adjacent characters (for even length palindromes) as a potential center of a palindrome. Then, we expand outwards from each center to find all possible palindromes. 

### Time Complexity:
> $O(n^2)$ 

### Space Complexity:
> $O(1)$

where n is the length of the string s.  



