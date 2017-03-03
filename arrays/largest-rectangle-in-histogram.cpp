//Largest Rectangle in Histogram
//Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.
//Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].
//The largest rectangle is shown in the shaded area, which has area = 10 unit.
//For example,
//Given heights = [2,1,5,6,2,3],
//return 10.

//################################################## Stack ################################################## 
//same as bfs/trapping-rain-water-ii.cpp
int largestRectangleArea(vector<int>& heights) { 
  if(heights.empty()) {
    return 0;
  }
  heights.push_back(0);
  int result=0;
  stack<int> h_stack;
  for(int i=0; i<heights.size(); i++) { 
    if(h_stack.empty() || heights[h_stack.top()] <= heights[i]) { //monotonic increase push 
      h_stack.push(i) ; 
    } else{ 
      while(!h_stack.empty() && heights[h_stack.top()] > heights[i]) {  //remove larger ht rectangles 
        int old_top = heights[h_stack.top()];
        h_stack.pop();
        int len = h_stack.empty() ? i : i-h_stack.top()-1;
        result = max(result, len* old_top); 
      } 
      h_stack.push(i); 
    } 
  } 
  return result; 
}


//############################## DNC  ############################## 
// T(n) = 2T(n/2) + O(n) = O(n log n)
int maxCombineArea(const vector<int> &height, int s, int m, int e) {
    // Expand from the middle to find the max area containing height[m] and height[m+1]
    int i = m, j = m+1;
    int area = 0, h = min(height[i], height[j]);
    while(i >= s && j <= e) { // <-------- i  j --------->
      h = min(h, min(height[i], height[j])); //pick min-ht with max-area
        area = max(area, (j-i+1) * h);
        if (i == s) {
            ++j;
        } else if (j == e) {
            --i;
        } else {
            // if both sides have not reached the boundary,
            // compare the outer bars and expand towards the bigger side
            if (height[i-1] > height[j+1]) { // <-------- i  j --------->
                --i;
            } else {
                ++j;
            }
        }
    }
    return area;
}
int maxArea(const vector<int> &height, int s, int e) {
    // if the range only contains one bar, return its height as area
    if (s == e) {
        return height[s];
    }
    // otherwise, divide & conquer, the max area must be among the following 3 values
    int m = s + (e-s)/2;
    int area = maxArea(height, s, m); // 1 - max area from left half
    area = max(area, maxArea(height, m+1, e));  // 2 - max area from right half
    area = max(area, maxCombineArea(height, s, m, e)); // 3 - max area across the middle
    return area;
}
int largestRectangleArea(vector<int> &height) {
    if (height.empty()) {
        return 0;
    }
    return maxArea(height, 0, height.size()-1);
}

