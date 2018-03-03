// Super Pow
//Your task is to calculate ab mod 1337 where a is a positive integer and b is
//an extremely large positive integer given in the form of an array.
//Example1:
//a = 2
//b = [3]
//Result: 8
//Example2:
//a = 2
//b = [1,0]
//Result: 1024
//Montgomery modular multiplication

//############################################# myPow  ##################################
int myPow( int x, int y ){
    int ans = 1;
    while( y-- ) {
        ans = (ans * x) % 1337;
    }
    return ans;
}

int superPow(int a, vector<int>& b) {
    a = a % 1337;
    long result = 1;
    while( b.size() ){
        result = ( result * myPow( a, b.back() ) ) % 1337;
        b.pop_back();
        a = myPow( a, 10 );
    }
    return result;
}
