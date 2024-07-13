#include<bits/stdc++.h>
using namespace std;

/*
Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

 

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Example 2:

Input: nums = [1], k = 1
Output: [1]
 

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
k is in the range [1, the number of unique elements in the array].
It is guaranteed that the answer is unique.
 

Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
*/


/*
## Approach 1 (using hash table and vector) : [Accepted]
    Take a map to store element-frequency.
    Traverse the array and increase the frequency of an element in the map by 1.
    Then take a vector to store all these element-frequncey pair.
    Sort the vector in increasing order.
    Take last k elements from this vector.
## Time Complexity : O(nlogn)

## Code :
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> m;
        for(auto i : nums) {
            if(m.find(i) == m.end()) m[i] = 1;
            else m[i]++;
        }
        vector<pair<int,int>> v;
        auto it = m.begin();
        while(it != m.end()) {
            v.push_back(make_pair(it->second,it->first));
            it++;
        }
        sort(v.begin(),v.end());
        vector<int> res;
        for(int i = v.size() - 1;k;i--,k--) {
            res.push_back(v[i].second);
        }
        return res;
    }
};
*/

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

/*
 ## Approach 2 (Using hash table and priority queue) : [Accepted]
 Similar to the previous method.
 But instead of storing the element-frequency pairs in the vector and then sorting them, we now push them to a priority queue.
 Then we extract top k items from that priority queue.
 ## Time complexity : O(nlogn)
*/
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> m;
        for(auto i : nums) {
            if(m.find(i) == m.end()) m[i] = 1;
            else m[i]++;
        }
        priority_queue<pair<int,int>> p;
        auto it = m.begin();
        while(it != m.end()) {
            p.push(make_pair(it->second,it->first));
            it++;
        }
        vector<int> res;
        while(k--) {
            res.push_back(p.top().second);
            p.pop();
        }
        return res;
    }
};