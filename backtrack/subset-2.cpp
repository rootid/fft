//Iteative with BFS at each level  1. copy all previous set
//                                 2. append 
vector<vector<int> > subsets(vector<int> &S) {
    int len = S.size();
    sort(S.begin(), S.end());
    vector<vector<int> > res(1);//start by adding empty set   [ [] ]
    for(int i = 0; i < len; ++i) // BFS tree with levels = len
    {
        int resSize = res.size();
        for(int j = 0; j < resSize; j++)
        {
            res.push_back(res[j]); //[ [],[] ]
            res.back().push_back(S[i]); //[ [],[1] ]
        }
    }
  return res;
}
