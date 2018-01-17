//Valid Number
//Validate if a given string is numeric.
//Some examples:
//"0" => true
//" 0.1 " => true
//"abc" => false
//"1 a" => false
//"2e10" => true
//Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one.
//Update (2015-02-10):
//The signature of the C++ function had been updated. If you still see your function signature accepts a const char * argument, please click the reload button  to reset your code definition.

//###################################### DFA : with flag  ###################################### 
bool isNumber(string str) { 
  int state=0, flag=0; // flag to judge the special case "."
  while(str[0]==' ')  str.erase(0,1);//delete the  prefix whitespace 
  while(str[str.length()-1]==' ') str.erase(str.length()-1, 1);//delete the suffix whitespace
  for(int i=0; i<str.length(); i++){
      if('0'<=str[i] && str[i]<='9'){
          flag=1;
          if(state<=2) state=2;
          else state=(state<=5)?5:7;
      }
      else if('+'==str[i] || '-'==str[i]){
          if(state==0 || state==3) state++;
          else return false;
      }
      else if('.'==str[i]){
          if(state<=2) state=6;
          else return false;
      }
      else if('e'==str[i]){
          if(flag&&(state==2 || state==6 || state==7)) state=3;
          else return false;
      }
      else return false;
  }
  return (state==2 || state==5 || (flag&&state==6) || state==7); 
}
//##################################### DFA : without flag skip state2-state6 ##################################### 
bool isNumber(string s) { 
  while(!s.empty() && s[0] == ' ') { 
    s.erase(s.begin()); 
  }
  while (!s.empty() && s[s.size()-1] == ' ') {
      s.erase(s.end()-1);
  }
  if(s.empty()) {
    return false;
  }
  int state = 0;
  for(int i=0; i<s.size(); i++) { 
    if(s[i] == '-' || s[i] == '+') { 
      if(state == 0 || state == 3) { 
        state ++; 
      } else { 
        return false; 
      } 
    } else if(s[i] == '.') { 
      if(state == 2) {   
          state = 7; //6
        }else if(state == 0|| state == 1) { 
          state = 6;
        }else{
          return false;
        }
    } else if(s[i] >= '0' && s[i] <= '9') {
        if(state == 1 || state == 4 || state == 6) {
            state++;
        } else if(state == 0 || state == 3) {
            state = state+2;
        }
    } else if(s[i] == 'e' || s[i] == 'E') {
        if(state == 2 ||  state == 7) { //6
            state = 3;
        } else {
            return false;
        }
    } else {
        return false;
    }
  }
  if(state == 2 || state == 7 || state == 5) {
    return true;
  }
  return false; 
}
//################################# NO DFA  ################################# 
bool isNumber(string s) { 
  int i = 0, n = s.length();
  // Skip the leading spaces
  while (i < n && isspace(s[i])) i++;
  // Skip the sign
  if (s[i] == '+' || s[i] == '-') i++;
  // Check for the following significant parts
  int digits = 0, dots = 0;
  while (i < n && (isdigit(s[i]) || s[i] == '.')) { 
      if (isdigit(s[i])) digits++;
      else dots++;
      i++;
  }
  if (digits < 1 || dots > 1) return false;
  if (i == n) return true;
  // Check for the exponential parts
  if (s[i] == 'e') {
      i++;
      if (i == n) return false;
      if (s[i] == '+' || s[i] == '-') i++;
      digits = 0;
      while (i < n && (isdigit(s[i]))) {
          digits++;
          i++;
      }
      if (digits < 1) return false;
  }
  // Skip the trailing spaces
  while (i < n && isspace(s[i])) i++;
  return i == n; 
}
