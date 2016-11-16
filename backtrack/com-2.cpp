vector<vector<int> > combine(int n, int k) {
         vector<vector<int> >res;
         vector<int>tmpres;
         //Maximum value of bit = (1<<n) - (1<<(n-k))
         for(int bit = (1<<k) - 1; bit <= (1<<n) - (1<<(n-k)); bit = NextN(bit))
         {
             tmpres.clear();
             for(int i = 0; i < n; i++)
             {
                 if(bit & (1<<i))
                     tmpres.push_back(i+1);
             }
             res.push_back(tmpres);
         }
         return res;
}
//Returns the smallest integer M that is greater than N, so that the binary representation of M and N has the same number 1
int NextN(int N) 
{ 
     int x = N&(-N);      
     int t = N+x; 
     return t | ((N^t)/x)>>2; 
 }
