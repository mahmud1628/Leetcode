# [LeetCode 299 - Bulls and Cows]()
***
## Solution 1:

```cpp
class Solution {
public:
    string getHint(string secret, string guess) {
        int bulls = 0, cows = 0;
        unordered_map<char, int> mp;
        for(char c : secret) mp[c]++;
        for(int i = 0; i < secret.size(); i++) {
            if(secret[i] == guess[i]) {
                bulls++;
                mp[guess[i]]--;
            }
        }
        for(int i = 0; i < secret.size(); i++) {
            if(secret[i] != guess[i] && mp.find(guess[i]) != mp.end()) {
                if(mp[guess[i]] > 0) {
                    cows++;
                    mp[guess[i]]--;
                }
            }
        }
        return to_string(bulls) + "A" + to_string(cows) + "B";
    }
};
```

### Idea:
The algorithm aims to count the number of bulls and cows by first identifying and counting all the bulls. Bulls are digits that match in both position and value. After accounting for bulls, it then tries to find cows. Cows are digits that are present in the secret number but not in the correct position, and crucially, they haven't already been counted as bulls. The algorithm uses a frequency map to keep track of the available digits in the secret number that can potentially form cows.

### Algorithm:
1.  Initialize `bulls` and `cows` counters to 0.
2.  Create an `unordered_map` (hash map) called `mp` to store the frequency of each character (digit) in the `secret` string.
3.  Iterate through the `secret` string and populate the `mp` with the counts of each digit.
4.  First pass: Iterate through both `secret` and `guess` strings simultaneously using an index `i`.
    *   If `secret[i]` is equal to `guess[i]`, increment `bulls`.
    *   Since this digit in `guess` is a bull, it cannot be a cow. Therefore, decrement the count of `guess[i]` in `mp`. This effectively removes the digit that formed a bull from being considered for cows.
5.  Second pass: Iterate through both `secret` and `guess` strings simultaneously again using an index `i`.
    *   This time, we only consider digits that were *not* bulls (i.e., `secret[i] != guess[i]`).
    *   Check if the current digit `guess[i]` exists in the `mp` (meaning it's a digit from the `secret` number) and if its count in `mp` is greater than 0.
    *   If both conditions are true, it means `guess[i]` is a digit present in `secret` but not in the correct position (and not already used as a bull). Increment `cows`.
    *   Decrement the count of `guess[i]` in `mp` to mark that this digit has now been used as a cow.
6.  Finally, construct the result string by concatenating the string representation of `bulls`, "A", the string representation of `cows`, and "B".

### Time Complexity:
The algorithm performs two passes through the strings `secret` and `guess`, each of length N (where N is the length of the strings). The operations within the loops (map lookups, insertions, decrements) take average O(1) time for an `unordered_map`. Therefore, the total time complexity is O(N).

### Space Complexity:
The algorithm uses an `unordered_map` to store the frequency of digits in the `secret` string. In the worst case, if all digits in the secret are unique, the map will store up to 10 entries (for digits '0' through '9'). This is a constant amount of extra space, independent of the input string length. Thus, the space complexity is O(1).
