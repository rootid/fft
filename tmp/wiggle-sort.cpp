//Wiggle Sort
//Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....
//For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4].
//
void wiggleSort(vector<int>& a) {
    for(int i=1;i<a.size();i++) {
        //even <= odd
        //odd >= even
        if(i%2 == 0) {
            if(a[i-1] < a[i]) {
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
