//Find Smallest Letter Greater Than Target
//Given a list of sorted characters letters containing only lowercase letters, and given a target letter target, find the smallest element in the list that is larger than the given target.
//Letters also wrap around. For example, if the target is target = 'z' and letters = ['a', 'b'], the answer is 'a'.
//Examples:
//Input:
//letters = ["c", "f", "j"]
//target = "a"
//Output: "c"
//Input:
//letters = ["c", "f", "j"]
//target = "c"
//Output: "f"
//Input:
//letters = ["c", "f", "j"]
//target = "d"
//Output: "f"
//Input:
//letters = ["c", "f", "j"]
//target = "g"
//Output: "j"
//Input:
//letters = ["c", "f", "j"]
//target = "j"
//Output: "c"
//Input:
//letters = ["c", "f", "j"]
//target = "k"
//Output: "c"
//Note:
//    letters has a length in range [2, 10000].
//    letters consists of lowercase letters, and contains at least 2 unique letters.
//    target is a lowercase letter.
//
//From O(N) to O(log n)
//######################################### use of mod operator + Intelligent search #########################################
public char nextGreatestLetter(char[] letters, char target) {
    int i = Arrays.binarySearch(letters, (char) (target + 1)); //Use target+1 to handle duplicate case
    return letters[i >= 0 ? i : ~i % letters.length]; //~i - 1's complement
}


//######################################### O(N) #########################################
 public char nextGreatestLetter(char[] letters, char target) {
        for (char c: letters)
            if (c > target) return c;
        return letters[0];
    }

//######################################### O(log n) #########################################
//Custom binary search
// Let mi = (lo + hi) / 2.
// If letters[mi] <= target, then we must insert it in the interval [mi + 1, hi]. Otherwise, we must insert it in the interval [lo, mi].
public char nextGreatestLetter(char[] letters, char target) {
     int lo = 0, hi = letters.length;
     while (lo < hi) {
         int mi = lo + (hi - lo) / 2;
         if (letters[mi] <= target) lo = mi + 1;
         else hi = mi;
     }
     return letters[lo % letters.length];
 }

//######################################### Ugly no use of mod operator #########################################
public char nextGreatestLetter(char[] letters, char target) {
    int len = letters.length;
    int idx = Arrays.binarySearch(letters, target);
    // System.out.println(idx + " | idx =  " + ~idx);
    if(idx < 0) return idx == -len-1 ? letters[0] : letters[-idx - 1];
    if(idx == 0) return letters[idx+1];
    if(idx < len-1) {
        boolean flg = false;
        while( idx < len && target == letters[idx]) {
            idx++;
            flg = true; //To handle duplicate
        }
        if(idx > len-1) return letters[0];
        if(flg == true) return letters[idx];
        return letters[idx - 1];
    }
    return letters[0];
}
/* vim: set ts=2 sw=2 sts=2 tw=120 et: */
