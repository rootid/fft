//Design Phone Directory
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
    //int* reclaimed;
    int* available;
    vector<int> reclaimed;
public:
    /** Initialize your data structure here
        @param maxNumbers - The maximum numbers that can be stored in the phone directory. */
    PhoneDirectory(int maxNumbers) {
        //reclaimed = new int[maxNumbers];
        available = new int[maxNumbers];
        unused = maxNumbers - 1;
        for(int i=0;i<maxNumbers;i++) {
            available[i] = 0;
            reclaimed.push_back(maxNumbers-1-i);
        }
    }
    
    /** Provide a number which is not assigned to anyone.
        @return - Return an available number. Return -1 if none is available. */
    int get() {
        if(reclaimed.size() == 0) {
            return -1;
        }
        int no_ = reclaimed.back();
        reclaimed.erase(reclaimed.end() - 1);
        available[no_] = -1;
        return no_;
    }
    
    /** Check if a number is available or not. */
    bool check(int number) {
         if(available[number] == -1) {
            return false;
        }
        return true;
    }
    
    /** Recycle or release a number. */
    void release(int number) {
        if(check(number)) {
            return;
        }
        available[number] = 0;
        reclaimed.push_back(number);
    }
    ~PhoneDirectory() {
        delete[] available;
    }
};
/**
 * Your PhoneDirectory object will be instantiated and called as such:
 * PhoneDirectory obj = new PhoneDirectory(maxNumbers);
 * int param_1 = obj.get();
 * bool param_2 = obj.check(number);
 * obj.release(number);
 */


class PhoneDirectory {
public:
    PhoneDirectory(int maxNumbers) {
        n = maxNumbers;
        available = new int[n];
        isAvailable = new bool[n];
        for (int i=0; i<n; i++) {
            available[i] = i;
            isAvailable[i] = true;
        }
    }
    
    ~PhoneDirectory() {
        delete[] available;
        delete[] isAvailable;
    }

    int get() {
        if (!n)
            return -1;
        int number = available[--n];
        isAvailable[number] = false;
        return number;
    }
    
    bool check(int number) {
        return isAvailable[number];
    }
    
    void release(int number) {
        if (!isAvailable[number]) {
            isAvailable[number] = true;
            available[n++] = number;
        }
    }
private:
    int n;
    int *available;
    bool *isAvailable;
};

//########################################### With Set  ########################################### 
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
