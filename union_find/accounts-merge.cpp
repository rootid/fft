//Accounts Merge
//Given a list accounts, each element accounts[i] is a list of strings, where
//the first element accounts[i][0] is a name, and the rest of the elements are
//emails representing emails of the account.
//Now, we would like to merge these accounts. Two accounts definitely belong to
//the same person if there is some email that is common to both accounts. Note
//that even if two accounts have the same name, they may belong to different
//people as people could have the same name. A person can have any number of
//accounts initially, but all of their accounts definitely have the same name.
//After merging the accounts, return the accounts in the following format: the
//first element of each account is the name, and the rest of the elements are
//emails in sorted order. The accounts themselves can be returned in any order.
//Example 1:
//Input:
//accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John",
//"johnnybravo@mail.com"], ["John", "johnsmith@mail.com",
//"john_newyork@mail.com"], ["Mary", "mary@mail.com"]]
//Output: [["John", 'john00@mail.com', 'john_newyork@mail.com',
//'johnsmith@mail.com'],  ["John", "johnnybravo@mail.com"], ["Mary",
//"mary@mail.com"]]
//Explanation:
//The first and third John's are the same person as they have the common email
//"johnsmith@mail.com".
//The second John and Mary are different people as none of their email
//addresses are used by other accounts.
//We could return these lists in any order, for example the answer [['Mary',
//'mary@mail.com'], ['John', 'johnnybravo@mail.com'],
//['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
//Note:
//The length of accounts will be in the range [1, 1000].
//The length of accounts[i] will be in the range [1, 10].
//The length of accounts[i][j] will be in the range [1, 30].

//######################################### DFS - Creat Undirected graph #########################################
class Solution {
    //Focus on emails rather than key (key is confusing)
    //Find connected components among emails
    //Key must be used for lookups
    //ll'ar to the 2 party system
    //2 john, 1 mary
    //
    //js->john, john_ny
    //traverse 2 times
    //1. (Jhn-> [JSM, JM] ), Jhn[]
    //To represent as graph -> hw to handl2 2 john
    public List<List<String>> accountsMerge(List<List<String>> acts) {
        //how to focus on the emails only
        //DFS on emails
        Map<String, String> emlLkp = new HashMap<>();
        Map<String, List<String>> undgrph = new HashMap<>(); // assctn amg emails
        List<List<String>> rst = new ArrayList<>();
        //1 -email -> rest emails, each email -> 1 email i.e. prepare undirected graph
        for(List<String> acct: acts) {
            String name = acct.get(0);
            for(int i=1;i<acct.size();i++) {
                String email = acct.get(i);
                //List<String> tmpList;
                //if(!undgrph.containsKey(acct.get(1)))
                //   tmpList = new ArrayList();
                //else
                //    tmpList = undgrph.get(acct.get(1));
                //tmpList.add(email);
                //undgrph.put(acct.get(1), tmpList); //
                //List<String> tmpList2;
                //if(!undgrph.containsKey(email))
                //   tmpList2 = new ArrayList();
                //else
                //    tmpList2 = undgrph.get(email);
                //tmpList2.add(acct.get(1));
                //undgrph.put(email, tmpList2);
                undgrph.computeIfAbsent(email, x-> new ArrayList<String>()).add(acct.get(1));
                undgrph.computeIfAbsent(acct.get(1), x-> new ArrayList<String>()).add(email);
                emlLkp.put(email, name);
            }
        }
        //DFS visit to find the connected components
        Stack<String> stk = new Stack<>();
        Set<String> seen = new HashSet<>();
        for(String email: undgrph.keySet()) {
            if(!seen.contains(email)) {
                stk.push(email);
                List<String> ccmpt = new ArrayList<>();
                seen.add(email);
                while(!stk.isEmpty()) {
                    String tmpEmail = stk.pop();
                    ccmpt.add(tmpEmail);
                    List<String> nemls = undgrph.get(tmpEmail);
                    for(String emls : nemls) {
                        if(!seen.contains(emls)) {
                            seen.add(emls);
                            stk.push(emls);
                        }
                    }
                }
                Collections.sort(ccmpt);
                ccmpt.add(0, emlLkp.get(email));
                rst.add(ccmpt);
            }
        }
        return rst;
    }
}



//######################################### W/ Union find #########################################
class Solution {
    public List<List<String>> accountsMerge(List<List<String>> accounts) {
        DSU dsu = new DSU();
        Map<String, String> emailToName = new HashMap();
        Map<String, Integer> emailToID = new HashMap();
        int id = 0;
        for (List<String> account: accounts) {
            String name = "";
            for (String email: account) {
                if (name == "") {
                    name = email;
                    continue;
                }
                emailToName.put(email, name);
                if (!emailToID.containsKey(email)) {
                    emailToID.put(email, id++);
                }
                dsu.union(emailToID.get(account.get(1)), emailToID.get(email));
            }
        }

        Map<Integer, List<String>> ans = new HashMap();
        for (String email: emailToName.keySet()) {
            int index = dsu.find(emailToID.get(email));
            ans.computeIfAbsent(index, x-> new ArrayList()).add(email);
        }
        for (List<String> component: ans.values()) {
            Collections.sort(component);
            component.add(0, emailToName.get(component.get(0)));
        }
        return new ArrayList(ans.values());
    }
}
class DSU {
    int[] parent;
    public DSU() {
        parent = new int[10001];
        for (int i = 0; i <= 10000; ++i)
            parent[i] = i;
    }
    public int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    public void union(int x, int y) {
        parent[find(x)] = find(y);
    }
}

//######################################### DFS - new appraoch #########################################
//We give each account an ID, based on the index of it within the list of
//accounts.
//[
//["John", "johnsmith@mail.com", "john00@mail.com"], # Account 0
//["John", "johnnybravo@mail.com"], # Account 1
//["John", "johnsmith@mail.com", "john_newyork@mail.com"],  # Account 2
//["Mary", "mary@mail.com"] # Account 3
//]
//Next, build an emails_accounts_map that maps an email to a list of accounts,
//which can be used to track which email is linked to which account. This is
//essentially our graph.
//# emails_accounts_map of email to account ID
//{
//  "johnsmith@mail.com": [0, 2],
//  "john00@mail.com": [0],
//  "johnnybravo@mail.com": [1],
//  "john_newyork@mail.com": [2],
//  "mary@mail.com": [3]
//}
//Next we do a DFS on each account in accounts list and look up
//emails_accounts_map to tell us which accounts are linked to that particular
//account via common emails. This will make sure we visit each account only
//once. This is a recursive process and we should collect all the emails that
//we encounter along the way.
//Lastly, sort the collected emails and add it to final results, res along with
//the name.

class Solution(object):
    def accountsMerge(self, accounts):
        from collections import defaultdict
        visited_accounts = [False] * len(accounts)
        emails_accounts_map = defaultdict(list)
        res = []
        # Build up the graph.
        for i, account in enumerate(accounts):
            for j in range(1, len(account)):
                email = account[j]
                emails_accounts_map[email].append(i)
        # DFS code for traversing accounts.
        def dfs(i, emails):
            if visited_accounts[i]:
                return
            visited_accounts[i] = True
            for j in range(1, len(accounts[i])):
                email = accounts[i][j]
                emails.add(email)
                for neighbor in emails_accounts_map[email]:
                    dfs(neighbor, emails)
        # Perform DFS for accounts and add to results.
        for i, account in enumerate(accounts):
            if visited_accounts[i]:
                continue
            name, emails = account[0], set()
            dfs(i, emails)
            res.append([name] + sorted(emails))
        return res
