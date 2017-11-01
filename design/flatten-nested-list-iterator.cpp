//Flatten Nested List Iterator
//Given a nested list of integers, implement an iterator to flatten it.
//Each element is either an integer, or a list -- whose elements may also be integers or other lists.
//Example 1:
//Given the list [[1,1],2,[1,1]],
//By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,1,2,1,1].
//Example 2:
//Given the list [1,[4,[6]]],
//By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,4,6].

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


//################# with Begin and end list iterators (Most optimum) #################### 
public class NestedIterator implements Iterator<Integer> {

    public NestedIterator(List<NestedInteger> nestedList) {
        lists = new Stack<>();
        lists.push(nestedList.listIterator());
    }

    public Integer next() {
        hasNext();
        return lists.peek().next().getInteger();
    }

    public boolean hasNext() {
        while (!lists.empty()) {
            if (!lists.peek().hasNext()) {
                lists.pop();
            } else {
                NestedInteger x = lists.peek().next();
                if (x.isInteger())
                    return lists.peek().previous() == x;
                lists.push(x.getList().listIterator());
            }
        }
        return false;
    }
    
    private Stack<ListIterator<NestedInteger>> lists;
}
//######################################### Lazy retreival ######################################### 
class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        for (int i = nestedList.size() - 1; i >= 0; --i) {
            s.push(nestedList[i]);
        }
    }
    int next() {
        NestedInteger t = s.top(); 
        s.pop();
        return t.getInteger();
    }
    bool hasNext() {
        while (!s.empty()) {
            NestedInteger t = s.top(); 
            if (t.isInteger())  {
                return true;
            }
            s.pop();
            for (int i = t.getList().size() - 1; i >= 0; --i) {
                s.push(t.getList()[i]);
            }
        }
        return false;
    }
private:
    stack<NestedInteger> s;
};
/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */


//######################################### Heavy constructor ######################################### 
class Solution {
 	private Stack<NestedInteger> stack;
    private List<NestedInteger> nestedList;
    List<Integer> result;
    int cIdx = 0;

    public NestedIterator(List<NestedInteger> nestedList) {
        stack = new Stack<>();
        this.nestedList = nestedList;
        result = new ArrayList();
        for(int i = nestedList.size() -1;i>=0 ;i--) stack.push(nestedList.get(i));

        while(!stack.isEmpty()) {
            NestedInteger ni = stack.pop();
            if(ni.isInteger()) result.add(ni.getInteger());
            else {
                List<NestedInteger> niList = ni.getList();
                 for(int i = niList.size()-1;i>=0 ;i--) stack.push(niList.get(i));
            }
        }
    }

    @Override
    public Integer next() {
        if(hasNext()) return result.get(cIdx++);
        return -1;
    }

    @Override
    public boolean hasNext() {
        if(result.size() == cIdx) return false;
        return true;
    }
}

//################ with Begin and end iterators ################ 
class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        begins.push(nestedList.begin());
        ends.push(nestedList.end());
    }

    int next() {
        hasNext();
        return (begins.top()++)->getInteger();
    }

    bool hasNext() {
        while (begins.size()) {
            if (begins.top() == ends.top()) {
                begins.pop();
                ends.pop();
            } else {
                auto x = begins.top();
                if (x->isInteger())
                    return true;
                begins.top()++;
                begins.push(x->getList().begin());
                ends.push(x->getList().end());
            }
        }
        return false;
    }

private:
    stack<vector<NestedInteger>::iterator> begins, ends;
};



//################# With DFS #################### 
class NestedIterator {
private:
    vector<int> nums;
    int index;
    void helper(NestedInteger& node, vector<int>& v) {
        if(node.isInteger()) {
          v.push_back(node.getInteger());
        }
        else for(auto& n: node.getList()) { 
          helper(n, v);
        }
    }
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        for(auto& node: nestedList) {
          helper(node, nums);
        }
        index = 0;
    }
    int next() {
        return nums[index++];
    }

    bool hasNext() {
        return index < nums.size();
    }
};


