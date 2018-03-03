//Can Place Flowers
//Suppose you have a long flowerbed in which some of the plots are planted and
//some are not. However, flowers cannot be planted in adjacent plots - they
//would compete for water and both would die.
//Given a flowerbed (represented as an array containing 0 and 1, where 0 means
//empty and 1 means not empty), and a number n, return if n new flowers can be
//planted in it without violating the no-adjacent-flowers rule.
//Example 1:
//Input: flowerbed = [1,0,0,0,1], n = 1
//Output: True
//Example 2:
//Input: flowerbed = [1,0,0,0,1], n = 2
//Output: False
//Note:
//The input array won't violate no-adjacent-flowers rule.
//The input array size is in the range of [1, 20000].
//n is a non-negative integer which won't exceed the input array size.


//##########################################  Overwrite array ##########################################
bool canPlaceFlowers(vector<int>& bed, int n) {
  for (int i = 0; i < bed.size(); i++) {
    //[0,0,1],[1,0,0],[0,0,0]
    if (!bed[i] && (i == 0 || !bed[i - 1]) && (i == bed.size() - 1 || !bed[i + 1])) {
      bed[i] = 1; //update the bed
      n--;
    }
  }
 return n <= 0;
}

//##########################################  addition of extra plots start + end+ no overwriting of array  ##########################################
bool canPlaceFlowers(vector<int>& flowerbed, int n) {
  //add
  flowerbed.insert(flowerbed.begin(),0);
  flowerbed.push_back(0);
  for(int i = 1; i < flowerbed.size()-1; ++i) {
      if(flowerbed[i-1] + flowerbed[i] + flowerbed[i+1] == 0) {
          --n;
          ++i;
      }

  }
  return n <=0;
}


//##########################################  pytonic  ##########################################
//
//For each plot from left to right, if we can plant a flower there, then do so.
//We can plant a flower if the left neighbor is 0 (or we are on the left edge),
//AND the right neighbor is 0 (or we are on the right edge).
//def canPlaceFlowers(self, A, N):
//    for i, x in enumerate(A):
//        if (not x and (i == 0 or A[i-1] == 0)
//                and (i == len(A)-1 or A[i+1] == 0)):
//            N -= 1
//            A[i] = 1
//    return N <= 0
//

//##########################################  ugly ##########################################
//[0,0,1,0,1] n = 1 expected : true  op : false
//[1,0,0,0,1,0,0] n= 2 expected : true  op : false
bool canPlaceFlowers(vector<int>& flowerbed, int n) {
  int idx = 0;
  int sz = flowerbed.size();
  if(sz == 1 && flowerbed[0] == 0) {
    n--;
  }
  if(sz >= 2 && !flowerbed[0] && !flowerbed[1]) {
    flowerbed[0] = 1
      n--;
  }
  for(int i=1;i<sz-1;i++) {
    if( !flowerbed[i] && flowerbed[i-1] == flowerbed[i+1] && !flowerbed[i-1]) {
      flowerbed[i] = 1;
      n--;
    }
  }
  return n <= 0;
}
