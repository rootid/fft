//Valid Word Square
//Given a sequence of words, check whether it forms a valid word square.
//A sequence of words forms a valid word square if the kth row and column read the exact same string, where 0 ≤ k < max(numRows, numColumns).
//Note:
//The number of words given is at least 1 and does not exceed 500.
//Word length will be at least 1 and does not exceed 500.
//Each word contains only lowercase English alphabet a-z.
//Example 1:
//Input:
//[
//  "abcd",
//  "bnrt",
//  "crmy",
//  "dtye"
//]
//Output:
//true
//Explanation:
//The first row and first column both read "abcd".
//The second row and second column both read "bnrt".
//The third row and third column both read "crmy".
//The fourth row and fourth column both read "dtye".
//Therefore, it is a valid word square.
//Example 2:
//Input:
//[
//  "abcd",
//  "bnrt",
//  "crm",
//  "dt"
//]
//Output:
//true
//Explanation:
//The first row and first column both read "abcd".
//The second row and second column both read "bnrt".
//The third row and third column both read "crm".
//The fourth row and fourth column both read "dt".
//Therefore, it is a valid word square.
//Example 3:
//Input:
//[
//  "ball",
//  "area",
//  "read",
//  "lady"
//]
//Output:
//false
//Explanation:
//The third row reads "read" while the third column reads "lead".
//Therefore, it is NOT a valid word square.
//
//


//######################################### O(n^2) #########################################
//cnstrnt
//1. sme len? X
//2. mty? t/f
//Ida -> 1. 2d check if match is found true O(n^2)

//rs - "abcd", "bnrt" , "crm"
//clchar - "abcd", "bnrt", "c"
public boolean validWordSquare(List<String> words) {
    if(words == null || words.size() == 0) return false;
    int len = words.size();
    for(int i=0,col=0;i<len;i++,col++) {
        String rs = words.get(i);
        char[] clchar = new char[rs.length()];
        for(int j=0;j<rs.length();j++) {
            if(len <= j || col >= words.get(j).length()) return false;
            clchar[j] = words.get(j).charAt(col);
        }
        if(!new String(clchar).equals(rs)) return false;
    }
    return true;
}


//######################################### O(n^2) #########################################
//Too long, too short
public boolean validWordSquare(List<String> words) {
        if (words.size() == 0 || words == null) return true;
        int n = words.size();
        for (int i = 0; i < n; i++) {
            String tmp = words.get(i);
            for (int j = 0; j < tmp.length(); j++) {
                // too long
                if (j >= n)
                    return false;
                // too short
                if (words.get(j).length() <= i)
                    return false;
                // letter not equal
                if (tmp.charAt(j) != words.get(j).charAt(i))
                    return false;
            }
        }
        return true;
    }

//######################################### O(n^2) #########################################
bool validWordSquare(vector<string>& words) {
       for(int i = 0; i < words.size(); ++i) {  //"abcd"
         for(int j = 0; j < words[i].size(); ++j) {            {
             if(j >= words.size() || words[j].size() <= i || words[j][i] != words[i][j]) {
                return false;
             }
         }
     }
     return true;
 }


//######################################### O(n^2) #########################################
class Solution(object):
    def validWordSquare(self, words):
        for i in range(len(words)):
            for j in range(len(words[i])):
                if j >= len(words) or i >= len(words[j]) or words[i][j] != words[j][i]:
                    return False
        return True


//######################################### O(n^2) #########################################
def validWordSquare(self, words):
    return map(None, *words) == map(None, *map(None, *words))

//Or saving some work but taking two lines:

def validWordSquare(self, words):
    t = map(None, *words)
    return t == map(None, *t)

//Explanation:
//The map(None, ...) transposes the "matrix", filling missing spots with None. For example:
//
//["abc",           [('a', 'd', 'f'),
// "de",     =>      ('b', 'e', None),
// "f"]              ('c', None, None)]
//And then I just need to check whether transposing it once more changes it.

//######################################### O(n^2) #########################################
// map could be used for transposing matrix.
from itertools import izip_longest as izip

class Solution(object):
    def validWordSquare(self, words):
        return map("".join, izip(*words, fillvalue='')) == words
