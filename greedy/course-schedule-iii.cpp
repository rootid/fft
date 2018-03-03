//Course Schedule III
//There are n different online courses numbered from 1 to n. Each course has some duration(course length) t and closed
//on dth day. A course should be taken continuously for t days and must be finished before or on the dth day. You will
//start at the 1st day.
//Given n online courses represented by pairs (t,d), your task is to find the maximal number of courses that can be
//taken.
//Example:
//Input: [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
//Output: 3
//Explanation:
//There're totally 4 courses, but you can take 3 courses at most:
//First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next
//course on the 101st day.
//Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next
//course on the 1101st day.
//Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day.
//The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.
//Note:
//The integer 1 <= d, t, n <= 10,000.
//You can't take two courses simultaneously.


int scheduleCourse(vector<vector<int>>& courses) {
    //sort by end time (ascending)
     sort(courses.begin(), courses.end(), [](vector<int> a, vector<int> b){return a[1] < b[1];});
     priority_queue<int> heap;
     int now = 0;
     for (int i = 0; i < courses.size(); i++) {
         heap.push(courses[i][0]); //first push duration
         now += courses[i][0]; //update duration
         if (now > courses[i][1]) { //if newly added schdule cannot be completed within bounds
             now -= heap.top(), heap.pop();
         }
     }
     return heap.size();
}

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(), courses.end(), mycompare);
        priority_queue<int> pq;
        int n = courses.size(), cur = 0;
        for (auto course:courses) {
            if (cur + course[0] <= course[1]) {
                pq.push(course[0]);
                cur += course[0];
            }
            else if (course[0] < pq.top()) {
                cur += course[0]-pq.top();
                pq.pop();
                pq.push(course[0]);
            }
        }
        return pq.size();
    }
private:
    static bool mycompare(vector<int>& a, vector<int>& b) {
        return a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]);
    }
};



//##################################### pytonic ######################################################
//
//**A rigorous proof of optimality for this greedy algorithm.**
//
//First, we want to show that the courses in the optimal solution must appear in ascending order with respect to their
//end time.
//Consider two adjacent courses a and b in the optimal solution, where a is prior to b. If there exists da>db, where da
//and db refer to the end time of a and b respectively, then we can swap a and b here. After swapping, the courses
//before a and the courses after b will NOT be affected. Besides, it is easy to see that the solution is still feasible
//due to the fact that da>db, where we have t0 + ta + tb < db < da, assuming course a starts at time t0 and ta, tb are
//the duration of a and b respectively.
//Now we can perform this swapping process to each adjacent pair until all the adjacent a, b satisfy da <= db, like the
//bubble sorting. After all, we still have a feasible solution with the same number of courses taken and this
//contradicts the optimality of the original solution. Therefore, we have proved our argument.
//
//Second, since we know that the optimal course list should appear in ascending order by the courses' end time, how
//shall we choose the courses?
//We just select the course one by one in ascending order. Once there is a conflict when we choose the Kth course, it
//means that we cannot put all the K courses in the candidate list. In other words, one course must be removed from the
//candidate list. Which one should we remove?
//Obviously, the one with the largest duration. Supposing the courses already chosen in the candidate list is c1, c2,
//..., ck with duration t1, t2, .., tk, then we find the maximum, say cj, and remove it. Now the total duration of the
//k-1 courses will be <= d_(k-1) because we have replaced cj with ck while tk<=tj. Then it follows that the total
//duration <=d_(k-1)<=d_k since we choose course in ascending order of the end time, which indicates d_(k-1)<=d_k.
//Therefore, by removing the longest course, we get a feasible partial solution now. By removing the longest duration
//course to eliminate conflicts, we ensure that we have saved most time for the remaining courses, that is, the
//remaining courses can start at an earliest possible time. Therefore, this will lead to an optimal solution. Continue
//this process until we have exhausted all the courses.

//######################################### heap ######################################################
//import heapq
//
//class Solution(object):
//    def scheduleCourse(self, courses):
//        """
//        :type courses: List[List[int]]
//        :rtype: int
//        """
//        s = []
//        start = 0
//        for t, end in sorted(courses, key=lambda c: c[1]):
//            start += t
//            heapq.heappush(s, -t)  # max heap
//            if start > end:
//                nt = heapq.heappop(s)  # the newly pushed t may also be poped
//                start += nt  # nt is the negative t
//        return len(s)


//######################################### heap ######################################################
//def scheduleCourse(self, A):
//    pq = []
//    start = 0
//    for t, end in sorted(A, key = lambda (t, end): end):
//        start += t
//        heapq.heappush(pq, -t)
//        while start > end:
//            start += heapq.heappop(pq)
//    return len(pq)
// vim: set sw=2 sts=2 tw=120 et nospell :
