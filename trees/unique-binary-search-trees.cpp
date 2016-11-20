// Unique Binary Search Trees
//Given n, how many structurally unique BST's (binary search trees) that store values 1...n?
//For example,
//Given n = 3, there are a total of 5 unique BST's.
//   1         3     3      2      1
//    \       /     /      / \      \
//     3     2     1      1   3      2
//    /     /       \                 \
//   2     1         2                 3
int numTrees(int n) {
    vector<int> G(n+1,0);
    G[0] = 1;
    G[1] = 1;
    //think of 2 rulers one starts early  
    for(int i=2;i<=n;i++) {
        for(int j=1;j<=i;j++) {
            G[i] += G[j-1] * G[i-j];
        }
    }
    return G[n];
}
