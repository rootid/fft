//Can I Win
//In the "100 game," two players take turns adding, to a running total, any
//integer from 1..10. The player who first causes the running total to reach or
//exceed 100 wins.
//What if we change the game so that players cannot re-use integers?
//For example, two players might take turns drawing from a common pool of
//numbers of 1..15 without replacement until they reach a total >= 100.
//Given an integer maxChoosableInteger and another integer desiredTotal,
//determine if the first player to move can force a win, assuming both players
//play optimally.
//You can always assume that maxChoosableInteger will not be larger than 20 and
//desiredTotal will not be larger than 300.
//Example
//Input:
//maxChoosableInteger = 10
//desiredTotal = 11
//Output:
//false
//Explanation:
//No matter which integer the first player choose, the first player will lose.
//The first player can choose an integer from 1 up to 10.
//If the first player choose 1, the second player can only choose integers from
//2 up to 10.
//The second player will win by choosing 10 and get a total = 11, which is >=
//desiredTotal.
//Same with other integers chosen by the first player, the second player will
//always win.
//

//########################################## DFS ##########################################
//Player1 can win if and only if they can make a move after which player2 will
//lose no matter how they move.
//Main Idea : So we can check all possible moves of player1 and call the same
//function to see if player2 will lose after this move.
//I use caching to memorize states for each possible desiredTotal and set of
//chosable integers. Since maxChoosableInteger is not greater than 20, all
//currently possible moves can be represented as a bit flag.
private :
  bool canWin(int key, int desiredTotal,vector<unordered_map<int,bool>> &cache, int mx) {
        if(cache[desiredTotal-1].find(key) != cache[desiredTotal-1].end())
           return cache[desiredTotal-1][key];
        for(int i = mx-1; i >= 0;--i) {
           if(key & (1 << i)) {
               key ^= (1 << i);
               if(i+1 >= desiredTotal || !canWin(key,desiredTotal-i-1,cache,mx)) {
                  cache[desiredTotal-1][key] = true;
                  key |= (1 << i);
                  return true;
               }
               key |= (1 << i);
           }
        }
        cache[desiredTotal-1][key] = false;
        return false;
    }
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if(desiredTotal <= 1)
          return true;
        if(maxChoosableInteger*(maxChoosableInteger+1) < desiredTotal*2)
           return false;
        vector<unordered_map<int,bool> > cache(desiredTotal);
        vector<bool> v(maxChoosableInteger,true);
        int key = (1 << maxChoosableInteger)-1;
        return canWin(key,desiredTotal,cache,maxChoosableInteger);
    }


//########################################## Minmax + DP  ##########################################
private:
    unordered_map<unsigned int,bool> cache;
    bool play(int target, unsigned int used, int size){
        if(cache.find(used) != cache.end()) return cache[used];
        //exist available integer >= target, return true
        if(target-1<size && (used > (1<<target-1))){
            cache[used] = true;
            return true;
        }
        int bit = 1;
        for(int i = 0; i<size; i++,bit <<=1){
            if((used & bit)== 0) continue; // the (i+1)th bit is '0', means (i+1) is used
            used ^= bit;
            if(!play(target-i-1,used,size)){
                used |= bit;
                cache[used] = true;
                return true;
            }
            used |= bit;
        }
        cache[used] =  false;
        return false;
    }
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if(maxChoosableInteger>=desiredTotal) return true;
        //sum of numbers from 1 to maxChoosableInteger, which is (1+maxChoosableInteger)*maxChoosableInteger/2 is less than desiredTotal and desiredTotal will never be reached.
        if((1 + maxChoosableInteger) * maxChoosableInteger / 2 < desiredTotal) return false;
        unsigned int used = (1<<maxChoosableInteger)-1; // use bit to record which number has been used (bit '1' means available, bit '0' means used)
        return play(desiredTotal,used,maxChoosableInteger);
    }


