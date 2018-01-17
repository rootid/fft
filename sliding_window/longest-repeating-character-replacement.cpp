//Longest Repeating Character Replacement
//Given a string that consists of only uppercase English letters, you can replace any letter in the string with another letter at most k times. Find the length of a longest substring containing all repeating letters you can get after performing the above operations.
//Note:
//Both the string's length and k will not exceed 104.
//Example 1:
//Input:
//s = "ABAB", k = 2
//Output:
//4
//Explanation:
//Replace the two 'A's with two 'B's or vice versa.
//Example 2:
//Input:
//s = "AABABBA", k = 1
//Output:
//4
//Explanation:
//Replace the one 'A' in the middle with 'B' and form "AABBBBA".
//The substring "BBBB" has the longest repeating letters, which is 4.

int characterReplacement(string s, int k) {
    
}



//The problem is similar to longest substring with most K distinct characte. But this time, the constraint is we can only have most K characters that is different with the most frequent character in the substring. For example in the sliding window:
//
//"ABBBAC" most frequent character is B with count 3, all other character is count as different to B, 
//    which is A and C, and the result is 2 + 1 = 3. 
//Each time we count the different characters. If it is not bigger than k we extend the sliding window.
//Since we only have 26 characters, keep the count in a integer array is good enough.
//####################
int characterReplacement(string str, int k) {
    if(str.size() == 0){
        return 0;
    }
    int maxLen = 0;
    vector<int>ch(26,0);
    for(int i=0, j=0; i<str.length(); i++) {
        while(j < str.length()){
            ch[str[j] - 'A']++;
            if(count(ch) > k){  //If exceed k, break
                ch[str[j] - 'A']--;
                break;
            }
            j++;
        }
        maxLen = max(maxLen , j-i);
        ch[str[i] - 'A']--;
    }
    return maxLen;
}
//Count the number of character that is different to the longest character
int count(vector<int>& ch) {
     int maxLen = 0;
     int sum = 0;
     for(auto val:ch){
         sum += val;
         maxLen = max(maxLen, val);
     }
     return sum - maxLen;
}
