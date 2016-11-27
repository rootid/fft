//Generalized Abbreviation
//Write a function to generate the generalized abbreviations of a word.
//Example:
//Given word = "word", return the following list (order does not matter):
//["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]

//for k size word , total # of words = 2^k
//000 -> abc -> abc
//001 -> ab_ -> ab1
//010 -> a_c -> a1c
//011 -> a__ -> a2
//100 -> _bc -> 1bc
//101 -> _b_ -> 1b1
//110 -> __c -> 2c
//111 -> ___ -> 3

    
void dfs(vector<string>& res, string curr, int start, string s) {
        // 表示数字替换已经越界，recursion终止 
        if (start > s.length()) 
            return;
            
        // 用之前结束位置存入当前符合条件的结果
        res.push_back(curr + s.substring(start));
        
        // 定义新的起始位置
        int i = 0;
        
        // 除了最开始，起始位置都要与之前结尾位置隔一个
        if (start > 0) {
            i = start + 1;
        }
        
        for (; i < s.length(); i++) {
            for (int j = 1; j <= s.length(); j++) {
                // 数字之前的字符串要append上
                dfs(res, curr + s.substring(start, i) + j, i + j, s);
            }
        }
}

vector<string> generateAbbreviations(string word) {
        vector<string> res;
        dfs(res, "", 0, word);
        return res;
}
