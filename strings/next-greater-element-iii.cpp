//Next Greater Element III
//Given a positive 32-bit integer n, you need to find the smallest 32-bit integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive 32-bit integer exists, you need to return -1.
//Example 1:
//Input: 12
//Output: 21
//Example 2:
//Input: 21
//Output: -1


/** 
 * GO FROM RIGHT TO LEFT
 * 1. a max number has the property of decreasing in every digit: 9876 from RIGHT 
 * 2. find the first non-max substring from the right; ex. in 1234(59876), 59876 is the first non-max substring from the right
 * 3. sort the max part of 5(9876), by reverse, becames 5(6789);
 * 4. flip 5,6, becames 65789; because 6 is the next smallest digit than 5, in 56789;
 * 5. incase of 66789, you got flip 6 with 7 to make it 76689, to make it bigger.
 */
//#################################### O(n) + with property #################################### 
int nextGreaterElement(int n) { 
  string s = to_string(n);
  if (s.length() == 1) {
      return -1;
  }
  /* find the first decreasing digit from the right, eg: 59876, 5 is the first decreasing digit */
  int i = s.length() - 2; // 21 -> i = 0; 59876 -> i = 3
  for (; i >= 0 && s[i] >= s[i + 1]; i--) { 
    //DO NOTHING
  }
  if (i == -1) {  // if a decreasing digit cannot be find, the number cannot be larger.
      return -1;
  }
  //reverse the increasing sequence
  reverse(s.begin() + i + 1, s.end());
  //Find first greater digit than current digit s[i]
  for (int j = i + 1; j < s.length(); j++) {
      if (s[j] > s[i]) {
          swap(s[i], s[j]);
          break;
      }
  }
  long next = stol(s);
  return next == n || next > INT_MAX ? -1 : next; 
}

//############################################# ############################################# 
int nextGreaterElement(int n) { 
  string s = to_string(n);
  int i = 0, p = 0, q = 0, len = s.length();
  while (++i < len) {
      //if last ele > current ele
      if (s[i - 1] >= s[i]) { // e.g. 5698776665443, s[p] = '6', s[q] = '7'(the rightmost one)
          if (s[i] > s[p]) {
            q = i; // s[q] is the next greater number in the down sequence for s[p] 
          }
      } else {
          p = i - 1;
          q = i;
      }
  }
  if (q == 0) return -1; // The sequence is descending
  swap(s[p], s[q]);
  reverse(s.begin() + p + 1, s.end()); // e.g. 5698776665443 -> 5798766665443 -> 5734456666789
  if (s.length() == 10 && s.compare(to_string(INT_MAX)) > 0) return -1;
  return stoi(s);
}


//############################# Overflow detect with long long ############################
int nextGreaterElement(int n) {
    multiset<int> d;
    while (n) {
        int t = n % 10;
        n /= 10;
        if (d.size() && *d.rbegin() > t) {
            auto it = d.upper_bound(t);
            long long ret = n * 10 + *it;
            d.erase(it);
            d.insert(t);
            for (int i : d) ret = ret * 10 + i;
            return ret > INT_MAX ? -1 : ret;
        }
        d.insert(t);
    }
    return -1;
}

//############################# Overflow detect + No long long ##############################
int nextGreaterElement(int n) {
    multiset<int> d;
    while (n) {
        int t = n % 10;
        n /= 10;
        if (d.size() && *d.rbegin() > t) {
            auto it = d.upper_bound(t);
            n = n * 10 + *it;
            d.erase(it);
            d.insert(t);
            for (int i : d) {
                if (n > 214748364 || n == 214748364 && i > 7)
                    return -1;
                n = n * 10 + i;
            }
            return n;
        }
        d.insert(t);
    }
    return -1;
}

//############################################# use of next_permutation ############################################# 
int nextGreaterElement(int n) {
    auto digits = to_string(n);
    next_permutation(begin(digits), end(digits));
    auto res = stoll(digits);
    return (res > INT_MAX || res <= n) ? -1 : res;
}


//############################################# pytonic ############################################# 
//Going through all permutations of the digits, returning the first one that's larger than the input (unless it's out of range). Pretty inefficient but gets accepted in about 200 ms...

//def nextGreaterElement(self, n):
//    n = tuple(str(n))
//    p = int(''.join(next((p for p in itertools.permutations(sorted(n)) if p > n), '9' * 10)))
//    return p if p < 2**31 else -1  # return if p falls within integer range 2**31
//
//The worst case is n = 1111111111, because I go through all 10! permutations and each one gets fully compared. This case takes about 600 ms.
