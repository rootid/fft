//Valid Perfect Square
//Given a positive integer num, write a function which returns True if num is a perfect square else False.
//Note: Do not use any built-in library function such as sqrt.
//Example 1:
//Input: 16
//Returns: True
//Example 2:
//Input: 14
//Returns: False

//################################### Good ################################### 
bool isPerfectSquare(int num) {
    int start = 0, end = num;
    while(start <= end) {
      lolong mid = start + (end - start) / 2;
        if(mid * mid < num)
            start = mid + 1;
        else if(mid * mid > num)
            end = mid - 1;
        else
            return true;
    }
    
    return false;
}

//################################### Good ################################### 
bool isPerfectSquare(int num) {
  int start = 1;
  int end = num - 1;
  if(num == 1) {
      return true;
  }
  while(start <= end) {
    long mid = start + (end - start)/2;
    if(mid * mid == num) {
      return true;
    }
    if(mid*mid < num) {
      start = mid + 1;
    } else {
      end = mid - 1;
    }
  }
  return false;
}
