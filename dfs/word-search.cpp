//Given a 2D board and a word, find if the word exists in the grid.
//The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.
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

int main() {
}
