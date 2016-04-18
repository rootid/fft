//Valid Palindrome
//Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
//For example,
//"A man, a plan, a canal: Panama" is a palindrome.
//"race a car" is not a palindrome.
//Note:
//Have you consider that the string might be empty? This is a good question to ask during an interview.
//For the purpose of this problem, we define empty string as valid palindrome
//
//

#include<iostream>
#include<string>
#include<ctype.h>

using namespace std;

bool isPalindrome(string s) {
   int i = 0, j = s.size() - 1;
   while(i < j)
   {
       while(i < j && !isalnum(s[i])) i++;
       while(i < j && !isalnum(s[j])) j--;
       if (toupper(s[i])!=toupper(s[j]))
           return false;
       i++;j--;
   }
   return true;
}


int main() {

  string s = "A man, a plan, a canal: Panama";
  //string s = "race a car";
  bool r = isPalindrome(s);
  if(r == true) {
    cout << s << " is palindorme " << endl;
  } else {
    cout << s << " is not palindorme " << endl;
  }

}
