//Evaluate Division
//Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0.
//Example:
//Given a / b = 2.0, b / c = 3.0. 
//queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? . 
//return [6.0, 0.5, -1.0, 1.0, -1.0 ].
//The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.
//According to the example above:
//equations = [ ["a", "b"], ["b", "c"] ],
//values = [2.0, 3.0],
//queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ]. 
//The input is always valid. You may assume that evaluating the queries will result in no division by zero and there is no contradiction.

//################################################## BFS ################################################ 
// BFS to get the value. I think the time complexity is O(N^2*query.size()), where N is the nodes number in the graph.
vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> query) {
        unordered_map<string,unordered_map<string,double>> g;
        for(int i=0;i<equations.size();i++){
            g[equations[i].first].emplace(equations[i].second,values[i]);
            g[equations[i].first].emplace(equations[i].first,1.0);
            g[equations[i].second].emplace(equations[i].first,1.0/values[i]);
            g[equations[i].second].emplace(equations[i].second,1.0);
        }
        
        vector<double> res;
        for(auto item:query){
            if(!g.count(item.first)||!g.count(item.second)) res.push_back(-1.0);
            else{
                queue<pair<string,double>> qs;
                unordered_set<string> used;
                qs.push({item.first,1.0});
                used.insert(item.first);
                bool find = false;
                while(!qs.empty()&&!find){
                    queue<pair<string,double>> nex;
                    while(!qs.empty()&&!find){
                        pair<string,double> tp = qs.front();
                        qs.pop();
                        
                        //check whether we find the divident
                        if(tp.first == item.second){
                            find = true;
                            res.push_back(tp.second);
                            break;
                        }
                        
                        for(pair<string,double> values:g[tp.first]){
                            if(used.find(values.first) == used.end()){
                                values.second *= tp.second;
                                nex.push(values);
                                used.insert(values.first);
                            }
                        }
                    }
                    
                    qs = nex;
                }
                
                if(!find) res.push_back(-1.0);
            }
        }
        
        return res;
    }
//################################################# DFS ############################################### 
vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> query) { 
  vector<double> ans(query.size()); 
  if(query.empty()) {
    return ans; 
  }
  unordered_map<string, unordered_map<string,double> > mp;
  unordered_set<string> vis;
  mp.clear();
  bool canReach = true;
  double res = 1.0, tmpres;
  for(int i = 0; i < equations.size(); ++ i) {
      mp[equations[i].first][equations[i].second] = values[i];
      mp[equations[i].second][equations[i].first] = 1.0/values[i];
  }
  for(int i = 0; i < query.size(); ++ i) {
      if(mp.find(query[i].first) == mp.end() || mp.find(query[i].second) == mp.end())
          ans[i] = -1.0;
      else{
          canReach = false;
          tmpres = 1.0;
          res = -1.0;
          vis.clear();
          vis.insert(query[i].first);
          dfs(query[i].first, query[i].second, res, tmpres, canReach, mp, vis);
          ans[i] = res;
      } 
  }
  return ans;
}
    
void dfs(string &sta, string &ends, double &res, double &tmpres, bool &canReach, unordered_map<string, unordered_map<string,double>> &mp, unordered_set<string> &vis) { 
  if(sta == ends) { 
    res = tmpres;
    canReach = true;
    return ; 
  }
  unordered_map<string,double>::iterator it = mp[sta].begin();
  double vres = 1.0;
  string u = "";
  for(; it != mp[sta].end(); ++ it){
      if(vis.find(it->first) != vis.end())
          continue;
      vres = tmpres*it->second;
      u = it->first;
      vis.insert(it->first);
      dfs(u, ends, res, vres, canReach, mp, vis);
  } 
}
//######################################### Union find ######################################### 
 vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        unordered_map<string, Node*> map;
        vector<double> res;
        for (int i = 0; i < equations.size(); i ++) {
            string s1 = equations[i].first, s2 = equations[i].second;
            if (map.count(s1) == 0 && map.count(s2) == 0) {
                map[s1] = new Node();
                map[s2] = new Node();
                map[s1] -> value = values[i];
                map[s2] -> value = 1;
                map[s1] -> parent = map[s2];
            } else if (map.count(s1) == 0) {
                map[s1] = new Node();
                map[s1] -> value = map[s2] -> value * values[i];
                map[s1] -> parent = map[s2];
            } else if (map.count(s2) == 0) {
                map[s2] = new Node();
                map[s2] -> value = map[s1] -> value / values[i];
                map[s2] -> parent = map[s1];
            } else {
                unionNodes(map[s1], map[s2], values[i], map);
            }
        }
        for (auto query : queries) {
            if (map.count(query.first) == 0 || map.count(query.second) == 0 || findParent(map[query.first]) != findParent(map[query.second]))
                res.push_back(-1);
            else
                res.push_back(map[query.first] -> value / map[query.second] -> value);
        }
        return res;
    }
    
