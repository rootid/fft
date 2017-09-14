//Sudoku Solver
//Write a program to solve a Sudoku puzzle by filling the empty cells.
//Empty cells are indicated by the character '.'.
//You may assume that there will be only one unique solution.
//#################################   O(9^m)  : Backtracking #################################   
   public void solveSudoku(char[][] board) {
        doSolve(board, 0, 0);
    }
    
    private boolean doSolve(char[][] board, int row, int col) {
        for (int i = row; i < 9; i++, col = 0) { // note: must reset col here!
            for (int j = col; j < 9; j++) {
                if (board[i][j] != '.') continue;
                for (char num = '1'; num <= '9'; num++) {
                    if (isValid(board, i, j, num)) {
                        board[i][j] = num;
                        if (doSolve(board, i, j + 1))
                            return true;
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        }
        return true;
    }
    
    private boolean isValid(char[][] board, int row, int col, char num) {
        int blkrow = (row / 3) * 3, blkcol = (col / 3) * 3; // Block no. is i/3, first element is i/3*3
        for (int i = 0; i < 9; i++)
            if (board[i][col] == num || board[row][i] == num || 
                    board[blkrow + i / 3][blkcol + i % 3] == num)
                return false;
        return true;
    }

//#################################   O(9^m)  : Backtracking #################################   
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
private:
    bool solve(vector<vector<char>>& board) {
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (board[r][c] == '.') {
                    for (char d = '1'; d <= '9'; d++) {
                        if (isValid(board, r, c, d)) {
                            board[r][c] = d;
                            if (solve(board)) return true;
                            board[r][c] = '.';
                        }
                    }
                    return false;
                }
            } 
        }
        return true;
    }
    bool isValid(vector<vector<char>>& board, int r, int c, char d) {
        for (int row = 0; row < 9; row++)
            if (board[row][c] == d) return false;
        for (int col = 0; col < 9; col++)
            if (board[r][col] == d) return false;
        for (int row = (r / 3) * 3; row < (r / 3 + 1) * 3; row++)
            for (int col = (c / 3) * 3; col < (c / 3 + 1) * 3; col++)
                if (board[row][col] == d) return false;
        return true;
    }
};

//#################################   O(9^m)  : Backtracking #################################   
//m - # of empty slots
//Try 1 through 9 for each cell. The time complexity should be 9 ^ m (m represents the number of blanks to be filled in), since each blank can have 9 choices
public class Solution {
    public void solveSudoku(char[][] board) {
        if(board == null || board.length == 0)
            return;
        solve(board);
    }
    
