//Given an input string, reverse the string word by word.
//For example,
//Given s = "the sky is blue",
//return "blue is sky the".
//
//Update (2015-02-12):
//For C programmers: Try to solve it in-place in O(1) space.
//click to show clarification.
//Clarification:
//What constitutes a word?
//A sequence of non-space characters constitutes a word.
//Could the input string contain leading or trailing spaces?
//Yes. However, your reversed string should not contain leading or trailing
//spaces.
//How about multiple spaces between two words?
//Reduce them to a single space in the reversed string.


void reverseWords(string &s) {
     string rs = "";
     for(int i=s.size() - 1;i>=0;) {
        while( i>= 0 && s[i] == ' ') {
            i--;
        }
        if(i < 0) {  ///" 1" op: "1"
            break;
        }
        string tmp = "";
        if (!rs.empty())  {
             rs.push_back(' ');
         }
        while( i >= 0 && s[i] != ' ') {
            tmp.push_back(s[i]);
            i--;
        }

        reverse(tmp.begin(),tmp.end());
        //rs += tmp;
        rs.append(tmp);

     }
  s= rs;
 }

int main() {
}
