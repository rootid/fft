//Relative Ranks
//Given scores of N athletes, find their relative ranks and the people with the
//top three highest scores, who will be awarded medals: "Gold Medal", "Silver
//Medal" and "Bronze Medal".
//Example 1:
//Input: [5, 4, 3, 2, 1]
//Output: ["Gold Medal", "Silver Medal", "Bronze Medal", "4", "5"]
//Explanation: The first three athletes got the top three highest scores, so
//they got "Gold Medal", "Silver Medal" and "Bronze Medal".
//For the left two athletes, you just need to output their relative ranks
//according to their scores.
//Note:
//N is a positive integer and won't exceed 10,000.
//All the scores of athletes are guaranteed to be unique.


//####################### Use priority queue ##################################
vector<string> findRelativeRanks(vector<int>& nums) {
  priority_queue<pair<int,int> > pq;
  for(int i=0;i<nums.size();i++) {
      pq.push(make_pair(nums[i],i));
      //pq.push({nums[i], i});
  }
  vector<string> res(nums.size(),"");
  int count = 1;
  for(int i=0; i<nums.size();i++) {
      if(count == 1) {
        res[pq.top().second] = "Gold Medal";
      } else if(count==2) {
        res[pq.top().second] = "Silver Medal";
      } else if(count==3) {
        res[pq.top().second] = "Bronze Medal";
      } else {
        res[pq.top().second] = to_string(count);
      }
      pq.pop();
      count++;
  }
  return res;
}

//################################## Map with sort ##################################
vector<string> findRelativeRanks(vector<int>& nums) {
     unordered_map<int, int> num2Idx; int i = 0;
     for (int n : nums) num2Idx[n] = i++; // build map: num -> index
     sort(nums.begin(), nums.end());

     vector<string> rank(i), medals{"Gold Medal", "Silver Medal", "Bronze Medal"};
     for (int n : nums) rank[num2Idx[n]] = i>3? to_string(i--) : medals[--i];
     return rank;
}
