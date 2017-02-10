//Permutation Sequence
//The set [1,2,3,…,n] contains a total of n! unique permutations.
//By listing and labeling all of the permutations in order,
//We get the following sequence (ie, for n = 3):
//"123"
//"132"
//"213"
//"231"
//"312"
//"321"
//Given n and k, return the kth permutation sequence.
//Note: Given n will be between 1 and 9 inclusive.
#include "../headers/global.hpp"


string getPermutation(int n, int k) {
    vector<int> numSet;
    string result;
    for (int i = 1; i <= n; i++) {
      numSet.push_back(i);
    }
    int fact[10] = {1};
    for (int i = 1; i < n; i++) {
      fact[i] = i*fact[i-1];
    }
    k = k-1; //idx starts from 0
    for (int i = n; i > 0; i--){
        int idx = k/fact[i-1]; //Select from choice(k)
        k = k%fact[i-1]; //Update choice 
        result += to_string(numSet[idx]);
        numSet.erase(numSet.begin() + idx);
    }
    return result;
}

//###### 
string getPermutation(int n, int k) {
    string result;
    vector<int> numSet;
    int fact = 1;
    for (int i = 1; i <= n; i++) {
        numSet.push_back(i);
    }
    for (int i = 2; i <= n; i++) {
        fact *= i; // factorial
    }
    for (k--; n > 0; n--) {
        fact /= n;
        int tmp = k/fact;
        result += to_string(numSet[tmp]);
        numSet.erase(numSet.begin() + tmp);
        k %= fact;
    }
    
    return result;
}
//######## Only store n digits #################
string getPermutation(int n, int k) {
    int pTable = n, temp;
    vector<char> numSet(n, '1');
    for(int i = 1; i < n; i++){
        pTable *= i;
        numSet[i] = numSet[i-1] + 1;
    }
    string res;
    while( n > 0 ){
        pTable /= n;
        temp = (k-1)/pTable;
        res += numSet[temp];
        numSet.erase(numSet.begin() + temp);
        k -= temp * pTable;
        n--;
    }
    return res;
}
//######## store 1-9 digits #################
string getPermutation(int n, int k) {
    int pTable[10] = {1};
    for(int i = 1; i <= 9; i++) {
        pTable[i] = i * pTable[i - 1];
        cout << pTable[i] << endl;
    }
    string result;
    vector<char> numSet{'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    while(n > 0){
      int temp = (k - 1) / pTable[n - 1]; //k-1 : index starts from 0
        result += numSet[temp];  //pick the element
        //remove the selected #
        numSet.erase(numSet.begin() + temp);
        k = k - temp * pTable[n - 1]; //update the k 
        n--;
    }
    return result;
}
int main() {
  getPermutation(4,2);
}
