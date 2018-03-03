//Baseball Game
//You're now a baseball game point recorder.
//Given a list of strings, each string can be one of the 4 following types:
//Integer (one round's score): Directly represents the number of points you get
//in this round.
//"+" (one round's score): Represents that the points you get in this round are the sum of the last two valid round's points.
//"D" (one round's score): Represents that the points you get in this round are the doubled data of the last valid round's points.
//"C" (an operation, which isn't a round's score): Represents the last valid round's points you get were invalid and should be removed.
//Each round's operation is permanent and could have an impact on the round
//before and the round after.
//You need to return the sum of the points you could get in all the rounds.
//Example 1:
//Input: ["5","2","C","D","+"]
//Output: 30
//Explanation:
//Round 1: You could get 5 points. The sum is: 5.
//Round 2: You could get 2 points. The sum is: 7.
//Operation 1: The round 2's data was invalid. The sum is: 5.
//Round 3: You could get 10 points (the round 2's data has been removed). The
//sum is: 15.
//Round 4: You could get 5 + 10 = 15 points. The sum is: 30.
//Example 2:
//Input: ["5","-2","4","C","D","9","+","+"]
//Output: 27
//Explanation:
//Round 1: You could get 5 points. The sum is: 5.
//Round 2: You could get -2 points. The sum is: 3.
//Round 3: You could get 4 points. The sum is: 7.
//Operation 1: The round 3's data is invalid. The sum is: 3.
//Round 4: You could get -4 points (the round 3's data has been removed). The
//sum is: -1.
//Round 5: You could get 9 points. The sum is: 8.
//Round 6: You could get -4 + 9 = 5 points. The sum is 13.
//Round 7: You could get 9 + 5 = 14 points. The sum is 27.
//Note:
//The size of the input list will be between 1 and 1000.
//Every integer represented in the list will be between -30000 and 30000.

//##################### T : O(n) , S : O(n) #####################
int calPoints(vector<string>& ops) {
       vector<int> pt;
       for (auto& s : ops) {
           if (s == "C")
               pt.pop_back();
           else if (s == "D")
               pt.push_back(pt.back() * 2);
           else if (s == "+")
               pt.push_back(pt[pt.size() - 2] + pt[pt.size() - 1]);
           else
               pt.push_back(stoi(s));
       }
       return accumulate(pt.begin(), pt.end(), 0);
}
//################ Stack  ################
   public int calPoints(String[] ops) {
        Stack<Integer> myStack = new Stack<>();
        int score = 0;
        int temp1 = 0;
        int temp2 = 0;
        for (int i = 0; i < ops.length; i++) {
            if (ops[i].equals("+")) {
                temp1 = myStack.pop();
                temp2 = temp1 + myStack.peek();
                myStack.push(temp1);
                myStack.push(temp2);
                score += temp2;
            } else if (ops[i].equals("D")) {
                temp2 = 2 * myStack.peek();
                myStack.push(temp2);
                score += temp2;
            } else if(ops[i].equals("C")) {
                score -= myStack.pop();
            } else {
                temp2 = Integer.parseInt(ops[i]);
                myStack.push(temp2);
                score += temp2;
            }
        }
        return score;
    }

//##### python  #####
class Solution(object):
    def calPoints(self, ops):
        # Time: O(n)
        # Space: O(n)
        history = []
        for op in ops:
            if op == 'C':
                history.pop()
            elif op == 'D':
                history.append(history[-1] * 2)
            elif op == '+':
                history.append(history[-1] + history[-2])
            else:
                history.append(int(op))
        return sum(history)

//######################################### cpp #########################################
int calPoints(vector<string>& ops){
        vector<int> r{};
        for (string& op : ops){
            if      (op=="C"){ r.pop_back(); }
            else if (op=="D"){ r.push_back(2*r.back()); }
            else if (op=="+"){ r.push_back(r.end()[-2]+r.end()[-1]); }
            else             { r.push_back(stoi(op)); }
        }
        return accumulate(r.begin(), r.end(), 0);
    }

//######################################### Java #########################################
public int calPoints(String[] ops) {
		Stack<Integer> score = new Stack<Integer>();
		for (String op : ops) {
			if (op.equals("C"))
				score.pop();
			else if (op.equals("D"))
				score.push(score.peek() * 2);
			else if (op.equals("+")) {
				int lastNum = score.pop();
				int sum = lastNum + score.peek();
				score.push(lastNum);
				score.push(sum);
			} else
				score.push(Integer.parseInt(op));
		}
		int ret = 0;
		while (!score.empty())
			ret += score.pop();
		return ret;
	}

