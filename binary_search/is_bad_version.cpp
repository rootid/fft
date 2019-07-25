//You are a product manager and currently leading a team to develop a new
//product. Unfortunately, the latest version of your product fails the quality
//check. Since each version is developed based on the previous version, all the
//versions after a bad version are also bad.
//Suppose you have n versions [1, 2, ..., n] and you want to find out the first
//bad one, which causes all the following ones to be bad.
//You are given an API bool isBadVersion(version) which will return whether
//version is bad. Implement a function to find the first bad version. You
//should minimize the number of calls to the API.
//Credits:
// Forward declaration of isBadVersion API.

//######################################### Binary Search (start,end] #########################################
public int firstBadVersion(int n) {
    int start = 0;
    int end = n;
    int mid = 0;
    while(start < end) {
        mid = start + (end - start)/2;
        //if(isBadVersion(mid) == true && isBadVersion(mid-1) == false) return mid;  << not required
        if(isBadVersion(mid) == true)
            end = mid;
        else start = mid+1;
    }
    return start;
}


//######################################### Binary Search #########################################
bool isBadVersion(int version);
class Solution {
public:
    int firstBadVersion(int n) {

        int left = 0;
        int right = n;
        while(right-left > 1) {
            int mid = left + (right - left)/2;
            if(isBadVersion(mid) == false) {
                left = mid;
            } else {
                right = mid ;
            }
        }
        return right;
    }
};


//Overflow happens because sums greater than 2^31-1 but less than 2^32-1 will
//be negative. For example, if you added 1 to 2^31-1, you'd get int32.minvalue,
//or -2^31. Lets use a smaller example, say an 8bit number, the max signed
//value you can store is 01111111, which is 127. If you add one, what do you
//expect to get as a result? It should be 10000000, which is -128. Due to this
//overflow, your code will likely infinitely loop.
//
//In C# there's a compiler flag (checked) that will throw an exception for
//overflow/underflow, but the default behavior is the same as java/c++ with
//"wrapping" or modulo 2^bitcount of your number type.
//
//In case that didn't make sense or you want to learn more, refer to this
//article to learn more about exactly what number your sum is becoming:
//http://www.cplusplus.com/articles/DE18T05o/
