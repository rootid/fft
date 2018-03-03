//Queue Reconstruction by Height
//Suppose you have a random list of people standing in a queue. Each person is
//described by a pair of integers (h, k), where h is the height of the person
//and k is the number of people in front of this person who have a height
//greater than or equal to h. Write an algorithm to reconstruct the queue.
//Note:
//The number of people is less than 1,100.
//Example
//Input:
//[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]
//Output:
//[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
//


//######################################### O(n log n) #########################################
//Sort(absolute ht decreasing , tie : use k) + Arrange with relative pos using
//k
public int[][] reconstructQueue(int[][] people) {

    Arrays.sort(people, (p,q) -> { if(p[0] == q[0])
                                        return p[1] - q[1];
                                   else
                                       return q[0] - p[0];
                                 });

    List<int[]> res = new LinkedList<>();
    for(int[] cur : people) {
        res.add(cur[1],cur);  //after insert at i all elements after i shifted by 1
    }
    return res.toArray(new int[people.length][]);
}


//######################################### O(n log n) #########################################
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


//######################################### O(n log n) #########################################
class Solution(object):
    def reconstructQueue(self, people):
        """
        :type people: List[List[int]]
        :rtype: List[List[int]]
        """
        res = []
        for p in sorted(people, key=lambda x: (-x[0], x[1])):
            res.insert(p[1],p)
        return res


//######################################### O(n log n) #########################################
class Solution(object):
    def reconstructQueue(self, people):
        if not people: return []

        # obtain everyone's info
        # key=height, value=k-value, index in original array
        peopledct, height, res = {}, [], []

        for i in xrange(len(people)):
            p = people[i]
            if p[0] in peopledct:
                peopledct[p[0]] += (p[1], i),
            else:
                peopledct[p[0]] = [(p[1], i)]
                height += p[0],

        height.sort()      # here are different heights we have

        # sort from the tallest group
        for h in height[::-1]:
            peopledct[h].sort()
            for p in peopledct[h]:
                res.insert(p[0], people[p[1]])

        return res
