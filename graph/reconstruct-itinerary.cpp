//Reconstruct Itinerary
//Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.
//Note:
//If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string. For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
//All airports are represented by three capital letters (IATA code).
//You may assume all tickets form at least one valid itinerary.
//Example 1:
//tickets = [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
//Return ["JFK", "MUC", "LHR", "SFO", "SJC"].
//Example 2:
//tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
//Return ["JFK","ATL","JFK","SFO","ATL","SFO"].
//Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"]. But it is larger in lexical order.

//################################### post order DFS #################################
vector<string> findItinerary(vector<pair<string, string>> tickets) {
		// Each node (airport) contains a set of outgoing edges (destination).
		unordered_map<string, multiset<string>> graph;
		// We are always appending the deepest node to the itinerary, 
		// so will need to reverse the itinerary in the end.
		vector<string> itinerary;
		if (tickets.size() == 0){
			return itinerary;
		}
		// Construct the node and assign outgoing edges
		for (pair<string, string> eachTicket : tickets){
			graph[eachTicket.first].insert(eachTicket.second);
		}
		stack<string> dfs;
		dfs.push("JFK");
		while (!dfs.empty()){
			string topAirport = dfs.top();
			if (graph[topAirport].empty()){
				// If there is no more outgoing edges, append to itinerary
				// Two cases: 
				// 1. If it searchs the terminal end first, it will simply get
				//    added to the itinerary first as it should, and the proper route
				//    will still be traversed since its entry is still on the stack.
				// 2. If it search the proper route first, the dead end route will also
				//    get added to the itinerary first.
				itinerary.push_back(topAirport);
				dfs.pop();
			}
			else {
				// Otherwise push the outgoing edge to the dfs stack and 
				// remove it from the node.
				dfs.push(*(graph[topAirport].begin()));
				graph[topAirport].erase(graph[topAirport].begin());
			}
		}
		// Reverse the itinerary.
		reverse(itinerary.begin(), itinerary.end());
		return itinerary;
}
//##################### Using Hierholzer's algorithm ##################### 
//In short,find the Euler path
unordered_map<string, priority_queue<string, vector<string>, greater<string>> > graph; vector<string> result;

void dfs(string vtex) {
    auto & edges = graph[vtex];
    while (!edges.empty())
    {
        string to_vtex = edges.top();
        edges.pop();
        dfs(to_vtex);
    }
    result.push_back(vtex);
}
vector<string> findItinerary(vector<pair<string, string>> tickets) {
    for (auto e : tickets)
        graph[e.first].push(e.second);
    dfs("JFK");
    reverse(result.begin(), result.end());
    return result;
}
