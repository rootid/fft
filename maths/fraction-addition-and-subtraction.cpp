//Fraction Addition and Subtraction
//Given a string representing an expression of fraction addition and
//subtraction, you need to return the calculation result in string format. The
//final result should be irreducible fraction. If your final result is an
//integer, say 2, you need to change it to the format of fraction that has
//denominator 1. So in this case, 2 should be converted to 2/1.
//Example 1:
//Input:"-1/2+1/2"
//Output: "0/1"
//Example 2:
//Input:"-1/2+1/2+1/3"
//Output: "1/3"
//Example 3:
//Input:"1/3-1/2"
//Output: "-1/6"
//Example 4:
//Input:"5/3+1/3"
//Output: "2/1"
//Note:
//The input string only contains '0' to '9', '/', '+' and '-'. So does the
//output.
//Each fraction (input and output) has format ±numerator/denominator. If the
//first input fraction or the output is positive, then '+' will be omitted.
//The input only contains valid irreducible fractions, where the numerator and
//denominator of each fraction will always be in the range [1,10]. If the
//denominator is 1, it means this fraction is actually an integer in a fraction
//format defined above.
//The number of given fractions will be in the range [1,10].
//The numerator and denominator of the final result are guaranteed to be valid
//and in the range of 32-bit int.
//

//################################## Add 0 to expression (0/1) = (A/B) ##################################
//Keep the overall result in A / B, read the next fraction into a / b. Their
//sum is (Ab + aB) / Bb (but cancel their greatest common divisor).
string fractionAddition(string expression) {
    istringstream in(expression);
    int A = 0, B = 1, a, b;
    char _;
    while (in >> a >> _ >> b) {
        A = A * b + a * B;
        B *= b;
        //normalize the result (6/2) => (3/1)
        int g = abs(__gcd(A, B));
        A /= g;
        B /= g;
    }
    return to_string(A) + '/' + to_string(B);
}

//############################################### stoi ############################################################
//The initial fraction is 0/1 (n/d).
//We just need to read next fraction (nn/dd), normalize denominators between
//n/d and nn/dd (using GCD), and add/subtract the numerator (n +/- nn).
//In the end, we also need to use GCD to make the resulting fraction
//irreducible.
int GCD(int a, int b ){ return (b == 0) ? a : GCD(b, a % b); }
string fractionAddition(string s) {
    int n = 0, d = 1, p = 0, p1 = 0, p2 = 0;
    if (s[0] != '-') {
      s = "+" + s;
    }
    while (p < s.size()) {
        for (p1 = p + 1; s[p1] != '/'; ++p1);
        for (p2 = p1 + 1; p2 < s.size() && s[p2] != '+' && s[p2] != '-'; ++p2);
        auto nn = stoi(s.substr(p + 1, p1 - p - 1)), dd = stoi(s.substr(p1 + 1, p2 - p1 - 1));
        auto gcd = GCD(d, dd);
        n = n * dd / gcd + (s[p] == '-' ? -1 : 1) * nn * d / gcd;
        d *= dd / gcd;
        p = p2;
    }
    auto gcd = GCD(abs(n), d);
    return to_string(n / gcd) + "/" + to_string(d / gcd);
}

//######################################## pytonic  ########################################
//math.gcd : Python3
//def fractionAddition(self, expression):
//    ints = map(int, re.findall('[+-]?\d+', expression))
//    A, B = 0, 1
//    for a in ints:
//        b = next(ints)
//        A = A * b + a * B
//        B *= b
//        g = math.gcd(A, B)
//        A //= g
//        B //= g
//    return '%d/%d' % (A, B)
//
//

//######################################## with reduction ########################################
//class Solution(object):
//    def fractionAddition(self, S):
//        from fractions import Fraction
//        ans = Fraction(0, 1)
//        left = count = 0
//        for right, symbol in enumerate(S):
//            if (right == len(S) - 1 or
//                    symbol.isdigit() and not S[right + 1].isdigit()):
//                count ^= 1
//                if not count:
//                    ans += Fraction(*map(int, S[left: right+1].split('/')))
//                    left = right + 1
//
//        return "{}/{}".format(ans.numerator, ans.denominator)
//
//
//
//
//######################################## with reduction ugly ########################################
//Evidently, we have 2 parts to our problem:
//1. Break our string into separate tokens which represent one fraction each
//2. Add the fractions together, keeping it in reduced form
//Let's decide how we want to break our string into tokens. Immediately after
//we see the second digit region, we know the first fraction must end there. To
//know whether we ended a digit region, we can look for a digit followed by a
//non-digit (or we are at the end of the string). Thus, every 2 digit regions,
//we'll report the token we've found. That token is something like "-10/3",
//which we'll convert into the integer tuple (-10, 3) representing fraction
//(-10 / 3).
//class Solution(object):
//    def fractionAddition(self, S):
//        def iter_tokens(S):
//            left = 0
//            count = 0
//            for right, symbol in enumerate(S):
//                if (right == len(S)-1 or
//                        symbol.isdigit() and not S[right + 1].isdigit()):
//                    count += 1
//                    if count % 2 == 0:
//                        yield map(int, S[left: right+1].split('/'))
//                        left = right + 1
//#To add two fractions (a, b) and (c, d) together, we convert to a common denominator bd, so the fraction is (ad + bc, bd). To keep fraction (x, y) reduced, we should divide both the numerator and denominator by their greatest common divisor. We can finish as follows:
//        def gcd(a, b):
//            if a == 0: return b
//            return gcd(b%a, a)
//        def add((an, ad), (bn, bd)):
//            n = an * bd + bn * ad
//            d = ad * bd
//            g = gcd(n, d)
//            return n/g, d/g
//        return "{}/{}".format(*reduce(add, iter_tokens(S)))

//######################################## JAVA  ########################################
//public String fractionAddition(String expression) {
//    Scanner sc = new Scanner(expression).useDelimiter("/|(?=[-+])");
//    int A = 0, B = 1;
//    while (sc.hasNext()) {
//        int a = sc.nextInt(), b = sc.nextInt();
//        A = A * b + a * B;
//        B *= b;
//        int g = gcd(A, B);
//        A /= g;
//        B /= g;
//    }
//    return A + "/" + B;
//}
//
//private int gcd(int a, int b) {
//    return a != 0 ? gcd(b % a, a) : Math.abs(b);
//}
