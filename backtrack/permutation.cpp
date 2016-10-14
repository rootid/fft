//Given a collection of distinct numbers, return all possible permutations.
//For example,
//[1,2,3] have the following permutations:
//[
//  [1,2,3],
//  [1,3,2],
//  [2,1,3],
//  [2,3,1],
//  [3,1,2],
//  [3,2,1]
//]


vector<vector<int>> permute(vector<int>& nums) {

    

}

////////////////Leetcode passed, iterative ///////////////////////////
/**            [  1 , 2  ]
                 ^  ^  ^
insert 3:        |  |  |    there are 3 positions to insert

**/
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> result;
    vector<vector<int>> buffer;
    result.push_back(vector<int>());

    for(int i=0; i<nums.size(); ++i){
        int vec_n = result.size();
        for(int j=0; j<vec_n; ++j){
            int vec_size = result[j].size();
            for(int k=0; k<=vec_size; ++k){
                vector<int> tmp(result[j]);
                tmp.insert(tmp.begin()+k, nums[i]);
                buffer.push_back(tmp);
            }
        }
        result=buffer;
        buffer.clear();
    }

    return result;
}

//Move semantics
//
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> v(1,vector<int>());
    for (int i = 0; i < nums.size(); ++i) {
        vector<vector<int>> tv(move(v));
        for (int j = 0; j < tv.size(); ++j) {
            for (int k = 0; k <= tv[0].size(); ++k) {
                vector<int> tmp(tv[j]);
                tmp.insert(tmp.begin()+k,nums[i]);
                v.push_back(move(tmp));
            }
        }
    }
    return v;
}


private:
vector<vector<int> > v;
vector<int> save;
vector<bool> visit;

public:
vector<vector<int> > permute(vector<int> &num) {
    v.clear();
    int size = num.size();
    
    visit.resize(size);
    save.resize(size);
    
    fill(visit.begin(), visit.end(), false);

    dfs(num, 0, size);
    return v;
}
void dfs(vector<int> num, int now, int size){
    if(now == size){
        v.push_back(save);
        return;
    }
    
    for(int i = 0; i < size; i++){
        if(!visit[i]){
            visit[i] = true;
            save[now] = num[i];
            dfs(num, now + 1, size);
            visit[i] = false;
        }
    }
}

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ret;
        int n = nums.size();
        if (n == 0)
            return ret;
        
        if (n == 1)
        {
            ret.push_back(nums);
            return ret;
        }
        
        int i = 0, j = 0, len = 0;
        vector<int> curNums;
        vector<int> per;
        vector<vector<int>> temp;
        
        for (i = 0; i < n; i++)
        {
            curNums = nums;
            curNums.erase(curNums.begin()+i);
            temp = permute(curNums);
            len = temp.size();
            
            for (j = 0; j < len; j++)
            {
                per = temp[j];
                per.push_back(nums[i]);
                ret.push_back(per);
            }
        }
            
        return ret;
    }



