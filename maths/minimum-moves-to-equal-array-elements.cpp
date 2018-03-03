//Minimum Moves to Equal Array Elements
//Given a non-empty integer array of size n, find the minimum number of moves
//required to make all array elements equal, where a move is incrementing n - 1
//elements by 1.
//Example:
//Input:
//[1,2,3]
//Output:
//3
//Explanation:
//Only three moves are needed (remember each move increments two elements):
//[1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]

//# of moves = sum - len*minNo
int minMoves(vector<int>& nums) {
    int len = nums.size();
    if(len == 0) {
        return 0;
    }
    int minNo = nums[0];
    int sum = minNo;
    for(int i=1;i<len;i++) {
        if(minNo > nums[i]) {
            minNo = nums[i];
        }
        sum += nums[i];
    }
    return (sum - len * minNo);
}
