//Strobogrammatic Number
//A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
//Write a function to determine if a number is strobogrammatic. The number is represented as a string.
//For example, the numbers "69", "88", and "818" are all strobogrammatic.
bool isStrobogrammatic(string num) {
    unordered_map<char,char> kv_pair= { {'1','1'},{'6','9'},{'8','8'},{'9','6'},{'0','0'} };
    int r = num.size() -1;
    int l = 0;
    while(l <= r) {
        if( kv_pair [ num[l] ]  == num[r] ) {
            l++;
            r--; 
        } else {
            return false;
        }
    }
    return true;
}

int main() {

}
