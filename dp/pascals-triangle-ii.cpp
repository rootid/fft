//Given an index k, return the kth row of the Pascal's triangle.
//For example, given k = 3,
//Return [1,3,3,1].
//Note:
//Could you optimize your algorithm to use only O(k) extra space?
#include "../headers/global.hpp"


//######################## O(k) #########################
public List<Integer> getRow(int rowIndex) {
    rowIndex++;
    int[] result = new int[rowIndex];
    result[0] = 1;
    for(int i=1;i<rowIndex;i++) {
        for(int j=i;j>=1;j--)  
            result[j] += result[j-1];
    }
    return Arrays.stream(result).boxed().collect(Collectors.toList());
	//return Arrays.asList(result);
}

//######################## GOOD #########################
vector<int> getRow(int rowIndex) { 
  int k = rowIndex;
  vector<int> rv(k+1,0);
  rv[0] = 1;
  for(int i=1;i<=k;i++) { 
        for(int j=i;j>=1;j--) {
            rv[j] += rv[j-1];
        }
  }
  return rv;
}
//######################## NC sol #########################
//Observing : T[j] + T[j-1]
//T[i][j] = T[i-1][j] + T[i-1][j-1] if i>0 && j>0
//      Or
//         =  1  if i=0
//      Or
//         =  T[i-1][j]  if j=0
vector<int> getRow(int rowIndex) {  
   vector<int> result(rowIndex+2,0);
   result[1]=1;  
   for(int i =0; i< rowIndex; i++)  {  
    for(int j =rowIndex+1; j>0; j--)  {  
      result[j] = result[j] + result[j-1];  
    }  
   }  
   result.erase(result.begin());  
   return result;  
}  

//######################## Python #########################
class Solution:
    # @return a list of integers
    def getRow(self, rowIndex):
        
        array = [1]*(rowIndex+1)

        for i in range(1,rowIndex+1):
            for j in range(i-1,0,-1):
                array[j] += array[j-1]

        return array

int main() {
  getRow(3);
}
