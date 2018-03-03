//Palindrome Permutation
//Given a string, determine if a permutation of the string could form a
//palindrome.
//For example,
//"code" -> False, "aab" -> True, "carerac" -> True.
//Hint:
//Consider the palindromes of odd vs even length. What difference do you
//notice?
//Count the frequency of each character.
//If each character occurs even number of times, then it must be a palindrome.
//How about character which occurs odd number of times?
//

//######################################### Compute the frequency of each character #########################################
boolean canPermutePalindrome(String s) {
	Set<Character> oddCharSet;
	for(int i=0;i<s.length();i++) {
		if(oddCharSet.contains(s.charAt(i))) oddCharSet.remove(s.charAt(i));
		else oddCharSet.add(s.charAt(i));
	}
	return oddCharSet.size() == 0 || (s.length()%2 == 1 && oddCharSet.size() == 1);
}

//######################################### Compute the frequency of each character #########################################
bool canPermutePalindrome(string s) {
   bitset <256> bs;
   for(char c:s) {
       bs.flip(c);
   }
   return bs.count() < 2;
}

//######################################### Compute the frequency of each character #########################################
bool canPermutePalindrome(string s) {
    unordered_map<char, int> m;
    int oddCharCnt = 0;
    for (auto a : s) ++m[a];
    for (auto it = m.begin(); it != m.end(); ++it) {
        if (it->second % 2) ++oddCharCnt;
    }
    return oddCharCnt == 0 || (s.size() % 2 == 1 && oddCharCnt == 1);
}

