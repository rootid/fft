//N-Queens II
//Instead outputting board configurations, return the total number of distinct
//solutions.

//https://www.cs.utexas.edu/users/EWD/transcriptions/EWD03xx/EWD316.9.html#contents
/* Things to consider
* 1.At max,# of queens in the ROW = 1.
* 2.At max,# of queens in the col = 1
* 3.At max,# of queen in the diagonal = 1. (upward + downward)
*/
#include "../headers/global.hpp"

void print_solution (int row[],int n) {
    for (int i=0;i<n+1;i++) {
        cout << row[i] << " " ;
    }
    cout << endl;
}

void enum_queen(int input,int k,int c,int solution_size
              ,bool col[],bool left_diag[],bool right_diag[],int row[],int& solution_count) {
    if (k == (solution_size - 1)) {
        //cout << "found the solution" <<endl;
       // print_solution (row,k);
        solution_count++;
    } else {
        k = k + 1; //iterate over row
        for (int i=0;i<c;i++) { //iterate over columns
            //Think of board
            //left diag = row+col , right digonal = row-col + (no_of_queen - 1)
            if (col[i] && left_diag[k+i] && right_diag[k-i+(input -1)]) {
                //cout << "( " << i << "," << k+i << "," << k-i+3 << ")" << endl;
                row[k] = i;
                //SET
                col[i] = false;
                left_diag[k+i]= false;
                right_diag[k-i+(input -1)] = false;
                enum_queen (input,k,c,solution_size,col,left_diag,right_diag,row,solution_count);
                //RESET /backtrack
                col[i] = true;
                left_diag[k+i]= true;
                right_diag[k-i+(input -1)] = true;
            }
        }
    }
}

int totalNQueens(int n) {
    bool col[n];
    bool left_diag[ (n * 2) -1]; //# of left digonals
    bool right_diag[(n * 2) -1]; //# of right digonals
    int row[n];
    for (int i=0;i<n;i++) {
        col[i] = true;
    }
    for (int i=0;i< (n*2)-1;i++) {
        left_diag [i] = true;
        right_diag[i] = true;
    }
    int solution_cnt = 0;
    enum_queen(n,-1,n,n
            ,col,left_diag,right_diag,row,solution_cnt) ;
    return solution_cnt;
}

int main () {
    int no_of_queens = 5 ;

    cout << "solution_cnt = " << totalNQueens(no_of_queens) << endl;
}
