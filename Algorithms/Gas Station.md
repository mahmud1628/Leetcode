# [LeetCode 134 - Gas Station](https://leetcode.com/problems/gas-station/description/)
***
## Solution 1: (Time Limit Exceeded).

```cpp
class Solution {
    bool canComplete(int startIndex, int remainingGas, int remainingStations, vector<int> & gas, vector<int> & cost) {
        if(remainingStations == 0) return true;

        if(remainingGas + gas[startIndex] < cost[startIndex]) return false;

        return canComplete((startIndex + 1) % gas.size(), remainingGas + gas[startIndex] - cost[startIndex], remainingStations - 1, gas, cost);
    }
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        bool complete = false;
        int index;
        int n = gas.size();
        for(index = 0; index < n; index++) {
            complete = canComplete(index, 0, n, gas, cost);
            if(complete) break;
        }
        if(complete) return index;
        return -1;
    }
};
```
### Idea:
The algorithm tries to find a starting gas station from which it's possible to complete a full circle. It does this by iterating through each gas station as a potential starting point. For each potential starting station, it simulates the journey using a recursive helper function. The helper function checks if there's enough gas to reach the next station and then recursively calls itself for the next station with updated gas levels. If a full circle is completed from any starting station, that station's index is returned; otherwise, after checking all stations, -1 is returned.

### Algorithm:
1. **`canCompleteCircuit(gas, cost)` function:**
   - Initializes `complete` to `false` and `index` to 0.
   - Gets the number of gas stations, `n`.
   - Iterates through each gas station from `index = 0` to `n-1`.
   - For each `index`, it calls the `canComplete` helper function to check if a circuit can be completed starting from this `index`.
   - If `canComplete` returns `true`, it means a solution is found, so the loop breaks.
   - After the loop, if `complete` is `true`, the `index` of the successful starting station is returned.
   - If `complete` is `false` (meaning no starting station allowed a full circuit), -1 is returned.

2. **`canComplete(startIndex, remainingGas, remainingStations, gas, cost)` function (recursive helper):**
   - **Base Case 1:** If `remainingStations` is 0, it means all stations have been visited, so the circuit is complete. Return `true`.
   - **Base Case 2:** If the current `remainingGas` plus the `gas` at the `startIndex` is less than the `cost` to travel from `startIndex` to the next station, then it's impossible to proceed from this station. Return `false`.
   - **Recursive Step:** If the journey can continue:
     - Calculate the gas remaining after filling up at `startIndex` and traveling to the next station: `remainingGas + gas[startIndex] - cost[startIndex]`.
     - Recursively call `canComplete` for the next station: `(startIndex + 1) % gas.size()`.
     - Pass the updated `remainingGas`, decrement `remainingStations` by 1, and pass the `gas` and `cost` vectors.
     - Return the result of this recursive call.

### Time Complexity:
The `canCompleteCircuit` function iterates through each of the `n` gas stations. For each starting station, the `canComplete` function, in the worst case, visits all `n` stations recursively. This leads to a time complexity of O(n^2).

### Space Complexity:
The space complexity is dominated by the recursion depth of the `canComplete` function. In the worst case, the recursion can go up to `n` levels deep. Therefore, the space complexity is O(n) due to the call stack.

## Solution 2 : (Accepted)

```cpp
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        vector<bool> valid(n, true);
        for(int index = 0; index < n; index++) {
            if(valid[index] == false) continue; 
            int currentGas = 0;
            int curr = index;
            while(true) {
                if(currentGas + gas[curr] < cost[curr]) {
                    if(curr > index) {
                        for(int i = index; i < curr; i++) valid[i] = false;
                    }
                    if(curr < index) {
                        for(int i = index; i < n; i++) valid[i] = false;
                        for(int i = 0; i < curr; i++) valid[i] = false;
                    }
                    break;
                }
                currentGas = currentGas + gas[curr] - cost[curr];
                curr = (curr + 1) % n;
                if(curr == index) {
                    return index;
                }
            }
        }
        return -1;
    }
};
```

### Idea:
The algorithm tries to find a starting gas station from which it's possible to complete a full circle. It simulates the journey starting from each station. If a journey fails, it marks the stations that were part of the failed journey as invalid starting points for future attempts. The core idea is that if you start at station `A` and run out of gas before reaching station `B`, then any station between `A` and `B` (inclusive of `A`, exclusive of `B`) also cannot be a valid starting point to complete the circuit, because starting at any of those intermediate stations would mean you'd have even less gas by the time you reach `B` compared to starting at `A`.

### Algorithm:
1. Initialize a boolean vector `valid` of size `n` (number of gas stations), with all elements set to `true`. This vector keeps track of potential starting stations.
2. Iterate through each potential starting station `index` from 0 to `n-1`.
3. If `valid[index]` is `false`, it means this station has already been determined to be an invalid starting point, so `continue` to the next `index`.
4. If `valid[index]` is `true`, begin a simulated journey from this `index`:
   a. Initialize `currentGas` to 0.
   b. Set `curr` to the current station's index, which is initially `index`.
   c. Enter a `while(true)` loop to simulate the journey:
      i. Check if the gas at the current station (`gas[curr]`) plus the `currentGas` is insufficient to reach the next station (i.e., `currentGas + gas[curr] < cost[curr]`).
      ii. If insufficient gas:
          - This starting station `index` (and possibly others) is invalid. Mark all stations from `index` up to `curr` (exclusive of `curr` if `curr` is not the starting `index`) as invalid in the `valid` vector. The logic for marking invalid stations accounts for whether the failed segment wraps around the circular route.
          - `break` out of the inner `while` loop to try the next potential starting station.
      iii. If sufficient gas:
          - Update `currentGas`: `currentGas = currentGas + gas[curr] - cost[curr]`.
          - Move to the next station: `curr = (curr + 1) % n`.
          - If `curr` is back to the original `index`, it means a full circuit has been completed successfully. Return `index` as the valid starting station.
5. If the loop finishes without returning an `index`, it means no station allows for a complete circuit. Return -1.

### Time Complexity:
The outer loop iterates `n` times. In the worst case, for each starting station, the inner `while` loop might iterate up to `n` times. The invalidation step within the `while` loop also takes O(n) time in the worst case. Therefore, the overall time complexity is O(n^2).

### Space Complexity:
The algorithm uses a boolean vector `valid` of size `n` to keep track of valid starting points. This results in a space complexity of O(n).
