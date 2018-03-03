//Largest Number
//Given a list of non negative integers, arrange them such that they form the
//largest number.
//For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.
//Note: The result may be very large, so you need to return a string instead of
//an integer.

string largestNumber(vector<int>& nums) {
    vector<string> tmpList;
    string result = "";
    for(auto n:nums) {
        tmpList.push_back(to_string(n));
    }
    sort(tmpList.begin(),tmpList.end(),[](string &s1, string &s2){ return s1+s2>s2+s1; });
    //sort(tmpList.begin(),tmpList.end(),
    //            [](const int &m,const int&n){
    //                return to_string(m)+to_string(n)>to_string(n)+to_string(m);
    for(auto str:tmpList) {
        result += str;
    }
    while(result[0]=='0' && result.length()>1) {
        result.erase(0,1);
    }
    return result;
}
