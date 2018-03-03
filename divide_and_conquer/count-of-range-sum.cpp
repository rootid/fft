//Count of Range Sum
//Given an integer array nums, return the number of range sums that lie in
//[lower, upper] inclusive.
//Range sum S(i, j) is defined as the sum of the elements in nums between
//indices i and j (i ≤ j), inclusive.
//Note:
//A naive algorithm of O(n2) is trivial. You MUST do better than that.
//Example:
//Given nums = [-2, 5, -1], lower = -2, upper = 2,
//	  Return 3.
//	  The three ranges are : [0, 0], [2, 2], [0, 2] and their respective sums are: -2, -1, 2

//######################################### Merge Sort #########################################
//y implementation of this algorithm in Java with manual merging subroutine
//(had to use long for prefix, as some testcases contain Integer.MAX_VALUE and
//Integer.MIN_VALUE instances). O(n log n) time, O(n) heap space, O(log n)
//stack space.
public class Solution {
    public int countRangeSum(int[] nums, int lower, int upper) {
        long[] prefix = new long[nums.length + 1];
        for(int i = 1; i <= nums.length; i++) prefix[i] = prefix[i-1] + nums[i-1];
        return countingMergeSort(prefix, new long[prefix.length], 0, prefix.length - 1, lower, upper);
    }

    private int countingMergeSort(long[] prefix, long[] helper, int low, int high, long lower, long upper) {
        if (low >= high)
            return 0;

        int mid = (high + 1 - low) / 2 + low; // start of right part
        int count = countingMergeSort(prefix, helper, low, mid - 1, lower, upper)
                  + countingMergeSort(prefix, helper, mid, high, lower, upper);

        int rangeStart = mid, rangeEnd = mid;  // start inclusive, end exclusive
        for(int i = low; i < mid; i++) {
            while(rangeStart <= high && prefix[rangeStart] - prefix[i] < lower)
                rangeStart++;
            while(rangeEnd <= high && prefix[rangeEnd] - prefix[i] <= upper)
                rangeEnd++;

            count += rangeEnd - rangeStart;
        }

        merge(prefix, helper, low, mid, high);
        return count;
    }

    private void merge(long[] prefix, long[] helper, int low, int mid, int high) {
        int left = low, right = mid, idx = low;

        while(left < mid && right <= high) {
            if (prefix[left] <= prefix[right])
                helper[idx++] = prefix[left++];
            else
                helper[idx++] = prefix[right++];
        }

        while(left < mid)
            helper[idx++] = prefix[left++];
        while(right <= high)
            helper[idx++] = prefix[right++];

        System.arraycopy(helper, low, prefix, low, high + 1 - low);
    }
}
//######################################### O(n log n)  #########################################
def countRangeSum(self, nums, lower, upper):
    first = [0]
    for num in nums:
        first.append(first[-1] + num)
    def sort(lo, hi):
        mid = (lo + hi) / 2
        if mid == lo:
            return 0
        count = sort(lo, mid) + sort(mid, hi)
        i = j = mid
        for left in first[lo:mid]:
            while i < hi and first[i] - left <  lower: i += 1
            while j < hi and first[j] - left <= upper: j += 1
            count += j - i
        first[lo:hi] = sorted(first[lo:hi])
        return count
    return sort(0, len(first))
//First compute the prefix sums: first[m] is the sum of the first m numbers.
//Then the sum of any subarray nums[i:k] is simply first[k] - first[i].
//So we just need to count those where first[k] - first[i] is in [lower,upper].
//To find those pairs, I use mergesort with embedded counting. The pairs in the
//left half and the pairs in the right half get counted in the recursive calls.
//We just need to also count the pairs that use both halves.
//For each left in first[lo:mid] I find all right in first[mid:hi] so that
//right - left lies in [lower, upper]. Because the halves are sorted, these
//fitting right values are a subarray first[i:j]. With increasing left we must
//also increase right, meaning must we leave out first[i] if it's too small and
//and we must include first[j] if it's small enough.
//Besides the counting, I also need to actually merge the halves for the
//sorting. I let sorted do that, which uses Timsort and takes linear time to
//recognize and merge the already sorted halves.
//With Divide and Conquer, you first suppose you sovled two halves of array
//fisrt[i] = sum (0..i) and counted the possible qualified ranges (sum of
//subarray of [lower, upper]) in each half. Then if you find all the qualified
//range crossing left half and right half then you complete the answer.
//
//Note you’ve already sorted first[i] in left half and right half. You pick a
//left element of first array in left half, call it “left”. And you then pick a
//right in right half. For each left: Right – left is a range sum across left
//half and right half. Check it meet [lower, upper] or not. If the range sum is
//too small? Simply increase right. Too large? Stop, you don’t need to increase
//right pointer anymore, because first is sorted and increasing right can only
//make the sum larger.
//
//Therefore for each left, you
//
//find min right index (i) that meets right – left >= lower,
//
//find max right index (j) that meets right – left > upper,
//
//the j – i is the number of valid range sums. Then you iterate next left and
//search the according answer.
//
//A side note is when left increase one element, the right-left can only become
//smaller, what you only need to do is increase right to find larger range sum
//so that it is valid. Therefore the two loops only takes linear time.

