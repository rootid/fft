//Factor Combinations
//Numbers can be regarded as product of its factors. For example,
//8 = 2 x 2 x 2;
//  = 2 x 4.
//Write a function that takes an integer n and return all possible combinations of its factors.
//Note: 
//Each combination's factors must be sorted ascending, for example: The factors of 2 and 6 is [2, 6], not [6, 2].
//You may assume that n is always positive.
//Factors should be greater than 1 and less than n.
//Examples: 
//input: 1
//output: 
//[]
//input: 37
//output: 
//[]
//input: 12
//output:
//[
//  [2, 6],
//  [2, 2, 3],
//  [3, 4]
//]
//input: 32
//output:
//[
//  [2, 16],
//  [2, 2, 8],
//  [2, 2, 2, 4],
//  [2, 2, 2, 2, 2],
//  [2, 4, 4],
//  [4, 8]
//]

//################################################### Backtracing  ################################################### 
class Solution {
    public:
        void getResult(vector<vector<int>> &result,vector<int> &row,int n){
            int i=row.empty()?2:row.back();
            for(;i<=n/i;++i){
                if(n%i==0){
                    row.push_back(i);
                    row.push_back(n/i);
                    result.push_back(row);
                    row.pop_back();
                    getResult(result,row,n/i);
                    row.pop_back();
                }
            }
        }
    
        vector<vector<int>> getFactors(int n) {
            vector<vector<int>> result;
            vector<int>row;
            getResult(result,row,n);
            return result;
        }
    };

//################################################### Backtracing  ################################################### 
void helper(int n, int start, vector<int> out, vector<vector<int>> &res) { 
	if (n == 1) { //stop the search when found 1
        if (out.size() > 1) 
			res.push_back(out);
    } else {
        for (int i = start; i <= n; ++i) {
            if (n % i == 0) {
                out.push_back(i); 
                helper(n / i, i, out, res); //get the remainder and iterate
                out.pop_back();
            }
        }
    }
}
vector<vector<int>> getFactors(int n) { 
	vector<vector<int>> res;
    helper(n, 2, {}, res);
    return res; 
}


//################################################### Backtracing  ################################################### 
public List<List<Integer>> getFactors(int n) { 
	List<List<Integer>> ans = new ArrayList<>();
    helper(n, 2, ans, new ArrayList<>());
    return ans; 
}
private void helper(int n, int m, List<List<Integer>> ans, List<Integer> cur) {
     for (int i = m; i <= n/i; ++i) {
         if (n % i > 0) continue; //not a valid factor
         List<Integer> sub = new ArrayList<>(cur);
         sub.add(i); //factor 
         sub.add(n / i); //remainder
         ans.add(sub); 
         cur.add(i); //holds current factors
         helper(n / i, i, ans, cur);
         cur.remove(cur.size() - 1);
     };
}

//################################################### Backtracing  ################################################### 
public List<List<Integer>> getFactors(int n) {
    List<List<Integer>> result = new ArrayList<List<Integer>>();
    helper(result, new ArrayList<Integer>(), n, 2);
    return result;
}

public void helper(List<List<Integer>> result, List<Integer> item, int n, int start){
    if (n <= 1) {
        if (item.size() > 1) {
            result.add(new ArrayList<Integer>(item));
        }
        return;
    }
    for (int i = start; i <= n; ++i) {
        if (n % i == 0) {
			//you have a for loop go from say 2 to 12 right? once you go [2, 2, 3], you get one combination, 
			//then you need to go back to the for loop to try the larger numbers, 
			//so you need to remove the newly added numbers 
			//so you will be able to try 2 3 and 2 4 and 2 5 until you find [2, 6] which is another combination
            item.add(i);
            helper(result, item, n/i, i);
            item.remove(item.size()-1);
        }
    }
}

//################################################### Python  ################################################### 
//################################################### Iterative ################################################### 
def getFactors(self, n):
    todo, combis = [(n, 2, [])], []
    while todo:
        n, i, combi = todo.pop()
        while i * i <= n:
            if n % i == 0:
                combis += combi + [i, n/i],
                todo += (n/i, i, combi+[i]),
            i += 1
    return combis

//################################################### Recursive ################################################### 
def getFactors(self, n):
    def factor(n, i, combi, combis):
        while i * i <= n:
            if n % i == 0:
                combis += combi + [i, n/i],
                factor(n/i, i, combi+[i], combis)
            i += 1
        return combis
    return factor(n, 2, [], [])


