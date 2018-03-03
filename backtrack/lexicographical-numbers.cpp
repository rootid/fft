//Lexicographical Numbers
//Given an integer n, return 1 - n in lexicographical order.
//For example, given 13, return: [1,10,11,12,13,2,3,4,5,6,7,8,9].
//Please optimize your algorithm to use less time and space. The input size may
//be as large as 5,000,000.

#include<iostream>

//############################### DFS #####################
List<Integer> lst = new ArrayList<>();

private void generate(int k, int n) {
    if(k > n) return;
    lst.add(k);
    for(int j=0;j<=9;j++) {
        if(10 * k + j > n)  break;
        generate(10 * k + j, n);
    }
}

public List<Integer> lexicalOrder(int n) {
    for(int i=1;i<=9;i++) {
        generate(i, n);
    }
    return lst;
}

//############################### DFS GOOD #####################
vector<int> lexicalOrder(int n) {
    vector<int> res;
    for(int i=1;i<10;++i){
      dfs(i, n, res);
    }
    return res;
}

void dfs(int cur, int n, vector<int>& res) {
    if(cur > n) {
        return;
    } else {
        res.push_back(cur);
        for(int i=0;i<10;++i){
            if(10*cur+i>n) {
                return;
            }
            dfs(10*cur+i, n, res);
        }
    }
}

//########################## Good Explicit stack ##########################
vector<int> lexicalOrder(int n) {
    stack<int> nums;
    nums.push(0);
    int i;
    vector<int> result;
    while (!nums.empty()) {
        //get a new number
        i= nums.top() + 1;
        nums.pop();
        if (i%10 == 0 ) {
          continue;
        }
        //then try to go up
        while (i <=n ){
            result.emplace_back(i);
            nums.push(i); //1,10,11,12
            i *= 10;
        }
    }
    return result;
}

vector<int> lexicalOrder(int n) {
    vector<int> result(n);
    int* first = &result[0];
    iota(first, first + n, 1);
    for (int ok = 9; ok < n; ok = 10*ok+9)
        inplace_merge(first,
                      first + ok,
                      first + min(ok*10+9, n),
                      [ok](int a, int b){
                          while (b <= ok) b *= 10;
                          return a < b;
                      });
    return result;
}
//Observations:
//For any given digit k, the lexical order of all numbers starting with digit k
//looks like:
//
//k, k×10, k×10^2, k×10^3, ..., k×10^p +1, k×10^p + 2, ..., k×10^(p-m) +1, ...
//
//For example, the sequence of numbers starting with digit 1 will be like (with
//n = 2000):
//
//1, 10, 100, 1000, 1001, 1002, ..., 1009, 101, 1010, 1011, 1012, ..., 1019,
//102, 1020, ..., 1099, 11, 110, 1100, 1101, ...
//
//Through the observations above, a valid sub-sequence can only be started when
//we 1) cannot append more zeroes to the previous number; or 2) encounter a
//number that ends in consecutive '9's.
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> rs;

        int i = 1, j;
        int k;
        for(;;)
        {
            // append as many zeroes as possible to the previous number
            for(k = 0; i*pow(10,k) <= n; ++k) rs.push_back(i*pow(10,k));

            // count continuously until we reach a number that ends with consecutive '9's
            for(j = rs.back()+1; j <= n && (j % 10) != 0; ++j) rs.push_back(j);

            // backtrace
            if(j % 10 == 0)
            {
                j--;
            }
            else
            {
                j /= 10;
            }
            // find the last non-'9' digit
            while(j % 10 == 9) j /= 10;

            // start a new sub-sequence
            i = j+1;

            if(rs.size() >= n) break;
        }
        return rs;
    }
};
