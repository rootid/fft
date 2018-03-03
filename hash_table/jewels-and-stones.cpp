//You're given strings J representing the types of stones that are jewels, and
//S representing the stones you have.  Each character in S is a type of stone
//you have.  You want to know how many of the stones you have are also jewels.
//The letters in J are guaranteed distinct, and all characters in J and S are
//letters. Letters are case sensitive, so "a" is considered a different type of
//stone from "A".
//Example 1:
//Input: J = "aA", S = "aAAbbbb"
//Output: 3
//Example 2:
//Input: J = "z", S = "ZZ"
//Output: 0
//Note:
//    S and J will consist of letters and have length at most 50.
//    The characters in J are distinct.

//######################## WITH SET ##########################################
//cnstrnt :
    //1. letter [a-z|A-Z] or any char ?
    //2.  J/S len ?
    //3  J< S
//Ida :
//1. Set < J  S XT(J) , TC : O(N) , SC : l(J)
//2. Sort J -> S XT(J) TC : O(n log n) + n * O(log n)
public int numJewelsInStones(String J, String S) {
    Set<Character> jSet = new HashSet<>();
    for(char j:J.toCharArray())
        jSet.add(j);
    int noOfJ = 0;
    for(char s: S.toCharArray()) if(jSet.contains(s)) noOfJ++;
    return noOfJ;
}

//######################## WITH SET ##########################################
int numJewelsInStones(string J, string S) {
        int res = 0;
        set<char> setJ(J.begin(), J.end());
        for (char s : S) if (setJ.count(s)) res++;
        return res;
    }

//######################## WITH SET ##########################################
int numJewelsInStones(string J, string S) {
        int res = 0;
        set<char> setJ(J.begin(), J.end());
        for (char s : S) if (setJ.count(s)) res++;
        return res;
}
