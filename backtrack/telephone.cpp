
  vector<string> letterCombinations(string digits) {
    vector<string> str;//str for final resut
    string save;//save for temporary answer
    int convert[10] = {0, 3, 6, 9, 12, 15, 19, 22, 26};
    dfs(str, save, digits, 0, digits.size(), convert);
    return str;
    }
    void dfs(vector<string> &str, string save, 
         string dig, int now, int size, int *convert){
    if(now == size){
        str.push_back(save);
        return;
    }
    int tmp = dig[now] - '0' - 2;//change '2' to 0, '3' to 1...
    for(int i = convert[tmp]; i < convert[tmp+1]; i++){
        save.push_back('a' + i);//ex: a,b,c | d,e,f
        dfs(str, save, dig, now + 1, size, convert);
        save.pop_back();
    }
    }


public List<String> letterCombinations(String digits) {
    LinkedList<String> ans = new LinkedList<String>();
    String[] mapping = new String[] {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    ans.add("");
    for(int i =0; i<digits.length();i++){
        int x = Character.getNumericValue(digits.charAt(i));
        while(ans.peek().length()==i){
            String t = ans.remove();
            for(char s : mapping[x].toCharArray())
                ans.add(t+s);
        }
    }
    return ans;
}


//I have a different approach and it is more intuitive to me. This is similar to printing all numbers with k digits. For example k=3, you start at 000, then you keep coming up: 001, 002, 003, ... until you reach 009, then reset last bit, and increase the next bit to 010, then 011, 012, etc.
//
//So we can solve this problem in a similar way. If our input string is "23". Because 2 = "abc", 3 = "def", we can start from the smallest "ad", then go up: "ae", "af", then we have to reset last char from "f" to "d" and we have "bd", "be", "bf", etc. This way, we don't need backtracking, recursive, or List.
//
//Hope this helps for some people.

vector<string> letterCombinations(string digits) {
    vector<string> R;
    if (digits.empty()) return R;
    string a[8] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    int n = digits.size();
    vector<int> v(n, 0);
    
    // Initialize string V
    string S = "";
    for (int i=0; i<n; i++)
        S += a[digits[i]-'0'-2][0];
    
    while (true) {
        R.push_back(S);
        int j = n-1;
        v[j]++;
        while (j>0 && v[j]==a[digits[j]-'0'-2].size()) {
            v[j] = 0;
            S[j] = a[digits[j]-'0'-2][0];
            v[--j]++;
        }
        
        //Check to see if outta range yet
        if (v[0]==a[digits[0]-'0'-2].size()) break;
        else S[0] = a[digits[0]-'0'-2][v[0]];
        
        S[j] = a[digits[j]-'0'-2][v[j]];
    }
    return R;
}

//Iterative solution
vector<string> letterCombinations(string digits) {
    vector<string> res;
    string charmap[10] = {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    res.push_back("");
    for (int i = 0; i < digits.size(); i++)
    {
        vector<string> tempres;
        string chars = charmap[digits[i] - '0'];
        for (int c = 0; c < chars.size();c++)
            for (int j = 0; j < res.size();j++)
                tempres.push_back(res[j]+chars[c]);
        res = tempres;
    }
    return res;
}


I have a different approach and it is more intuitive to me. This is similar to printing all numbers with k digits. For example k=3, you start at 000, then you keep coming up: 001, 002, 003, ... until you reach 009, then reset last bit, and increase the next bit to 010, then 011, 012, etc.

So we can solve this problem in a similar way. If our input string is "23". Because 2 = "abc", 3 = "def", we can start from the smallest "ad", then go up: "ae", "af", then we have to reset last char from "f" to "d" and we have "bd", "be", "bf", etc. This way, we don't need backtracking, recursive, or List.

Hope this helps for some people.

vector<string> letterCombinations(string digits) {
    vector<string> R;
    if (digits.empty()) return R;
    string a[8] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    int n = digits.size();
    vector<int> v(n, 0);
    
    // Initialize string V
    string S = "";
    for (int i=0; i<n; i++)
        S += a[digits[i]-'0'-2][0];
    
    while (true) {
        R.push_back(S);
        int j = n-1;
        v[j]++;
        while (j>0 && v[j]==a[digits[j]-'0'-2].size()) {
            v[j] = 0;
            S[j] = a[digits[j]-'0'-2][0];
            v[--j]++;
        }
        
        //Check to see if outta range yet
        if (v[0]==a[digits[0]-'0'-2].size()) break;
        else S[0] = a[digits[0]-'0'-2][v[0]];
        
        S[j] = a[digits[j]-'0'-2][v[j]];
    }
    return R;
}


I've decided to experiment with different approach than backtracking and recursion. It reminds a bit radix-sort style. The main idea is to keep a buffer of chars representing the word. At first it is initiated by first letter from the corresponding mapping list for each digit. Then we sequentially try all letters of a first digit. Then "increment" letter for the second digit, and run through all first ones again. Etc. Like spinning the rings of a number lock.

public class Solution {
    
    private static final Map<Character, String> mapping = new HashMap<>();
    static { 
        mapping.put('2', "abc"); mapping.put('3', "def"); 
        mapping.put('4', "ghi"); mapping.put('5', "jkl"); 
        mapping.put('6', "mno"); mapping.put('7', "pqrs");
        mapping.put('8', "tuv"); mapping.put('9', "wxyz");
    }
    
    public List<String> letterCombinations(String digits) {
        if (digits.isEmpty()) return Arrays.asList("");
        List<String> res = new LinkedList<>();
        // init our buffer with first letters for each digit
        char[] buf = new char[digits.length()];
        for (int k = 0; k < buf.length; k++) 
                buf[k] = mapping.get(digits.charAt(k)).charAt(0);
        // array of current letter's indices for each position
        int[] idx = new int[digits.length()];
        int i = 0;
        while (i < digits.length()) {
            res.add(new String(buf)); // add the current buffer to the result
            i = 0;
            // run through positions incrementing the corresponding index,
            // there could be two cases:
            // 1. we tried all letters at this position -> we must reset it and
            //     move to the next one;
            // 2. we find the position where we didn't try all, so we just
            //     increment corresponding index and break the loop,
            //     because we actually found the next combination.
            while (i < digits.length()) {
                idx[i] = (idx[i] + 1) % mapping.get(digits.charAt(i)).length();
                buf[i] = mapping.get(digits.charAt(i)).charAt(idx[i]);
                if (idx[i] != 0) break;
                i++;
            }
        }
        return res;
    }
}
Actually, this approach looks more effective than recursive search not only because it's iterative but also because we reuse the tail of our buffer making some kind of memoization.

Have a nice one!
