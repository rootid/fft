//Ransom Note
//Given an arbitrary ransom note string and another string containing letters from all the magazines, write a function that will return true if the ransom note can be constructed from the magazines ; otherwise, it will return false.
//Each letter in the magazine string can only be used once in your ransom note.
//Note:
//You may assume that both strings contain only lowercase letters.
//canConstruct("a", "b") -> false
//canConstruct("aa", "ab") -> false
//canConstruct("aa", "aab") -> true

//######################################## With Array ########################################
public boolean canConstruct(String ransomNote, String magazine) {
     //store freq of all chars
     int len = magazine.length();
     int[] magFreq = new int[26];
     for(char c: magazine.toCharArray())
        magFreq[c - 'a']++;
     for(char c:ransomNote.toCharArray()) {
         if(magFreq[c - 'a'] == 0) return false;
         magFreq[c - 'a']--;
     }
     return true;
 }

//######################################## With Map ########################################
public boolean canConstruct(String ransomNote, String magazine) {
        Map<Character, Integer> magM = new HashMap<>();
        for (char c:magazine.toCharArray()){
            int newCount = magM.getOrDefault(c, 0)+1;
            magM.put(c, newCount);
        }
        for (char c:ransomNote.toCharArray()){
            int newCount = magM.getOrDefault(c,0)-1;
            if (newCount<0)
                return false;
            magM.put(c, newCount);
        }
        return true;
    }

//######################################## With Map ########################################
//getOrDefault is replaced with compute
public boolean canConstruct(String ransomNote, String magazine) {
    // final Multiset<Character> occurrences = CharStream.from(magazine).boxed().collect(Collectors.toMultiset());
    // return CharStream.from(ransomNote).boxed().forEach2(e -> occurrences.getAndRemove(e) > 0);
    final Map<Character, Integer> magM = new HashMap<>();
    for (char c : magazine.toCharArray()) {
        magM.compute(c, (k, v) -> v == null ? 1 : v + 1);
    }
    for (char c : ransomNote.toCharArray()) {
        if (magM.compute(c, (k, v) -> v == null ? -1 : v - 1) < 0) {
            return false;
        }
    }
    return true;
}

//######################################## cpp ########################################
//T: O(N)
bool canConstruct(string ransomNote, string magazine) {
    unordered_map<char, int> map(26);
    for (int i = 0; i < magazine.size(); ++i)
        ++map[magazine[i]];
    for (int j = 0; j < ransomNote.size(); ++j)
        if (--map[ransomNote[j]] < 0)
            return false;
    return true;
}


//######################################## cpp ########################################
 bool canConstruct(string ransomNote, string magazine) {
      unordered_map<char, int> map(26);
      for (char mchar : magazine) ++map[mchar];
      for (char rchar : ransomNote) if (--map[rchar] < 0) return false;
      return true;
  }


//######################################## Python ########################################
//T O(m+n)
def canConstruct(self, ransomNote, magazine):
    return not collections.Counter(ransomNote) - collections.Counter(magazine)


//######################################## Python ########################################
def canConstruct(self, ransomNote, magazine):
    return all(ransomNote.count(i) <= magazine.count(i) for i in string.ascii_lowercase)

// vim: set sw=2 sts=2 tw=120 et nospell :