private:
    struct Node {
        Node* parent;
        double value = 0.0;
        Node()  {parent = this;}
    };
    
    void unionNodes(Node* node1, Node* node2, double num, unordered_map<string, Node*>& map) {
        Node* parent1 = findParent(node1), *parent2 = findParent(node2);
        double ratio = node2 -> value * num / node1 -> value;
        for (auto it = map.begin(); it != map.end(); it ++)
            if (findParent(it -> second) == parent1)
                it -> second -> value *= ratio;
        parent1 -> parent = parent2;
    }
    
    Node* findParent(Node* node) {
        if (node -> parent == node)
            return node;
        node -> parent = findParent(node -> parent);
        return node -> parent;
    }


//############################### FLoyd warshall ############################### 

// "a / b = 2.0" means from point a to point b there is an edge, and its weight is 2.0. So the question is, given a query "e / f", we need to check whether e and f are connected. If yes, calculate the value, otherwise return -1. Thus, we can use Floyd method in graph to solve it.
//
typedef unordered_map<string, unordered_map<string, double>> Map;
Map m;
vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
    int n = equations.size();
    for (int i = 0; i < n; ++i) {
      m[equations[i].first][equations[i].second] = values[i];
      m[equations[i].second][equations[i].first] = 1.0 / values[i];
    }
    for (auto& kv: m)
      kv.second[kv.first] = 1.0;
    
    for (auto k = m.begin(); k != m.end(); ++k) {
      for (auto i = m.begin(); i != m.end(); ++i) {
        for (auto j = m.begin(); j != m.end(); ++j) {
          i->second[j->first] = max(i->second[j->first], i->second[k->first] * k->second[j->first]);
        }
      }
    }
    vector<double> res;
    for (const auto& q: queries) {
      auto val = m[q.first][q.second];
      res.push_back(val ? val: -1.0);
    }
    return res; 
}

//A variation of Floyd–Warshall, computing quotients instead of shortest paths. An equation A/B=k is like a graph edge A->B, and (A/B)*(B/C)*(C/D) is like the path A->B->C->D. Submitted once, accepted in 35 ms.
//def calcEquation(self, equations, values, queries):
//    quot = collections.defaultdict(dict)
//    for (num, den), val in zip(equations, values):
//        quot[num][num] = quot[den][den] = 1.0
//        quot[num][den] = val
//        quot[den][num] = 1 / val
//    for k, i, j in itertools.permutations(quot, 3):
//        if k in quot[i] and j in quot[k]:
//            quot[i][j] = quot[i][k] * quot[k][j]
//    return [quot[num].get(den, -1.0) for num, den in queries]
//
//Variation without the if (submitted twice, accepted in 68 and 39 ms):
//
//def calcEquation(self, equations, values, queries):
//    quot = collections.defaultdict(dict)
//    for (num, den), val in zip(equations, values):
//        quot[num][num] = quot[den][den] = 1.0
//        quot[num][den] = val
//        quot[den][num] = 1 / val
//    for k in quot:
//        for i in quot[k]:
//            for j in quot[k]:
//                quot[i][j] = quot[i][k] * quot[k][j]
//    return [quot[num].get(den, -1.0) for num, den in queries]
//Could save a line with for i, j in itertools.permutations(quot[k], 2) but it's longer and I don't like it as much here.
