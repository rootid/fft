//Palindrome Permutation II
//Given a string s, return all the palindromic permutations (without duplicates) of it. Return an empty list if no palindromic permutation could be form.
//For example:
//Given s = "aabb", return ["abba", "baab"].
//Given s = "abc", return [].

//######################################### Backracking , T = O(n/2+1)! ######################################### 
//
//we just need to get one half of the string (each character appea//rs half the times in s), then generate all its unique permutations and concatenate them with the reversed half (possibly the single middle character if the length of the string s is odd).

//All the above work will only be done if an palindrome permutation exists. To tell whether a palindrome permutation exists, Palindrome Permutation has paved the way for us. To generate all the unique permutations, you may as well refer to Permutations II or Next Permutation as suggested by the second hint. But I guess this part is not the main point of this problem, so I directly use the next_permutation of C++. Well, I am not quite whether this is the right way, but this gives shorter codes. Moreover, the tag of this problem is backtracking, which I guess only needs to be used in generating the permutations. After this is done, we can simply concatenate to make the palindromes.
class Solution {
public:
    vector<string> generatePalindromes(string s) {
		vector<string> palindromes;
        unordered_map<char, int> counts;
        for (char c : s) counts[c]++;
        int odd = 0; char mid; string half;
        for (auto p : counts) {
            if (p.second & 1) {
                odd++, mid = p.first;
				if (odd > 1) return palindromes;
            }
            half += string(p.second / 2, p.first);
        }
        palindromes = permutations(half);
        for (string& p : palindromes) {
            string t(p);
            reverse(t.begin(), t.end());
			if (odd) t = mid + t;
            p += t;
        }
        return palindromes;
    }
private: 
    vector<string> permutations(string& s) {
        vector<string> perms;
        string t(s);
        do {
            perms.push_back(s);
            next_permutation(s.begin(), s.end()); 
        } while (s != t);
        return perms; 
    }
};


//######################################### Backracking , T = O(n/2+1)! ######################################### 
private List<String> list = new ArrayList<>();

public List<String> generatePalindromes(String s) {
    int numOdds = 0; // How many characters that have odd number of count
    int[] map = new int[256]; // Map from character to its frequency
    for (char c: s.toCharArray()) {
        map[c]++;
        numOdds = (map[c] & 1) == 1 ? numOdds+1 : numOdds-1;
    }
    if (numOdds > 1)   return list;
    
    String mid = "";
    int length = 0;
    for (int i = 0; i < 256; i++) {
        if (map[i] > 0) {
            if ((map[i] & 1) == 1) { // Char with odd count will be in the middle
                mid = "" + (char)i;
                map[i]--;
            }
            map[i] /= 2; // Cut in half since we only generate half string
            length += map[i]; // The length of half string
        }
    }
    generatePalindromesHelper(map, length, "", mid);
    return list;
}
private void generatePalindromesHelper(int[] map, int length, String s, String mid) {
    if (s.length() == length) {
        StringBuilder reverse = new StringBuilder(s).reverse(); // Second half
        list.add(s + mid + reverse);
        return;
    }
    for (int i = 0; i < 256; i++) { // backtracking just like permutation
        if (map[i] > 0) {
            map[i]--;
            generatePalindromesHelper(map, length, s + (char)i, mid);
            map[i]++;
        } 
    }
}
