//Restore IP Addresses
//Given a string containing only digits, restore it by returning all possible valid IP address combinations.
//For example:
//Given "25525511135",
//return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
//################################################### BT + Pruning ###################################################
//step : # of elements
void dfs(string s,int start,int step,string ip,vector<string>& result) {
    int len = s.size(); 
    if(start == len && step==4) {
        ip.erase(ip.end()-1); //remove the last '.' from the last decimal number
        result.push_back(ip);
        return;
    }
    //Pruning
    if(len-start > (4-step)*3) 
      return;
    if(len-start < (4-step)) return;
    int num = 0;
    //Always pick 3 elements //233
    for(int i=start;i< start+3 ;i++){
        num=num*10+ (s[i]-'0');
        if(num <= 255) {
            ip+=s[i];
            dfs(s,i+1,step+1,ip+'.',result);
        }
        if(num==0) break;
    }
}
vector<string> restoreIpAddresses(string s) { 
  vector<string> result;
  string ip;
  dfs(s,0,0,ip,result); //paras:string s,start index of s,step(from0-3),intermediate ip,final result
  return result;
}
//####################################### Iteration with Octets  ##########################################
vector<string> restoreIpAddresses(string s) {
    vector<string> ret;
    string ans;
    //12.345.34.456
    for (int a=1; a<=3; a++) //ends at a Each interval of length = 3
    for (int b=1; b<=3; b++) //ends at b
    for (int c=1; c<=3; c++) //ends at c
    for (int d=1; d<=3; d++) //ends at d
        if (a+b+c+d == s.length()) {
            int A = stoi(s.substr(0, a));
            int B = stoi(s.substr(a, b));
            int C = stoi(s.substr(a+b, c));
            int D = stoi(s.substr(a+b+c, d));
            if (A<=255 && B<=255 && C<=255 && D<=255)
                if ( (ans = to_string(A)+"."+to_string(B)+"."+to_string(C)+"."+to_string(D)).length() == s.length()+3)
                    ret.push_back(ans);
        }    
    return ret;
}

//####################################### Recursion with generating 4 octets ###########################################
vector<string> restoreIpAddresses(string s) {
    vector<string> result;
    restoreIp(s, result, 0, "", 0);
    return result;
}
void restoreIp(string ip, vector<string>& result, int idx, string restored, int count) {
    if (count > 4) return;
    if (count == 4 && idx == ip.length()) {
      result.push_back(restored);
    }
    for (int i=1;i<=3; i++) {
        if (idx+i > ip.length()) {
          break;
        }
        string s = ip.substr(idx,i);
        if ((s.length()>1 && s[0] == '0') || (i==3 && stoi(s) >= 256)) continue;
        restoreIp(ip, result, idx+i, restored+s+ (count == 3?"" : "."), count+1);
    }
}
