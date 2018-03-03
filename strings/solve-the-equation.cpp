//Solve the Equation
//Solve a given equation and return the value of x in the form of string "x=#value". The equation contains only '+', '-'
//operation, the variable x and its coefficient.
//If there is no solution for the equation, return "No solution".
//If there are infinite solutions for the equation, return "Infinite solutions".
//If there is exactly one solution for the equation, we ensure that the value of x is an integer.
//Example 1:
//Input: "x+5-3+x=6+x-2"
//Output: "x=2"
//Example 2:
//Input: "x=x"
//Output: "Infinite solutions"
//Example 3:
//Input: "2x=x"
//Output: "x=0"
//Example 4:
//Input: "2x+3x-6x=x+2"
//Output: "x=-1"
//Example 5:
//Input: "x=x+2"
//Output: "No solution"

//######################################### Traversal O(n) #########################################
//the coefficient of x and the total sum. On the left and right side of '=',
//we have to use opposite signs for each numbers, so I define a sign variable, which will flip if '=' is seen.
string solveEquation(string equation) {
     //coeff : value of x
     int n = equation.size(), sign = 1, coeff = 0, tot = 0, i = 0;
     //evaluate equation
     //update total
     for (int j = 0; j < n; j++) { //R-L traversal
         if (equation[j] == '+' || equation[j] == '-') {
             if (j > i) {
               tot += sign*stoi(equation.substr(i, j-i));
             }
             i = j;
         }
     	 //update coeff
         // corner case: x, -x, +x
         else if (equation[j] == 'x') {
             if ((i == j) || equation[j-1] == '+')
                 coeff += sign;
             else if (equation[j-1] == '-')
                 coeff -= sign;
             else
                 coeff += sign*stoi(equation.substr(i, j-i));
             i = j+1;
         }
     	 //update coeff
        // flip sign
         else if (equation[j] == '=') {
             if (j > i) {
               tot += sign*stoi(equation.substr(i, j-i));
             }
             sign = -1; //flip the sign in case of RHS side
             i = j+1;
         }
     }
     // there may be a number in the end
     if (i < n) tot += sign*stoi(equation.substr(i));
     if (coeff == 0 && tot == 0) return "Infinite solutions";
     if (coeff == 0 && tot) return "No solution";
     int ans = -tot/coeff;
     return "x="+to_string(ans);
 }


//######################################### Regex O(n) #########################################

private :
  pair<int, int> coef(string s) {
      // split the side into form of (+/-)123x
      auto e = regex("(^|[+-])\\d+x?");
      regex_token_iterator<string::iterator> it(s.begin(), s.end(), e), end;

      int a = 0, b = 0;
      for (; it != end; it++)
          (it->str().back() == 'x' ? a : b) += stoi(*it);

      return {a, b};
  }

public :
  string solveEquation(string equation) {
      // normalize the equation, add 1 for x's which have no coefficient: x => 1x
      equation = regex_replace(equation, regex("(^|[+=-])x"), "$011x");

      // calculate coefficients for both sides
      auto pos = equation.find('=');
      auto l = coef(equation.substr(0, pos));
      auto r = coef(equation.substr(pos + 1));

      // l.first x + l.second = r.first x + r.second => ax = b
      int a = l.first - r.first, b = r.second - l.second;

      return a != 0 ? "x=" + to_string(b/a) : b != 0 ? "No solution" : "Infinite solutions";
  }

//######################################### pytonic #########################################
//
//

//It's easy to change an equation like 2+3x=5x-7 to an expression for a complex number like 2+3i-(5i-7). Then I let Ruby
//evaluate that and it gives me the total of "x numbers" and the total of "non-x numbers" as the imaginary and real part
//of the complex number.
//Same in Python:
//def solveEquation(self, equation):
//    z = eval(equation.replace('x', 'j').replace('=', '-(') + ')', {'j': 1j})
//    a, x = z.real, -z.imag
//    return 'x=%d' % (a / x) if x else 'No solution' if a else 'Infinite solutions'
//And here's a completely different one using a regular expression to parse the tokens:
//
//def solveEquation(self, equation):
//    x = a = 0
//    side = 1
//    for eq, sign, num, isx in re.findall('(=)|([-+]?)(\d*)(x?)', equation):
//        if eq:
//            side = -1
//        elif isx:
//            x += side * int(sign + '1') * int(num or 1)
//        elif num:
//            a -= side * int(sign + num)
//    return 'x=%d' % (a / x) if x else 'No solution' if a else 'Infinite solutions'



//
//Before the program, here's a small example for the equation : x+5-3+x=6+x-2
//LHS: x+5-3+x
//RHS: 6+x-2
//LHS coefficients: ['x', 'x']
//RHS coefficients: ['x']
//Just the numbers on the LHS ['', '', '5', '-3', '', '', '']
//Just the numbers on the RHS ['6', '', '', '-2', '']
//LHS SUM of the numbers: 2
//RHS SUM of the numbers: 4
//LHS Coeff sum: 2
//RHS Coeff sum: 1
//Final Answer: x=2
//Coefficients are defined by the following regex
//'-?\d*x'
//-? - An optional negative sign
//\d* - 0 or more digits
//x - literal x
//Regex for number:
//'-?\d*' Again, this is as explained above.

//def solveEquation(self, equation):
//        """
//        :type equation: str
//        :rtype: str
//        """
//        # define the patterns
//        co_p = re.compile('-?\d*x')
//        num_p = re.compile('-?\d*')
//        # split the 2 parts of the equation.
//        lhs = equation.split('=')[0]
//        rhs = equation.split('=')[1]
//        # find the list of coefficients with x(in both lhs and rhs)
//        lhs_co = co_p.findall(lhs)
//        rhs_co = co_p.findall(rhs)
//        # find the list of all signed numbers after removing the coefficient
//        # Notice that, I replace the coeffiecients with an '*' symbol to extract the remaining numbers.
//        # And I retrieve the numbers with the sign.
//        lhs_num_list = num_p.findall(re.sub('-?\d*x', '*', lhs))
//        rhs_num_list = num_p.findall(re.sub('-?\d*x', '*', rhs))
//        # Now, simply add the numbers on the LHS and RHS
//        lhs_sum = 0
//        rhs_sum = 0
//        for i in lhs_num_list:
//            if i:
//                lhs_sum += int(i)
//        for i in rhs_num_list:
//            if i:
//                rhs_sum += int(i)
//        # Add the Coefficients on both LHS and RHS.
//        lhs_coeff_sum = 0
//        rhs_coeff_sum = 0
//        # While adding coefficients, 'x' and '-x' wil be replaced by 1 and -1 respectively.
//        for i in lhs_co:
//                i = i.replace('x', '')
//                if not i:
//                    i = 1
//                elif i == '-':
//                    i = -1
//                lhs_coeff_sum += int(i)
//        for i in rhs_co:
//                i = i.replace('x', '')
//                if not i:
//                    i = 1
//                elif i == '-':
//                    i = -1
//                rhs_coeff_sum += int(i)
//        # Now, this is simple math and check the conditions to handle the edge cases.
//        if lhs_sum == rhs_sum and lhs_coeff_sum == rhs_coeff_sum:
//            return "Infinite solutions"
//        if lhs_coeff_sum == rhs_coeff_sum:
//            return "No solution"
//        result = (rhs_sum - lhs_sum) / (lhs_coeff_sum - rhs_coeff_sum)
//        return "x=" + str(result)

// vim: set sw=2 sts=2 tw=120 et nospell :
