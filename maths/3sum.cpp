//3Sum
//Given an array S of n integers, are there elements a, b, c in S such that a +
//b + c = 0? Find all unique triplets in the array which gives the sum of zero.
//Note:
//Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤
//c)
//The solution set must not contain duplicate triplets.
//    For example, given array S = {-1 0 1 2 -1 -4},
//    A solution set is:
//    (-1, 0, 1)
//    (-1, -1, 2)
//
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;



//################################################### O(n^2) ###################################################
public List<List<Integer>> threeSum(int[] nums) {
    //sort array
    //pick 1 and check rest i.e. a+b = -c
    //for duplicates continue or pick last
    Arrays.sort(nums);
    int n = nums.length;
    List<List<Integer>> result = new ArrayList<>();
    for(int i=0;i< n-2;i++) {
        if ((i>0) && (nums[i]==nums[i-1])) continue; // No duplicate a's
        int c = -nums[i];
        for(int j=i+1,k=n-1;j<k;) {
            int aPlusb = nums[j] + nums[k];
            if(aPlusb == c) {
                result.add(Arrays.asList(nums[i],nums[j],nums[k]));
                while( j+1 < k && nums[j] == nums[j+1]) { j++; continue;} // No duplicate b's
                while( k-1 > j && nums[k] == nums[k-1]) { k--; continue;} // No duplicate c's
                j++; k--;
            }
            else if(aPlusb > c) k--;
            else j++;
        }
    }
    return result;
}
//################################################### O(n^2) ###################################################
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    for (unsigned int i=0; i<nums.size(); i++) {
        if ((i>0) && (nums[i]==nums[i-1]))
            continue;
        int l = i+1, r = nums.size()-1;
        while (l<r) {
            int s = nums[i]+nums[l]+nums[r];
            if (s>0) r--;
            else if (s<0) l++;
            else {
                res.push_back(vector<int> {nums[i], nums[l], nums[r]});
                while (nums[l]==nums[l+1]) l++;
                while (nums[r]==nums[r-1]) r--;
                l++; r--;
            }
        }
    }
    return res;
}

//################################################### O(n^2) ###################################################
vector<vector<int> > threeSum(vector<int>& nums) {
  vector<vector<int> > triplet;
  int len = nums.size();
  if(len < 3) {
      return triplet;
  }
  sort(nums.begin(),nums.end());
  for(int i=0;i<len;i++) {
    int a = nums[i];
    int j = i + 1;
    int k = len - 1;
    while(j < k) {
      int b = nums[j];
      int c = nums[k];
      //cout << " ---> a,b,c = " << a << "," << b << "," << c << endl;
      //cout << " ---> j,k = " << j << "," << k << endl;
      if(a + b + c  == 0) {
        cout << " a,b,c = " << a << "," << b << "," << c << endl;
        triplet.push_back({a,b,c});
        while(b == nums[j+1] && j<k) {
          j++;
        }
        while(c == nums[k-1] && j<k) {
          k--;
        }
        j++;
        k--;
      } else if (a+b+c < 0) {
        while( j<k && b == nums[j+1] ) {
          j++;
        }
        j++;
      } else {
        while(j<k && c == nums[k-1] ) {
          k--;
        }
        k--;
      }
    }
    while(i + 1<len && a == nums[i+1] ) { //avoid a duplicates
      i++;
    }
  }
  return triplet;
}

//##################################################### O(n^2) #####################################################
//O(n^2) : can we do better?
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;

    sort(nums.begin(), nums.end());

    for (auto i = 0; i < nums.size();) {
        auto target = -nums[i];
        int l = i + 1, u = nums.size() - 1;

        while (l < u) {
            auto sum = nums[l] + nums[u];

            if (sum < target)
                while (nums[++l] == nums[l - 1]);  // Processing duplicates of Number 2
            else if (sum > target)
                while (nums[--u] == nums[u + 1]);  // Processing duplicates of Number 3
            else {
                result.push_back(vector<int>{nums[i], nums[l], nums[u]});
                while (nums[++l] == nums[l - 1]);  // Processing duplicates of Number 2
                while (nums[--u] == nums[u + 1]);  // Processing duplicates of Number 3
            }

        }

        // Processing duplicates of Number 1
        while (nums[++i] == nums[i - 1]);
    }

    return result;
}


//######################################### 3Sum using 2 Sum #########################################
void twoSum(vector<int>& nums,int cIdx,int ltIdx,int rtIdx,int target,vector<vector<int>>& result) {
    while(ltIdx < rtIdx) {
        if(nums[ltIdx] + nums[rtIdx] > target) {
            rtIdx -= 1;
        } else if (nums[ltIdx] + nums[rtIdx] < target) {
            ltIdx += 1;
        } else {
            result.push_back(vector<int>{nums[cIdx], nums[ltIdx], nums[rtIdx]});
            int l = nums[ltIdx];
            int r = nums[rtIdx];
            while( ltIdx < rtIdx &&  l == nums[ltIdx]) {
              ltIdx += 1;
            }
            while(ltIdx < rtIdx && r == nums[rtIdx]) {
              rtIdx -= 1;
            }
        }
   }
}

vector<vector<int>> threeSum(vector<int>& nums) {
  int len = nums.size();
  if(len <=2) return {};
  sort(nums.begin(),nums.end());
  vector<vector<int>> result;
  for(int i=0;i<len-2;i++) {
    int target = -nums[i];
    int ltIdx = i+1;
    int rtIdx = len-1;
    int cIdx = i;
    twoSum(nums,cIdx,ltIdx,rtIdx,target,result);
    while( i < len && nums[i] == nums[i+1]) {
        i = i+1;
    }
  }
  return result;
}
int main(int argc, char *argv[])
{

  //int a[] =  {1,-1,-1,0};
  //int a[] =  {-2,0,0,2,2};
  //int a[] = {-2,0,1,1,2};
  int a[] = {-1,0,1,2,-1,-4};
  //int a[] = {1,2,-2,-1};
  vector<int> r (a,a+sizeof(a)/sizeof(a[0]));
  threeSum(r);
  return 0;
}
//vector<int> twoSum(int target,int idx,vector<int>& nums) {
//  vector<int> result;
//  unordered_map<int,int> idxMap;
//  int len = nums.size();
//  for(int i=idx;i<len;i++) {
//    int r = target - nums[idx];
//    if(idxMap.find(r) != idxMap.end()) {
//      return vector<int> {idxMap[r],idx};
//    }
//    idxMap[ nums[idx] ] = i;
//  }
//  return vector<int> {};
//}
//vector<vector<int>> threeSum(vector<int>& nums) {
//  vector<vector<int> > result;
//  vector<int> partialResult;
//  int i = 0;
//  int len = nums.size();
//  if(len < 3) {
//      return result;
//  }
//  for(int i=0;i<len;i++) {
//    int target = -nums[i];
//    partialResult= twoSum(target,i,nums);
//    if(partialResult.size() > 1) {
//      partialResult.push_back(i);
//      sort(partialResult.begin(),partialResult.end());
//      result.push_back(partialResult);
//    }
//  }
//  return result;
//}
//

