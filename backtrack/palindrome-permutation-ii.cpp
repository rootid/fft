//Palindrome Permutation II
//Given a string s, return all the palindromic permutations (without
//duplicates) of it. Return an empty list if no palindromic permutation could
//be form.
//For example:
//Given s = "aabb", return ["abba", "baab"].
//Given s = "abc", return [].

//######################################### Brute Force  #########################################
//Time complexity : O((n+1)!). A total of n!n!n! permutations are possible. For
//every permutation generated, we need to check if it is a palindrome, each of
//which requires O(n)O(n)O(n) time.
//Space complexity : O(n). The depth of the recursion tree can go upto nnn.
public class Solution {
    Set < String > set = new HashSet < > ();
    public List < String > generatePalindromes(String s) {
        permute(s.toCharArray(), 0);
        return new ArrayList < String > (set);
    }
    public boolean isPalindrome(char[] s) {
        for (int i = 0; i < s.length; i++) {
            if (s[i] != s[s.length - 1 - i])
                return false;
        }
        return true;
    }
    public void swap(char[] s, int i, int j) {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
    void permute(char[] s, int l) {
        if (l == s.length) {
            if (isPalindrome(s))
                set.add(new String(s));
        } else {
            for (int i = l; i < s.length; i++) {
                swap(s, l, i);
                permute(s, l + 1);
                swap(s, l, i);
            }
        }
    }
}

//######################################### Backtracking #########################################
//Time complexity : O((n2+1)!). Atmost
//n2!\frac{n}{2}!​2​​n​​! permutations need to be
//generated in the worst case. Further, for each permutation generated,
//string.reverse() function will take n/4n/4n/4 time.
//Space complexity : O(n). The depth of recursion tree can go upto n/2n/2n/2 in
//the worst case.
public class Solution {
    Set < String > set = new HashSet < > ();
    public List < String > generatePalindromes(String s) {
        int[] map = new int[128];
        char[] st = new char[s.length() / 2];
        if (!canPermutePalindrome(s, map))
            return new ArrayList < > ();
        char ch = 0;
        int k = 0;
        for (int i = 0; i < map.length; i++) {
            if (map[i] % 2 == 1)
                ch = (char) i;
            for (int j = 0; j < map[i] / 2; j++) {
                st[k++] = (char) i;
            }
        }
        permute(st, 0, ch);
        return new ArrayList < String > (set);
    }
    public boolean canPermutePalindrome(String s, int[] map) {
        int count = 0;
        for (int i = 0; i < s.length(); i++) {
            map[s.charAt(i)]++;
            if (map[s.charAt(i)] % 2 == 0)
                count--;
            else
                count++;
        }
        return count <= 1;
    }
    public void swap(char[] s, int i, int j) {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
    void permute(char[] s, int l, char ch) {
        if (l == s.length) {
            set.add(new String(s) + (ch == 0 ? "" : ch) + new StringBuffer(new String(s)).reverse());
        } else {
            for (int i = l; i < s.length; i++) {
                if (s[l] != s[i] || l == i) {
                    swap(s, l, i);
                    permute(s, l + 1, ch);
                    swap(s, l, i);
                }
            }
        }
    }
}


//######################################### Backracking , T = O(n/2+1)! #########################################
private List<String> list = new ArrayList<>();

public List<String> generatePalindromes(String s) {

    int numOdds = 0; // How many characters that have odd number of count
    int[] freqCounter = new int[256]; // Map from character to its frequency
    for (char c: s.toCharArray()) {
        freqCounter[c]++;
        numOdds = (freqCounter[c] & 1) == 1 ? numOdds+1 : numOdds-1; //checks valid palindrome
    }
    if (numOdds > 1)   return list;

    String mid = "";
    int length = 0;
    for (int i = 0; i < 256; i++) {
        if (freqCounter[i] > 0) {
            if ((freqCounter[i] & 1) == 1) { // Char with odd count will be in the middle
                mid = "" + (char)i;
                freqCounter[i]--;
            }
            freqCounter[i] /= 2; // Cut in half since we only generate half string
            length += freqCounter[i]; // The length of half string
        }
    }
    generatePalindromesHelper(freqCounter, length, "", mid);
    return list;
}
private void generatePalindromesHelper(int[] freqCounter, int length, String s, String mid) {
    if (s.length() == length) {
        StringBuilder reverse = new StringBuilder(s).reverse(); // Second half
        list.add(s + mid + reverse);
        return;
    }
    for (int i = 0; i < 256; i++) { // backtracking just like permutation
        if (freqCounter[i] > 0) {
            freqCounter[i]--;
            generatePalindromesHelper(freqCounter, length, s + (char)i, mid); //pick the start char
            freqCounter[i]++;
        }
    }
}

//######################################### Backracking , T = O(n/2+1)! #########################################
//
//we just need to get one half of the string (each character appea//rs half the
//times in s), then generate all its unique permutations and concatenate them
//with the reversed half (possibly the single middle character if the length of
//the string s is odd).

//All the above work will only be done if an palindrome permutation exists. To
//tell whether a palindrome permutation exists, Palindrome Permutation has
//paved the way for us. To generate all the unique permutations, you may as
//well refer to Permutations II or Next Permutation as suggested by the second
//hint. But I guess this part is not the main point of this problem, so I
//directly use the next_permutation of C++. Well, I am not quite whether this
//is the right way, but this gives shorter codes. Moreover, the tag of this
//problem is backtracking, which I guess only needs to be used in generating
//the permutations. After this is done, we can simply concatenate to make the
//palindromes.
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


