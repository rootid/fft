//Given a sorted integer array where the range of elements are [lower, upper] inclusive, return its missing ranges.
//For example, given [0, 1, 3, 50, 75], lower = 0 and upper = 99, return ["2", "4->49", "51->74", "76->99"].
//

#include "../headers/global.hpp"
//[-2147483648, 2147483647] -2147483648 2147483647
//Expected output: ["-2147483647->2147483646"]

//######################################### Forward Traversal  ######################################### 
public List<String> findMissingRanges(int[] nums, int lower, int upper) {
      List<String> list = new ArrayList<String>();
      if(nums == null) return list;
      int n = nums.length;
      for(int i = 0; i <= n; i++) {
          int lt = (i == 0) ? lower : nums[i - 1] + 1;
          int gt = (i == n) ? upper : nums[i] - 1;
          addRange(list, lt, gt);
      }
      return list;
  }
private void addRange(List<String> list, int lo, int hi) {
      if(lo > hi) return;
      else if(lo == hi) list.add(String.valueOf(lo));
      else list.add(lo + "->" + hi);
}


//######################################### Traverse Backwards ######################################### 
public List<String> findMissingRanges(int[] nums, int lower, int upper) {
     //[0, 1, 3, 50, 75], return [“2”, “4->49”, “51->74”, “76->99”]
    int uL = upper;
    int lL = lower;
    int m = nums.length - 1;
    Deque<String> missingRangeDeque = new ArrayDeque<>();
    while(end >= start) {
        String missingRange = "";
        if(nums[end] == uL) uL--;
        else {
            if(nums[end]+ 1 == uL)
                missingRange += String.valueOf(nums[end]+ 1);
            else
                 missingRange += String.valueOf(nums[end]+ 1) + "->" + uL;
            missingRangeDeque.push(missingRage);
            uL = nums[end] -1;
        }
    }
	return missingRangeDeque.stream().collect(Collectors.toList()); //it returns FIFO ordering not LIFO
}



//######################################### Forward traversal  ######################################### 
vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
    // key here: make inclusive range exclusive to avoid corner cases
    // now problem becomes finding inclusive ranges between the pair of numbers: 
    // {lower, nums[0], ..., nums[n], upper} 
    if(lower == INT_MIN) {
      lower++;
    } else {
      lower--;    
    }
    if(upper != INT_MAX) { //eg. 1,99,100 1,2147483647,2147483647 NOTE : (x,x+1), (x,x) : are same
      upper++; //INT_MAX ?
    }

    vector<string> res;
    nums.push_back(upper);      
    int pre = lower;
    for (int i=0; i<nums.size(); ++i) {
        // case 1: pair (x, x) or (x, x+1) has no range between them (4,5)
        //if (nums[i] <= pre+1) { //(4,5)
        if (nums[i] <= pre || nums[i] - pre == 1) { //(4,5)
            pre = nums[i];
            continue;
        }
        // case 2: pair (x, x+2) use one single integer to represent the range
        if (nums[i] - pre == 2) { //(4,6)
            res.push_back(to_string(pre+1));
        }
        // case 3: regular ranges
        else { 
            res.push_back(to_string(pre+1)+"->"+to_string(nums[i]-1));
        }
        pre = nums[i];
    }
    // recover the input if needed
    nums.pop_back();
    cout << res.size() << endl;
    return res;

}

int main() {

  vector<int>  t;
  findMissingRanges (t,1,1);
}
