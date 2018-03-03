//Restore IP Addresses
//Given a string containing only digits, restore it by returning all possible
//valid IP address combinations.
//For example:
//Given "25525511135",
//return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)


//####################################### Recursion ###########################################
//1. Each section has at most 3 elements
//2. Use of section to hold the result
public List<String> restoreIpAddresses(String s) {
    List<String> ret = new LinkedList<>();
    int[] section = new int[4];
    helper(ret, s, 0,  section, 0);
    return ret;
}

void helper(List<String> acc, String s, int k, int[] section,  int segment){
    if(segment == 4 && k == s.length() ){
        acc.add(section[0] + "." + section[1] + "."+ section[2] + "." + section[3]);
        return ;
    }
 	for(int len = 1; len <= 3 && k + len <= s.length() && segment < 4 ; len++) {
        int val = Integer.parseInt(s.substring(k, k + len)); //take all substring upto length = 3
        // range check, no leading 0. | Pruniing
        if(val > 255 || len >= 2  && s.charAt(k) == '0')
            break;
        section[segment] = val;
        helper(acc, s, k + len, section, segment + 1); //pick the next segment
        section[segment] = -1; // for debug.
    }
}

//####################################### Recursion ###########################################
public List<String> restoreIpAddresses(String s) {
    List<String> list = new ArrayList();
    if(s.length() > 12) return list;
    helper(s, list, 0, "", 0);
    return list;
}

void helper(String s, List<String> list, int k, String res, int sec){
  if(sec == 4 && k == s.length()) {
    list.add(res);
    return;
  }
  for(int i = 1; i <= 3; i++) {
    if(k + i > s.length()) break;
    String section = s.substring(k, k + i);
	//Pruning
    if(section.length() > 1 && section.startsWith("0") || Integer.parseInt(section) >= 256)  break;

    helper(s, list, k + i, sec == 0 ? section : res + "." + section, sec + 1);
  }
}



//################################################### Iterative version ###################################################
//O(3^4)
public List<String> restoreIpAddresses(String s) {
        List<String> result = new ArrayList<>();
        int len = s.length();
        String ans = "";
        for(int a=1;a <=3;a++)
            for(int b=1;b <=3;b++)
                for(int c=1;c <=3;c++)
                    for(int d=1;d <=3;d++)
                        if(a+b+c+d == len) {
                            int A = Integer.parseInt(s.substring(0,a));
                            int B = Integer.parseInt(s.substring(a,a+b));
                            int C = Integer.parseInt(s.substring(a+b,a+b+c));
                            int D = Integer.parseInt(s.substring(a+b+c,a+b+c+d));
                            if(A <= 255 && B <= 255 && C <= 255 && D <= 255) {
                                ans = String.valueOf(A) + "." + String.valueOf(B) + "." + String.valueOf(C) + "." + String.valueOf(D);
                                if(ans.length() == len + 3) result.add(ans);
                                ans = "";
                            }
                        }
        return result;
    }
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
