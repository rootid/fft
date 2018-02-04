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


//################################################### Backtracking ###################################################
//Add 2 elements at a time
//Oprimized and efficient
public class Solution {
    List<List<Integer>> ans = new ArrayList<>();

    public List<List<Integer>> getFactors(int n) {
        getFactors(n, 2, new ArrayList<>());
        return ans;
    }

    private void getFactors(int n, int s, List<Integer> path) {
        for (int i = s; i * i <= n; ++i) {
            if (n % i == 0) {
                path.add(i);
                getFactors(n / i, i, path);
                path.add(n / i);
                ans.add(new ArrayList<>(path));
                path.remove(path.size() - 1);
                path.remove(path.size() - 1);
            }
        }
    }

}

//################################################### Backtracking ###################################################
//Add 1 element at a time
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
            item.add(i);
            helper(result, item, n/i, i);
            item.remove(item.size()-1);
        }
    }
}

//################################################### Backtracking ###################################################
class Solution {
    //cnstrnt :
    //1. upp lt n ?
    //2. return srted (# of factors)

    //1. Ida : get prime lst < n and the number list -> list of all primes - >
    // prbmls :     //how to avvoid duplicates
    //2. Start from 2 and iterate over combination
    public List<List<Integer>> getFactors(int n) {
        List<List <Integer> > result = new ArrayList<>();
        List<Integer> primes = getPrimeNumberList(n);
        if(primes.size() < 1) return result;
        Set<Integer> primeSet = new HashSet<>(primes);
        List<Integer> ltPrimes = new LinkedList<>();
        getFactorHelper(n, primes, primeSet, ltPrimes, result);
        return result;
    }

    private void getFactorHelper(int n, List<Integer> primes,
                                 Set<Integer> primeSet, List<Integer> ltPrimes, List<List<Integer>> result) {

        List<Integer> tmp = new ArrayList<>();
        if(!primeSet.contains(n))  {
        //32 -> 2,16 -> 2,2,8
            for(int i=0;i<primes.size();i++) {
                int p = primes.get(i);
                if(n%p == 0) {
                    ltPrimes.add(p);
                    getFactorHelper(n/p, primes, primeSet,ltPrimes, result);
                    result.add(new ArrayList (ltPrimes));
                    result.get(result.size() - 1).add(n/p);
                    result.get
                    ltPrimes.remove(ltPrimes.size() - 1);


                }
            }
        }

    }

    private boolean isPrime(int n) {
        for(int i=2;i<n-1;i++) if(n%i == 0) return false;
        return true;
     }
    private List<Integer> getPrimeNumberList(int n) {
        List<Integer> lst = new ArrayList<>();
        for(int i = 2;i < n;i++) {
            if(isPrime(i)) lst.add(i);
        }
        return lst;
    }
}

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


