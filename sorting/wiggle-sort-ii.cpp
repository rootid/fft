//Wiggle Sort II
//Given an unsorted array nums, reorder it such that nums[0] < nums[1] >
//nums[2] < nums[3]....
//Example:
//(1) Given nums = [1, 5, 1, 1, 6, 4], one possible answer is [1, 4, 1, 5, 1, 6].
//(2) Given nums = [1, 3, 2, 2, 3, 1], one possible answer is [2, 3, 1, 3, 1, 2].
//Note:
//You may assume all input has valid answer.
//Follow Up:
//Can you do it in O(n) time and/or in-place with O(1) extra space?
#include "../headers/global.hpp"

//######################################### Sort + Arrangement (even<odd) #########################################
    public void wiggleSort(int[] nums) {
        Arrays.sort(nums);
        int n = nums.length;
        int[] tmp = Arrays.copyOf(nums, n);
        int i, k = (n+1)/2, j=n; //(n+1)/2 - To handle odd length
        for(i=0; i<n; i++)
            nums[i] = (i%2 == 1)? tmp[--j]:tmp[--k];
    }

//######################################### Median find + Dutch partition with Wiggled indices  #########################################
//
//Original Indices:    0  1  2  3  4  5  6  7  8  9 10 11
//Mapped Indices:      1  3  5  7  9 11  0  2  4  6  8 10
//(its reverse mapping is)
//
//Mapped Indices:      0  1  2  3  4  5  6  7  8  9 10 11
//Original Indices:    6  0  7  1  8  2  9  3 10  4 11  5   (wiggled)
	void wiggleSort(vector<int>& nums) {
		if (nums.empty()) {
			return;
		}
		int n = nums.size();

		// Step 1: Find the median
		vector<int>::iterator nth = next(nums.begin(), n / 2);
		nth_element(nums.begin(), nth, nums.end());
		int median = *nth;

		// Step 2: Tripartie partition within O(n)-time & O(1)-space.
		auto m = [n](int idx) { return (2 * idx + 1) % (n | 1); };
		int first = 0, mid = 0, last = n - 1;
		while (mid <= last) {
			if (nums[m(mid)] > median) {
				swap(nums[m(first)], nums[m(mid)]);
				++first;
				++mid;
			}
			else if (nums[m(mid)] < median) {
				swap(nums[m(mid)], nums[m(last)]);
				--last;
			}
			else {
				++mid;
			}
		}
	}


//######################################### Median find + Virtual indxing  #########################################
void wiggleSort(vector<int>& nums) {
    int n = nums.size();
    // Find a median.
    auto midptr = nums.begin() + n / 2;
    nth_element(nums.begin(), midptr, nums.end());
    int mid = *midptr; //15

    // Index-rewiring. if n is even n|1 -> odd
    #define A(i) nums[(1+2*(i)) % (n|1)]
    // 3-way-partition-to-wiggly in O(n) time with O(1) space.
    // 3 way-partiioing with virtual indexing
    int i = 0, j = 0, k = n - 1;
    while (j <= k) {
        if (A(j) > mid) {
            swap(A(i++), A(j++)); //move the ele to lt if > mid
        } else if (A(j) < mid) {
            swap(A(j), A(k--)); //move the ele to rt if< mid
        } else {
            j++;
        }
    }
}
//Accessing A(0) actually accesses nums[1].
//Accessing A(1) actually accesses nums[3].
//Accessing A(2) actually accesses nums[5].
//Accessing A(3) actually accesses nums[7].
//Accessing A(4) actually accesses nums[9].
//Accessing A(5) actually accesses nums[0].
//Accessing A(6) actually accesses nums[2].
//Accessing A(7) actually accesses nums[4].
//Accessing A(8) actually accesses nums[6].
//Accessing A(9) actually accesses nums[8].
//
///############################ Extra space
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        // Only four Line
        if (2>(n = nums.size())) return;
        r_start = n/2;
        dfs(nums, find_medin(nums));
        re_order(nums);
    }
