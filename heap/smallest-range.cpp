//Smallest Range
//You have k lists of sorted integers in ascending order. Find the smallest range that includes at least one number from each of the k lists.
//We define the range [a,b] is smaller than range [c,d] if b-a < d-c or a < c if b-a == d-c.
//Example 1:
//Input:[[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
//Output: [20,24]
//Explanation: 
//List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
//List 2: [0, 9, 12, 20], 20 is in range [20,24].
//List 3: [5, 18, 22, 30], 22 is in range [20,24].
//Note:
//The given list may contain duplicates, so ascending order means >= here.
//1 <= k <= 3500
//-105 <= value of elements <= 105.
//For Java users, please note that the input type has been changed to List<List<Integer>>. And after you reset the code template, you'll see this point.

//#########################################  Merge k sorted list #########################################  
//TC : O(n * logm) : n =elements from all lists, m = size of heap
//SC : O(m)
//1. Use Min-heap to keep track of min elements
public class Solution {
    public int[] smallestRange(int[][] nums) {
        int minx = 0, miny = Integer.MAX_VALUE, max = Integer.MIN_VALUE;
        int[] next = new int[nums.length];
        boolean flag = true;
        PriorityQueue < Integer > min_queue = new PriorityQueue < Integer > ((i, j) -> nums[i][next[i]] - nums[j][next[j]]);
        for (int i = 0; i < nums.length; i++) {
            min_queue.offer(i);
            max = Math.max(max, nums[i][0]);
        }
        for (int i = 0; i < nums.length && flag; i++) {
            for (int j = 0; j < nums[i].length && flag; j++) {
                int min_i = min_queue.poll();
                if (miny - minx > max - nums[min_i][next[min_i]]) {
                    minx = nums[min_i][next[min_i]];
                    miny = max;
                }
                next[min_i]++;
                if (next[min_i] == nums[min_i].length) {
                    flag = false;
                    break;
                }
                min_queue.offer(min_i);
                max = Math.max(max, nums[min_i][next[min_i]]);
            }
        }
        return new int[] { minx, miny};
    }
}

//######################################### Merge K sorted list ######################################### 
//similar to Merge K Sorted List. Keep a priority queue of iterators/pointers which points to the current head of a row.
vector<int> smallestRange(vector<vector<int>>& nums) { 
	typedef vector<int>::iterator vi;
    
    struct comp {
        bool operator()(pair<vi, vi> p1, pair<vi, vi> p2) {
            return *p1.first > *p2.first;
        }
    };
    int lo = INT_MAX, hi = INT_MIN;
    priority_queue<pair<vi, vi>, vector<pair<vi, vi> >, comp> pq;
    for (auto &row : nums) {
        lo = min(lo, row[0]);
        hi = max(hi, row[0]);
        pq.push({row.begin(), row.end()}); //pair of iterator
    }
    vector<int> ans = {lo, hi};
    while (true) {
        auto p = pq.top();
        pq.pop();
        ++p.first;
        if (p.first == p.second)
            break;
        pq.push(p);
        
        lo = *pq.top().first; //update lo
        hi = max(hi, *p.first); //updte hi
        if (hi - lo < ans[1] - ans[0])
            ans = {lo, hi};
    }
    return ans; 
}

//######################################### Merge K sorted list ######################################### 
class Solution {
public:
    struct mycompare {
        bool operator () (pair<int, int>& a, pair<int, int>& b) {return a.first > b.first;}  
    };
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int n = nums.size(), large = INT_MIN, maxlen = INT_MAX;
		//T, Container, compare
        priority_queue<pair<int, int>, vector<pair<int, int>>, mycompare> pq;
        for (int i = 0; i < nums.size(); i++) {
            large = max(large, nums[i][0]);
            pq.push({nums[i][0], i});
        }
        vector<int> ans(2, 0), idx(n, 0);
        while (pq.size() == n) {
            int cur = pq.top().first, row = pq.top().second;
            pq.pop();
            if (large-cur < maxlen) {
                maxlen = large-cur;
                ans[0] = cur;
                ans[1] = large;
            }
            if (++idx[row] < nums[row].size()) {
                pq.push({nums[row][idx[row]], row});
                large = max(large, nums[row][idx[row]]);
            }
        }
        return ans;
    }
};

//######################################### Merge K sorted list ######################################### 
public int[] smallestRange(List<List<Integer>> nums) { 
//pq compares its incoming element (a) and old elements (b) for order based
//on the value of a[0] - b[0]. The value of a[0] - b[0] can be a negative integer, zero, or a positive integer as a is less than, equal to, or greater than b.
	PriorityQueue<int[]> pq = new PriorityQueue<int[]>((a, b) -> a[0] - b[0]);
    int max = Integer.MIN_VALUE;
    for(int i = 0; i < nums.size(); i++) {
    	max = Math.max(max, nums.get(i).get(0));
    	pq.add(new int[] {nums.get(i).get(0), i, 0}); //<#, row idx, element idx>
    }
    int[] result = {pq.peek()[0], max};
    while(result[1] - result[0] != 0 && pq.peek()[2] + 1 < nums.get(pq.peek()[1]).size()) {
    	int[] curr = pq.poll();
    	pq.add(new int[] {nums.get(curr[1]).get(curr[2] + 1), curr[1], curr[2] + 1});
    	max = Math.max(max, nums.get(curr[1]).get(curr[2] + 1));
    	if(max - pq.peek()[0] < result[1] - result[0]) result = new int[] {pq.peek()[0], max};
    }
    return result; 
}


