 
//3,4 : q = 0
//INT_MAX 
//9,3 = 3 
//3+3+3
//9,3 = (a-b) = 6
//6 3*6 = 18 = 3*6 = 18
//3*3 = 9      3*3 = 9
//3*2 = 6      
//16,2   = 10 * 2
          = 8*2
          = 6*2 = 12
//10 2* = 5*2
//10 2*8 
    //9,12 = 0
   //9,9 += 1
  //9,6  += 2
//9,3 +=3
  
  //8,1 = 7 
  
  9,3 = 4 * 3
  
//log(n)
int helper(int a,int b) { 
     int high = b;
     int low = 0;
     while(high > low) {       
         int mid = low + (high-low)/2;          // 9,3 = mid 4,1,2,3
         if(mid * b == a) {                       high = 3
             return mid;                          low = 0,1,3
         } 
         if(mid *b > a) {
             high = mid - 1;
         } else {
             low = mid + 1;
         }
     }
     return low;
}
int get_quotient(int a,int b) {
    
    int count = 0;
    if(a < b) { //3<4
        return count;
    }
    count = helper(a,b); //b = a
    return count;
}
