//Container With Most Water
//Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.
//Note: You may not slant the container and n is at least 2.

//############################################ Reduction ############################################ 
//Idea same as  bfs/trapping-rain-water.cpp
int maxArea(vector<int>& height) {
    int water = 0;
    int l = 0, r = height.size() - 1;
    //widest to highest
    while (l < r) {
        int h = min(height[l], height[r]);
        water = max(water, (r - l) * h);
        while (height[l] <= h && l < r) {
          l++;
        }
        while (height[r] <= h && l < r) {
          r--;
        }
    }
    return water;
}


//############################################ Same as above added extra equn ############################################ 
//           / max{v(i, j), S(i...j-1)};  height(i) >= height(j)
//S(i..j) = |
//           \ max{v(i, j), S(i+1...j)};  height(i) < height(j)

int maxArea(vector<int>& height) { 
  int lo = 0;
  int hi = height.length - 1;
  int maxV = 0;
  while(lo < hi) {
      int min = min(height[lo], height[hi]);
      maxV = max(max, min * (hi - lo));
      while(lo <= hi && height[lo] <= min) {
        lo++;
      }
      while(lo <= hi && height[hi] <= min) { 
        hi--;
      }
  }
  return maxV;
}

int main() {

}
