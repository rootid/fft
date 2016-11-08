#include "../headers/global.hpp"
int numDecodings(string s) {
      
   int len = s.size();
  vector<int> opt_dec(len+1,0);
 if(s.empty() || s[0]<'1' || s[0]>'9') return 0;
  opt_dec[0] = 1;
  opt_dec[1] = 1;
  
  for(int i=1;i<len;i++) {
      // <= 26 , >=10
      int v = (s[i-1]-'0')*10 + (s[i]-'0');
      //if( (s[i-1] <= '2' && s[i] <= '6') && (s[i-1] >= '1' && s[i] >= '0') ) { // '10' , '101' , "100"
      if(v <=26 && v>=10) {
        opt_dec[i+1] += opt_dec[i-1];
      } 
      if(s[i] != '0') {  // 110
        opt_dec[i+1] += opt_dec[i];
      }
      if(opt_dec[i+1] == 0) {
        return 0;
      }
      //cout << "i = " << i <<  "| opt_dec[i] " << opt_dec[i]  << endl;
  }
  return opt_dec[len];
}

int main() {
  numDecodings("1");
  numDecodings("12");
  numDecodings("27"); //1
  numDecodings("26"); //2
  numDecodings("262"); //2 (2 6 2) (26 2) 
  numDecodings("100"); // 1
  numDecodings("10"); //0 
}
