//Wiggle Sort
//Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....
//For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4].
//

//######################################### O(n) ######################################### 
public void wiggleSort(int[] nums) {
    int m = nums.length;
    for (int i=1;i< m;i++) {
        if(i%2 == 0) {
            if(nums[i-1] < nums[i]) swap(nums, i-1,i);
        } else {
            if(nums[i-1] > nums[i]) swap(nums, i-1,i);
        }
    }
}
private void swap(int[] nums, int i, int j) {
    int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
}

//######################################### O(n) ######################################### 
void wiggleSort(vector<int>& a) {
    for(int i=1;i<a.size();i++) {
        //even <= odd
        //odd >= even
        if(i%2 == 0) {
            if(a[i-1] < a[i]) { //if equal no need to swap
                swap(a[i-1],a[i]);
            }
        } else {
            if(a[i-1] > a[i]) {
                swap(a[i-1],a[i]);
            }
        }
    }
}

int main() {

}
