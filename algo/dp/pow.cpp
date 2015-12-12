

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
