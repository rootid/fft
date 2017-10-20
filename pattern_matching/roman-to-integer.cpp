//Roman to Integer 

//Given a roman numeral, convert it to an integer.
//Input is guaranteed to be within the range from 1 to 3999.


#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
#include<limits.h>
#include<stdlib.h>

using namespace std;

//######################################### Recursion ######################################### 
class Solution {
    public int romanToInt(String s) {
        final Map<Character, Integer> rMap = new HashMap<>();
        rMap.put('I', 1);
        rMap.put('V', 5);
        rMap.put('L', 50);
        rMap.put('X', 10);
        rMap.put('C', 100);
        rMap.put('D', 500);
        rMap.put('M', 1000);
        char [] arr  = s.toCharArray();
		return romanToIntHelper(arr, arr.length - 1, rMap);
    }

    public int romanToIntHelper(char[] arr, int k, Map<Character,Integer> rMap) {
		int sum = 0;
		if(k < 0) return sum;
        if( k+1 < arr.length && rMap.get(arr[k]) < rMap.get(arr[k+1]) ) sum -=  rMap.get(arr[k]); //IV
		else sum += rMap.get(arr[k]);
		sum += romanToIntHelper(arr,k - 1, rMap);
        return sum;
	}
}

//######################################### Iteration  ######################################### 
public int romanToInt(String s) {
    final Map<Character, Integer> rMap = new HashMap<>();
    rMap.put('I', 1);
    rMap.put('V', 5);
    rMap.put('L', 50);
    rMap.put('X', 10);
    rMap.put('C', 100);
    rMap.put('D', 500);
    rMap.put('M', 1000);
    char [] str = s.toCharArray();
    int sum = rMap.get(str[str.length - 1]);
    for(int i=str.length - 2;i>=0;i--) {
        if(rMap.get(str[i]) < rMap.get(str[i+1]) ) sum -= rMap.get(str[i]); //IV
        else sum += rMap.get(str[i]);
    }
   return sum;
}


//######################################### Iteration  ######################################### 
int romanToInt(string s) {

  int len = s.length();
  if(len == 0) {
    return len;
  }
  unordered_map<char,int> rMap = { {'I',1}
                                   ,{'V',5} 
                                   ,{'X',10} 
                                   ,{'L',50} 
                                   ,{'C',100} 
                                   ,{'D',500}
                                   ,{'M',1000} };
  int sum = 0;
  sum = rMap[ s[len-1] ];
  for(int i=len-2;i>=0;i--)  {
    if(rMap[ s[i] ] >= rMap[ s[i+1] ]) { //DCXXI
      sum += rMap[ s[i] ];
    } else {
      sum -= rMap[ s[i] ];
    }
  }
  return sum;
}

int main() {

  //int result = romanToInt("IX");
  int result = romanToInt("XI");
  cout << "R = " << result << endl;
}
