//Bold Words in String
// Given a set of keywords words and a string S, make all appearances of all keywords in S bold. Any letters between <b> and </b> tags become bold.
//The returned string should use the least number of tags possible, and of course the tags should form a valid
//combination.
//For example, given that words = ["ab", "bc"] and S = "aabcd", we should return "a<b>abc</b>d". Note that returning
//"a<b>a<b>b</b>c</b>d" would use more tags, so it is incorrect.
//Note:
//    words has length in range [0, 50].
//    words[i] has length in range [1, 10].
//    S has length in range [0, 500].
//    All characters in words[i] and S are lowercase letters.



//######################################### W/O HashMap #########################################
public String boldWords(String[] words, String S) {
    int len = S.length();
    int[] sum = new int[len+1];
    //PreSum/Running sum
    for(String s: words) {
        int i= 0;
        while( (i = S.indexOf(s, i)) >= 0) {
            sum[i]++;
            sum[i + s.length()]--;
            i++;
        }
    }
    int pre = 0;
    int rsum = 0;
    StringBuilder result = new StringBuilder();
    for(int i=0;i<= S.length();i++) {
        rsum += sum[i];
        if(pre == 0 && rsum > 0) result.append("<b>");
        if(pre > 0 && rsum == 0)  result.append("</b>");
        if (i < S.length()) result.append(S.charAt(i));
        pre = rsum;
    }
    return result.toString();
}

//######################################### W/O boolean array #########################################
//Keep track of substring
public String boldWords(String[] words, String S) {
        if (words == null || words.length == 0) return "";

        boolean[] marked = new boolean[S.length()];
        for (String word : words) {
            markWords(S, word, marked);
        }

        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < S.length(); i++) {
            if (marked[i] && (i == 0 || !marked[i - 1]))
                sb.append("<b>");
            sb.append(S.charAt(i));
            if (marked[i] && (i == S.length() - 1 || !marked[i + 1]))
                sb.append("</b>");
        }
        return sb.toString();
    }

    void markWords(String S, String word, boolean[] marked) {
        for (int i = 0; i <= S.length() - word.length(); i++) {
            String substr = S.substring(i, i + word.length());
            if (substr.equals(word)) {
                for (int j = i; j < i + word.length(); j++) {
                    marked[j] = true;
                }
            }
        }
    }


/* vim: set ts=2 sw=2 sts=2 tw=120 et: */
