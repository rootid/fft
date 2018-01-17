// Unique Binary Search Trees
//Given n, how many structurally unique BST's (binary search trees) that store values 1...n?
//For example,
//Given n = 3, there are a total of 5 unique BST's.
//   1         3     3      2      1
//    \       /     /      / \      \
//     3     2     1      1   3      2
//    /     /       \                 \
//   2     1         2                 3

 //res += catalan(i-1)*catalan(n-i);


//#################################### Catlan # + Memoization #################################### 
//T = O(n^2)
// compute C(n), we will need to compute all of the C(i) values between 0 and n­1,
Map<Integer,Integer> map = new HashMap<>();
public int numTrees(int n) {
 	if (n <= 1) return 1; //base case
    if(map.containsKey(n)) return map.get(n);
    int res = 0;
    for(int i=1;i<=n;i++) {
         res += numTrees(i-1)*numTrees(n-i); //recursion case
    }
    map.put(n, res);
    return res;
}

//#################################### Catlan #  #################################### 
//O(3 ^ N)
//https://stackoverflow.com/questions/27371612/catalan-numbers-recursive-function-time-complexity
//n implies exactly 2(n-1) recursive calls,
int numTrees(int n) {
	if (n <= 1) return 1; //base case
	int res = 0;
    for(int i=1;i<=n;i++) {
		 res += numTrees(i-1)*numTrees(n-i); //recursion case
	}
	return res;
}


//#################################### Math + O(n^2) #################################### 
int numTrees(int n) {
    vector<int> G(n+1,0);
    G[0] = 1;
    G[1] = 1;
    //think of 2 rulers one starts early  
    for(int i=2;i<=n;i++) {
        for(int j=1;j<=i;j++) {
            G[i] += G[j-1] * G[i-j];  //left part * right par
        }
    }
    return G[n];
}
/*    
Hope it will help you to understand :
    
    n = 0;     null   
    
    count[0] = 1
    
    
    n = 1;      1       
    
    count[1] = 1 
    
    
    n = 2;    1__       			 __2     
    		      \					/ 
    		     count[1]	   	count[1]	
    
    count[2] = 1 + 1 = 2
    
    
    
    n = 3;    1__				      __2__	                   __3
    		      \		            /       \			      /		
    		  count[2]		  count[1]    count[1]		count[2]
    
    count[3] = 2 + 1 + 2  = 5
    
    
    
    n = 4;    1__  					__2__					   ___3___                  
    		      \				 /        \					  /		  \			
    		  count[3]		 count[1]    count[2]		  count[2]   count[1]
    
                 __4				
               /
           count[3]   
    
    count[4] = 5 + 2 + 2 + 5 = 14     
    
And  so on...
*/


int numTrees(int n) { 
	if(n == 0) return 0;
}
