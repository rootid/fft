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


//Treeset hold only single occurance
//[["EZE","AXA"],["TIA","ANU"],["ANU","JFK"],["JFK","ANU"],["ANU","EZE"],["TIA","ANU"],["AXA","TIA"],["TIA","JFK"],["ANU","TIA"],["JFK","TIA"]]
//Output:
//["JFK","ANU","EZE","AXA","TIA","ANU","TIA","JFK","TIA","JFK"]
//Expected:
//["JFK","ANU","EZE","AXA","TIA","ANU","JFK","TIA","ANU","TIA","JFK"]


//################################### Iterative - With Set #################################
//NOTE : Cannot break ties 
public List<String> findItinerary(String[][] tickets) {
    
    Deque<String> set = new ArrayDeque<>();
    set.push("JFK"); //incoming deg = 0;
    
    int len = tickets.length;
    List<String> result = new ArrayList<>();
    //Represent graph with String and Set
    Map<String, Set<String>> graph = new HashMap<>();
    for(int i=0;i<len;i++) {
        String src = tickets[i][0];
        String dest = tickets[i][1];
        if(!graph.containsKey(src)) 
            //graph.put(src, new TreeSet<>());
			graph.put(src, new TreeSet<>( (s1, s2) -> s2.compareTo(s1)) ); //Compare did not work
        graph.get(src).add(dest);
    }
    
    while(!set.isEmpty()) {
        String current = set.pop();
        Set<String> toBeVisited = graph.getOrDefault(current, null);
        if(toBeVisited != null)  {
            for(String t: toBeVisited) 
                set.push(t);
             graph.remove(current);
        }
         result.add(current);
    }
    return result;
}

// node, <outgoing node>
//################################### Iterative #################################
    public List<String> findItinerary(String[][] tickets) {
        List<String> itinerary = new ArrayList<>();
        Map<String, PriorityQueue<String>> itineryMap = new HashMap<>();
       // Arrays.sort(tickets); 2D sort
        for(String[] ticket: tickets) {
            PriorityQueue<String> destListList = null;
            if(itineryMap.containsKey(ticket[0])) 
               destListList = itineryMap.get(ticket[0]); 
            else destListList = new PriorityQueue<>();
            destListList.add(ticket[1]);
            itineryMap.put(ticket[0],destListList);
        }
        Stack<String> stack = new Stack<>();
        stack.push("JFK");
        while(!stack.isEmpty()) {
            while (itineryMap.containsKey(stack.peek()) && !itineryMap.get(stack.peek()).isEmpty()) 
                stack.push(itineryMap.get(stack.peek()).poll());
            itinerary.add(stack.pop());
        }
        Collections.reverse(itinerary);
        return itinerary;
    }

//################################### Iterative #################################
public List<String> findItinerary(String[][] tickets) {
    Map<String, PriorityQueue<String>> targets = new HashMap<>();
    for (String[] ticket : tickets)
        targets.computeIfAbsent(ticket[0], k -> new PriorityQueue()).add(ticket[1]); //Add to priority queue
    List<String> route = new LinkedList();
    Stack<String> stack = new Stack<>();
    stack.push("JFK");
    while (!stack.empty()) {
        while (targets.containsKey(stack.peek()) && !targets.get(stack.peek()).isEmpty()) 
            stack.push(targets.get(stack.peek()).poll()); //after visiting the targests remove destinations
        route.add(0, stack.pop());
    }
    return route;
}
		
//################################### Recursive #################################
Map<String, PriorityQueue<String>> targets = new HashMap<>();
List<String> route = new LinkedList();

public List<String> findItinerary(String[][] tickets) { 
	for (String[] ticket : tickets)
		targets.computeIfAbsent(ticket[0], k -> new PriorityQueue()).add(ticket[1]);
	visit("JFK");
	return route;
}

void visit(String airport) { 
	//node with at least one outgoing edge && not a leaf node 
	while(targets.containsKey(airport) && !targets.get(airport).isEmpty())  
		visit(targets.get(airport).poll());
	route.add(0, airport);
}


//################################### Iterative #################################
def findItinerary(self, tickets):
    targets = collections.defaultdict(list)
    for a, b in sorted(tickets)[::-1]:
        targets[a] += b,
    route, stack = [], ['JFK']
    while stack:
        while targets[stack[-1]]:
            stack += targets[stack[-1]].pop(),
        route += stack.pop(),
    return route[::-1]


//################################### Recursive #################################
def findItinerary(self, tickets):
    targets = collections.defaultdict(list)
    for a, b in sorted(tickets)[::-1]:
        targets[a] += b,
    route = []
    def visit(airport):
        while targets[airport]:
            visit(targets[airport].pop())
        route.append(airport)
    visit('JFK')
    return route[::-1]


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
