//##  First Missing Positive
//### Given an unsorted integer array, find the first missing positive integer.
//For example,
//Given [1,2,0] return 3,
//and [3,4,-1,1] return 2.
//Your algorithm should run in O(n) time and uses constant space.
//Assumption : A[i] <= n
//


//Why it is O(n)?
//Since we only see each element at most twice as @makuiyu mentioned, the time
//complexity should be O(2n) = O(n). Sometimes we might see some negative
//numbers more than twice, but when that happens we will only see the positive
//number we swapped with that negative number once. In conclusion, it is
//equivalent we see all the positive number twice and negative number once.
//Let's assume k is the number of the positive numbers in the array, where k <
//n. The time complexity is O(2k + n - k) = O(n + k), where worst case is O(2n)
//= O(n).
//
//
//

//Move 1 to 0th index
public int firstMissingPositive(int[] nums) {
   int n = nums.length;
   for(int i=0;i<n;i++)
       while(nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1])
           swap(nums,i,nums[i]-1);
    for(int i=0;i<n;i++)
        if(nums[i] != i+1) return i+1;
    return n+1;
}

private void swap(int[] nums, int i, int j) {
	nums[i] ^= nums[j];
	nums[j] ^= nums[i];
	nums[i] ^= nums[j];
}


//Put each number in its right place.
//For example:
//When we find 5, then swap it with A[4].
//At last, the first place where its number is not right, return the place + 1.
  public int firstMissingPositive(int[] nums) {
		int n = nums.length;
		for(int i = 0; i < n; i++) {
            //In, short move 1 to 0th index
			while(nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1])
				swap(nums, i, nums[i] - 1);
		}
		for(int i = 0; i < n; i++)
			if(nums[i] != i + 1)
				return i + 1;
		return n + 1;
	}

	private void swap(int[] nums, int i, int j) {
		nums[i] ^= nums[j];
		nums[j] ^= nums[i];
		nums[i] ^= nums[j];
	}

//Idea : put 1 to A[0]
int firstMissingPositive(vector<int>& nums) {
       int res = 0;
       int ln = nums.size();
       for(int i=0;i<ln;i++) {
           int c_idx = nums[i];
           if(c_idx < 0 || nums[i] == i+1 || c_idx > ln) {
           //if(c_idx < 0 || c_idx == i+1 || c_idx > ln) {
               continue;
           }
           swap(nums[c_idx - 1],nums[i]);
           if(nums[c_idx -1] != nums[i]) { //current # is not at correct location
               i--;  //reset i/ backtrack with i
           }
       }
       for(int i=0;i<ln;i++) {
           if(nums[i] != i+1) {
               return i+1;
           }
       }
       return ln+1;
}

int main() {
}
