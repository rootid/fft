//Simplify Path
//Given an absolute path for a file (Unix-style), simplify it.
//For example,
//path = "/home/", => "/home"
//path = "/a/./b/../../c/", => "/c"
//click to show corner cases.
//Corner Cases:
//    Did you consider the case where path = "/../"?
//    In this case, you should return "/".
//    Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
//    In this case, you should ignore redundant slashes and return "/home/foo"

//######################################## With Stack ########################################
public String simplifyPath(String path) {
    String[] dirs = path.split("/");
    Deque<String> stk = new ArrayDeque<>();
    String opPath = "";
    for(String dir: dirs) {
        if( dir.length() > 0 && !dir.equals(".") && !dir.equals("..") ) stk.push(dir);
        else if(!stk.isEmpty() && dir.equals("..")) stk.pop();
    }
    if(stk.isEmpty()) return "/";
    while(!stk.isEmpty())
        opPath += "/" + stk.pollLast();
     return opPath;
}

//######################################## With Stack + CPP ########################################
//
string simplifyPath(string path) {
    string res, tmp;
    vector<string> stk;
    stringstream ss(path);
    while(getline(ss,tmp,'/')) {
        if (tmp == "" or tmp == ".") continue;
        if (tmp == ".." and !stk.empty()) stk.pop_back();
        else if (tmp != "..") stk.push_back(tmp);
    }
    for(auto str : stk) res += "/"+str;
    return res.empty() ? "/" : res;
}

//######################################## With Stack ########################################
class Solution(object):
    def simplifyPath(self, path):
        places = [p for p in path.split("/") if p!="." and p!=""]
        stack = []
        for p in places:
            if p == "..":
                if len(stack) > 0:
                    stack.pop()
            else:
                stack.append(p)
        return "/" + "/".join(stack)

//######################################## With Stack ########################################
def simplifyPath(self, path):
    stack = []
    for p in path.split("/"):
      if p == "..":
        if stack: stack.pop()
      elif p and p != '.': stack.append(p)
    return "/" + "/".join(stack)


// vim: set sw=2 sts=2 tw=120 et nospell :
