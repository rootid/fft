//Flip Game II
//You are playing the following Flip Game with your friend: Given a string that
//contains only these two characters: + and -, you and your friend take turns
//to flip two consecutive "++" into "--". The game ends when a person can no
//longer make a move and therefore the other person will be the winner.
//Write a function to determine if the starting player can guarantee a win.
//For example, given s = "++++", return true. The starting player can guarantee
//a win by flipping the middle "++" to become "+--+".
//Follow up:
//Derive your algorithm's runtime complexity.


//######################################### Backtracking  #########################################
public boolean canWin(String s) {
	s = s.replace('-', ' ');
    int G = 0;
    List<Integer> g = new ArrayList<>();
    for (String t : s.split("[ ]+")) {
        int p = t.length();
        if (p == 0) continue;
        while (g.size() <= p) {
            char[] x = t.toCharArray();
            int i = 0, j = g.size() - 2;
            while (i <= j)
                x[g.get(i++) ^ g.get(j--)] = '-';
            g.add(new String(x).indexOf('+'));
        }
        G ^= g.get(p);
    }
    return G != 0;
}

//######################################### Backtracking #########################################
//The idea is try to replace every "++" in the current string s to "--" and see
//if the opponent can win or not, if the opponent cannot win, great, we win!
//For the time complexity, here is what I thought, let's say the length of the
//input string s is n, there are at most n - 1 ways to replace "++" to "--"
//(imagine s is all "+++..."), once we replace one "++", there are at most (n -
//2) - 1 ways to do the replacement, it's a little bit like solving the
//N-Queens problem, the time complexity is (n - 1) x (n - 3) x (n - 5) x ...,
//so it's O(n!!), double factorial.
public boolean canWin(String s) {
  if (s == null || s.length() < 2) {
    return false;
  }

  for (int i = 0; i < s.length() - 1; i++) {
    if (s.startsWith("++", i)) {
      String t = s.substring(0, i) + "--" + s.substring(i + 2);

      if (!canWin(t)) {
        return true;
      }
    }
  }
  return false;
}

//######################################### Backtracking With Memoization #########################################
public boolean canWin(String s) {
    if(s == null || s.length() < 2) return false;

    Set<String> winSet = new HashSet<String>();
    return canWin(s, winSet);
}

public boolean canWin(String s, Set<String> winSet){
    if(winSet.contains(s)) return true;

    for(int i = 0; i < s.length() - 1; i++) {
        if(s.charAt(i) == '+' && s.charAt(i + 1) == '+') {

            String sOpponent = s.substring(0, i) + "--" + s.substring(i + 2);
            if(!canWin(sOpponent, winSet)) {
                winSet.add(s);
                return true;
            }
        }
    }
    return false;
}

//######################################### Backtracking  With Memoization #########################################
public boolean canWin(String s) {
     HashMap<String, Boolean> h = new HashMap();
     return canWin(s.toCharArray(), h);
 }

private boolean canWin(char[] c, HashMap<String, Boolean> h) {
	for (int i = 1; i < c.length; i++)
         if (c[i] == '+' && c[i - 1] == '+') {
             c[i] = '-'; c[i - 1] = '-';

             boolean t;
             String key = String.valueOf(c);
             if (!h.containsKey(key)) {
                 t = canWin(c, h);
                 h.put(key, t);      //System.out.println(key + " --> " + t);
             } else {
                 t = h.get(key);     //System.out.println(key + " ==> " + t);
             }   // can not directly use if (t) return true here, cuz you need to restore

             c[i] = '+'; c[i - 1] = '+';
             if (!t) return true;
         }
     return false;
 }

//######################################### Backtracking  #########################################
//
//backtracking seems to be the only feasible solution to this problem.
//We can basically try every possible move for the first player (Let's call him
//1P from now on),
//and recursively check if the second player 2P has any chance to win.
//If 2P is guaranteed to lose, then we know the current move 1P takes must be
//the winning move.

int len;
string ss;
bool canWin(string s) {
    len = s.size();
    ss = s;
    return canWin();
}
bool canWin() {
    for (int is = 0; is <= len-2; ++is) {
        if (ss[is] == '+' && ss[is+1] == '+') {
            ss[is] = '-'; ss[is+1] = '-';
            bool wins = !canWin();
            ss[is] = '+'; ss[is+1] = '+';
            if (wins) return true;
        }
    }
    return false;
}

//Now let's check the time complexity: Suppose originally the board of size N
//contains only '+' signs, then roughly we have:
//T(N) = (N-2) * T(N-2) = (N-2) * (N-4) * T(N-4) ... = (N-2) * (N-4) * (N-6) *
//... ~ O(N!!)
//DP will reduce TC upto O(N^2) by Sprague–Grundy theorem (S-G) From Game
//Theory (impartial game, Normal Play vs Misere Play))

//######################################### Backtracking  #########################################
bool canWin(string s) {
    replace(s.begin(), s.end(), '-', ' ');
    istringstream in(s);
    int G = 0;
    vector<int> g;
    for (string t; in >> t; ) {
        int p = t.size();
        while (g.size() <= p) {
            string x = t;
            int i = 0, j = g.size() - 2;
            while (i <= j)
                x[g[i++] ^ g[j--]] = '-';
            g.push_back(x.find('+'));
        }
        G ^= g[p];
    }
    return G;
}

//######################################### Backtracking  #########################################
def canWin(self, s):
    g, G = [0], 0
    for p in map(len, re.split('-+', s)):
        while len(g) <= p:
            g += min(set(range(p)) - {a^b for a, b in zip(g, g[-2::-1])}),
        G ^= g[p]
    return G > 0

