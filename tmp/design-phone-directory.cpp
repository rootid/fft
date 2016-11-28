//Design a Phone Directory which supports the following operations:
//get: Provide a number which is not assigned to anyone.
//check: Check if a number is available or not.
//release: Recycle or release a number.
//Example:
//// Init a phone directory containing a total of 3 numbers: 0, 1, and 2.
//PhoneDirectory directory = new PhoneDirectory(3);
//// It can return any available phone number. Here we assume it returns 0.
//directory.get();
//// Assume it returns 1.
//directory.get();
//// The number 2 is available, so return true.
//directory.check(2);
//// It returns 2, the only number that is left.
//directory.get();
//// The number 2 is no longer available, so return false.
//directory.check(2);
//// Release number 2 back to the pool.
//directory.release(2);
//// Number 2 is available again, return true.
//directory.check(2);

class PhoneDirectory {
    
private :
    vector<int> numbers;
    unordered_set<int> dir_set;
public:
    /** Initialize your data structure here
        @param maxNumbers - The maximum numbers that can be stored in the phone directory. */
    PhoneDirectory(int maxNumbers) {
        int i = maxNumbers;
        while(i-- > 0) {
           // cout << i << endl;
            numbers.push_back(i);
            dir_set.insert(i);
        }
    }
    
    /** Provide a number which is not assigned to anyone.
        @return - Return an available number. Return -1 if none is available. */
    int get() {
        if(numbers.size() == 0) {
            return -1;
        }
        int no_ = numbers.back();
        dir_set.erase(no_);
        numbers.pop_back();
        return no_;
    }
    
    /** Check if a number is available or not. */
    bool check(int number) {
        return dir_set.find(number) != dir_set.end();
    }
    
    /** Recycle or release a number. */
    void release(int number) {
        if(check(number)) {
            return;
        }
        dir_set.insert(number);
        numbers.push_back(number);
    }
};
/**
 * Your PhoneDirectory object will be instantiated and called as such:
 * PhoneDirectory obj = new PhoneDirectory(maxNumbers);
 * int param_1 = obj.get();
 * bool param_2 = obj.check(number);
 * obj.release(number);
 */
