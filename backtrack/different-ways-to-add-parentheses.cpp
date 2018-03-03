//Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.
//Example 1
//Input: "2-1-1".
//((2-1)-1) = 0
//(2-(1-1)) = 2
//Output: [0, 2]
//Example 2
//Input: "2*3-4*5"
//(2*(3-(4*5))) = -34
//((2*3)-(4*5)) = -14
//((2*(3-4))*5) = -10
//(2*((3-4)*5)) = -10
//(((2*3)-4)*5) = 10
//Output: [-34, -14, -10, -10, 10]

//1. Divide w/ symbols 2-> multiply to 3 or rest
//2. Combine the result

//#### Compute all operations ####
vector<int> diffWaysToCompute(string input) {
    vector<int> output;
    for (int i=0; i<input.size(); i++) {
        char c = input[i];
        if (ispunct(c))
            for (int a : diffWaysToCompute(input.substr(0, i)))
                for (int b : diffWaysToCompute(input.substr(i+1)))
                    output.push_back(c=='+' ? a+b : c=='-' ? a-b : a*b);
    }
    return output.size() ? output : vector<int>{stoi(input)};
}

//### Avoid duplicate operations ### hw 2 use pruning
vector<int> compute(string input, unordered_map<string, vector<int>>& str_to_vec){
     if(str_to_vec.find(input)!=str_to_vec.end())
         return str_to_vec[input];
     vector<int> res;
     for(int i=0; i<input.size(); ++i){
         if( ispunct(input[i]) )
             for(int a:compute(input.substr(0,i), str_to_vec))
                 for(int b:compute(input.substr(i+1), str_to_vec))
                     res.push_back(input[i]=='+'?a+b:input[i]=='-'?a-b:a*b );
     }
     return str_to_vec[input]=res.size()?res:vector<int>{stoi(input)};
}
vector<int> diffWaysToCompute(string input) {
     unordered_map<string, vector<int>> str_to_vec;
     return compute(input, str_to_vec);
}

//################# Recursion #################
vector<int> diffWaysToCompute(string input) {
		if(input.size()==0)return vector<int>();
        return solve(input);
}

vector<int> solve(string input){
  vector<int> ret;
  int i;
  for(i=0;i<input.length();i++)if(isOperator(input[i]))break;
  if(i==input.length()){
  		ret.push_back(atoi(input.c_str()));
  		return ret;
  }
      int st = 0;
  while(st<input.length()){
  	while(st<input.length()&&!isOperator(input[st]))st++;
  	if(st<input.length()){
  		vector<int> tmpLeft = solve(input.substr(0,st));
  		vector<int> tmpRight = solve(input.substr(st+1,input.length()-st-1));
  			for(int i=0;i<tmpLeft.size();i++)
  				for(int j=0;j<tmpRight.size();j++){
  					int x = operate(input[st],tmpLeft[i],tmpRight[j]);
  					ret.push_back(x);
  				}
  	}
  	st++;
  }
  return ret;
}

    bool isOperator(char c){
        return c=='+'||c=='-'||c=='*';
    }

	int operate(char c, int left, int right){
		switch(c){
			case '+': return left+right;
			case '-': return left-right;
			case '*': return left*right;
			default: return 0;
		}
		return 0;
	}


//######################## Recursive  ########################
  vector<int> diffWaysToCompute(string input) {
        vector<int> result;
        int size = input.size();
        for (int i = 0; i < size; i++) {
            char cur = input[i];
            if (cur == '+' || cur == '-' || cur == '*') {
                // Split input string into two parts and solve them recursively
                vector<int> result1 = diffWaysToCompute(input.substr(0, i));
                vector<int> result2 = diffWaysToCompute(input.substr(i+1));
                for (auto n1 : result1) {
                    for (auto n2 : result2) {
                        if (cur == '+')
                            result.push_back(n1 + n2);
                        else if (cur == '-')
                            result.push_back(n1 - n2);
                        else
                            result.push_back(n1 * n2);
                    }
                }
            }
        }
        // if the input string contains only number
        if (result.empty())
            result.push_back(atoi(input.c_str()));
        return result;
    }

//######################## DP ########################

	vector<int> diffWaysToCompute(string input) {
		unordered_map<string, vector<int>> dpMap;
		return computeWithDP(input, dpMap);
	}

	vector<int> computeWithDP(string input, unordered_map<string, vector<int>> &dpMap) {
		vector<int> result;
		int size = input.size();
		for (int i = 0; i < size; i++) {
			char cur = input[i];
			if (cur == '+' || cur == '-' || cur == '*') {
				// Split input string into two parts and solve them recursively
				vector<int> result1, result2;
				string substr = input.substr(0, i);
				// check if dpMap has the result for substr
				if (dpMap.find(substr) != dpMap.end())
					result1 = dpMap[substr];
				else
					result1 = computeWithDP(substr, dpMap);

				substr = input.substr(i + 1);
				if (dpMap.find(substr) != dpMap.end())
					result2 = dpMap[substr];
				else
					result2 = computeWithDP(substr, dpMap);

				for (auto n1 : result1) {
					for (auto n2 : result2) {
						if (cur == '+')
							result.push_back(n1 + n2);
						else if (cur == '-')
							result.push_back(n1 - n2);
						else
							result.push_back(n1 * n2);
					}
				}
			}
		}
		// if the input string contains only number
		if (result.empty())
			result.push_back(atoi(input.c_str()));
		// save to dpMap
		dpMap[input] = result;
		return result;
	}
