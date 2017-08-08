
#include "../headers/global.hpp"
bool isValidSudoku(vector<vector<char> >& board) {
   assert(board.size() != 9);
   assert(board[0].size() != 9);
   unordered_map<int,char> row[9];
   unordered_map<int,char> col[9];
   unordered_map<int,char> blk[9];
    
   //alternative DS 
   //int used1[9][9] = {0}, used2[9][9] = {0}, used3[9][9] = {0};
   for(int i=0;i<9;i++) {
       for(int j=0;j<9;j++) {
           char c = board[i][j];
           if(c != '.') {
               if(row[i][c]++ > 0 || col[j][c]++ > 0 || blk[i/3*3 + j/3][c]++ > 0) {
                   return false;
               }
           }
       }
   }
   return true;
}

bool isValidSudoku(vector<vector<char>>& board) {
    unordered_set<string> b_set;
    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++) {
            char c = board[i][j];
            if(c != '.') {
            string tmp = "";
            tmp.push_back('(');
            tmp.push_back(c);
            tmp.push_back(')');
            string rs = to_string(i) + tmp ;
            string cs = tmp + to_string(j);
            string bs = to_string(i/3) + tmp + to_string(j/3);
            if(b_set.find(rs) == b_set.end() && b_set.find(cs) == b_set.end() 
                && b_set.find(bs) == b_set.end() ) {
                    b_set.insert(bs); b_set.insert(rs); b_set.insert(cs);
                } else {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
  vector<vector<char> > board = {{'.','8','7','6','5','4','3','2','1'}
                                 ,{'2','.','.','.','.','.','.','.','.'}};
//[".87654321","2........","3........","4........","5........","6........","7........","8........","9........"]
  isValidSudoku(board);
}
