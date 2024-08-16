# LeetCode 125 - Valid Palindrome
***
## Problem Description:
    A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

    Given a string s, return true if it is a palindrome, or false otherwise.


    Example 1:
    Input: s = "A man, a plan, a canal: Panama"
    Output: true
    Explanation: "amanaplanacanalpanama" is a palindrome.

    Example 2:
    Input: s = "race a car"
    Output: false
    Explanation: "raceacar" is not a palindrome.

    Example 3:
    Input: s = " "
    Output: true
    Explanation: s is an empty string "" after removing non-alphanumeric characters.
    Since an empty string reads the same forward and backward, it is a palindrome.

### Constraints:
 * 1 <= s.length <= 2 * 105
 * s consists only of printable ASCII characters.

## Solutions:

### Approach 1 : [Accepted]
 * Take a vector.
 * Iterate through the given string.
     * Check each character if it is alphanumeric. If it is, then push it to the vector. To check if it is alphanumeric, we can use ASCII values of alphanumeric characters or we can use c++ function isalpha() and isdigit().
 * Now iterate through the vector and check if it is a palindrome by matching i-th character with (n - i - 1)-th character where n is the size of the vector.

#### Time Complexity: O(n)
#### Space Complexity: O(n)

``` cpp
class Solution {
public:
    bool isPalindrome(string s) {
        vector<char> v;
        for(char c : s) {
            if((48 <= c && c <= 57) || (65 <= c && c <= 90) || (97 <= c && c <= 122)) { // or use isalpha() and isdigit()
                v.push_back(tolower(c));
            }
        }
        int n = v.size();
        for(int i=0;i<n;i++) {
            if(v[i] != v[n - i -1]) {
                return false;
            }
        }
        return true;
    }
};
```

### Approach 2[Two pointer] : [Accepted]
 * Take two variable left,right.
 * Initialize left = 0 and right = s.size() - 1.
 * Take a while loop with condition left <= right
    * Check if s[left] and s[right] both are alphanumeric. If so, then match them. If they are same, then continue by increasing left and decreasing right. Otherwise return false.
    * If s[left] is not alphanumeric, then increase left.
    * If s[right] is not alphanumeric, then decrease right.
 * At last, return true.

#### Time Complexity: O(n)
#### Space Complexity: O(1)

``` cpp
class Solution {
    bool valid_char(char c) {
        if(((48 <= c && c <= 57) || (65 <= c && c <= 90) || (97 <= c && c <= 122))) { // or use isalpha() and isdigit()
            return true;
        }
        return false;
    }
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.size() - 1;
        while(left <= right) {
            if(valid_char(s[left]) && valid_char(s[right])) {
                if(tolower(s[left]) != tolower(s[right])) {
                    return false;
                }
                else {
                    left++;
                    right--;
                }
            }
            else if(!valid_char(s[left])) {
                left++;
            }
            else {
                right--;
            }
        }
        return true;
    }
};
```
