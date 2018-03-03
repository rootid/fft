//Maximum Gap
//Given an unsorted array, find the maximum difference between the successive
//elements in its sorted form.
//Try to solve it in linear time/space.
//Return 0 if the array contains less than 2 elements.
//You may assume all elements in the array are non-negative integers and fit in
//the 32-bit signed integer range.
//################################################ Bucket Sort (Good) ########################################################
//TC  : O(n)
int maximumGap(vector<int>& nums) {
      int n = nums.size();
      if (n < 2) return 0;
      auto lu = minmax_element(nums.begin(), nums.end());
      int l = *lu.first, u = *lu.second;
      int gap = max((u - l) / (n - 1), 1);
      int m = (u - l) / gap + 1;
      vector<int> bucketsMin(m, INT_MAX); //m : buckets initlized with min and max
      vector<int> bucketsMax(m, INT_MIN);
      for (int num : nums) {
          int k = (num - l) / gap; //get the bucket #
          if (num < bucketsMin[k]) bucketsMin[k] = num;
          if (num > bucketsMax[k]) bucketsMax[k] = num;
      }
      int i = 0, j;
      gap = bucketsMax[0] - bucketsMin[0]; //max gap
      while (i < m) { //traverse all buckets
          j = i + 1;
          while (j < m && bucketsMin[j] == INT_MAX && bucketsMax[j] == INT_MIN)
              j++;
          if (j == m) break;
          gap = max(gap, bucketsMin[j] - bucketsMax[i]);
          i = j;
      }
      return gap;
  }
//################################################ Bucket Sort with Pigenhole idea ########################################################
//Suppose you have n pigeons with labels and you put them into m holes based on
//their label with each hole of the same size. Why bother putting pigeons into
//holes? Because you want to disregard the distance between pigeons within each
//one hole.
//Only when at least one hole is empty can we disregard the distance between
//pigeons within each one hole and compute the maximum gap solely by the
//distance between pigeons in adjacent holes. We make sure that at least one
//hole is empty by using m=n-1 (i.e. n-2 pigeons in n-1 holes => at least one
//hole is empty).
int maximumGap(vector<int>& nums) {
        const int n = nums.size();
        if(n<=1) return 0;
        int maxE = *max_element(nums.begin(),nums.end());
        int minE = *min_element(nums.begin(),nums.end());
        double len = double(maxE-minE)/double(n-1);
        vector<int> maxA(n,INT_MIN);
        vector<int> minA(n,INT_MAX);
        for(int i=0; i<n; i++) {
            int index = (nums[i]-minE)/len;
            maxA[index] = max(maxA[index],nums[i]);
            minA[index] = min(minA[index],nums[i]);
        }
        int gap = 0, prev = maxA[0];
        for(int i=1; i<n; i++) {
            if(minA[i]==INT_MAX) continue;
            gap = max(gap,minA[i]-prev);
            prev = maxA[i];
        }
        return gap;
    }
//We divide the range of array into array.size() interval, where k =
//(maximum-minimum) / n.
//[minimum, minimum + k), [minimum + k, minimum + 2k), ... , [minimum + (n-1)k, maximum]
//And we uses two extra array "max_in_interval" and "min_in_interval" to record
//the maximum and minimum of each interval.
//First, let's considering an uniformly distributed array of n numbers. By
//which I mean,
//[minimum, minimum + k), [minimum + k, minimum + 2k), ... , [minimum + (n-1)k, maximum]
//n intervals each contains a single number. we could easily find the maximum
//gap by calculate min_in_interval[i+1] - max_in_interval[i]
//Now comes the most important observation. If any single interval contains
//more than 1 number, then there must be an empty interval, and maximum gap is
//larger than a single interval. By which I mean if multiple numbers appear in
//the same interval, we can safely ignore the numbers which lies in the middle
//of interval(not max_in_interval nor min_in_interval).

int maximumGap(vector<int>& nums) {
    if (nums.size() < 2)
        return 0;

    int max = *max_element(nums.begin(), nums.end());
    int min = *min_element(nums.begin(), nums.end());

    double interval_length = double(max - min) / nums.size();

    vector<int> max_in_interval(nums.size(), INT_MIN);
    vector<int> min_in_interval(nums.size(), INT_MAX);

    for (auto &&each : nums) {
        size_t index = (each - min) / interval_length; // auto ceiling
        if (index == nums.size()) {  // in considering of float-point number round up
            index = nums.size() - 1;
        }
        if (max_in_interval[index] < each) {
            max_in_interval[index] = each;
        }
        if (min_in_interval[index] > each) {
            min_in_interval[index] = each;
        }
    }

    int gap = 0;
    int max_in_previous_interval = max_in_interval[0];
    for (size_t i = 0; i < nums.size() - 1; ++i) {
        if (min_in_interval[i + 1] == INT_MAX) { // skip the empty interval
            continue;
        }
        else {
            if (gap < min_in_interval[i + 1] - max_in_previous_interval) {
                gap = min_in_interval[i + 1] - max_in_previous_interval;
            }
            max_in_previous_interval = max_in_interval[i + 1];
        }
    }
    return gap;
}

//################################################ Bucket Sort ########################################################
int maximumGap(vector<int>& nums) {
      int n = nums.size();
      if (n < 2) return 0;
      auto lu = minmax_element(nums.begin(), nums.end());
      int l = *lu.first, u = *lu.second;
      int gap = max((u - l) / (n - 1), 1); //get the maxgap
      int m = (u - l) / gap + 1;
      vector<vector<int>> buckets(m, {INT_MAX, INT_MIN});
      for (int num : nums) {
          int k = (num - l) / gap;
          if (num < buckets[k][0]) buckets[k][0] = num;
          if (num > buckets[k][1]) buckets[k][1] = num;
      }
      int i = 0, j;
      gap = buckets[0][1] - buckets[0][0];
      while (i < m) {
          j = i + 1;
          while (j < m && buckets[j][0] == INT_MAX && buckets[j][1] == INT_MIN)
              j++;
          if (j == m) break;
          gap = max(gap, buckets[j][0] - buckets[i][1]);
          i = j;
      }
      return gap;
}


//################################################ Radix Sort ########################################################
int maximumGap(std::vector<int> &num) {
	for(unsigned bit = 0; bit < 31; bit++)
	std::stable_partition(num.begin(), num.end(), [bit](int a){
		return !(a & (1 << bit));
	});
	int difference = 0;
	for(std::size_t i = 1; i < num.size(); i++) {
		difference = std::max(difference, num[i] - num[i-1]);
	}
	return difference;
}

//################################################ Radix Sort ########################################################
int maximumGap(vector<int> &num) {
     if (num.size() < 2) return 0;
     int imax = num[0];
     for (int x : num) {
         if (x > imax) imax = x;
     }
     // LSD (least significant digit) radix sort
     int base = 10;
     vector<list<int>> buckets(base);
     vector<int> numbers = num;
     for (long long i = 1; i <= imax; i *= base) {
         // distribute numbers
         for (int x : numbers) {
             int index = x / i % base;
             buckets[index].push_back(x);
         }
         // put back numbers
         for (int j = 0, k = 0; j < buckets.size(); j++) {
             for (int x : buckets[j]) numbers[k++] = x;
             buckets[j].clear();
         }
     }
     int result = 0;
     for (int i = 1; i < numbers.size(); i++) {
         int gap = numbers[i] - numbers[i-1];
         if (gap > result) result = gap;
     }
     return result;
 }
