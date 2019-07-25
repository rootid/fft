//Trapping Rain Water
//Given n non-negative integers representing an elevation map where the width
//of each bar is 1, compute how much water it is able to trap after raining.
//For example,
//Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.

#include "../headers/global.hpp"

//############################### W/O stack only reduction ###############################
int trap(vector<int>& height) {
  int l = 0, r = height.size()-1, level = 0, water = 0;
  while (l < r) {
    //cout << "l = " << l << "," << height[l] << " r = " << r << "," << height[r] << endl;
    int lower;
    if(height[l] < height[r])
      lower = height[l++];
     else
      lower = height[r--];

    //int lower = height[height[l] < height[r] ? l++ : r--];
    level = max(level, lower);
    water += level - lower;
    //cout << "level = " <<  level << " water = " << water  << " lower = " << lower<< endl;
  }

  return water;
}

//############################### with stack + store monotonically decreasing ###############################
int trap(vector<int>& height)  {
  stack<int> s;
  int max_water(0);
  int i(0);
  while (i < height.size()) {
      if (s.empty() || height[s.top()] >= height[i])  //monotonic decreaing then add
          s.push(i++);
       else {
          //Obs : we need at least 3 bars to hold the water
          int oldTop = height[s.top()];
          s.pop(); //remove 1 so at least 1 must left
          max_water += s.empty() ? 0 : ( (min(height[i],height[s.top()])-oldTop) * (i-s.top()-1));
	   }
  }
  return max_water;
}


int main () {
  vector<int> t {0,1,0,2,1,0,1,3,2,1,2,1;
  trap(t);
}
