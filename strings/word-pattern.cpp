//Word Pattern
//Given a pattern and a string str, find if str follows the same pattern.
//Here follow means a full match, such that there is a bijection between a
//letter in pattern and a non-empty word in str.
//Examples:
//pattern = "abba", str = "dog cat cat dog" should return true.
//pattern = "abba", str = "dog cat cat fish" should return false.
//pattern = "aaaa", str = "dog cat cat dog" should return false.
//pattern = "abba", str = "dog dog dog dog" should return false.
//Notes:
//You may assume pattern contains only lowercase letters, and str contains
//lowercase letters separated by a single space.
//


//Beats 33%
bool wordPattern(string pattern, string str) {
    unordered_map<char, int> p2i;
    unordered_map<string, int> w2i;
    istringstream in(str);
    int i = 0, n = pattern.size();
    for (string word; in >> word; ++i) {
        if (i == n || p2i[pattern[i]] != w2i[word])
            return false;
        p2i[pattern[i]] = w2i[word] = i + 1;
    }
    return i == n;
}
//Beats 1.69
bool wordPattern(string pattern, string str) {
    unordered_map<char,string> tmp;
    unordered_set<string> tset;
    int pLen = pattern.size();
    vector<string> tV;
    stringstream ss(str);
    string item;
    while(getline(ss,item,' ')) {
        tV.push_back(item);
    }
     int sLen = tV.size();
    if(pLen != sLen) {
        return false;
    }
    for(int i=0;i<pLen;i++) {
        if ( tmp.count(pattern[i]) == 0) {
            if (tset.find(tV[i]) == tset.end() ) {
                tset.insert(tV[i]);
            } else {
                return false;
            }
            tmp[ pattern[i] ] = tV[i];
        } else {
            if(tmp[pattern[i] ] != tV[i]) {
                return false;
            }
        }
    }
    return true;
}
