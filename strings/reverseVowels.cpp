//Reverse Vowels of a String
//Write a function that takes a string as input and reverse only the vowels of
//a string.
//Example 1:
//Given s = "hello", return "holle".
//Example 2:
//Given s = "leetcode", return "leotcede".

string reverseVowels(string s) {
    int start = 0;
    int end = s.length() - 1;
    unordered_set<char> vowelStore = {'a','e','i','o','u','A','E','I','O','U'};
    while(start < end) {
        if(vowelStore.find(s[start]) == vowelStore.end() ) {
            start++;
        } else if (vowelStore.find(s[end]) == vowelStore.end()) {
            end--;
        } else {
            swap(s[start],s[end]);
            start++;
            end--;
        }
    }
    return s;
}

int main(int argc, char *argv[])
{

  string s = "hello";
  string t = reverseVowels(s);
  cout << " reversal " << t << endl;
  return 0;
}
