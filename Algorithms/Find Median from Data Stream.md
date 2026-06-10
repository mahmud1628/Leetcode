# [LeetCode 295 - Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/description/)
***
## Solution 1 : [Accepted on Neetcode, TLE on Leetcode(16th test case)]
```cpp
class MedianFinder {
    priority_queue<int> pq;

    double findMedianOdd() { // returns the kth largest element in the priority queue (k = queue size / 2)
        int k = pq.size() / 2;
        vector<int> removed_nums;
        while(k--) {
            int n = pq.top();
            removed_nums.push_back(n);
            pq.pop();
        }
        int median = pq.top();
        for(int i : removed_nums) {
            pq.push(i);
        }
        return median;
    }

    double findMedianEven() {
        int k = pq.size() / 2 - 1;
        vector<int> removed_nums;
        while(k--) {
            int n = pq.top();
            removed_nums.push_back(n);
            pq.pop();
        }
        int median1 = pq.top();
        pq.pop();
        removed_nums.push_back(median1);
        int median2 = pq.top();
        for(int i : removed_nums) {
            pq.push(i);
        }
        return 1.0 * (median1 + median2) / 2;
    }
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        pq.push(num);
    }
    
    double findMedian() {
        if(pq.size() % 2 == 0) 
            return findMedianEven();
        else 
            return findMedianOdd();
    }
};
```

### Idea: 
    Store the nums on a priority queue. 
    When finding the median, take the kth largest num from the queue if the size of the queue is odd. Otherwise take the (k-1)th and kth larget element and take their average.
    
### Time complexity: 
> For function `addNum`: O(log N)\
> For function `findMedian`: O(Nlog N)

### Space complexity: 
> For function `addNum`: O(1)\
> For function `findMedian`: O(N)

> here `N` is the number of elements currently stored in the priority queue.

## Solution 2: [Accepted on Neetcode, TLE on Leetcode(20th test case)]
```cpp
class MedianFinder {
    vector<int> nums;
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        int pos = 0;
        int size = nums.size();
        while(pos < size && nums[pos] <= num) {
            pos++;
        }
        nums.push_back(num);
        for(int i = size; i > pos; i--) {
            nums[i] = nums[i - 1];
        }
        nums[pos] = num;
    }
    
    double findMedian() {
        int mid = nums.size() / 2;
        if(nums.size() % 2 == 0) {
            int median1 = nums[mid - 1];
            int median2 = nums[mid];
            return 1.0 * (median1 + median2) / 2;
        }
        else {
            return nums[mid];
        }  
    }
};
```
### Idea:
    Each time a new number is added, insert it in its ideal position considering the vector `nums` is sorted.
    When finding median, just return the middle element (if size is odd), or return the average of middle two elements (if the size is even)

### Time complexity: 
> For function `addNum`: O(N)\
> For function `findMedian`: O(1)

### Space complexity: 
> For function `addNum`: O(1)\
> For function `findMedian`: O(1)

> here `N` is the number of elements currently stored in the priority queue.

## Solution 3: [Accepted]
```cpp
class MedianFinder {
    priority_queue<int> max_heap; // contains smaller half of the elements
    priority_queue<int, vector<int>, greater<int>> min_heap; // contains bigger half of the elements
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        int min_size = min_heap.size();
        int max_size = max_heap.size();

        if(min_size == 0 && max_size == 0) {
            min_heap.push(num);
            return;
        }

        // push to the appropriate half
        if(num >= min_heap.top()) {
            min_heap.push(num);
            min_size++;
        }
        else {
            max_heap.push(num);
            max_size++;
        }

        /*
            This portion ensures that the sizes of the two vectors differ by at most one.
        */
        if(min_size == max_size + 2) {
            max_heap.push(min_heap.top());
            min_heap.pop();
        } else if(max_size == min_size + 2) {
            min_heap.push(max_heap.top());
            max_heap.pop();
        }
    }
    
    double findMedian() {
        if(min_heap.size() == max_heap.size()) return 1.0 * (min_heap.top() + max_heap.top()) / 2;
        if(min_heap.size() > max_heap.size()) return min_heap.top();
        return max_heap.top();
    }
};
```

### Idea:
    Maintain two heaps. A `min_heap` that will contain the bigger half of the elements and a `max_heap` that will contain the smaller hald of the elements.
    Always make sure that the size of one heap is equal to the other or at most one larger than the other. 

### Time complexity: 
> For function `addNum`: O(log N)\
> For function `findMedian`: O(1)

### Space complexity: 
> For function `addNum`: O(1)\
> For function `findMedian`: O(1)

> here `N` is the number of elements currently stored in the priority queue.