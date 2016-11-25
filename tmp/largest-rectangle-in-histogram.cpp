
  int largestRectangleArea(vector<int>& heights) {
        if(heights.size()==0)  return 0;
        heights.push_back(0);
        int result=0;
        stack<int> h_stack;
        for(int i=0; i<heights.size(); i++){
            if(h_stack.empty() || heights[h_stack.top()]<=heights[i])
                h_stack.push(i);
            else{
                /*** I forget to check the stack is empty() **/
                /***while(heights[h_stack.top()]>heights[i]){ **/
                while(!h_stack.empty() && heights[h_stack.top()]>heights[i]){
                    int cur=heights[h_stack.top()];
                    h_stack.pop();
                    int len = h_stack.empty() ? i : i-h_stack.top()-1;
                    result=max(result, len*cur);
                }
                /** I forget to push_back i after pop the bigger element **/
                h_stack.push(i);
            }
        }
        return result;
    }


  string minWindow(string s, string t) {
        vector<int> v(128, 0);
        for(auto c:t) v[c]++;
        int start=0, end=0, counter=t.size();
        int m_start=0, m_len=INT_MAX;
        while(end<s.size()){
            if(v[s[end]]>0)  counter--;
            v[s[end]]--;
            end++;
            /** loop from start to check whether we can find more short string **/
            while(counter==0){
                if(m_len>end-start){
                    m_start=start;
                    m_len=end-start;
                }
                v[s[start]]++;
                if(v[s[start]]>0) counter++;
                start++;
            }
        }
        return m_len==INT_MAX ? "" : s.substr(m_start, m_len);
    }


int lengthOfLongestSubstring(string s) {
     vector<int> v(128, 0);
     int start=0, end=0;
     int m_len=INT_MIN;
     while(end<s.size()){
         if(v[s[end]]==0) m_len=max(m_len, end-start+1);
         v[s[end]]++;
         end++;
         while(v[s[end]]>0){
             v[s[start]]--;
             start++;
         }
     }
     return m_len==INT_MIN ? 0 : m_len;
 }
