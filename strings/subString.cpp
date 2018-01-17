

//You are given two strings, A and B. Find if there is a substring of minimum length 2 that 
//appears in both A and B.

s = "bac" //ba
t = "lacpd"


//wnd = 2
//a = "acacacacacacacacaca"
//b = "bdbdbdbdbdbdbdbdbdb"

bool isSubstring (string s,string t,int wnd =2 )  {
    
    unordered_set<string> u_set;
    for (int i=0;i<s.length() - wnd;i++) {
        u_set.push_back(s.substr(i,wnd) ); //la,ac,cp,pd
    }

    for (int j=0;j<t.length()- wnd;j++) {
        if (u_set.find (t.substr(i,wnd) ) != u_set.end() ) {
            return true;
        }
    }
    return false;
}



boolean isSubstring(String A, String B){
    if(A==null || B==null){
        return false;
    }

    Set<String> keys = new HashSet<String>();

    for(int i=0;i<A.length-1;i++){
        keys.put(A[i]+A[i+1]);
    }

    for(int j=0;j<B.length-1;j++){
        if(keys.contains(B[j]+B[j+1])){
            return true;
        }
    }

    return false;

}



