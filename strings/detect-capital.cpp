//Given a word, you need to judge whether the usage of capitals in it is right
//or not.
//We define the usage of capitals in a word to be right when one of the
//following cases holds:
//All letters in this word are capitals, like "USA".
//All letters in this word are not capitals, like "leetcode".
//Only the first letter in this word is capital if it has more than one letter,
//like "Google".
//Otherwise, we define that this word doesn't use capitals in a right way.
//Example 1:
//Input: "USA"
//Output: True
//Example 2:
//Input: "FlaG"
//Output: False
//Note: The input will be a non-empty word consisting of uppercase and
//lowercase latin letters.
//
#include "../headers/global.hpp"


//######################################### Regex  #########################################
public boolean detectCapitalUse(String word) {
    if(word.matches("[A-Z][a-z]+") || word.matches("[A-Z]+") || word.matches("[a-z]+")) return true;
    return false;
}


//######################################### Compact regex #########################################
public boolean detectCapitalUse(String word) {
    return word.matches("[A-Z]+|[a-z]+|[A-Z][a-z]+");
}

//######################################### Primitive #########################################
//def detectCapitalUse(self, word):
//    return word.isupper() or word.islower() or word.istitle()

bool isCapital(char c) {
  return ( 'A' <= c && c <= 'Z');
}


bool detectCapitalUse(string word) {
  int numCaps = 0;
  for (auto &c : word) {
    if (isCapital(c)) {
      numCaps++;
    }
  }
  return ( numCaps == word.size() || ( numCaps == 1 && isCapital(word[0]) ) || numCaps==0 );
}

int main() {
  //string t = "FlaG";
  string t = "USA";
  detectCapitalUse(t);
}
