//Implement pow(x, n).
//Example 1:
//Input: 2.00000, 10
//Output: 1024.00000
//Example 2:
//Input: 2.10000, 3
//Output: 9.26100

//#########################################  T: log(n) #########################################  
public double myPow(double x, int n) {
    if(n == 0) return 1;
    double r =  myPow(x, n/2);
    if(n%2 == 0) return r*r;
    if(n < 0) return 1/x * r * r;  
    return x * r * r;
}

//######################################### Ugly ######################################### 
// TC : O(log n)
public double myPow(double x, int n) {
    if(n == 0) return 1;
    if(n == 1) return x;
    if(n == -1) return 1/x;
    double r =  myPow(x, n/2);
    if(n%2 == 0) return r*r;
    else { 
        if(n < 0) return 1/x * r * r;  
        return x * r * r;
    }
}

// Complexity
double pow(double x, int n) {
    if ( n == 1) {
          return x;
    } else if (n == 0) {
         return 1;
    } else if ( n == -1) {
         return 1/x;
    } else {
        double cache_result = pow(x,n/2);
        if ( n % 2 == 0) {
            return (cache_result * cache_result);
        } else {
            if (n > 0) {
             return (cache_result * cache_result * x);
            } else {
                return (cache_result * cache_result * 1/x);
            }
        }
    }
}
