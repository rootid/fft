//Super Washing Machines
//You have n super washing machines on a line. Initially, each washing machine
//has some dresses or is empty.
//For each move, you could choose any m (1 ≤ m ≤ n) washing machines, and pass
//one dress of each washing machine to one of its adjacent washing machines at
//the same time .
//Given an integer array representing the number of dresses in each washing
//machine from left to right on the line, you should find the minimum number of
//moves to make all the washing machines have the same number of dresses. If it
//is not possible to do it, return -1.
//Example1
//Input: [1,0,5]
//Output: 3
//Explanation:
//1st move:    1     0 <-- 5    =>    1     1     4
//2nd move:    1 <-- 1 <-- 4    =>    2     1     3
//3rd move:    2     1 <-- 3    =>    2     2     2
//Example2
//Input: [0,3,0]
//Output: 2
//Explanation:
//1st move:    0 <-- 3     0    =>    1     2     0
//2nd move:    1     2 --> 0    =>    1     1     1
//Example3
//Input: [0,2,0]
//Output: -1
//Explanation:
//It's impossible to make all the three washing machines have the same number
//of dresses.
//Note:
//The range of n is [1, 10000].
//The range of dresses number in a super washing machine is [0, 1e5].
//

//######################################### O(n) - #########################################
//Let me use an example to briefly explain this. For example, your machines[]
//is [0,0,11,5]. So your total is 16 and the target value for each machine is
//4. Convert the machines array to a kind of gain/loss array, we get:
//[-4,-4,7,1]. Now what we want to do is go from the first one and try to make
//all of them 0.
//To make the 1st machines 0, you need to give all its "load" to the 2nd
//machines.
//So we get: [0,-8,7,1]
//then: [0,0,-1,1]
//lastly: [0,0,0,0], done.
//You don't have to worry about the details about how these machines give load
//to each other. In this process, the least steps we need to eventually finish
//this process is determined by the peak of abs(cnt) and the max of "gain/loss"
//array. In this case, the peak of abs(cnt) is 8 and the max of gain/loss array
//is 7. So the result is 8.
//
//Some other example:
//machines: [0,3,0]; gain/loss array: [-1,2,-1]; max = 2, cnt = 0, -1, 1, 0,
//its abs peak is 1. So result is 2.
//machines: [1,0,5]; gain/loss array: [-1,-2,3]; max = 3, cnt = 0, -1, -3, 0,
//its abs peak is 3. So result is 3.
//There are mainly two scenarios:
//(1) the "gain/loss" array: [2,-2,-2,2], because the adjacent machines can neutralize each other directly. The result comes directly from the max of the load need to be transferred of a machines. In this case, it is 2. Easy.
//(2) the "gain/loss" array: [1,7,-4,-4], for the 1st "1", inorder to be neutralized by a negative number, it need to climb over "7", because it cannot just do the neutralization with its neighbors. So, effectively, [1,7,-4,-4] equals [0,8,-4,-4]. Similar to (1), we can know for [0,8,-4,-4], we need 8 steps.
//After trying some examples, we can find that keeping track of max of our
//array and the max of any intermediate values, while doing our neutralization
//process, can give us the result.

public class Solution {
    public int findMinMoves(int[] machines) {
        int total = 0;
        for(int i: machines) total+=i;
        if(total%machines.length!=0) return -1;
        int avg = total/machines.length, cnt = 0, max = 0;
        for(int load: machines){
            cnt += load-avg; //load-avg is "gain/loss"
            max = Math.max(Math.max(max, Math.abs(cnt)), load-avg);
        }
        return max;
    }
}


//######################################### O(n) #########################################
//toLeft: the number of cloths moved to left from this machine
//toRight: the number of cloths moved to right from this machine
//toLeft and toRight may be negative but it's okay.

def findMinMoves(self, machines):
    if sum(machines) % len(machines) == 0:
        target = sum(machines) / len(machines)
    else:
        return -1
    toLeft = 0
    res = 0
    for i in range(len(machines)):
        toRight =  machines[i]- target - toLeft
        res = max(res, toLeft, toRight, toLeft + toRight)
        toLeft = -toRight
    return res

https://discuss.leetcode.com/topic/79923/c-16ms-o-n-solution-with-trivial-proof/25
