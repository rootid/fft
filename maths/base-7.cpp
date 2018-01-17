//Base 7
//Given an integer, return its base 7 string representation.
//Example 1:
//Input: 100
//Output: "202"
//Example 2:
//Input: -7
//Output: "-10"
//Note: The input will be in range of [-1e7, 1e7].
//###################### Iterative  ################## 
string convertToBase7(int num) {
    if(num == 0) {
        return "0";
    }
    string str ="";
    if(num < 0) {
        return "-" + convertToBase7(-num);
    }
    while( num > 0) {
        int rem = num % 7;
        num = num/7;
        str = to_string(rem) + str;
    }
    
    return str;
}

//###################### Recursion ################## 
string convertToBase7(int num) {
  if (num < 0) {
    return '-' + convertTo7(-num); 
  } 
  if (num < 7) {
    return num + ""; 
  }
  return convertTo7(num / 7) + num % 7;
}

