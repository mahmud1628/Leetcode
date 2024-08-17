# LeetCode 20 - Valid Parantheses
***
## Problem description:
    Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

    An input string is valid if:

    Open brackets must be closed by the same type of brackets.
    Open brackets must be closed in the correct order.
    Every close bracket has a corresponding open bracket of the same type.
    

    Example 1:
    Input: s = "()"
    Output: true

    Example 2:
    Input: s = "()[]{}"
    Output: true

    Example 3:
    Input: s = "(]"
    Output: false

### Constraints: 
 * 1 <= s.length <= 104
 * s consists of parentheses only '()[]{}'.

## Solutions: 

### Approach 1 [Using stack] :  [Accepted]
 * Take an empty stack.
 * Iterate through the string.
    * If the character is an opening one, then push it to the stack.
    * If the character is an closing one, 
        * Check if the stack is empty, if so, return false.
        * Otherwise check the top of the stack whether we have the corresponding opening bracket of the closing one. If so, pop that bracket. Otherwise return false.
 * After iterating the whole string, if the stack is not empty, then return false. Otherwise return true.

#### Time complexity: O(n)
#### Space complexity: O(n)

``` cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for(auto ch:s) {
            if(ch=='(' || ch=='{' || ch=='[') {
                st.push(ch);
            }
            else if(ch == ')') {
                if(st.size() == 0) {
                    return false;
                }
                if(st.top() == '(') {
                    st.pop();
                }
                else return false;
            }
            else if(ch == '}') {
                if(st.size() == 0) {
                    return false;
                }
                if(st.top() == '{') {
                    st.pop();
                }
                else return false;
            }
            else if(ch == ']') {
                if(st.size() == 0) {
                    return false;
                }
                if(st.top() == '[') {
                    st.pop();
                }
                else return false;
            }
        }
        if(st.size()) {
            return false;
        }
        return true;
    }
};
```