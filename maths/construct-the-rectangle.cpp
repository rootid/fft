//Construct the Rectangle
//For a web developer, it is very important to know how to design a web page's
//size. So, given a specific rectangular web page’s area, your job by now is to
//design a rectangular web page, whose length L and width W satisfy the
//following requirements:
//1. The area of the rectangular web page you designed must equal to the given
//target area.
//2. The width W should not be larger than the length L, which means L >= W.
//3. The difference between length L and width W should be as small as
//possible.
//You need to output the length L and the width W of the web page you designed
//in sequence.
//Example:
//Input: 4
//Output: [2, 2]
//Explanation: The target area is 4, and all the possible ways to construct it
//are [1,4], [2,2], [4,1].
//But according to requirement 2, [1,4] is illegal; according to requirement 3,
//[4,1] is not optimal compared to [2,2]. So the length L is 2, and the width W
//is 2.
//Note:
//The given area won't exceed 10,000,000 and is a positive integer
//The web page's width and length you designed must be positive integers.
//Subscribe to see which companies asked this question.


//######################################## Growing length ########################################
//
vector<int> constructRectangle(int area) {
  if(area <= 0) {
     return {};
  }
  vector<int> res({area,1});
  int target = 0;
  for(int l = 1 ; l * l <= area ; l++) {
    if(area % l == 0) {
      res[0] = l;
      res[1] = area / l;
    }
  }
  if(res[0] < res[1]) {
      std::swap(res[0],res[1]);
  }
  return res;
}

//###################################### Always compute min diff ########################################
vector<int> constructRectangle(int area) {
     if(area <= 0) {
        return {};
     }
     vector<int> res(2);
     int L = area, W = 1; //4,1
     int dif = area - 1;  //3
     for(int i = 1; i <= sqrt(area); ++i) {
         int l = area/i;  //4/1
         if(l * i == area && l >= i && l - i < dif) {
             L = l;
             W = i;
             dif = l - i;
         }
     }
    res[0] = L, res[1] = W;
    return res;
}
