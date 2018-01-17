//Repeated DNA Sequences
//All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.
//Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.
//For example,
//Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",
//Return:
//["AAAAACCCCC", "CCCCCAAAAA"].


//################### Customized hashMap ################### 
  public List<String> findRepeatedDnaSequences(String s) {
        Map<Integer, Boolean> m = new HashMap<>();
        List<String> result = new LinkedList<>();
        for (int t = 0, i = 0; i < s.length(); i++) {
            t = t << 3 & 0x3FFFFFFF | s.charAt(i) & 7;
            if (m.containsKey(t)) {
                if (m.get(t)) {
                    result.add(s.substring(i - 9, i+1));
                    m.put(t, false);
                }
            } else m.put(t, true);
        }

      return result;
    }


//################### HashMap ################### 
//"AAAAAAAAAAA" o/p = AAAAAAAAAA (As AAAAAAAAAA occured at idx=0,1)
  public List<String> findRepeatedDnaSequences(String s) {
        List<String> result = new LinkedList<>();
        Map<String,Boolean> map = new HashMap<>();
        for(int i=0;i<=s.length() - 10;i++) {
            String tmp = s.substring(i,i+10);
            if(map.containsKey(tmp)) {
                if(map.get(tmp))
                    result.add(tmp);
                map.put(tmp, false);
            } else map.put(tmp, true);
        }
      return result;
    }

//################### Encode with last 3 bits ################### 
vector<string> findRepeatedDnaSequences(string s) {
      unordered_map<int,int> umap;
      vector<string> r;
      for(int i=0,t=0;i<s.size();i++) {
          if(umap[ t = t << 3 & 0x3FFFFFFF | s[i] & 7 ]++ == 1) {
              r.push_back(s.substr(i-9,10));
          }
      }
      return r;
}


//################## use boolean instead of int counter as a value (SPACE Eff) ################## 
vector<string> findRepeatedDnaSequences(string s) {
    unordered_map<int, bool> m;
    vector<string> r;
    for (int t = 0, i = 0; i < s.size(); i++) {
        t = t << 3 & 0x3FFFFFFF | s[i] & 7;
        if (m.find(t) != m.end()) {
            if (m[t]) {
                r.push_back(s.substr(i - 9, 10));
                m[t] = false;
            }
        } else {
            m[t] = true;
        }
    }
    return r;
}