private:
    int n;
    int r_start;
        int pivot(vector<int> &nums, int i, int j) {
        assert(i<j);
        swap(nums[i],nums[(i+j)/2]);
        int idx = i++;
        int val = nums[idx];
        while (i<j) {
            if (nums[i]<=val) i++;
            else if (nums[j]>=val) j--;
            else swap(nums[i],nums[j]);
        }
        if (nums[i]>val) i--;
        if (nums[i] != nums[idx]) swap(nums[i], nums[idx]);
        return i;
    }

    double find_kth(vector<int> &nums, int k) {
        int i = 0, j = n-1;
        while (i<j) {
            int m = pivot(nums,i,j);
            int len = m-i+1;
            if (k<len) {
                j = m-1;
            } else if (k>len) {
                k-=len;
                i = m+1;
            } else {
                return nums[m];
            }
        }
        return nums[i];
    }

    double find_medin(vector<int> &nums) {
        if (n&1) {
            return find_kth(nums, 1+(n>>1));
        } else {
            return (find_kth(nums,n>>1) + find_kth(nums, 1+(n>>1)))/2;
        }
    }

    //Dutch Flag Srot (reversed order)
    void dfs(vector<int> &nums, double target) {
        int i = 0, j = n-1, k = 0;
        while (k<=j) {
            if (nums[k]>target) {
                swap(nums[i++], nums[k++]);
            } else if (nums[k] < target) {
                swap(nums[j--], nums[k]);
            } else {
                k++;
            }
        }
    }
    int get_next(int i) {
        if (i>=r_start) return (i-r_start)<<1;
        else return 1+(i<<1);
    }
    // giving up to think a legitimate O(1) space solution.
    // cheat by using a mask to show whether it has
    // been visited or not. This sub-problem is much harder compare
    // to array rotation, I cannot use a count and increase
    // the start by one whenever count < limit.
    void re_order(vector<int> & nums) {
        for (int mask = 1<<30, i, temp, start=0; start<n; ++start) {
            if (!(nums[start] & mask)) {
                temp = nums[i = start];
                do {swap(temp|=mask, nums[i=get_next(i)]);} while (i!=start);
            }
            nums[start] ^= mask;
        }
    }
};
//############################################## T: O(n log n)  s:O(n) ##############################################
void wiggleSort(vector<int>& nums) {
    vector<int> sorted(nums);
    sort(sorted.begin(), sorted.end());
    for (int i=nums.size()-1, j=0, k=i/2+1; i>=0; i--) {
        nums[i] = sorted[i&1 ? k++ : j++];
    }
}
//Small half:    4 . 3 . 2 . 1 . 0 .
//Large half:    . 9 . 8 . 7 . 6 . 5
//----------------------------------
//Together:      4 9 3 8 2 7 1 6 0 5
//So write nums from the back, interweaving sorted[0..4] (indexed by j) and
//sorted[5..9] (indexed by k).
//################## Find the median by guessing  ##################
public void wiggleSort(int[] nums) {
    if (nums.length <= 1) {
        return;
    }
    int p = bsSelect(nums, (nums.length - 1) / 2 + 1);
    // Reverse Dutch National Flag with Wiggle Indexing (StefanPochmann's Virtual Indexing).
    // Thanks to apolloydy for reversing this thing.
    final int n = nums.length;
    int m = 0, r = nums.length - 1;
    int lw = 1, mw = 1, rw = (1 + 2 * (nums.length - 1)) % (n | 1);
    while (m <= r) {
        if (nums[mw] > p) {
            int tmp = nums[mw];
            nums[mw] = nums[lw];
            nums[lw] = tmp;
            mw = (mw + 2) % (n | 1);
            ++m;
            lw = (lw + 2) % (n | 1);
        } else if (nums[mw] < p) {
            int tmp = nums[mw];
            nums[mw] = nums[rw];
            nums[rw] = tmp;
            rw = (rw - 2 + (n | 1)) % (n | 1);
            --r;
        } else {
            mw = (mw + 2) % (n | 1);
            ++m;
        }
    }
}
private int bsSelect(int[] nums, int k) {
    if (k < 1 || k > nums.length) {
        throw new IllegalArgumentException("length=" + nums.length + " k=" + k);
    }
    //Guessing the median
    int left = Integer.MIN_VALUE, right = Integer.MAX_VALUE;
    while (left <= right) {
        int mid = (left < 0 && right > 0) ? (left + right) / 2 : left + (right - left) / 2;
        int cl = 0, cg = 0, d = 0;
        for (int n : nums) {
            if (n < mid) {
                if (++cl > k - 1) {
                    d = +1; // mid larger than kth
                    break;
                }
            } else if (n > mid) {
                if (++cg > (nums.length - k)) {
                    d = -1; // mid smaller than kth
                    break;
                }
            }
        }
        if (d == 0) {
            return mid;
        } else if (d < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    throw new AssertionError();
}

//why bother with all those algorithms if we know that possible values of the
//median lie between INT_MIN and INT_MAX. We can use binary search on the
//entire range! And since checking whether some number is the median or not
//takes O(n), then the whole thing is just O(n log 2^32). But log 2^32 is a
//constant, so it's technically still O(n).
//
//
//It almost feels like cheating. But according to that post on Quora, that's
//exactly what the interviewers expect. Thinking out of the box and such.
//This thing runs on my PC for 500 million elements in 31 seconds if the array
//is sorted and in 38 seconds if it's wiggle-sorted to begin with. This is
//slower than the median of medians solution (22 and 12 seconds), but this time
//it's true O(1) space.
//Note that I moved the argument check to the beginning because the old variant
//was really bugged. And I fixed the binary search because I forgot to do the
//mid + 1 / mid - 1 part. That turned 15 ms into 18 ms for some reason, and if
//I put while (true) there then it raises the runtime to 20 ms. Figures. But at
//least it's not bugged now (I hope). Note that integer overflows aren't
//possible because if mid is either INT_MIN or INT_MAX then the respective
//condition for decreasing/increasing it would be false.
//As noted in the comment below, mid = (left + right) / 2 may overflow, so it
//was replaced by that ugly, but overflow-aware line.


//############################################## Median of medians ##############################################

public void wiggleSort(int[] nums) {
    if (nums.length <= 1) {
        return;
    }
    int p = bfprtSelect(nums, 0, nums.length, (nums.length - 1) / 2 + 1);
    // Reverse Dutch National Flag with Wiggle Indexing (StefanPochmann's Virtual Indexing).
    // Thanks to apolloydy for reversing this thing.
    final int n = nums.length;
    int m = 0, r = nums.length - 1;
    int lw = 1, mw = 1, rw = (1 + 2 * (nums.length - 1)) % (n | 1);
    while (m <= r) {
        if (nums[mw] > p) {
            int tmp = nums[mw];
            nums[mw] = nums[lw];
            nums[lw] = tmp;
            mw = (mw + 2) % (n | 1);
            ++m;
            lw = (lw + 2) % (n | 1);
        } else if (nums[mw] < p) {
            int tmp = nums[mw];
            nums[mw] = nums[rw];
            nums[rw] = tmp;
            rw = (rw - 2 + (n | 1)) % (n | 1);
            --r;
        } else {
            mw = (mw + 2) % (n | 1);
            ++m;
        }
    }
}

/**
 * Finds the kth order statistic in linear time. Thanks to Blum, Floyd, Pratt, Rivest and Tarjan,
 * hence this funny name BFPRT. Or just the Median of Medians, but really it can find more
 * than just medians. And anyway, "bfprtSelect" is shorter than "medianOfMediansSelect".
 *
 * @param nums the input array
 * @param start the start of the input array
 * @param length the length of the input array
 * @param k the number of order statistic to find, {@code 1 <= k <= length}
 * @return the kth order statistic
 */
private static int bfprtSelect(int[] nums, int start, int length, int k) {
    if (length <= 0) {
        throw new IllegalArgumentException("length=" + length);
    }
    if (k < 1 || k > length) {
        throw new IllegalArgumentException("length=" + length + " k=" + k);
    }
    if (length == 1) {
        return nums[start];
    }
    int gc = findGroupMedians(nums, start, length);
    int p = bfprtSelect(nums, start, gc, (gc - 1) / 2 + 1);
    int[] dnf = dnfPartition(nums, start, length, p);
    if (start + k - 1 >= dnf[0] && start + k - 1 < dnf[1]) {
        return p; // Got lucky, the pivot is the kth order statistic.
    } else if (start + k - 1 < dnf[0]) {
        return bfprtSelect(nums, start, dnf[0] - start, k);
    } else {
        return bfprtSelect(nums, dnf[1], length - (dnf[1] - start), k - (dnf[1] - start));
    }
}

private static int findGroupMedians(int[] nums, int start, int length) {
    final int gc = (length + 4) / 5; // group count (5 elements in each group)
    for (int g = 0; g < gc; ++g) {
        final int gs = start + 5 * g; // group start
        final int ge = start + Math.min(5 * (g + 1), length); // group end
        // Let's do some insertion sort to find the median!
        for (int i = gs, j = gs; i < ge - 1; j = ++i) {
            int v = nums[i + 1];
            while (j >= gs && nums[j] > v) {
                nums[j + 1] = nums[j--]; // LHS evaluated first, so j-- is safe
            }
            nums[j + 1] = v;
        }
        // Move the medians to the beginning of the array to recurse on them later.
        final int mid = (gs + ge) / 2;
        int tmp = nums[start + g];
        nums[start + g] = nums[mid];
        nums[mid] = tmp;
    }
    return gc;
}

private static int[] dnfPartition(int[] nums, int start, int length, int p) {
    int l = start, m = start, r = start + length - 1;
    while (m <= r) {
        if (nums[m] < p) {
            int tmp = nums[m];
            nums[m++] = nums[l];
            nums[l++] = tmp;
        } else if (nums[m] > p) {
            int tmp = nums[m];
            nums[m] = nums[r];
            nums[r--] = tmp;
        } else {
            ++m;
        }
    }
    return new int[] {l, m};
}
int main () {
}

//######################################### Sort + merge #########################################
//Roughly speaking I put the smaller half of the numbers on the even indexes
//and the larger half on the odd indexes.

def wiggleSort(self, nums):
    nums.sort()
    half = len(nums[::2])
    nums[::2], nums[1::2] = nums[:half][::-1], nums[half:][::-1]

def wiggleSort(self, nums):
    nums.sort()
    half = len(nums[::2]) - 1
    nums[::2], nums[1::2] = nums[half::-1], nums[:half:-1]
//Explanation / Proof
//I put the smaller half of the numbers on the even indexes and the larger half
//on the odd indexes, both from right to left:
//
//Example nums = [1,2,...,7]      Example nums = [1,2,...,8]
//
//Small half:  4 . 3 . 2 . 1      Small half:  4 . 3 . 2 . 1 .
//Large half:  . 7 . 6 . 5 .      Large half:  . 8 . 7 . 6 . 5
//--------------------------      --------------------------
//Together:    4 7 3 6 2 5 1      Together:    4 8 3 7 2 6 1 5
//I want:
//
//Odd-index numbers are larger than their neighbors.
//Since I put the larger numbers on the odd indexes, clearly I already have:
//
//Odd-index numbers are larger than or equal to their neighbors.
//Could they be "equal to"? That would require some number M to appear both in
//the smaller and the larger half. It would be the largest in the smaller half
//and the smallest in the larger half. Examples again, where S means some
//number smaller than M and L means some number larger than M.
//
//Small half:  M . S . S . S      Small half:  M . S . S . S .
//Large half:  . L . L . M .      Large half:  . L . L . L . M
//--------------------------      --------------------------
//Together:    M L S L S M S      Together:    M L S L S L S M
//You can see the two M are quite far apart. Of course M could appear more than
//just twice, for example:
//
//Small half:  M . M . S . S      Small half:  M . S . S . S .
//Large half:  . L . L . M .      Large half:  . L . M . M . M
//--------------------------      --------------------------
//Together:    M L M L S M S      Together:    M L S M S M S M
//You can see that with seven numbers, three M are no problem. And with eight
//numbers, four M are no problem. Should be easy to see that in general, with n
//numbers, floor(n/2) times M is no problem. Now, if there were more M than
//that, then my method would fail. But... it would also be impossible:
//
//If n is even, then having more than n/2 times the same number clearly is
//unsolvable, because you'd have to put two of them next to each other, no
//matter how you arrange them.
//If n is odd, then the only way to successfully arrange a number appearing
//more than floor(n/2) times is if it appears exactly floor(n/2)+1 times and
//you put them on all the even indexes. And to have the wiggle-property, all
//the other numbers would have to be larger. But then we wouldn't have an M in
//both the smaller and the larger half.
//So if the input has a valid answer at all, then my code will find one.
//


//######################################### T : O(n) , S: O(n) #########################################
public class Solution {
	public void wiggleSort(int[] nums) {
		int median = selectKth(nums, 0, nums.length-1, nums.length%2==0 ? nums.length/2 : nums.length/2+1);
		List<Integer> leftArr = new ArrayList<Integer>();
		for(int i=0; i<=median; i++)
		leftArr.add(nums[i]);
		List<Integer> rightArr = new ArrayList<Integer>();
		for(int i=median+1; i<nums.length; i++)
		rightArr.add(nums[i]);
		for(int li=leftArr.size()-1,ri=rightArr.size()-1,i=0; ri>=0; li--,ri--,i+=2) { // right is same or shorter than left
		nums[i] = leftArr.get(li);
		nums[i+1] = rightArr.get(ri);
		}
		if(nums.length%2!=0)
		nums[nums.length-1] = leftArr.get(0);
	}

 private int selectKth(int[] nums, int start, int end, int k) {
     int[] res = partition(nums,start,end);
     int lb = res[0]; int hb = res[1];
     if(k-1<lb)
         return selectKth(nums,start,lb-1,k);
     else if (k-1>hb)
         return selectKth(nums,hb+1,end,k);
     else
         return k-1;
 }

 private int[] partition(int[] nums, int lb, int hb) {
     int pVal = nums[lb]; // use random genarater is better in performance
     int i = lb;
     while(i<=hb) {
         if(nums[i]==pVal)
             i++;
         else if(nums[i]<pVal)
             swap(nums,i++,lb++);
         else
             swap(nums,i,hb--);
     }
     int[] res = new int[2];
     res[0] = lb; res[1] = hb;
     return res;
 }

 private void swap(int[] nums, int i, int j) {
     int tmp = nums[i];
     nums[i] = nums[j];
     nums[j] = tmp;
 }
}
