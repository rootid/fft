//Fraction to Recurring Decimal
//Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.
//If the fractional part is repeating, enclose the repeating part in parentheses.
//For example,
//Given numerator = 1, denominator = 2, return "0.5".
//Given numerator = 2, denominator = 1, return "2".
//Given numerator = 2, denominator = 3, return "0.(6)".

//############################################ Map + Recurring remainder ############################################ 
//decimal parts to recur, the remainders should recur. 
//1. Pay attention to the sign of the result;
//2. Handle cases that may cause overflow like numerator = -2147483648, denominator = -1 appropriately by using long long;
//3. Handle all the cases of 
//(1) no fractional part; 
//(2) fractional part does not recur; 
//(3) fractional part recurs respectively.
//
//To handle problem 3, we divide the division process into the integral part 
//and the fractional part. For the fractional part, 
//if it does not recur, then the remainder will become 0 at some point and we could return. 
string fractionToDecimal(int numerator, int denominator) { 
  if (!numerator) return "0"; // 0/a = 0 
  string res;
  //update the sign of result
  if (numerator < 0 ^ denominator < 0) {
    res += '-';
  }
  //convert to +ve values
  long numer = numerator < 0 ? (long)numerator * (-1) : (long)numerator; //avoids buffer overflow
  long denom = denominator < 0 ? (long)denominator * (-1) : (long)denominator;
  long integral = numer / denom;
  res += to_string(integral);
  long rmd = numer % denom;
  if (!rmd) return res; //no remaider
  res += '.';
  rmd *= 10;
  unordered_map<long, long> mp;  //holds <remainder:position> tuple
  while (rmd) {
      long quotient = rmd / denom;
      if (mp.find(rmd) != mp.end()) { 
          res.insert(mp[rmd], 1, '(');
          res += ')';
          break;
      }
      mp[rmd] = res.size();
      res += to_string(quotient);
      rmd = (rmd % denom) * 10; //update the remaider 
  }
  return res;
}

//############################################ Map + Recurring remainder + int_64 ############################################ 
string fractionToDecimal(int64_t n, int64_t d) {
    // zero numerator
    if (n == 0) return "0";
    string res;
    // determine the sign
    if (n < 0 ^ d < 0) res += '-';
    // remove sign of operands
    n = abs(n), d = abs(d);
    // append integral part
    res += to_string(n / d);
    // in case no fractional part
    if (n % d == 0) return res;
    res += '.';
    unordered_map<int, int> map;
    // simulate the division process
    for (int64_t r = n % d; r; r %= d) {
        // meet a known remainder
        // so we reach the end of the repeating part
        if (map.count(r) > 0) {
            res.insert(map[r], 1, '(');
            res += ')';
            break;
        }
        // the remainder is first seen
        // remember the current position for it
        map[r] = res.size();
        r *= 10;
        // append the quotient digit
        res += to_string(r / d);
    }
    return res;
}

//############################### pytonic  ############################### 
//Find the start point of a linked list cycle". I used the fast pointer and slow pointer trick.
//class Solution:
//# @return a string
//def fractionToDecimal(self, numerator, denominator):
//    n, remainder = divmod(abs(numerator), abs(denominator))
//    sign = '-' if numerator*denominator < 0 else ''
//    result = [sign+str(n), '.']
//    stack = []
//    while remainder not in stack:
//        stack.append(remainder)
//        n, remainder = divmod(remainder*10, abs(denominator))
//        result.append(str(n))
//
//    idx = stack.index(remainder)
//    result.insert(idx+2, '(')
//    result.append(')')
//    return ''.join(result).replace('(0)', '').rstrip('.')
//
//######################################## linked list fast pointer + slow pointer ######################################## 
//frem : fast pointer
//srem : slow pointer
//def fractionToDecimal(self, numerator, denominator):
//    n = numerator
//    d = denominator
//    if n % d == 0:
//        return str(n//d)
//    # Deal with negatives
//    if (abs(n)/n) * (abs(d)/d) < 0:
//        res = '-'
//        n = abs(n)
//        d = abs(d)
//    else:
//        res = ''
//    # Integer part
//    res = res + str(n//d) + '.'
//    n = n % d
//    # Start point of the "list"
//    frem = n
//    srem = n
//    firstTime = True
//    while frem != 0 and not (firstTime == False and frem == srem):
//        firstTime = False
//        srem = (srem * 10) % d
//        frem = (frem * 10) % d
//        if frem:
//            frem = (frem * 10) % d
//    # The fast pointer encounters a remainder of 0, so no cycle in the "list"
//    if frem == 0:
//        res += str((n * 10) // d)
//        rem = (n * 10) % d
//        while rem:
//            res += str((rem * 10) // d)
//            rem = (rem * 10) % d
//        return res
//    else:
//        # Find the start point of the cycle, meanwhile, generate the non recurring part
//        srem = n
//        while frem != srem:
//            res += str((srem * 10) // d)
//            srem = (srem * 10) % d
//            frem = (frem * 10) % d
//        res += '('
//        # Generate the recurring part
//        firstTime = True
//        while not (firstTime == False and srem == frem):
//            firstTime = False
//            res += str((srem * 10) // d)
//            srem = (srem * 10) % d
//        res += ')'
//        return res
