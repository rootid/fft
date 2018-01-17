//Surrounded Regions
//Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.
//A region is captured by flipping all 'O's into 'X's in that surrounded region.
//For example,
//X X X X
//X O O X
//X X O X
//X O X X
//After running your function, the board should be:
//X X X X
//X X X X
//X X X X
//X O X X
#include "../headers/global.hpp"

//######################################### BFS ######################################### 
//Pick boundry points
	int[] dirs = {0,1,0,-1,0};

    public void solve(char[][] board) {
        int m = board.length;
        if(m == 0) return;
        int n = board[0].length;
        Queue<Integer> q = new ArrayDeque<>();
        for(int i=0;i<m;i++) {
            if(board[i][0] == 'O') tryMarking(board,i,0,q);
            if(board[i][n-1] == 'O') tryMarking(board,i,n-1,q);
        }
        for(int j=0;j<n;j++) {
            if(board[0][j] == 'O') tryMarking(board,0,j,q);
            if(board[m-1][j] == 'O') tryMarking(board,m-1,j,q);
        }
        while(!q.isEmpty()) {
            int point = q.poll();
            int x = point/n; int y = point % n;
            for(int i=0;i<dirs.length-1;i++) {
				int dx = dirs[i]+x; int dy = dirs[i+1]+y;
                if( dx >=0 && dx < m && dy >=0 && dy < n)
                    tryMarking(board, dx, dy, q);
            }
        }
        for(int i=0;i<m;i++) {
            for(int j=0;j<n;j++) {
                if(board[i][j] == 'V') board[i][j] = 'O';
                else board[i][j] = 'X';
            }
        }
    }
  
    private void tryMarking(char[][] board, int i, int j, Queue<Integer> q) {
        int n = board[0].length;
        if(board[i][j] == 'O') {
            board[i][j] = 'V';
            q.offer(i*n + j);
        }
    }


//######################################### BFS ######################################### 
void boundry_traversal(vector<vector<char> >& board,int l,int w) {
 
  int m = board.size();
  int n = board[0].size();
  queue<pair<int,int> > q;
  q.push( make_pair(l,w) );
  while(!q.empty()) {
    pair<int,int> tmp = q.front();
    q.pop();
    int i = tmp.first;
    int j = tmp.second;
    if(i >= 0 && i<m && j >= 0 && j<n && board[i][j] == 'O') {
      board[i][j] = 'B';
      q.push(make_pair(i-1,j));
      q.push(make_pair(i+1,j));
      q.push(make_pair(i,j-1));
      q.push(make_pair(i,j+1));
    }
  }
}

void solve(vector<vector<char> >& board) {
  int m = board.size();
  if(m > 0) { 
    int n = board[0].size();
    if(n == 0) {
      return;
    }
     //boundry traversal
     for(int k=0;k<m;k++) {
       if(board[k][0] == 'O')
         boundry_traversal(board,k,0);
       if(board[k][n-1] == 'O')
         boundry_traversal(board,k,n-1);
     }
     for(int k=0;k<n;k++) {
       if(board[0][k] == 'O')
         boundry_traversal(board,0,k);
       if(board[m-1][k] == 'O')
         boundry_traversal(board,m-1,k);
     }
    //Phase 2 : 
    for(int i=0;i<m;i++) {
     for(int j=0;j<n;j++) {
       if(board[i][j] == 'B') {
         board[i][j] = 'O';
       } else if(board[i][j] == 'O') {
         board[i][j] = 'X';
       }
     }
    }
  }
}
int main() {
}
