//Create Maximum Number
//Given two arrays of length m and n with digits 0-9 representing two numbers. Create the maximum number of length k <= m + n from digits of the two. The relative order of the digits from the same array must be preserved. Return an array of the k digits. You should try to optimize your time and space complexity.
//Example 1:
//nums1 = [3, 4, 6, 5]
//nums2 = [9, 1, 2, 5, 8, 3]
//k = 5
//return [9, 8, 6, 5, 3]
//Example 2:
//nums1 = [6, 7]
//nums2 = [6, 0, 4]
//k = 5
//return [6, 7, 6, 0, 4]
//Example 3:
//nums1 = [3, 9]
//nums2 = [8, 9]
//k = 3
//return [9, 8, 9]


//To create max number of length k from two arrays, you need to create max number of length i from array one and max number of length k-i from array two, then combine them together. After trying all possible i, you will get the max number created from two arrays.
//

//######################################## O(n+m)^3 ######################################## 
class Solution {
public:
    #define MIN(a,b) (a<b?a:b)
    #define MAX(a,b) (a>b?a:b)
    // create max number of length t from single non-empty vector
    void getMax(int* num, int& len, int* result, int& t, int& sortedLen)
    {
    	int n, top = 0;
    	result[0] = num[0];
    	const int need2drop = len - t;
    	for (int i = 1; i < len; ++i){
    		n = num[i];
    		while (top >= 0 && result[top] < n && (i - top) <= need2drop) --top; // i - top means already dropped i - top numbers
    		if (i - top > need2drop){
    			sortedLen = MAX(1,top);
    			while (++top < t) result[top] = num[i++];
    			return;
    		}
    		if (++top < t) result[top] = n;
    		else top = t - 1;
    	}
    }
    // create max number of different length from single vector
    void dp(int *num, int len, int&sortedLen, int& minL, int& maxL, int *res, int &k){
    	int  j, *head, *prevhead = res;
    	const int soi = sizeof(int);
    	getMax(num, len, res, maxL,sortedLen);
    	for (int l = maxL; l > MAX(minL,1); --l){
    		head = prevhead + k;
    		memcpy(head, prevhead, l*soi);
    		for (j = sortedLen; j < l; ++j){
    			if (head[j] > head[j - 1]){
    				sortedLen = MAX(1, j - 1);
    				memcpy(head + j - 1, prevhead + j, soi*(l - j));
    				break;
    			}
    		}
    		if (j == l) sortedLen = l;
    		prevhead = head;
    	}
    }
    // merge max number created from single vector
    void merge(int* num1,int len1,int* num2,int len2,int* result,int& resSize){
    	int i = 0, j = 0, k = 0;
    	while (i < resSize){
    		if (j < len1 && k < len2){
    			if (num1[j] > num2[k])
    				result[i++] = num1[j++];
    			else if (num1[j] < num2[k])
    				result[i++] = num2[k++];
    			else{
    				int remaining1 = len1 - j, remaining2 = len2 - k, tmp = num1[j];
    				int flag = memcmp(num1 + j, num2 + k, sizeof(int) * MIN(remaining1, remaining2));
    				flag = (flag == 0 ? (remaining1>remaining2 ? 1 : -1) : flag);
    				int * num = flag > 0 ? num1 : num2;
    				int & cnt = flag > 0 ? j : k;
    				int len = flag > 0 ? len1 : len2;
    				while (num[cnt]==tmp && cnt < len && i<resSize) result[i++] = num[cnt++];
    			}
    		}
    		else if (j < len1) result[i++] = num1[j++];
    		else result[i++] = num2[k++];
    	}
    }
    
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k){
    	int soi = sizeof(int), len1 = nums1.size(), len2 = nums2.size(), step = k*soi;
    	int minL1 = MAX(0, k - len2), maxL1 = MIN(k, len1), minL2 = k - maxL1, maxL2 = k - minL1, range = maxL1 - minL1 + 1;
    	int * res = new int[range * k * 2 + 2 * k], *dp1 = res + k, *dp2 = res + range*k+k, *tmp=res+range*2*k+k;
    	memset(res, 0, step);
    	int sortedLen1 = 1, sortedLen2 = 1;
    	if (len1 == 0 && len2 > 0) getMax(&nums2[0], len2, res, k, sortedLen2);
    	else if (len1 > 0 && len2 == 0) getMax(&nums1[0], len1, res, k, sortedLen2);
    	else if (len1 > 0 && len2 > 0){
    		dp(&nums1[0], len1, sortedLen1, minL1, maxL1, dp1,k);
    		dp(&nums2[0], len2, sortedLen2, minL2, maxL2, dp2,k);
    		if (sortedLen1 + sortedLen2 > k){
    			merge(dp1 + k*(maxL1 - sortedLen1), sortedLen1, dp2 + k*(maxL2 - sortedLen2), sortedLen2, tmp, k);
    			vector<int> resv(tmp, tmp + k);
    			delete[] res;
    			return resv;
    		}
    		for (int i = minL1; i <= maxL1; ++i){
    			merge(dp1+k*(maxL1-i), i, dp2+k*(maxL2-k+i), (k-i), tmp,k);
    			if (memcmp(res, tmp, step) < 0) memcpy(res, tmp, step);
    		}
    	}
    	vector<int> resv(res, res + k);
    	delete[] res;
    	return resv;
    }
};
//######################################## O(n+m)^3 ######################################## 
class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> result(k), tmp_result(k);
        vector<vector<int> > max_num1(k + 1), max_num2(k + 1);
        //generate max numbers of size k
        genDP(nums1, max_num1, k);  
        genDP(nums2, max_num2, k);
        for(int i = 0; i <= k; i++) {
            if(max_num1[i].size() + max_num2[k - i].size() < k)
                continue;
            merge(tmp_result, max_num1, max_num2, i, k);
            if(result.empty() || smaller(result, tmp_result))
                result = tmp_result;
        }
        return result;
    }
    
