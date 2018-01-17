
//################################ O(N) ################################ 
public int compress(char[] chars) {
    int len = chars.length;
    int endIdx = 0;
    int freq = 1;
    for(int i=0;i<len;i++) {
        if(i == len-1 || chars[i] != chars[i+1]) {
            chars[endIdx++] = chars[i];
            if(freq != 1) {
                String freqS = freq + "";
                for(int j=0;j<freqS.length();j++) 
                    chars[endIdx++] = freqS.charAt(j);
                freq = 1;
            } 
        } else freq++;
    }
    return endIdx;
}

// vim: set sw=2 sts=2 tw=120 et nospell : 
