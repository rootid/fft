//Nested List Weight Sum II
//Given a nested list of integers, return the sum of all integers in the list weighted by their depth.
//Each element is either an integer, or a list -- whose elements may also be integers or other lists.
//Different from the previous question where weight is increasing from root to leaf, now the weight is defined from bottom up. i.e., the leaf level integers have weight 1, and the root level integers have the largest weight.
//Example 1:
//Given the list [[1,1],2,[1,1]], return 8. (four 1's at depth 1, one 2 at depth 2)
//Example 2:
//Given the list [1,[4,[6]]], return 17. (one 1 at depth 3, one 4 at depth 2, and one 6 at depth 1; 1*3 + 4*2 + 6*1 = 17)
//
//
//

//################################################### 2 DFS ###################################################
//[1,1], 2, [1,1]
//cnstrnt : 1. lvl? , elem in lvls?
//2. lst in mem?
//-ve?
//Ida
//1. DFS -> lvl add(l1) -> l1 + add(l2) ->
//2. BFS
//DFS ->
//1. compute length O(n)
//2. compute sum O(n)
public int depthSumInverse(List<NestedInteger> nestedList) {
    int maxLvl = getMaxLvl(nestedList);
    return depthSumInverseHelper(nestedList, maxLvl);
}

private int getMaxLvl(List<NestedInteger> nsL) {
    int mxLvl = 0;
    if(nsL == null && nsL.size() == 0) return 0;
    for(NestedInteger nsi: nsL) {
        if(nsi.isInteger()) mxLvl = Math.max(mxLvl, 1); // No chng in lvl wn int found
        else mxLvl = Math.max(mxLvl, getMaxLvl(nsi.getList()) + 1);  //chng in lvl wn lst found
     }
    return mxLvl;
}

private int depthSumInverseHelper(List<NestedInteger> nsL, int lvl) {
    int result = 0;
    for(NestedInteger nsi: nsL) {
        if(nsi.isInteger()) result += (lvl * nsi.getInteger());
        else result += depthSumInverseHelper(nsi.getList(), lvl - 1);
    }
    return result;
}

//################################################### Only addition + T: O(n) + Iterative ###################################################
//Instead of multiplying by depth, add integers multiple times (by going level by level and adding the unweighted sum to the weighted sum after each level).
public int depthSumInverse(List<NestedInteger> nestedList) {
  int unweighted = 0, weighted = 0;
  while (!nestedList.isEmpty()) {
    List<NestedInteger> nextLevel = new ArrayList<>();
    for (NestedInteger ni : nestedList) {
      if (ni.isInteger()) {
        unweighted += ni.getInteger();
      } else nextLevel.addAll(ni.getList());
    }
    weighted += unweighted;
    nestedList = nextLevel;
  }
  return weighted;
}

//################################################### addition + T: O(n) + Recursion ###################################################
public int depthSumInverse(List<NestedInteger> nestedList) {
	return helper(nestedList, 0);
}

private int helper(List<NestedInteger> nestedList, int sum){
	List<NestedInteger> nextList = new ArrayList();
    for(NestedInteger nestedInt: nestedList){
        if(nestedInt.isInteger()){
            sum += nestedInt.getInteger();
        }else{
            nextList.addAll(nestedInt.getList());
        }
    }
	//From the first layer to the nth layer, each recursion, the previous sum is added once again
    sum += nextList.isEmpty()? 0 : helper(nextList, sum);
    return sum;
}

//################################################### Multiplication + T: O(n) + Recursion ###################################################
//2 *3 + 6*3 = 3 *(2+6)
class Solution {
public:
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        vector<int> result; //store the
        for(auto ni : nestedList) {
            dfs(ni, 0, result);
        }
        //post processing
        int sum = 0;
        for(int i = result.size()-1,level = 1; i >=0; i--, level++) {
            sum += result[i]*level;
        }
        return sum;
    }

private:
    void dfs(NestedInteger &ni, int depth, vector<int> & result) {
        if(result.size() < depth+1) result.resize(depth+1);
        if(ni.isInteger()) {
            result[depth] += ni.getInteger(); //add the numbers levelwise
        } else {
            for(auto n_ni : ni.getList()) {
                dfs(n_ni, depth+1, result);
            }
        }
    }
};


//################################################### Addition + T: O(n) + S :O(n) + BFS  ###################################################
public int depthSumInverse(List<NestedInteger> nestedList) {
        if (nestedList == null) return 0;
        Queue<NestedInteger> queue = new LinkedList<NestedInteger>();
        int prev = 0;
        int total = 0;
        for (NestedInteger next: nestedList) {
            queue.offer(next);
        }
        while (!queue.isEmpty()) {
            int size = queue.size();
            //int currentLevelSum = 0;
            for (int i = 0; i < size; i++) {
                NestedInteger current = queue.poll();
                if (current.isInteger()) {
					prev += current.getInteger();
				}
                List<NestedInteger> nextList = current.getList();
                if (nextList != null) {
                    for (NestedInteger next: nextList) {
                        queue.offer(next);
                    }
                }
            }
            //prev += currentLevelSum;
            total += prev;
        }
        return total;
    }

//######################################### Python  #########################################
//######################################### 2 Pass #########################################
class Solution(object):
    def depthSumInverse(self, nestedList):
        maxDeep = self.dfsDeep(nestedList)
        return self.dfsHelper(nestedList, 1, maxDeep)

    def dfsDeep(self, nestedList):
        if len(nestedList) == 1 and nestedList[0].isInteger():
            return 1
        deep = 0
        for nInt in nestedList:
            if nInt.isInteger():
                deep = max(deep, 1)
            else:
                deep = max(self.dfsDeep(nInt.getList()) + 1, deep)
        return deep

    def dfsHelper(self, nestedList, level, maxDeep):
        if len(nestedList) == 1 and nestedList[0].isInteger():
            return (maxDeep - level + 1) * nestedList[0].getInteger()
        s = 0
        for nInt in nestedList:
            if nInt.isInteger():
                s += (maxDeep - level + 1) * nInt.getInteger()
            else:
                s += self.dfsHelper(nInt.getList(), level + 1, maxDeep)
        return s