private:
    void genDP(vector<int>& nums, vector<vector<int> >& max_num, int k) {
        int i, start;
        for(start = 0; nums.size() > 0; start = (i == 0 ? 0 : i - 1)) {
            if(nums.size() <= k)
                max_num[nums.size()] = nums;
            for(i = start; i + 1 < nums.size() && nums[i] >= nums[i + 1]; i++); //curr elem >= next elem
            nums.erase(nums.begin() + i);
        }
    }
    
    void merge(vector<int>& tmp_result, vector<vector<int> >& max_num1, vector<vector<int> >& max_num2, int n, int k) {
        int i, j, ii, jj;
        for(i = j = 0; i < max_num1[n].size() && j < max_num2[k - n].size(); ) {
            for(ii = i, jj = j; ii < max_num1[n].size() && jj < max_num2[k - n].size() && max_num1[n][ii] == max_num2[k - n][jj]; ii++, jj++);
            if(jj >= max_num2[k - n].size() || (ii < max_num1[n].size() && max_num1[n][ii] > max_num2[k - n][jj]))
                tmp_result[i + j] = max_num1[n][i++];
            else
                tmp_result[i + j] = max_num2[k - n][j++];
        }
        for( ; i < max_num1[n].size(); i++)
            tmp_result[i + j] = max_num1[n][i];
        for( ; j < max_num2[k - n].size(); j++)
            tmp_result[i + j] = max_num2[k - n][j];
    }
    
    bool smaller(vector<int>& result, vector<int>& tmp_result) {
        int i;
        for(i = 0; i < result.size() && result[i] == tmp_result[i]; i++);
        if(i < result.size() && result[i] < tmp_result[i])
            return true;
        return false;
    }
};

//######################################## O(n+m)^3 ######################################## 
class Solution {
private:
    //get the max k-length number of array nums ...
    vector<int> helper(vector<int>& nums, int k) {
        int n=nums.size();
        int j=0; // the count of the stacked array 
        vector<int> result(k,0);
        for(int i=0; i<n; i++){
            //result[j-1] stores the top of the stack 
            while(j>0 && n-i+j>k && nums[i]>result[j-1])  j--;
            if(j<k) result[j++]=nums[i];
        }
        return result;
    }

    vector<int> merge(vector<int>& nums1, vector<int>& nums2, int k){
        vector<int> result(k, 0);
        ostringstream num_str1, num_str2;
        string str1, str2;
        for(auto num:nums1)  num_str1 << num;
        for(auto num:nums2)  num_str2 << num;
        str1= num_str1.str();
        str2= num_str2.str();
        for(int i=0, j=0, r=0; r<k; r++) { 
          //pick max char between str1 and str2
          result[r] = str1.substr(i).compare(str2.substr(j)) > 0 ? nums1[i++] : nums2[j++];
        }
        return result;
    }

public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int n=nums1.size(), m=nums2.size();
        vector<int> result(k, 0);
        string result_str;
        for(int i=max(0, k-m); i<=k && i<=n; i++){
            vector<int> sub_1 = helper(nums1, i);
            vector<int> sub_2 = helper(nums2, k-i);
            vector<int> candidate = merge(sub_1, sub_2, k);
            ostringstream str_c;
            for(auto number:candidate) {
              str_c << number;
            }
            if(result_str=="" || str_c.str().compare(result_str) > 0 ){
                result_str=str_c.str();
                result=candidate;
            }
        }
        return result;
    }
};