//######################################### O(n^2) #########################################
//Preprocess to calculate the prefix sums S[i] = S(0, i), then S(i, j) = S[j] -
//S[i].
//Note that here we define S(i, j) as the sum of range [i, j) where j exclusive
//and j > i. With these prefix sums, it is trivial to see that with O(n^2) time
//we can find all S(i, j) in the range [lower, upper]
public int countRangeSum(int[] nums, int lower, int upper) {
    int n = nums.length;
    long[] sums = new long[n + 1];
    for (int i = 0; i < n; ++i)
        sums[i + 1] = sums[i] + nums[i];
    int ans = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (sums[j] - sums[i] >= lower && sums[j] - sums[i] <= upper)
                ans++;
    return ans;
}


//######################################### Merge Sort #########################################
//Recall count smaller number after self where we encountered the problem
//count[i] = count of nums[j] - nums[i] < 0 with j > i
//Here, after we did the preprocess, we need to solve the problem
//count[i] = count of a <= S[j] - S[i] <= b with j > i
//ans = sum(count[:])
//Therefore the two problems are almost the same. We can use the same technique
//used in that problem to solve this problem. One solution is merge sort based;
//another one is Balanced BST based. The time complexity are both O(n log n).
//The merge sort based solution counts the answer while doing the merge. During
//the merge stage, we have already sorted the left half [start, mid) and right
//half [mid, end). We then iterate through the left half with index i. For each
//i, we need to find two indices k and j in the right half where
//j is the first index satisfy sums[j] - sums[i] > upper and
//k is the first index satisfy sums[k] - sums[i] >= lower.
//Then the number of sums in [lower, upper] is j-k. We also use another index t
//to copy the elements satisfy sums[t] < sums[i] to a cache in order to
//complete the merge sort.
//Despite the nested loops, the time complexity of the "merge & count" stage is
//still linear. Because the indices k, j, t will only increase but not
//decrease, each of them will only traversal the right half once at most. The
//total time complexity of this divide and conquer solution is then O(n log n).
//One other concern is that the sums may overflow integer. So we use long
//instead.

public int countRangeSum(int[] nums, int lower, int upper) {
    int n = nums.length;
    long[] sums = new long[n + 1];
    for (int i = 0; i < n; ++i)
        sums[i + 1] = sums[i] + nums[i];
    return countWhileMergeSort(sums, 0, n + 1, lower, upper);
}
private int countWhileMergeSort(long[] sums, int start, int end, int lower, int upper) {
    if (end - start <= 1) return 0;
    int mid = (start + end) / 2;
    int count = countWhileMergeSort(sums, start, mid, lower, upper)
              + countWhileMergeSort(sums, mid, end, lower, upper);
    int j = mid, k = mid, t = mid;
    long[] cache = new long[end - start];
    for (int i = start, r = 0; i < mid; ++i, ++r) {
        while (k < end && sums[k] - sums[i] < lower) k++;
        while (j < end && sums[j] - sums[i] <= upper) j++;
        while (t < end && sums[t] < sums[i]) cache[r++] = sums[t++];
        cache[r] = sums[i];
        count += j - k;
    }
    System.arraycopy(cache, 0, sums, start, t - start);
    return count;
}



//There are BST solutions, but they suffer from unbalance in the worst-case,
//degrading to O(n^2). What's worse, the worst case, no pun intended, is a very
//regular case when all numbers are positive or negative. So we need to keep
//our tree balanced, and that immediately rings a bell: Red-Black Trees.
//The only trick is that we need to keep track of node counts in subtrees so
//that we can quickly count the number of elements less than or equal to
//something without traversing around (like TreeMap.subMap().size() does). It
//is also important to update those node counts when performing rotations.
//This solution is not terribly efficient: only 72 ms, and I can't think of any
//ways to optimize it. In fact, Java TreeMap sources look very similar except
//that they use more branches and don't use explicit NIL nodes. Maybe the fact
//that RBT is not perfectly balanced also plays its role: some paths can be
//twice as long as others. And we also need to perform the search twice on each
//loop iteration, which also doesn't make it any faster.
//The conclusion is that this solution is probably only of theoretical
//interest.

