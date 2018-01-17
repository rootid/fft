// Count and Say
//The count-and-say sequence is the sequence of integers beginning as follows:
//1, 11, 21, 1211, 111221, ...
//1 is read off as "one 1" or 11.
//11 is read off as "two 1s" or 21.
//21 is read off as "one 2, then one 1" or 1211.
//Given an integer n, generate the nth sequence.
//Note: The sequence of integers will be represented as a string.


//######################################### Iterative ######################################### 
public String countAndSay(int n) {
    String say = "1";
    if(n == 1) return "1";
    StringBuilder countAndSay = new StringBuilder();
    countAndSay.append("1");
    for(int i=1;i<n;i++) {
        int count = 1;
        StringBuilder tmp = new StringBuilder();
        countAndSay.append('X');
        int len = countAndSay.length();
        for(int j=0;j<len-1;j++) {
            while(j < len- 1 && countAndSay.charAt(j) == countAndSay.charAt(j+1)) {
                count++;
                j++;
            }
            tmp.append(String.valueOf(count) + countAndSay.charAt(j));
            count = 1;
        }
		countAndSay = tmp;
    } 
   return countAndSay.toString();
}


//######################################### Iterative ######################################### 
string countAndSay(int n) {
  if(n == 0) {
    return "";
  }
  string c = "10";  // any seq starts with d always ends with d eg. d,1d,111d,...
                    //reason to add suffix 0 line # 12
     string tmp = "";
     for(int i=1;i<n;i++) {
         int cnt = 1;
         for(int j=1;j<c.size();j++) {
             if(c[j-1] == c[j]) {
                 cnt++;
             } else {
                 tmp += to_string(cnt) + c[j-1]; //don't want to check the same condition outside the 
                                                 //loop so updated string by adding suffix 0
                 cnt = 1;
             }
         }
         c = tmp;
         tmp = "";
         c += "0";
     }
     return c.substr(0,c.size() - 1);
}

int main() {

}
