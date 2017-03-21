//Repeated DNA Sequences
//All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.
//Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.
//For example,
//Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",
//Return:
//["AAAAACCCCC", "CCCCCAAAAA"].


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
