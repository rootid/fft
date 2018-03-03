//Moving Average from Data Stream
//Given a stream of integers and a window size, calculate the moving average of
//all integers in the sliding window.
//For example,
//MovingAverage m = new MovingAverage(3);
//m.next(1) = 1
//m.next(10) = (1 + 10) / 2
//m.next(3) = (1 + 10 + 3) / 3
//m.next(5) = (10 + 3 + 5) / 3

#include "../headers/global.hpp"

class MovingAverage {

private :
    queue<int> q;
    const int avg_size;
    double sum;
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) : avg_size(size),sum(0) {

    }

    double next(int val) {
        int sz = q.size();
        sum += val;
        if(sz == avg_size) {
            sum -= q.front();
            q.pop();
        } else {
            sz += 1;
        }
        q.push(val);
        return sum/sz;
    }
};
/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage obj = new MovingAverage(size);
 * double param_1 = obj.next(val);
 */
