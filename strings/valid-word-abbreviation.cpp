//Valid Word Abbreviation
//Given a non-empty string s and an abbreviation abbr, return whether the
//string matches with the given abbreviation.
//A string such as "word" contains only the following valid abbreviations:
//["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]
//Notice that only the above abbreviations are valid abbreviations of the
//string "word". Any other string is not a valid abbreviation of "word".
//Note:
//Assume s contains only lowercase letters and abbr contains only lowercase
//letters and digits.
//Example 1:
//Given s = "internationalization", abbr = "i12iz4n":
//Return true.
//Example 2:
//Given s = "apple", abbr = "a2e":
//Return false.

bool validWordAbbreviation(string word, string abbr) {
    int i =0 ;
    int j = 0;
    int m = word.size();
    int n = abbr.size();
    while(i < m && j < n) {
        int val = 0;
        if(isdigit(abbr[j]) ) {
            if(abbr[j] == '0') {
                return false;
            }
            while(j < n && isdigit(abbr[j])) {
                val = val * 10 + abbr[j] - '0';
                j++;
            }
            cout << val << endl;
            i += val;
        }
        if( i < m && j < n && word[i++] != abbr[j++]) {
            return false;
        }
    }
    return i == m && j == n;
}

//################################# pytonic #############################

//def validWordAbbreviation(self, word, abbr):
//    return bool(re.match(re.sub('([1-9]\d*)', r'.{\1}', abbr) + '$', word))
//
//def validWordAbbreviation(self, word, abbr):
//    regex = re.sub('\d+', lambda m: '.' * int(m.group()), abbr)
//    return bool(re.match(regex + '$', word)) and not re.search('(^|\D)0', abbr)
//
//def validWordAbbreviation(self, word, abbr):
//    regex = re.sub('\d+', lambda m: '.' * int(m.group()), abbr)
//    return re.match(regex + '$', word) > re.search('(^|\D)0', abbr)
//
//I turn each number into that many dots to get a regular expression. For
//example, when asked whether "3t2de" is a valid abbreviation for word
//"leetcode", I turn "3t2de" into "...t..de" and check whether that regular
//expression matches "leetcode", which it does. I also need to rule out the
//number "0" and leading zeros, which I do with another regular expression.
//
//adding test case "bignumberhahaha", "999999999" : memmor yerror
//$0 just means the match. In general, you can capture groups with parentheses and refer to the groups
//like that in the replacement string. For example,
//"leetcode".replaceAll("(.)(.)", "$2$1")
//finds pairs of characters and switches their order, resulting in the string
//"elteoced". Group zero is just the whole match.
