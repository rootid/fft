//Given a collection of distinct numbers, return all possible permutations.
//For example,
//[1,2,3] have the following permutations:
//[
//  [1,2,3],
//  [1,3,2],
//  [2,1,3],
//  [2,3,1],
//  [3,1,2],
//  [3,2,1]
//]



#include "../headers/global.hpp"

//##################################### Recursive insert version #####################################
//Each iteration create a new copy of list by picking next element
//Took space and more efficent
public List<List<Integer>> permute(int[] nums) {
    List<List<Integer>> result = new ArrayList<>();
    if (nums.length == 0) return result;
    backtrack(result, nums, new ArrayList<>(), 0);
    return result;
}

private void backtrack(List<List<Integer>> result, int[] nums, List<Integer> soFarList, int k) {
    if (k == nums.length) {
        result.add(soFarList);
        return ;
    }
    for (int i = 0; i <= soFarList.size(); i++) { //insert elment at start
        List<Integer> copy = new ArrayList<>(soFarList);
        copy.add(i, nums[k]); //k is the level/depth
        backtrack(result, nums, copy, k + 1); //increase the depth
    }
}

//##################################### Recursive insert version #####################################
class Solution {

   public List<List<Integer>> permute(int[] nums) {
      List<List<Integer>> result = new ArrayList<>();
      if (nums.length == 0) return result;
      backtrack(result, nums, new ArrayList<>(), 0);
      return result;
  }

  private void backtrack(List<List<Integer> > result, int[] nums, List<Integer> soFarList, int k) {
      if (k == nums.length) {
          result.add(new ArrayList(soFarList));
          return ;
      }
      for (int i = 0; i <= k; i++) {
          soFarList.add(i, nums[k]);
          backtrack(result, nums, soFarList, k + 1);
          soFarList.remove(i);
      }
  }
}

//##################################### Recursive Swap version #####################################
//Not effcient
class Solution {

    public List<List<Integer>> permute(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        permuteHelper(nums,0,result);
        return result;
    }

    public void permuteHelper(int[] nums,int k,List<List<Integer>> result) {

       Arrays.stream(nums).boxed().forEach(System.out::print);
       System.out.println("");
       int n = nums.length;
       if(k == n) result.add(new ArrayList(Arrays.stream(nums).boxed().collect(Collectors.toList())));
       for(int i=k;i<n;i++) { //n *  n-1 * n-2...
           doSwap(nums,i,k);
           permuteHelper(nums,k+1,result);
           doSwap(nums,k,i);
       }
    }

    private void doSwap(int[] nums,int i,int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
}

//##################################### Recursive version #####################################
//Recursive, take any number as first
def permute(self, nums):
    return [[n] + p
            for i, n in enumerate(nums)
            for p in self.permute(nums[:i] + nums[i+1:])] or [[]]

//Solution 2: Recursive, insert first number anywhere
//Insert the first number anywhere in any permutation of the remaining numbers.

def permute(self, nums):
    return nums and [p[:i] + [nums[0]] + p[i:]
                     for p in self.permute(nums[1:])
                     for i in range(len(nums))] or [[]]

//Solution 3: Reduce, insert next number anywhere
//Use reduce to insert the next number anywhere in the already built permutations.
def permute(self, nums):
    return reduce(lambda P, n: [p[:i] + [n] + p[i:]
                                for p in P for i in range(len(p)+1)],
                  nums, [[]])
//Solution 4: Using the library
def permute(self, nums):
    return list(itertools.permutations(nums))


def permute(self, nums):
        def gen(nums):
            n = len(nums)
            if n == 0 : yield []
            else:
                for i in range(n):
                    for cc in gen(nums[:i] + nums[i+1:]):
                        yield [nums[i]] + cc
        return list(gen(nums))

def permute(self, nums):
    def gen(nums):
        if not nums:
            yield []
        for i, n in enumerate(nums):
            for p in gen(nums[:i] + nums[i+1:]): #(0,i)  (i+1,n)
                yield [n] + p #current ele, rest
    return list(gen(nums))

//######################################### SoFar technique #########################################
void recSubsets(string soFar, string rest) {
   if (rest == "") cout << soFar << endl;
   else {
		// add to subset, remove from rest, recur
		recSubsets(soFar + rest[0], rest.substr(1));
		// don't add to subset, remove from rest,recur
		recSubsets(soFar, rest.substr(1));
  }
}
void listSubsets(string str) {
   recSubsets("", str);
}



//1,2,3
//##################################### Iterative version #####################################
vector<vector<int> > permute(vector<int>& nums) {

  vector< vector<int> > result;
  int len = nums.size();
  if(len == 0) {
    return result;
  }
  vector<int> l0;
  l0.push_back(nums[0]);
  result.push_back(l0);
  //iterate over elements
  for(int i=1;i<len;i++) {
    vector< vector<int> > tmp;
    //list of candidates/positions
    for(int j=0;j<=i;j++) {
      for(auto itr = result.begin();itr!=result.end();itr++) {
        vector<int> curr1(*itr); // copy the list into new vector
        curr1.insert(curr1.begin()+j,nums[i]); // insert num[i] at pos j
        tmp.push_back(curr1); // insert new list into tmp

      }
    }
    result = tmp;
  }
  return result;
}

//################################## Move + iteration #####################3
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> v(1,vector<int>());
    for (int i = 0; i < nums.size(); ++i) {
        vector<vector<int>> tv(move(v));
        for (int j = 0; j < tv.size(); ++j) {
            for (int k = 0; k <= tv[0].size(); ++k) {
                vector<int> tmp(tv[j]);
                tmp.insert(tmp.begin()+k,nums[i]);
                v.push_back(move(tmp));
            }
        }
    }
    return v;
}

//################################## iteration2 #####################3
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int> > ret;
    int n = nums.size();
    if (n == 0)
        return ret;
    if (n == 1) {
        ret.push_back(nums);
        return ret;
    }

    int i = 0, j = 0, len = 0;
    vector<int> curNums;
    vector<int> per;
    vector<vector<int>> temp;

    for (i = 0; i < n; i++) {
        curNums = nums;
        curNums.erase(curNums.begin()+i);
        temp = permute(curNums);
        len = temp.size();
        for (j = 0; j < len; j++) {
            per = temp[j];
            per.push_back(nums[i]);
            ret.push_back(per);
        }
    }
    return ret;
}

//######################### procedural recursion  #########################
private:
vector<vector<int> > v;
vector<int> save;
vector<bool> visit;
public:
  vector<vector<int> > permute(vector<int> &num) {
      v.clear();
      int size = num.size();

      visit.resize(size);
      save.resize(size);

      fill(visit.begin(), visit.end(), false);

      dfs(num, 0, size);
      return v;
  }
  void dfs(vector<int> num, int k,int size,vector<bool>& visit,vector<vector<int> >&result){
      if(k == size){
         result.push_back(save);
          return;
      }
      for(int i = 0; i < size; i++){
          if(!visit[i]){
              visit[i] = true;
              save[k] = num[i];
              dfs(num, k + 1, size);
              visit[i] = false;
          }
      }
  }