//######################################### python ######################################### 
import heapq
class Solution(object):
    def smallestRange(self, nums):
        """
        :type nums: List[List[int]]
        :rtype: List[int]
        """
        q = []  # element in the heap: val, i, j, where val is nums[i][j]
        max_val = nums[0][0]
        for i in range(len(nums)):
            heapq.heappush(q, (nums[i][0], i, 0))
            max_val = max(max_val, nums[i][0])  # also remember max of the heap
        min_range = [-10 ** 5, 10 ** 5]
        while q:
            min_val, i, j = heapq.heappop(q)
            if max_val - min_val < min_range[1] - min_range[0] or (
                                max_val - min_val == min_range[1] - min_range[0] and min_val < min_range[0]):
                min_range = [min_val, max_val]
            # push the next value in the ith array if any
            if j + 1 < len(nums[i]):
                max_val = max(max_val, nums[i][j + 1])
                heapq.heappush(q, (nums[i][j + 1], i, j + 1))
            else:  # ths ith array is exhausted
                return min_range



//######################################### Merge K sorted list ######################################### 
//merging k sorted array using a heap.
//Then everytime you pop the smallest element out and
//add the next element of that array to the heap. By keep doing this, you will have the smallest range.
public int[] smallestRange(int[][] nums) {

		PriorityQueue<Element> pq = new PriorityQueue<Element>(new Comparator<Element>() {
			public int compare(Element a, Element b) {
				return a.val - b.val;
			}
		});

		int min = Integer.MAX_VALUE, max = Integer.MIN_VALUE;
		for (int i = 0; i < nums.length; i++) {
			//All nums arrays are sorted 
			Element e = new Element(i, 0, nums[i][0]); //get min element
			pq.offer(e);
			max = Math.max(max, nums[i][0]); //update the max 
		}
		int range = Integer.MAX_VALUE;
		int start = -1, end = -1;
		while (pq.size() == nums.length) {

			Element curr = pq.poll();
			if (max - curr.val < range) {
				range = max - curr.val;
				start = curr.val;
				end = max;
			}
			//Iterate over the array , heap decides which array to pick to iterate 
			if (curr.idx + 1 < nums[curr.row].length) {
				curr.idx = curr.idx + 1;
				curr.val = nums[curr.row][curr.idx];
				pq.offer(curr);
				if (curr.val > max) {
					max = curr.val;
				}
			}
		}
		return new int[] { start, end };
	}

	class Element {
		int val;
		int idx;
		int row;

		public Element(int r, int i, int v) {
			val = v;
			idx = i;
			row = r;
		}
	}

//################################################### Python ################################################### 
//Keep a heap of the smallest elements. As we pop element A[i][j], we'll replace it with A[i][j+1]. For each such element left, we want right, the maximum of the closest value in each row of the array that is >= left, which is also equal to the current maximum of our heap. We'll keep track of right as we proceed.
def smallestRange(self, A):
    pq = [(row[0], i, 0) for i, row in enumerate(A)]
    heapq.heapify(pq)
    
    ans = -1e9, 1e9
    right = max(row[0] for row in A)
    while pq:
        left, i, j = heapq.heappop(pq)
        if right - left < ans[1] - ans[0]:
            ans = left, right
        if j + 1 == len(A[i]):
            return ans
        v = A[i][j+1]
        right = max(right, v)
        heapq.heappush(pq, (v, i, j+1))




//######################################### Brute force ######################################### 
//TC : O(n^3) SC : O(1)
public class Solution {
    public int[] smallestRange(int[][] nums) {
        int minx = 0, miny = Integer.MAX_VALUE; // all elements are in the range of 0 <-----> MAX_VALUE
        for (int i = 0; i < nums.length; i++) {
            for (int j = 0; j < nums[i].length; j++) { //row traversal
                for (int k = i; k < nums.length; k++) {
                    for (int l = (k == i ? j : 0); l < nums[k].length; l++) {
                        int min = Math.min(nums[i][j], nums[k][l]);
                        int max = Math.max(nums[i][j], nums[k][l]);
                        int n, m;
                        for (m = 0; m < nums.length; m++) {
                            for (n = 0; n < nums[m].length; n++) {
                                if (nums[m][n] >= min && nums[m][n] <= max)
                                    break;
                            }
                            if (n == nums[m].length)
                                break;
                        }
                        if (m == nums.length) {
							//b-a > d-c || b-a == d-c  && a > c
                            if (miny - minx > max - min || (miny - minx == max - min && minx > min)) {
                                miny = max; //update miny and minx to get the shortest miny and minx 
                                minx = min;
                            }
                        }
                    }
                }
            }
        }
        return new int[] {minx, miny};
    }
}

//######################################### Brute force ######################################### 
//next : keep track of indices while traversing all the array
//TC : O(n*m) SC : O(m)
public class Solution {
    public int[] smallestRange(int[][] nums) {
        int minx = 0, miny = Integer.MAX_VALUE;
        int[] next = new int[nums.length];
        boolean flag = true;
        for (int i = 0; i < nums.length && flag; i++) {
            for (int j = 0; j < nums[i].length && flag; j++) {
                int min_i = 0, max_i = 0;
                for (int k = 0; k < nums.length; k++) {
                    if (nums[min_i][next[min_i]] > nums[k][next[k]])
                        min_i = k;
                    if (nums[max_i][next[max_i]] < nums[k][next[k]])
                        max_i = k;
                }
                if (miny - minx > nums[max_i][next[max_i]] - nums[min_i][next[min_i]]) {
                    miny = nums[max_i][next[max_i]];
                    minx = nums[min_i][next[min_i]];
                }
                next[min_i]++;
                if (next[min_i] == nums[min_i].length) {
                    flag = false;
                }
            }
        }
        return new int[] {minx, miny};
    }
}


