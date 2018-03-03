//Given a nested list of integers, return the sum of all integers in the list
//weighted by their depth.
//Each element is either an integer, or a list -- whose elements may also be
//integers or other lists.
//Example 1:
//Given the list [[1,1],2,[1,1]], return 10. (four 1's at depth 2, one 2 at
//depth 1)
//Example 2:
//Given the list [1,[4,[6]]], return 27. (one 1 at depth 1, one 4 at depth 2,
//and one 6 at depth 3; 1 + 4*2 + 6*3 = 27)
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

//######################################### Recursive #########################################
public int depthSum(List<NestedInteger> nestedList) {
    return helper(nestedList, 1);
}

public int helper(List<NestedInteger> nestedList, int depth){
    if(nestedList==null||nestedList.size()==0)
        return 0;

    int sum=0;
    for(NestedInteger ni: nestedList){
        if(ni.isInteger()){
            sum += ni.getInteger() * depth;
        }else{
            sum += helper(ni.getList(), depth+1);
        }
    }

    return sum;
}

//######################################### Iterative  #########################################
public int depthSum(List<NestedInteger> nestedList) {
    int sum=0;

    LinkedList<NestedInteger> queue = new LinkedList<NestedInteger>();
    LinkedList<Integer> depth = new LinkedList<Integer>();

    for(NestedInteger ni: nestedList){
        queue.offer(ni);
        depth.offer(1);
    }

    while(!queue.isEmpty()){
        NestedInteger top = queue.poll();
        int dep = depth.poll();

        if(top.isInteger()) {
            sum += dep*top.getInteger();
        } else {
            for(NestedInteger ni: top.getList()){
                queue.offer(ni);
                depth.offer(dep+1);
            }
        }
    }
    return sum;
}
//######################################### Recursive #########################################
class Solution {
public:
    int helper(vector<NestedInteger>& nestedList,int level,int d) {
        //NOTE :level variable is not required.
        int result = 0;
        int n = nestedList.size();
        for(int i=0;i<n;i++) {
            if(nestedList[i].isInteger()){
                result += nestedList[i].getInteger()*d;
            }else{
                result += helper(nestedList[i].getList(),i,d+1);
            }
        }
        return result;
    }
    int depthSum(vector<NestedInteger>& nestedList) {
        int result = 0;
        int depth = 1;
        return helper(nestedList,0,depth);
    }
};
