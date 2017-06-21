//Queue Reconstruction by Height
//Suppose you have a random list of people standing in a queue. Each person is described by a pair of integers (h, k), where h is the height of the person and k is the number of people in front of this person who have a height greater than or equal to h. Write an algorithm to reconstruct the queue.
//Note:
//The number of people is less than 1,100.
//Example
//Input:
//[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]
//Output:
//[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
//

struct ICompare {
  bool operator()(pair<int, int> &a,pair<int, int> &b) {
    if(a.first == b.first) {
        return a.second < b.second; //[6,1],[6,0] => [6,0],[6,1]
    } 
    return a.first > b.first; // [6,0],[7,0] => [7,0],[6,0]
  }
};

vector<pair<int, int> > reconstructQueue(vector<pair<int, int> >& people) {  
     if(people.size() == 0 ) {
       return {};  
     }
     sort(people.begin(), people.end(), ICompare());  
     
     vector<pair<int, int> > ans;  
     for(auto& val: people) {
         ans.insert(ans.begin() + val.second, val);  
     }
     return ans;  
} 
