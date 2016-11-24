//Paint Fence
//There is a fence with n posts, each post can be painted with one of the k colors.
//You have to paint all the posts such that no more than two adjacent fence posts have the same color.
//Return the total number of ways you can paint the fence.
//Note:
//n and k are non-negative integers.
//

#include "../headers/global.hpp"

int numWays(int n, int k) {
    
    vector<int> ways ( {0,k,k*k,0} );
    if(n <= 2) {
        return ways[n];
    }
    for(int i=2;i<n;i++) {
        ways[3] = (k-1) * (ways [1] + ways[2] );
        ways[1] = ways[2];
        ways[2] = ways[3];
    }
    return ways[3];
}

int main() {

}
