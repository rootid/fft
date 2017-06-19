//Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
//push(x) -- Push element x onto stack.
//pop() -- Removes the element on top of the stack.
//top() -- Get the top element.
//getMin() -- Retrieve the minimum element in the stack.
//Example:
//MinStack minStack = new MinStack();
//minStack.push(-2);
//minStack.push(0);
//minStack.push(-3);
//minStack.getMin();   --> Returns -3.
//minStack.pop();
//minStack.top();      --> Returns 0.
//minStack.getMin();   --> Returns -2.

#include "../headers/global.hpp"

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
    }
    void push(int x) {
        this->data_stack.push(x);
        if(this->min_stack.empty() || this->min_stack.top() >= x) {
            this->min_stack.push(x);
        }
    }
    
    void pop() {
        if(!this->data_stack.empty()) {
            int tmp = this->top();
            if(tmp == this->min_stack.top()) {
                this->min_stack.pop();
            }
            this->data_stack.pop();
        }
    }
    
    int top() {
        return this->data_stack.top();
    }
    
    int getMin() {
         return this->min_stack.top();
    }
    
private :
    stack<int> min_stack;
    stack<int> data_stack;
};
/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
