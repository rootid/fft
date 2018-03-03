//Distribute Candies
//Given an integer array with even length, where different numbers in this
//array represent different kinds of candies. Each number means one candy of
//the corresponding kind. You need to distribute these candies equally in
//number to brother and sister. Return the maximum number of kinds of candies
//the sister could gain.
//Example 1:
//Input: candies = [1,1,2,2,3,3]
//Output: 3
//Explanation:
//There are three different kinds of candies (1, 2 and 3), and two candies for
//each kind.
//Optimal distribution: The sister has candies [1,2,3] and the brother has
//candies [1,2,3], too.
//The sister has three different kinds of candies.
//Example 2:
//Input: candies = [1,1,2,3]
//Output: 2
//Explanation: For example, the sister has candies [2,3] and the brother has
//candies [1,1].
//The sister has two different kinds of candies, the brother has only one kind
//of candies.
//Note:
//The length of the given array is in range [2, 10,000], and will be even.
//The number in given array is in range [-100,000, 100,000].

//################################  #############################
int distributeCandies(vector<int>& candies) {
   return min(unordered_set<int>(candies.begin(), candies.end()).size(), candies.size() / 2);
}

//######################## Sort - O(N logN) time, O(1) space ########################
int distributeCandies(vector<int>& candies) {
   size_t kinds = 0;
   sort(candies.begin(), candies.end());
   for (int i = 0; i < candies.size(); i++) {
       kinds += i == 0 || candies[i] != candies[i - 1]; //determine unique kinds of candies
   }
   return min(kinds, candies.size() / 2);
}

//######################## bitset + determine unique candies ########################
int distributeCandies(vector<int>& candies) {
  bitset<200001> hash;
  int count = 0;
  for (int i : candies) {
      if (!hash.test(i+100000)) {
         count++;
         hash.set(i+100000);
      }
  }
  int n = candies.size();
  return min(count, n/2);
}

//########################## pytonic  ##########################
//There are len(set(candies)) unique candies, and the sister picks only
//len(candies) / 2 of them, so she can't have more than this amount.
//For example, if there are 5 unique candies, then if she is picking 4 candies,
//she will take 4 unique ones. If she is picking 7 candies, then she will only
//take 5 unique ones
//def distributeCandies(self, candies):
//    return min(len(candies) / 2, len(set(candies)))
