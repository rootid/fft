//Next Permutation
//Implement next permutation, which rearranges numbers into the
//lexicographically next greater permutation of numbers.
//If such arrangement is not possible, it must rearrange it as the lowest
//possible order (ie, sorted in ascending order).
//The replacement must be in-place, do not allocate extra memory.
//Here are some examples. Inputs are in the left-hand column and its
//corresponding outputs are in the right-hand column.
//1,2,3 → 1,3,2
//3,2,1 → 1,2,3
//1,1,5 → 1,5,1

//################################################ Narayan Pandit algo ################################################
void nextPermutation(vector<int>& nums) {
  int k = -1;
  //Find largest index : k
 	for (int i = nums.size() - 2; i >= 0; i--) {
 		if (nums[i] < nums[i + 1]) {
 			k = i;
 			break;
 		}
 	}

  //array is sorted in descending order
  if (k == -1) {
 	    reverse(nums.begin(), nums.end());
 	    return;
 	}

  //Find largest index : l > k
 	int l = -1;
 	for (int i = nums.size() - 1; i > k; i--) {
 		if (nums[i] > nums[k]) {
 			l = i;
 			break;
 		}
 	}
 	swap(nums[k], nums[l]);

  //Reverse from k+1 till end
 	reverse(nums.begin() + k + 1, nums.end());
}


//################################# built in function #################################
void nextPermutation(vector<int>& nums) {
    next_permutation(begin(nums), end(nums));
}

//################################# lib function #################################
void nextPermutation(vector<int>& nums) {
    auto i = is_sorted_until(nums.rbegin(), nums.rend());
    if (i != nums.rend())
        swap(*i, *upper_bound(nums.rbegin(), i, *i));
    reverse(nums.rbegin(), i);
}
//################################# NP algo modified #################################
void nextPermutation(vector<int>& nums) {
    int i = nums.size() - 1, k = i;
    while (i > 0 && nums[i-1] >= nums[i]) {
        i--;
    }
    for (int j=i; j<k; j++, k--) {
        swap(nums[j], nums[k]);
    }
    if (i > 0) {
        k = i--;
        while (nums[k] <= nums[i]) {
            k++;
        }
        swap(nums[i], nums[k]);
    }
}
