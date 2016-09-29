// Ransom Note
//Given an arbitrary ransom note string and another string containing letters from all the magazines
//,write a function that will return true if the ransom note can be constructed 
//from the magazines ; otherwise, it will return false.  Each letter in the magazine string can only be used once in your ransom note. Note: You may assume that both strings contain only lowercase letters.
//canConstruct("a", "b") -> false
//canConstruct("aa", "ab") -> false
//canConstruct("aa", "aab") -> true

#include<iosteram>
using namespace std;

//BETTER
bool canConstruct(string ransomNote, string magazine) {
        vector<int> magazLetters(128, 0);
        for(char m : magazine)
            magazLetters[m]++;
        for(char r : ransomNote)
            if(--magazLetters[r]<0) return false;
        return true;
}

//BAD
bool canConstruct(string ransomNote, string magazine) {
      int l1 = ransomNote.size();
      int l2 = magazine.size();
      char ransom[26] = {0};
      char mag[26] = {0};
      for(int i=0;i<l1;i++) {
          ransom[ ransomNote[i] - 'a']++;
      }
      for(int i=0;i<l2;i++) {
         if(ransom [ magazine[i] - 'a'] == 0) {
             continue;
         }
         ransom [ magazine[i] - 'a']--;
      }
      for(int i=0;i<l1;i++) {
          if(ransom[ ransomNote[i] - 'a' ] > 0) {
              return false;
          }
      }
    return true;
}
