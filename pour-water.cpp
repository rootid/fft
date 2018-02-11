//Pour Water
//We are given an elevation map, heights[i] representing the height of the terrain at that index. The width at each index is 1. After V units of water fall at index K, how much water is at each index?
//Water first drops at index K and rests on top of the highest terrain or water at that index. Then, it flows according to the following rules:
//If the droplet would eventually fall by moving left, then move left.
//Otherwise, if the droplet would eventually fall by moving right, then move right.
//Otherwise, rise at it's current position.
//Here, "eventually fall" means that the droplet will eventually be at a lower level if it moves in that direction. Also, "level" means the height of the terrain plus any water in that column.
//We can assume there's infinitely high terrain on the two sides out of bounds of the array. Also, there could not be partial water being spread out evenly on more than 1 grid block - each unit of water has to be in exactly one block.
//Example 1:
//Input: heights = [2,1,1,2,1,2,2], V = 4, K = 3
//Output: [2,2,2,3,2,2,2]
//Explanation:
//#       #
//#       #
//##  # ###
//#########
// 0123456    <- index
//The first drop of water lands at index K = 3:
//#       #
//#   w   #
//##  # ###
//#########
// 0123456
//When moving left or right, the water can only move to the same level or a lower level.
//(By level, we mean the total height of the terrain plus any water in that column.)
//Since moving left will eventually make it fall, it moves left.
//(A droplet "made to fall" means go to a lower height than it was at previously.)
//#       #
//#       #
//## w# ###
//#########
// 0123456
//Since moving left will not make it fall, it stays in place.  The next droplet falls:
//#       #
//#   w   #
//## w# ###
//#########
// 0123456
//Since the new droplet moving left will eventually make it fall, it moves left.
//Notice that the droplet still preferred to move left,
//even though it could move right (and moving right makes it fall quicker.)
//#       #
//#  w    #
//## w# ###
//#########
// 0123456
//#       #
//#       #
//##ww# ###
//#########
// 0123456
//After those steps, the third droplet falls.
//Since moving left would not eventually make it fall, it tries to move right.
//Since moving right would eventually make it fall, it moves right.
//#       #
//#   w   #
//##ww# ###
//#########
// 0123456
//#       #
//#       #
//##ww#w###
//#########
// 0123456
//Finally, the fourth droplet falls.
//Since moving left would not eventually make it fall, it tries to move right.
//Since moving right would not eventually make it fall, it stays in place:
//#       #
//#   w   #
//##ww#w###
//#########
// 0123456
//The final answer is [2,2,2,3,2,2,2]:
//    #
// #######
// #######
// 0123456
//Example 2:
//Input: heights = [1,2,3,4], V = 2, K = 2
//Output: [2,3,3,4]
//Explanation:
//The last droplet settles at index 1, since moving further left would not cause it to eventually fall to a lower height.
//Example 3:
//Input: heights = [3,1,3], V = 5, K = 1
//Output: [4,4,4]
//Note:
//    heights will have length in [1, 100] and contain integers in [0, 99].
//    V will be in range [0, 2000].
//    K will be in range [0, heights.length - 1].
//

//######################################### Simulation ######################################### p
//Intuition and Algorithm
//We attempt to perform the steps directly as described.
//First, notice that an index with terrain or with water is indistinguishable with respect to the flow of water. Thus, we can model heights as the total level of terrain and water directly as we perform our simulation.
//When a droplet falls, we should check if it is possible for it to fall left. For our left pointer i = K, if i - 1 is in bounds and heights[i - 1] <= heights[i], the water will fall to a candidate block in that direction. We keep track of every time we actually fall at index best. If we "eventually fall" (best != K) as described in the problem statement, then we will drop the water there.
//Otherwise, (if moving left will not cause the droplet to eventually fall), we can perform a similar check for i = K going right, and otherwise the droplet stays in place.
//For convenience, we will name the initial array H = heights.

class Solution {
    public int[] pourWater(int[] H, int V, int K) {
        while (V-- > 0) droplet: {
            for (int d = -1; d <= 1; d += 2) {
                int i = K, best = K;
                while (0 <= i+d && i+d < H.length && H[i+d] <= H[i]) {
                    if (H[i+d] < H[i]) best = i + d;
                    i += d;
                }
                if (H[best] < H[K]) {
                    H[best]++;
                    break droplet;
                }
            }
            H[K]++;
        }
        return H;
    }
}

//Time Complexity: O(V∗N), where NNN is the length of heights. For each of VVV droplets, our while loop might iterate NNN times.
//Space Complexity: O(1) in additional space complexity.


//######################################### #########################################
public int[] pourWater(int[] heights, int V, int K) {
        if (heights == null || heights.length == 0 || V == 0) {
            return heights;
        }
        int index;
        while (V > 0) {
            index = K;
            for (int i = K - 1; i >= 0; i--) {
                if (heights[i] > heights[index]) {
                    break;
                } else if (heights[i] < heights[index]) {
                    index = i;
                }
            }
            if (index != K) {
                heights[index]++;
                V--;
                continue;
            }
            for (int i = K + 1; i < heights.length; i++) {
                if (heights[i] > heights[index]) {
                    break;
                } else if (heights[i] < heights[index]) {
                    index = i;
                }
            }
            heights[index]++;
            V--;
        }
        return heights;
    }

//######################################### #########################################

class Solution {
    public int[] pourWater(int[] heights, int V, int K) {
        while (V-- > 0)
            drop(heights, K, heights[K] + 1, true, true);
        return heights;
    }
   private boolean drop(int[] h, int i, int j, boolean l, boolean r) {
        if (l && i > 0            && h[i - 1] <= h[i] && drop(h, i - 1, h[i], l, false)) return true;
        if (r && i < h.length - 1 && h[i + 1] <= h[i] && drop(h, i + 1, h[i], false, r)) return true;

        if (h[i] == j) return false;
        h[i]++;
        return true;
    }
}

//######################################### #########################################
class Solution {
public:
    vector<int> pourWater(vector<int>& heights, int V, int K) {
        while (V-- > 0)
            drop(heights, K, heights[K] + 1, 1, 1);
        return heights;
    }
private:
    bool drop(vector<int>& h, int i, int j, bool l, bool r) {
        if (l && i > 0          && h[i - 1] <= h[i] && drop(h, i - 1, h[i], l, 0)) return true;
        if (r && i < h.size()-1 && h[i + 1] <= h[i] && drop(h, i + 1, h[i], 0, r)) return true;

        if (h[i] == j) return false;
        h[i]++;
        return true;
    }
};

//######################################### #########################################
class Solution(object):
    def pourWater(self, H, V, K):
        for _ in xrange(V):
            for d in (-1, 1):
                i = best = K
                while 0 <= i+d < len(H) and H[i+d] <= H[i]:
                    if H[i+d] < H[i]: best = i+d
                    i += d
                if best != K:
                    H[best] += 1
                    break
            else:
                H[K] += 1
        return H