    public boolean solve(char[][] board){
        for(int i = 0; i < board.length; i++){
            for(int j = 0; j < board[0].length; j++){
                if(board[i][j] == '.'){
                    for(char c = '1'; c <= '9'; c++){//trial. Try 1 through 9
                        if(isValid(board, i, j, c)){
                            board[i][j] = c; //Put c for this cell
                            if(solve(board))
                                return true; //If it's the solution return true
                            else
                                board[i][j] = '.'; //Otherwise go back
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    
    private boolean isValid(char[][] board, int row, int col, char c){
        for(int i = 0; i < 9; i++) {
            if(board[i][col] != '.' && board[i][col] == c) return false; //check row
            if(board[row][i] != '.' && board[row][i] == c) return false; //check column
            if(board[3 * (row / 3) + i / 3][ 3 * (col / 3) + i % 3] != '.' && 
board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c) return false; //check 3*3 block
        }
        return true;
    }

//######################################### Mask + Backtracking ######################################### 
//use rmask, cmask, bmask to record the appearance of 1-9 in each row,col and cube.
class Solution:
def modifyMask(self, rmask,cmask,bmask,i,j,b,change):
    rmask[i] ^= change
    cmask[j] ^= change
    bmask[b] ^= change
    
def dfs(self, board, k, rmask, cmask, bmask):
    if k == 81:
        return True
    i,j=k/9,k%9
    b = i / 3 * 3 + j / 3
    if board[i][j] != '.':
        return self.dfs(board,k+1,rmask,cmask,bmask)
    for digit in range(9):
        change = 1 << digit
        if rmask[i] & change == 0 and cmask[j] & change == 0 and bmask[b] & change == 0:
            self.modifyMask(rmask,cmask,bmask,i,j,b,change)
            board[i][j] = str(digit+1)
            if self.dfs(board,k+1,rmask,cmask,bmask):
                return True
            board[i][j] = '.'
            self.modifyMask(rmask,cmask,bmask,i,j,b,change)
    return False
    
# @param board, a 9x9 2D array
# Solve the Sudoku by modifying the input board in-place.
# Do not return any value.
def solveSudoku(self, board):
    rmask,cmask,bmask=[0]*9,[0]*9,[0]*9
    for i in range(9):
        for j in range(9):
            b = i / 3 * 3 + j / 3
            if board[i][j] != '.':
                change = 1 << (int(board[i][j]) - 1)
                self.modifyMask(rmask,cmask,bmask,i,j,b,change)
    self.dfs(board,0,rmask,cmask,bmask)

//######################################### Singapore PM's code  ######################################### 
// Original author: Hsien Loong Lee (http://bit.ly/1zfIGMc)
// Slight modification by @1337c0d3r to adapt to run on LeetCode OJ.
// https://leetcode.com/problems/sudoku-solver/
int InBlock[81], InRow[81], InCol[81];

const int BLANK = 0;
const int ONES = 0x3fe; 	// Binary 1111111110

int Entry[81];	// Records entries 1-9 in the grid, as the corresponding bit set to 1
int Block[9], Row[9], Col[9];	// Each int is a 9-bit array

int SeqPtr = 0;
int Sequence[81];



void SwapSeqEntries(int S1, int S2)
{
     int temp = Sequence[S2];
     Sequence[S2] = Sequence[S1];
     Sequence[S1] = temp;
}


void InitEntry(int i, int j, int val)
{
	 int Square = 9 * i + j;
	 int valbit = 1 << val;
     int SeqPtr2;

     // add suitable checks for data consistency
     
	 Entry[Square] = valbit;
	 Block[InBlock[Square]] &= ~valbit;
	 Col[InCol[Square]] &= ~valbit; // Simpler Col[j] &= ~valbit;
	 Row[InRow[Square]] &= ~valbit; // Simpler Row[i] &= ~valbit;

     SeqPtr2 = SeqPtr;
     while (SeqPtr2 < 81 && Sequence[SeqPtr2] != Square)
           SeqPtr2++ ;

     SwapSeqEntries(SeqPtr, SeqPtr2);
     SeqPtr++;
}


void PrintArray(char **board)
{
     int i, j, valbit, val, Square;
     char ch;
     
     Square = 0;

     for (i = 0; i < 9; i++) {
         for (j = 0; j < 9; j++) {
             valbit = Entry[Square++];
             if (valbit == 0) ch = '-';
             else {
                 for (val = 1; val <= 9; val++) 
                     if (valbit == (1 << val)) {
                        ch = '0' + val;
                        break;
                     }
             }    
             board[i][j] = ch;
         }
     }
}


int NextSeq(int S)
{
    int S2, Square, Possibles, BitCount;
    int T, MinBitCount = 100;

    for (T = S; T < 81; T++) {
        Square = Sequence[T];
        Possibles = Block[InBlock[Square]] & Row[InRow[Square]] & Col[InCol[Square]];
        BitCount = 0;
        while (Possibles) {
           Possibles &= ~(Possibles & -Possibles);
           BitCount++;
        }

        if (BitCount < MinBitCount) {
           MinBitCount = BitCount;
           S2 = T;
        }
    }

    return S2;
}


void Place(int S, char** board)
{
    if (S >= 81) {
        PrintArray(board);
        return;
    }

    int S2 = NextSeq(S);
    SwapSeqEntries(S, S2);

    int Square = Sequence[S];

    int 	BlockIndex = InBlock[Square],
			RowIndex = InRow[Square],
			ColIndex = InCol[Square];

    int 	Possibles = Block[BlockIndex] & Row[RowIndex] & Col[ColIndex];
    while (Possibles) {
          int valbit = Possibles & (-Possibles); // Lowest 1 bit in Possibles
          Possibles &= ~valbit;
          Entry[Square] = valbit;
          Block[BlockIndex] &= ~valbit;
          Row[RowIndex] &= ~valbit;
          Col[ColIndex] &= ~valbit;
				
          Place(S + 1, board);

          Entry[Square] = BLANK; // Could be moved out of the loop
          Block[BlockIndex] |= valbit;
          Row[RowIndex] |= valbit;
          Col[ColIndex] |= valbit;
	}

    SwapSeqEntries(S, S2);
}

void solveSudoku(char **board, int m, int n) {
    SeqPtr = 0;
    int i, j, Square;

	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++) {
			Square = 9 * i + j;
			InRow[Square] = i;
			InCol[Square] = j;
			InBlock[Square] = (i / 3) * 3 + ( j / 3);
		}


	for (Square = 0; Square < 81; Square++) {
        Sequence[Square] = Square;
		Entry[Square] = BLANK;
    }
    
	for (i = 0; i < 9; i++) 
		Block[i] = Row[i] = Col[i] = ONES;
    
    for (int i = 0; i < 9; ++i)
       for (int j = 0; j < 9; ++j) {
           if ('.' != board[i][j])
                InitEntry(i, j, board[i][j] - '0');
       }
       
    Place(SeqPtr, board);
}
