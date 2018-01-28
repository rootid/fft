//Self Dividing Numbers 67.5% Easy
//A self-dividing number is a number that is divisible by every digit it contains.
//For example, 128 is a self-dividing number because 128 % 1 == 0, 128 % 2 == 0, and 128 % 8 == 0.
//Also, a self-dividing number is not allowed to contain the digit zero.
//Given a lower and upper number bound, output a list of every possible self dividing number, including the bounds if possible.
//Example 1:
//Input:
//left = 1, right = 22
//Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 22]
//Note:
//The boundaries of each input argument are 1 <= left <= right <= 10000.

//######################################### Brute Force #########################################
// TC : O(D) D = |right- left|
// SC : O(D)
private boolean isSelfDividing(int n) {
    String v = String.valueOf(n);
    for(int i=0;i<v.length();i++)
        if ((v.charAt(i) - '0') == 0 || n % (v.charAt(i) - '0') != 0) return false;
    return true;
}

public List<Integer> selfDividingNumbers(int left, int right) {
    List<Integer> lst = new ArrayList<>();
    while(left <= right) {
        if(isSelfDividing(left)) lst.add(left);
        left++;
    }
    return lst;
}

//######################################### Brute Force #########################################
public List<Integer> selfDividingNumbers(int left, int right) {
     List<Integer> res = new ArrayList<>();
     for (int i = left, n = 0; i <= right; i++) {
         for (n = i; n > 0; n /= 10)
             if (n % 10 == 0 || i % (n % 10) != 0) break;
         if (n == 0) res.add(i);
     }
     return res;
 }

//######################################### Brute Force #########################################
 def selfDividingHelper(self, num):
        temp = num
        while temp:
            if not temp % 10 or num % (temp % 10): return False
            temp = temp//10
        return True

    def selfDividingNumbers(self, left, right):
        result = []
        for num in range(left, right+1):
            if self.selfDividingHelper(num): result.append(num)
        return result

//######################################### Brute Force #########################################
vector<int> selfDividingNumbers(int left, int right) {
      vector<int> res;
      for (int i = left, n = 0; i <= right; i++) {
          for (n = i; n > 0; n /= 10)
              if (!(n % 10) || i % (n % 10)) break;
          if (!n) res.push_back(i);
      }
      return res;
  }

/* vim: set ts=2 sw=2 sts=2 tw=120 et: */
