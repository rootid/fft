//Text Justification
//Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.
//You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly L characters.
//Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.
//For the last line of text, it should be left justified and no extra space is inserted between words.
//For example,
//words: ["This", "is", "an", "example", "of", "text", "justification."]
//L: 16.
//Return the formatted lines as:
//[
//   "This    is    an",
//   "example  of text",
//   "justification.  "
//]
//Note: Each word is guaranteed not to exceed L in length.
//click to show corner cases.
//Corner Cases:
//A line other than the last line might contain only one word. What should you do in this case?
//In this case, that line should be left-justified.
//#############################################################################################
//(L-l) % (k-1) : Normal space
//(j < (L - l) % (k - 1)) : Extra space
vector<string> fullJustify(vector<string>& words, int L) {
   vector<string> res;
   //k : # of words
   for(int i = 0, k, l; i < words.size(); i += k) {
       //adjust words
       for(k = l = 0; i + k < words.size() and l + words[i+k].size() <= L - k; k++) {
           l += words[i+k].size(); //# of chars in the word 
       }
       string tmp = words[i]; //take the first word
       //adjust spaces + skip the last word 
       for(int j = 0; j < k - 1; j++) {
           if(i + k >= words.size()) {
             tmp += " ";
           } else tmp += string((L - l) / (k - 1) + (j < (L - l) % (k - 1)), ' ');
           tmp += words[i+j+1];
       }
       tmp += string(L - tmp.size(), ' ');
       res.push_back(tmp);
   }
   return res;
}
//################################################################################################ 
//   0   1  2    3
// "This is an example..."
//  i=0, j=3, width=8, space=(16-8)/(3-0-1)=4, extra=0
// ------------------------------------------------------
//   3      4   5        6
// "example of text justification."
//  i=3, j=6, width=13, space=(16-13)/(3-0-1)=1, extra=1
// ------------------------------------------------------
// "justification."
//  i=6, j=7, space=1, extra=0
vector<string> fullJustify(vector<string>& words, int L) { 
  vector<string> result;
  //i : LHS of line 
  //j : RHS of line 
  for(int i = 0, j; i < words.size(); i = j) {
      int width = 0;
      for(j = i; j < words.size() && width + words[j].size() + j - i <= L; j++) { //j-i : relative size of current line
          width += words[j].size();
      }
      int space = 1, extra = 0;
      if(j - i != 1 && j != words.size()) {
          space = (L - width) / (j - i - 1);
          extra = (L - width) % (j - i - 1);
      }
      string line(words[i]);
      for(int k = i + 1; k < j; k++) {
          line += string(space, ' ');
          if(extra-- > 0) {
              line += " ";
          }
          line += words[k];
      }
      
      line += string(L - line.size(), ' ');
      result.push_back(line);
  }
  return result; 
}
//################################################################################################ 
//len update change 
//len = len -1
vector<string> fullJustify(vector<string> words, int L) { 
  vector<string> res;
  for (int i = 0, k; i < words.size(); i = k) {
      // i: the index of word 
      // k: the current index of words in the line
      // len: current total len of words in the line
      int len = -1;
      for (k = i; k < words.size() && len + words[k].size() + 1 <= L; k++) {
          len += words[k].size() + 1;
      }
      string curStr(words[i]);
      int space = 1, extra = 0;
      // not 1 char, not last line
      if (k != i + 1 && k != words.size()) {
          space = (L - len) / (k - i - 1) + 1; // 1 is for another space
          extra = (L - len) % (k - i - 1);
      }
      // not 1 char, including last line, initialize space == 1 is to deal with last line case.
      for (int j = i + 1; j < k; j++) { // j: index of word in the current line
          for (int s = space; s > 0; s--) curStr+=" "; // add the "even" space
          if (extra-- > 0) curStr+=" ";
          curStr+=words[j];
      }
      // if it's the last line
      int strLen = L - curStr.size();
      while (strLen-- > 0) curStr+=" ";
      res.push_back(curStr);
  }
  return res; 
}