//########################################## Minmax + DP  ##########################################
//
//The key part for the top-down dp strategy is that we need to avoid repeatedly
//solving sub-problems. Instead, we should use some strategy to "remember" the
//outcome of sub-problems. Then when we see them again, we instantly know their
//result. By doing this, we can always reduce time complexity from exponential
//to polynomial.
//(EDIT: Thanks for @billbirdh for pointing out the mistake here. For this problem, by applying the memo, we at most compute for every subproblem once, and there are O(2^n) subproblems, so the complexity is O(2^n) after memorization. (Without memo, time complexity should be like O(n!))
//For this question, the key part is: what is the state of the game?
//Intuitively, to uniquely determine the result of any state, we need to know:
//The unchosen numbers
//The remaining desiredTotal to reach
//A second thought reveals that 1) and 2) are actually related because we can
//always get the 2) by deducting the sum of chosen numbers from original
//desiredTotal.
//Then the problem becomes how to describe the state using 1).
//In my solution, I use a boolean array to denote which numbers have been
//chosen, and then a question comes to mind, if we want to use a Hashmap to
//remember the outcome of sub-problems, can we just use Map<boolean[], Boolean>
//? Obviously we cannot, because the if we use boolean[] as a key, the
//reference to boolean[] won't reveal the actual content in boolean[].
//Since in the problem statement, it says maxChoosableInteger will not be
//larger than 20, which means the length of our boolean[] array will be less
//than 20. Then we can use an Integer to represent this boolean[] array. How?
//Say the boolean[] is {false, false, true, true, false}, then we can transfer
//it to an Integer with binary representation as 00110. Since Integer is a
//perfect choice to be the key of HashMap, then we now can "memorize" the
//sub-problems using Map<Integer, Boolean>.
//The rest part of the solution is just simulating the game process using the
//top-down dp.
//
public class Solution {
    Map<Integer, Boolean> map;
    boolean[] used;
    public boolean canIWin(int maxChoosableInteger, int desiredTotal) {
        int sum = (1+maxChoosableInteger)*maxChoosableInteger/2;
        if(sum < desiredTotal) return false;
        if(desiredTotal <= 0) return true;

        map = new HashMap();
        used = new boolean[maxChoosableInteger+1];
        return helper(desiredTotal);
    }

    public boolean helper(int desiredTotal){
        if(desiredTotal <= 0) return false;
        int key = format(used);
        if(!map.containsKey(key)){
    // try every unchosen number as next step
            for(int i=1; i<used.length; i++){
                if(!used[i]){
                    used[i] = true;
     // check whether this lead to a win (i.e. the other player lose)
                    if(!helper(desiredTotal-i)){
                        map.put(key, true);
                        used[i] = false;
                        return true;
                    }
                    used[i] = false;
                }
            }
            map.put(key, false);
        }
        return map.get(key);
    }

// transfer boolean[] to an Integer
    public int format(boolean[] used){
        int num = 0;
        for(boolean b: used){
            num <<= 1;
            if(b) num |= 1;
        }
        return num;
    }
}

//################################################# DP #########################################################
bool canIWin(int maxChoosableInteger, int desiredTotal) {
  if(desiredTotal <= 0) return true;
  if(maxChoosableInteger >= desiredTotal) {
    return true;
  }
  if(maxChoosableInteger * (maxChoosableInteger + 1) / 2 < desiredTotal) return false;

  unordered_map<int, bool> mp;
  return helper(maxChoosableInteger, desiredTotal, 0, mp);
}

//Next state/winning state depends on
//1. The unchoosen number 2. Remaining total
private:
    bool helper(int mci, int dt, int cur, unordered_map<int, bool> &mp) {
        if(mp.count(cur)) {
          return mp[cur];
        }
        for(int i = 0; i < mci; i++) {
          //cur : map of selected values (11000) : select 1,2 ,do not selected 3-5
          if((cur & (1 << i)) == 0 && (dt <= i + 1 || !helper(mci, dt - i - 1, cur | (1 << i), mp))) {
              return mp[cur] = true;
           }
        }
        return mp[cur] = false;
    }