public int countRangeSum(int[] nums, int lower, int upper) {
    long sum = 0;
    RedBlackTree sumTree = new RedBlackTree();
    sumTree.add(sum); // zero-length prefix
    int count = 0;
    for (int i = 0; i < nums.length; ++i) {
        sum += nums[i];
        // we need to count lower <= sums[i] - sums[j] <= upper, j < i, or
        // -lower >= sums[j] - sums[i] >= -upper, or sums[i] - lower >= sums[j] >= sums[i] - upper, or
        // sums[i] - lower >= sums[j] > sums[i] - upper - 1
        count += countLE(sumTree.root, sum - lower) - countLE(sumTree.root, sum - upper - 1);
        sumTree.add(sum);
    }
    return count;
}

private static int countLE(RedBlackTree.Node root, long sum) {
    RedBlackTree.Node current = root;
    int count = current.totalCount;
    while (current != RedBlackTree.Node.NIL) {
        if (current.value == sum) {
            count -= current.right.totalCount;
            break;
        } else if (sum < current.value) {
            count -= current.valueCount + current.right.totalCount;
            current = current.left;
        } else { // we haven't seen anything greater than sum yet
            current = current.right;
        }
    }
    return count;
}

static class RedBlackTree {

    Node root = Node.NIL;

    void add(long value) {
        Node current = root, prev = Node.NIL;
        while (current != Node.NIL && current.value != value) {
            ++current.totalCount;
            prev = current;
            if (value < current.value) {
                current = current.left;
            } else {
                current = current.right;
            }
        }
        if (current != Node.NIL) { // Note: can't test for current.value == value here because value can be 0.
            // exact match
            ++current.totalCount;
            ++current.valueCount;
            return;
        }
        Node node = new Node(value);
        if (prev == Node.NIL) {
            root = node;
        } else {
            if (value < prev.value) {
                assert prev.left == Node.NIL;
                prev.left = node;
            } else {
                assert prev.right == Node.NIL && value > prev.value;
                prev.right = node;
            }
            node.parent = prev;
        }
        // fix up the Red-Blackness (CLR, Introduction to Algorithms)
        while (node.parent.color == Node.Color.RED) {
            Node parent = node.parent;
            Node granddad = parent.parent;
            assert granddad.color == Node.Color.BLACK;
            boolean left = granddad.left == parent;
            Node uncle = left ? granddad.right : granddad.left;
            if (uncle.color == Node.Color.RED) { // case 1
                granddad.color = Node.Color.RED;
                parent.color = uncle.color = Node.Color.BLACK;
                node = granddad;
            } else {
                if ((left ? parent.right : parent.left) == node) { // case 2
                    node = parent;
                    rotate(node, left);
                }
                // case 3
                parent.color = Node.Color.BLACK;
                granddad.color = Node.Color.RED;
                rotate(granddad, !left);
            }
        }
        root.color = Node.Color.BLACK;
    }

    void rotate(Node node, boolean left) {
        Node parent = node.parent;
        Node child = left ? node.right : node.left;
        if (left) { node.right = child.left; } else { node.left = child.right; }
        node.totalCount = node.left.totalCount + node.valueCount + node.right.totalCount;
        (left ? child.left : child.right).parent = node;
        child.parent = parent;
        if (parent == Node.NIL) {
            root = child;
        } else {
            if (parent.left == node) {
                parent.left = child;
            } else {
                assert parent.right == node;
                parent.right = child;
            }
        }
        if (left) { child.left = node; } else { child.right = node; }
        child.totalCount = child.left.totalCount + child.valueCount + child.right.totalCount;
        node.parent = child;
        Node.NIL.left = Node.NIL.right = Node.NIL.parent = Node.NIL; // fix it up in case we've messed it up
    }

    static class Node {
        static final Node NIL = new Node();

        static { // need this because we can't initialize fields to NIL until it is created
            NIL.left = NIL.right = NIL.parent = NIL;
        }

        long value;
        int valueCount, totalCount;
        Node parent = NIL, left = NIL, right = NIL;
        Color color;

        private Node() { // NIL constructor
            this.color = Color.BLACK;
        }

        Node(long value) {
            this.value = value;
            this.valueCount = this.totalCount = 1;
            this.color = Color.BLACK;
        }

        enum Color {
            RED, BLACK
        }
    }
}
