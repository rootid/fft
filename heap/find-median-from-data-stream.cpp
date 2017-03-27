//Find Median from Data Stream
//Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.
//Examples: 
//[2,3,4] , the median is 3
//[2,3], the median is (2 + 3) / 2 = 2.5
//Design a data structure that supports the following two operations:
//void addNum(int num) - Add a integer number from the data stream to the data structure.
//double findMedian() - Return the median of all elements so far.
//For example:
//addNum(1)
//addNum(2)
//findMedian() -> 1.5
//addNum(3) 
//findMedian() -> 2

class MedianFinder {
   priority_queue<long> small, large;
public:
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    void addNum(int num) { 
      small.push(num); //2
      large.push(-small.top()); //-2
      small.pop();
      if (small.size() < large.size()) {
          small.push(-large.top());
          large.pop();
      }
    }
    
    double findMedian() { 
      return small.size() > large.size() 
        ? small.top() 
        : (small.top() - large.top()) / 2.0;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder obj = new MedianFinder();
 * obj.addNum(num);
 * double param_2 = obj.findMedian();
 */

