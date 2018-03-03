//Mini Parser
//Given a nested list of integers represented as a string, implement a parser
//to deserialize it.
//Each element is either an integer, or a list -- whose elements may also be
//integers or other lists.
//Note: You may assume that the string is well-formed:
//String is non-empty.
//String does not contain white spaces.
//String contains only digits 0-9, [, - ,, ].
//Example 1:
//Given s = "324",
//You should return a NestedInteger object which contains a single integer 324.
//Example 2:
//Given s = "[123,[456,[789]]]",
//Return a NestedInteger object containing a nested list with 2 elements:
//1. An integer containing value 123.
//2. A nested list containing two elements:
//    i.  An integer containing value 456.
//    ii. A nested list with one element:
//         a. An integer containing value 789.
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
//the add() method adds a NestedInteger object to the caller. e.g.:
//outer = NestedInteger() # []
//nested = NestedInteger(5)
//outer2 = nested
//outer.add(nested) # outer is now [5]
//outer2.add(outer) # outer2 is now [5, [5]]
//"Set this NestedInteger to hold a nested list and adds a nested integer elem to it." cannot be more vague.
//'-' means negative. It's not a delimiter.
//For test cases like "324" you need to return something like
//NestedInteger(324) not "[324]".
//A list cannot have multiple consecutive integers. e.g. "321, 231" is invalid.
//I guess it's for difficulty purposes


//################################################################  Recursion ################################################################
 NestedInteger deserialize(string s)
    {
        // end condition
        if (s.empty()) return NestedInteger(); // empty string
        if (s[0] != '[') return NestedInteger(stoi(s)); // number string

        NestedInteger res;
        for (int i = 1; i < s.size();)
        {
            // value ni OR list ni
			if (isNumber(s[i]) || s[i] == '[')
			{
				int j = i; // end of substring for recursion

				if (isNumber(s[i])) // value ni
					while (isNumber(s[j])) ++j; // end of number string

				if (s[i] == '[') // list ni
				{
					int cnt = 1;
					while (cnt > 0) { ++j; cnt = s[j] == '[' ? cnt + 1 : s[j] == ']' ? cnt - 1 : cnt; } // pos of correspondent ']'
				}

				res.add(deserialize(s.substr(i, j - i)));
				i = j;
			}
			else
                ++i;
        }
        return res;
    }

    bool isNumber(char c) { return isdigit(c) || c == '-'; }

//################################################  Recursion ################################################
NestedInteger deserialize(string s) {
   if (s.empty())
       return NestedInteger();
   if (s[0] != '[') {
       return NestedInteger(stoi(s));
   }
   int len = s.size(), i = 1;
   NestedInteger num;
   while (i < len - 1) {
       if (s[i] == '[') {
           int cnt = 1, j = i + 1;
           //validate for invalid parenthesis [[]]]
           while (cnt) {
               if (s[j] == '[')
                   cnt++;
               else if (s[j] == ']')
                   cnt--;
               j++;
           }
           num.add(deserialize(s.substr(i, j - i)));
           i = j; //update i
       } else if (s[i] == ',') {
           i++;
           continue;
       } else {
           int j = i + 1;
           while (j < n - 1 && s[j] != ',')
               j++;
           num.add(deserialize(s.substr(i, j - i)));
           i = j; //update i
       }
   }
   return num;
}

//################################################  Iterative ################################################
NestedInteger deserialize(string s) {
        if (!s.empty() && s[0] != '[') return stoi(s);

        NestedInteger result;
        stack<NestedInteger> st;
        bool hasNum = false;
        int num = 0, sign = 1;

        for (int i = 1; i < s.size(); i++) {
            char c = s[i];
            if (isdigit(c)) {
                num = num * 10 + c - '0';
                hasNum = true;
            }
            if (c == '-') {
                sign = -1;
            }
            if (c == '[') { // push current NestedInteger to stack and start a new one.
                st.push(result);
                result = NestedInteger();
            }
            if (c == ']') { // end current NestedInteger and pop a NestedInteger from stack to continue
                if (hasNum) {
                    result.add(NestedInteger(sign * num));
                }
                if (!st.empty()) {
                    st.top().add(result);
                    result = st.top();
                    st.pop();
                }
                hasNum = false; num = 0; sign = 1;
            }
            if (c == ',') { // append a new number to curr NestedInteger
                if (hasNum) {
                    result.add(NestedInteger(sign * num));
                }
                hasNum = false; num = 0; sign = 1;
            }
        }
        return result;
    }

