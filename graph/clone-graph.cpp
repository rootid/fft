UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
     UndirectedGraphNode* dummyNode;
     queue<UndirectedGraphNode* > q;
     unordered_set<UndirectedGraphNode*> visited;
     unordered_map<UndirectedGraphNode*,UndirectedGraphNode*> mp;
     if(node) {
          q.push(node);
          dummyNode = new UndirectedGraphNode(node->label);
          mp[node] = dummyNode;
     }
     while(!q.empty()) {
              UndirectedGraphNode* tmpNode = q.front();
              q.pop();
              for(int i=0;i<tmpNode->neighbors.size();i++) {
                  if(mp.find(tmpNode->neighbors[i]) == mp.end()) {
                          UndirectedGraphNode* dummyNbr = new UndirectedGraphNode(tmpNode->neighbors[i]->label);
                          mp[tmpNode->neighbors[i]] = dummyNbr;
                          q.push(tmpNode->neighbors[i]);
                     }
                    mp[tmpNode]->neighbors.push_back(mp[tmpNode->neighbors[i]]);
                }
          } 
       
     return mp[node];
}
