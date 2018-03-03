//IPO
//Suppose LeetCode will start its IPO soon. In order to sell a good price of
//its shares to Venture Capital, LeetCode would like to work on some projects
//to increase its capital before the IPO. Since it has limited resources, it
//can only finish at most k distinct projects before the IPO. Help LeetCode
//design the best way to maximize its total capital after finishing at most k
//distinct projects.
//You are given several projects. For each project i, it has a pure profit Pi
//and a minimum capital of Ci is needed to start the corresponding project.
//Initially, you have W capital. When you finish a project, you will obtain its
//pure profit and the profit will be added to your total capital.
//To sum up, pick a list of at most k distinct projects from given projects to
//maximize your final capital, and output your final maximized capital.
//Example 1:
//Input: k=2, W=0, Profits=[1,2,3], Capital=[0,1,1].
//Output: 4
//Explanation: Since your initial capital is 0, you can only start the project
//indexed 0.
//             After finishing it you will obtain profit 1 and your capital becomes 1.
//             With capital 1, you can either start the project indexed 1 or the project indexed 2.
//             Since you can choose at most 2 projects, you need to finish the project indexed 2 to get the maximum capital.
//             Therefore, output the final maximized capital, which is 0 + 1 + 3 = 4.
//Note:
//1. You may assume all numbers in the input are non-negative integers.
//2. The length of Profits array and Capital array will not exceed 50,000.
//3. The answer is guaranteed to fit in a 32-bit signed integer.

#include "../headers/global.hpp"

//observations
//
//1. The more capital W you have now, the more maximum capital you will
//eventually earn.
//2. Working on any doable project with positive P[i] > 0 increases your
//capital W.
//3. Any project with P[i] = 0 is useless and should be filtered away
//immediately (note that the problem only guarantees all inputs non-negative).
//4. For 0 projects or projects with 0 profit.o/p is unchanged working capital

//########################### W/O multiset ###########################
struct Node {int profit, capital;};
int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
  if(Profits.empty() || Capital.empty())
    return W;

  vector<Node*> projects; //with capital and profit
  for(int i = 0; i < Profits.size(); i++) {
      projects.push_back(new Node({Profits[i], Capital[i]}));
  }
  priority_queue<int> pq;

  //sort by capital
  sort(projects.begin(), projects.end(), [](Node* n1, Node* n2) { return n1->capital < n2->capital; });

  for(auto start = projects.begin(); k > 0; k--) {
      for(; start != projects.end() && (*start)->capital <= W; start++) {
        //iterate over all projects
        pq.push((*start)->profit);
      }
      if(pq.empty()) {
        break;
      }
      W += pq.top();
      pq.pop();
  }
  return W;
}

//
//
//
//At each stage, split projects into two categories:
//"doables": ones with C[i] <= W (store P[i] in priority_queue<int> low)
//"undoables": ones with C[i] > W (store (C[i], P[i]) in multiset<pair<int,int>> high)
//Work on most profitable project from low (low.top()) first, and update
//capital W += low.top().
//Move those previous undoables from high to doables low whose C[i] <= W.
//Repeat steps 2 and 3 until we reach maximum k projects or no more doable
//projects.
////#################################### ####################################
int findMaximizedCapital(int k, int W, vector<int>& P, vector<int>& C) {
  priority_queue<int> low;      // P[i]'s within current W
  multiset<pair<int,int> > high; // (C[i],P[i])'s' outside current W

  for (int i = 0; i < P.size(); ++i) {  // initialize low and high
    if(P[i] > 0) {  //accept project with +ve profit
      if (C[i] <= W) {
        low.push(P[i]);
      } else {
        high.emplace(C[i], P[i]); //after capital increase select the most profitable project
      }
    }
  }

  while (k-- && low.size()) {
    W += low.top(); // greedy to work on most profitable first
    low.pop();
    for (auto i = high.begin(); high.size() && i->first <= W; i = high.erase(i))  {
      low.push(i->second);
    }
  }
  return W;
}

