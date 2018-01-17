//Complex Number Multiplication
//Given two strings representing two complex numbers.
//You need to return a string representing their multiplication. Note i2 = -1 according to the definition.
//Example 1:
//Input: "1+1i", "1+1i"
//Output: "0+2i"
//Explanation: (1 + i) * (1 + i) = 1 + i2 + 2 * i = 2i, and you need convert it to the form of 0+2i.
//Example 2:
//Input: "1+-1i", "1+-1i"
//Output: "0+-2i"
//Explanation: (1 - i) * (1 - i) = 1 + i2 - 2 * i = -2i, and you need convert it to the form of 0+-2i.
//Note:
//The input strings will not have extra blank.
//The input strings will be given in the form of a+bi, where the integer a and b will both belong to the range of [-100, 100]. And the output should be also in this form.

//################################ O(n) + parse with find ################################ 
string complexNumberMultiply(string a, string b) {
     pair<int, int> av = parse(a);
     pair<int, int> bv = parse(b);
     int ra = av.first * bv.first - av.second * bv.second; //a.r*b.r - a.i*b.i
     int rb = av.first * bv.second + av.second * bv.first; //a.r*b.i + a.i*b.r
     return to_string(ra) + "+" + to_string(rb) + "i";
}

pair<int, int> parse(const string& a) {
    int plus = find(a.begin(), a.end(), '+') - a.begin(); 
    int i = find(a.begin(), a.end(), 'i') - a.begin();
    int ra = stoi(a.substr(0, plus));
    int ia= stoi(a.substr(plus + 1, i - plus));
    return {ra, ia};
}

//################################ O(n) + parse with stringsteram ################################ 
string complexNumberMultiply(string a, string b) {
     int ra, ia, rb, ib;
     char buff;
     stringstream aa(a), bb(b), ans;
     aa >> ra >> buff >> ia >> buff;
     bb >> rb >> buff >> ib >> buff;
     ans << ra*rb - ia*ib << "+" << ra*ib + rb*ia << "i";
     return ans.str();
}

//################################ O(n) + parse w/o new utils################################ 
vector<int> getNums(string s) {
    int i=0;
    while(s[i]!='+') ++i;
    int x = stoi(s.substr(0, i));
    int y = stoi(s.substr(i+1, s.length()-1));
    return vector<int> ({x, y});
}
string complexNumberMultiply(string a, string b) {
    vector<int> A = getNums(a);
    vector<int> B = getNums(b);
    return to_string(A[0]*B[0] - A[1]*B[1]) + "+" + to_string(A[0]*B[1] + A[1]*B[0]) + "i";
}

//################################ O(n) + Lame parse ################################ 
string complexNumberMultiply(string a, string b) {
    auto A = getNum(a);
    auto B = getNum(b);
    int real = A.first * B.first + A.second * B.second * -1;
    int i = A.first * B.second + A.second * B.first;
    return to_string(real) + '+' + to_string(i) + 'i';
}

pair<int,int> getNum(string& s){
    if(s.empty()) return {};
    int real = 0, im = 0;
    int i = 0;
    int sign_r = 1, sign_im = 1;
    if(s[i] == '-'){
        sign_r = -1;
        i++;
    }else if(s[i] == '+'){i++;}
    while(isdigit(s[i])){
        real = real * 10 + (s[i++] - '0');
    }
    while(!isdigit(s[i])){
        if(s[i] == '-') sign_im = sign_im * -1;
        i++;
    }
    while(s[i] != 'i'){
        im = im * 10 + (s[i++] - '0');
    }
    
    return {real * sign_r, im * sign_im};
}

//################################ pytonic ################################ 
//class Solution(object):
//    def complexNumberMultiply(self, a, b):
//        a = a.split("+")
//        b = b.split("+")
//        first = int(a[0]) * int(b[0]) - int(a[1][:-1]) * int(b[1][:-1])
//        second = int(a[0]) * int(b[1][:-1]) + int(b[0]) * int(a[1][:-1])
//        return str(first) + "+" + str(second) + "i"
//
//def complexNumberMultiply(self, a, b):
//        a, ai, b, bi = map(int, (a[:-1] + '+' + b[:-1]).split('+'))
//        return '%d+%di' % (a * b - ai * bi, a * bi + ai * b)
//
//def complexNumberMultiply(self, a, b):
//    z = eval(('(%s)*(%s)' % (a, b)).replace('i', 'j'))
//    return '%d+%di' % (z.real, z.imag)
//
//def complexNumberMultiply(self, a, b):
//    a, ai, b, bi = map(int, re.findall('-?\d+', a+b))
//    return '%d+%di' % (a*b - ai*bi, a*bi + ai*b)
