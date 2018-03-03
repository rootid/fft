//Given a 2D board and a word, find if the word exists in the grid.
//The word can be constructed from letters of sequentially adjacent cell, where
//"adjacent" cells are those horizontally or vertically neighboring. The same
//letter cell may not be used more than once.
//For example,
//Given board =
//[
//  ['A','B','C','E'],
//  ['S','F','C','S'],
//  ['A','D','E','E']
//]
//word = "ABCCED", -> returns true,
//word = "SEE", -> returns true,
//word = "ABCB", -> returns false
#include "../headers/global.hpp"

bool dfs(vector<vector<char>>& board,int i,int j,int k,string word) {
    if(k > word.size()) {
        return false;
    }
    if(k == word.size()) {
        return true;
    }
    if ((i<0) || (i >= board.size()) || (j <0) || (j >= board[i].size())) {
      return false;
    }

    if(board[i][j] == word[k]) {
        board[i][j] = '\0';
        if(i < board.size()) {
           if ( dfs(board,i+1,j,k+1,word) ) return true;
        }
        if(j < board[i].size()) {
           if ( dfs(board,i,j+1,k+1,word)) return true;
        }
        if(i > 0) {
           if ( dfs(board,i-1,j,k+1,word)) return true;
        }
        if(j>0) {
           if ( dfs(board,i,j-1,k+1,word)) return true;
        }
        board[i][j] = word[k];
    }
    return false;
}

bool exist(vector<vector<char>>& board, string word) {
    int m = board.size();
    int n = board[0].size();
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            if(board[i][j] == word[0]) {
                 int k = 0;
                 if ( true == dfs(board,i,j,k,word) ) {
                     return true;
                 }
            }
        }
    }
    return false;
}



//######################################### In place #########################################
//T(k)=4(T(k-1))=4*4T(k-2)=....=.. which will be 4^k.
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (search(board, i, j, word.c_str()))
                    return true;
        return false;
    }
private:
    bool search(vector<vector<char>>& board, int r, int c, const char* word) {
        if (!word[0]) return true;
        int m = board.size(), n = board[0].size();
        if (r < 0 || r >= m || c < 0 || c >= n || board[r][c] != word[0]) return false;
        board[r][c] = '$';
        if (search(board, r - 1 ,c, word + 1) || search(board, r + 1, c, word + 1) ||
            search(board, r, c - 1, word + 1) || search(board, r, c + 1, word + 1))
            return true;
        board[r][c] = word[0];
        return false;
    }
};

//######################################### In place #########################################
public class Solution {
public boolean exist(char[][] board, String word) {
    for(int i = 0; i < board.length; i++)
        for(int j = 0; j < board[0].length; j++){
            if(exist(board, i, j, word, 0))
                return true;
        }
    return false;
}
private boolean exist(char[][] board, int i, int j, String word, int ind){
    if(ind == word.length()) return true;
    if(i > board.length-1 || i <0 || j<0 || j >board[0].length-1 || board[i][j]!=word.charAt(ind))
        return false;
    board[i][j]='*';
    boolean result =    exist(board, i-1, j, word, ind+1) ||
                        exist(board, i, j-1, word, ind+1) ||
                        exist(board, i, j+1, word, ind+1) ||
                        exist(board, i+1, j, word, ind+1);
    board[i][j] = word.charAt(ind);
    return result;
}
}

//######################################### Bit wise solution #########################################
//apply bit mask for every visited cell. Please check board[y][x] ^= 256;
//board[y][x] ^= 256 it's a marker that the letter at position x,y is a part of
//word we search.
//After board[y][x] ^= 256 the char became not a valid letter. After second
//board[y][x] ^= 256
//it became a valid letter again.
public boolean exist(char[][] board, String word) {
    char[] w = word.toCharArray();
    for (int y=0; y<board.length; y++) {
    	for (int x=0; x<board[y].length; x++) {
    		if (exist(board, y, x, w, 0)) return true;
    	}
    }
    return false;
}

private boolean exist(char[][] board, int y, int x, char[] word, int i) {
	if (i == word.length) return true;
	if (y<0 || x<0 || y == board.length || x == board[y].length) return false;
	if (board[y][x] != word[i]) return false;
	board[y][x] ^= 256;
	boolean exist = exist(board, y, x+1, word, i+1)
		|| exist(board, y, x-1, word, i+1)
		|| exist(board, y+1, x, word, i+1)
		|| exist(board, y-1, x, word, i+1);
	board[y][x] ^= 256;
	return exist;
}

//######################################### DFS #########################################
def exist(self, board, word):
    if not board:
        return False
    for i in xrange(len(board)):
        for j in xrange(len(board[0])):
            if self.dfs(board, i, j, word):
                return True
    return False

# check whether can find word, start at (i,j) position
def dfs(self, board, i, j, word):
    if len(word) == 0: # all the characters are checked
        return True
    if i<0 or i>=len(board) or j<0 or j>=len(board[0]) or word[0]!=board[i][j]:
        return False
    tmp = board[i][j]  # first character is found, check the remaining part
    board[i][j] = "#"  # avoid visit agian
    # check whether can find "word" along one direction
    res = self.dfs(board, i+1, j, word[1:]) or self.dfs(board, i-1, j, word[1:]) \
    or self.dfs(board, i, j+1, word[1:]) or self.dfs(board, i, j-1, word[1:])
    board[i][j] = tmp
    return res


//######################################### Bound check variation #########################################
//compare board[row][col] with word[start], if they match, change
//board[row][col] to '*' to mark it as visited.
// Then move to the next one (i.e. word[start+1]) and compare it to the current neighbors ( doing it by recursion)
class Solution {
private:
    bool dfs(vector<vector<char>>& board, int row, int col, const string &word, int start, int M, int N, int sLen)
    {
        char curC;
        bool res = false;
        if( (curC = board[row][col]) != word[start]) return false;
        if(start==sLen-1) return true;
        board[row][col] = '*';
        if(row>0) res = dfs(board, row-1, col, word, start+1, M, N, sLen);
        if(!res && row < M-1) res = dfs(board, row+1, col, word, start+1, M, N, sLen);
        if(!res && col > 0)   res = dfs(board, row, col-1, word, start+1, M, N, sLen);
        if(!res && col < N-1) res = dfs(board,  row, col+1, word, start+1, M, N, sLen);
        board[row][col] = curC;
        return res;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        int M,N,i,j,sLen = word.size();
        if( (M=board.size()) && (N=board[0].size()) && sLen)
        {
            for(i=0; i<M; ++i)
                for(j=0; j<N; ++j)
                    if(dfs(board, i, j, word, 0, M, N, sLen)) return true;
        }
        return false;
    }
};



int main() {
}
