//Valid Square
//Given the coordinates of four points in 2D space, return whether the four
//points could construct a square.
//The coordinate (x,y) of a point is represented by an integer array with two
//integers.
//Example:
//Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
//Output: True
//Note:
//All the input integers are in the range [-10000, 10000].
//A valid square has four equal sides with positive length and four equal
//angles (90-degree angles).
//Input points have no order.


bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
}

//############################  combination ############################
//NOTE : this solution will work as the problem is limited to integer
//coordinates.
//equilateral triangle: Non integer case (0,0),(0,2),(-1,√3),(1,√3) : Ideally
//expected false,howerver in this case it returns true.

//
int d(vector<int>& p1, vector<int>& p2) {
    return (p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1]);
}
bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
    unordered_set<int> s({ d(p1, p2), d(p1, p3), d(p1, p4), d(p2, p3), d(p2, p4), d(p3, p4) });
    return !s.count(0) && s.size() == 2;
}


//################# pytonic #################
//    def validSquare(self, p1, p2, p3, p4):
//        """
//        :type p1: List[int]
//        :type p2: List[int]
//        :type p3: List[int]
//        :type p4: List[int]
//        :rtype: bool
//        """
//        points = [p1, p2, p3, p4]
//        return len({(a[0]-b[0])**2 + (a[1]-b[1])**2 for a in points for b in points}) == 3 and \
//               len(set(map(tuple, points))) == 4
//
//
//################# Iterators #################
//class Solution(object):
//    def validSquare(self, p1, p2, p3, p4):
//        def D((P, Q)):
//            return (P[0] - Q[0]) ** 2 + (P[1] - Q[1]) ** 2
//        S = set(map(D, itertools.combinations((p1, p2, p3, p4), 2)))
//        return len(S) == 2 and 0 not in S
//
//######################## Naive ########################
//class Solution(object):
//    def validSquare(self, p1, p2, p3, p4):
//        points = [p1, p2, p3, p4]
//
//        dists = collections.Counter()
//        for i in range(len(points)):
//            for j in range(i+1, len(points)):
//                dists[self.getDistance(points[i], points[j])] += 1
//
//        return len(dists.values())==2 and 4 in dists.values() and 2 in dists.values()
//
//    def getDistance(self, p1, p2):
//        return (p1[0] - p2[0])**2 + (p1[1] - p2[1])**2
//
//######################### Sort + No multiplication #########################
//def validSquare(self, p1, p2, p3, p4):
//    if p1 == p2 == p3 == p4: return False
//
//    p1,p2,p3,p4 = sorted([p1,p2,p3,p4])
//    if p2[1] < p3[1]: p2,p3 = p3,p2
//
//    return p3 == [p1[0] + (p2[1]-p1[1]), p1[1] - (p2[0]-p1[0])]\
//       and p4 == [p2[0] + (p2[1]-p1[1]), p2[1] - (p2[0]-p1[0])]
//
//
//#########Any 3 points make up a Isosceles Right Triangle #########
//
//class Solution(object):
//    def validSquare(self, p1, p2, p3, p4):
//        """
//        :type p1: List[int]
//        :type p2: List[int]
//        :type p3: List[int]
//        :type p4: List[int]
//        :rtype: bool
//        """
//        def distance(p1, p2):
//            return (p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2
//
//        def foo(p1, p2, p3):
//            d1, d2, d3 = sorted((distance(p1, p2), distance(p2, p3), distance(p3, p1)))
//            return 0 < d1 == d2 == d3 / 2.0
//
//class Solution(object):
//    def validSquare(self, p1, p2, p3, p4):
//        """
//        :type p1: List[int]
//        :type p2: List[int]
//        :type p3: List[int]
//        :type p4: List[int]
//        :rtype: bool
//        """
//        def distance(p1, p2):
//            return (p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2
//        def foo(p1, p2, p3):
//            arr = [distance(p1, p2), distance(p2, p3), distance(p3, p1)]
//            if 0 in arr:
//                return False
//            if arr[0] == arr[1] and 2 * arr[0] == arr[2]:
//                return True
//            if arr[1] == arr[2] and 2 * arr[1] == arr[0]:
//                return True
//            if arr[2] == arr[0] and 2 * arr[2] == arr[1]:
//                return True
//            return False
//        return foo(p1, p2, p3) and foo(p1, p2, p4) and foo(p1, p3, p4) and foo(p2, p3, p4)
