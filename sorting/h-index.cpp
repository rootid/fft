//Given an array of citations (each citation is a non-negative integer) of a
//researcher, write a function to compute the researcher's h-index.
//According to the definition of h-index on Wikipedia: "A scientist has index h
//if h of his/her N papers have at least h citations each, and the other N − h
//papers have no more than h citations each."
//For example, given citations = [3, 0, 6, 1, 5], which means the researcher
//has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations
//respectively. Since the researcher has 3 papers with at least 3 citations
//each and the remaining two with no more than 3 citations each, his h-index is
//3.
//Note: If there are several possible values for h, the maximum one is taken as
//the h-index.
//Hint:
//An easy approach is to sort the array first.
//What are the possible values of h-index?
//A faster approach is to use extra space.
//

#include "../headers/global.hpp"

int hIndex(vector<int>& citations) {
    sort(citations.begin(),citations.end());
    //sort(citations.rbegin(), citations.rend());
    int h = 0, i = citations.size() - 1;
    //3, 0, 6, 1, 5 => 6,5,3,1,0 =>   0,1,3,5,6
    for (int c : citations) {       //5,4,3,2,1
        if(c > i) { //if citations are greater than the paper count compute (n-h > 0)
            h++;
        }
        i--;
    }
    return h;
}

int main() {

}
