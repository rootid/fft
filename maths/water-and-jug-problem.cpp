//Water and Jug Problem
//You are given two jugs with capacities x and y litres. There is an infinite amount of water supply available. You need to determine whether it is possible to measure exactly z litres using these two jugs.
//If z liters of water is measurable, you must have z liters of water contained within one or both buckets by the end.
//Operations allowed:
//Fill any of the jugs completely with water.
//Empty any of the jugs.
//Pour water from one jug into another till the other jug is completely full or the first jug itself is empty.
//Example 1: (From the famous "Die Hard" example)
//Input: x = 3, y = 5, z = 4
//Output: True
//Example 2:
//Input: x = 2, y = 6, z = 5
//Output: False

//########################### GCD way ########################### 
bool canMeasureWater(int x, int y, int z) {
    if(x + y < z) { //(1,1 z=10) You must have z liters of water contained within one or both buckets by the end.
      return false;
    }
    //case x or y is zero
    if( x == z || y == z || x + y == z ) 
      return true;
    
    //get GCD, then we can use the property of Bézout's identity
    return z % GCD(x, y) == 0;
}

int GCD(int a, int b){
    while(b != 0 ){
        int temp = b;
        b = a%b;
        a = temp;
    }
    return a;
}

//##################### BFS way using nodes as states ##################### 
bool canMeasureWaterbfs(int x, int y, int z) {
 if(z > x+y || z < 0) return false; 
   if(z == 0) return true;
   if(x < y) return canMeasureWaterbfs(y, x, z);
   //assert x >= y
   vector<char> visited(x+1, 0);
   //bfs
   queue<int> bfsQ;
   bfsQ.push(x);
   visited[x] = 1;
   while(!bfsQ.empty()) {
       int w = bfsQ.front();
       bfsQ.pop();
       if(w == z || w + y == z) return true;
       if( w <= y) {
           //water in Y
           if(w + x == z) return true;
           if(!visited[x - (y - w)]) { 
               bfsQ.push(x - (y - w));
               visited[x - (y - w)] = 1;
           }
       }
       //water in X
       int diffX = x - w;
       if(diffX >= y) {
           if(!visited[w + y]) { 
               bfsQ.push(w+y);
               visited[w + y] = 1;
           }
       }else {
           if(!visited[y - diffX]) {
               bfsQ.push(y - diffX);
               visited[y - diffX] = 1;
           }
       }

   }
   return false;
}
