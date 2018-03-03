//Heaters
//Winter is coming! Your first job during the contest is to design a standard
//heater with fixed warm radius to warm all the houses.
//Now, you are given positions of houses and heaters on a horizontal line, find
//out minimum radius of heaters so that all houses could be covered by those
//heaters.
//So, your input will be the positions of houses and heaters seperately, and
//your expected output will be the minimum radius standard of heaters.
//Note:
//Numbers of houses and heaters you are given are non-negative and will not
//exceed 25000.
//Positions of houses and heaters you are given are non-negative and will not
//exceed 10^9.
//As long as a house is in the heaters' warm radius range, it can be warmed.
//All the heaters follow your radius standard and the warm radius will the
//same.
//Example 1:
//Input: [1,2,3],[2]
//Output: 1
//Explanation: The only heater was placed in the position 2, and if we use the
//radius 1 standard, then all the houses can be warmed.
//Example 2:
//Input: [1,2,3,4],[1,4]
//Output: 1
//Explanation: The two heater was placed in the position 1 and 4. We need to
//use radius 1 standard, then all the houses can be warmed.
//################################### binary search ###################################
int findRadius(vector<int>& houses, vector<int>& heaters) {
  sort(heaters.begin(), heaters.end());
  int res = 0;
  for (auto house: houses) {
      int left = 0, right = heaters.size() - 1, mid;
     // find first heater larger than or equal to house
      while (left <= right) {
          mid = (left + right) / 2;
          if (heaters[mid] < house) {
              left = mid + 1;
          } else  {
              right = mid - 1;
          }
      }
      if (left > 0 && left < heaters.size()) // house between two heaters
          res = max(res, min(abs(house - heaters[left - 1]), abs(heaters[left] - house)));
      else if (left >= heaters.size()) // house larger  than all heaters
          res = max(res, abs(house - heaters.back()));
      else if (left == 0) // house smaller than all heaters
          res = max(res, abs(house - heaters[left]));
      // cout << "res = " << res << endl;
  }
  return res;
}

//################################# Sort + updating the middle pointer #################################
//3 pointer solution
// two of them point at houses and heaters; the third one points at the middle position of two neighbor heaters.
int findRadius(vector<int>& houses, vector<int>& heaters) {
        int res = 0;
        // Sorting first
        sort(houses.begin(), houses.end());
        sort(heaters.begin(),heaters.end());
        // Sizes
        int s1 = houses.size();
        int s2 = heaters.size();
       // This is the position of the middle point of two neighbor heaters
        double mid = 0;
       // If house[i] < mid, the house[i] is at the left of "mid"
       // "mid" helps determine which heater the house is close to
        int j = -1;      // Index of heater
        int i = 0;       // Index of house
        while (i<s1) {
             // If the house is at the right side of "mid", we need to update "mid" and compare them again
            if (double(houses[i])>=mid) {
                ++j;
                if (j<s2-1)
                    mid = double(heaters[j] + heaters[j+1]) / 2;
                else {
                    // If this is the last heater, we can set the "mid" to the right side of the last house
                    mid = houses[s1-1] + 1;
                }
                continue;  // Compare them again
            }
            res = max(res, abs(heaters[j]-houses[i]));
            ++i;
        }
        return res;
}
//################################# Sort + 3 conditions  #################################
int findRadius(vector<int>& houses, vector<int>& heaters) {
  int radius=0;
  if(houses.empty() || heaters.empty() )
    return 0;
  sort(houses.begin(),houses.end());
  sort(heaters.begin(), heaters.end());

  int left, right, house, heater, j=0;

  //For houses < heaters[0], max radius = heaters[0] - houses[0]
  if(houses[0] <= heaters[0]) {
     radius = heaters[0] - houses[0];
     while(j<houses.size() && houses[j] <= heaters[0])
      j++;
  }
  //For heater[i-1] < houses <= heaters[i], find max radius
  for(int i = 1; i< heaters.size() && j<houses.size(); i++) {
     left = heaters[i-1];
     right = heaters[i];
     while(j<houses.size() && houses[j] <= right) {
         heater = houses[j];
         if(min(heater-left, right-heater) > radius)
          radius = min(heater-left, right-heater);
         j++;
     }
  }
  //For houses > heater[last],  max radius = house[last] - heater[last]
  heater = heaters[heaters.size() - 1];
  house = houses[houses.size() - 1];
  if(j<houses.size() && house > heater) {
     if(house - heater > radius)
      radius = house - heater;
  }

  return radius;
}
