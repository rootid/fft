//
//Given a rows x cols screen and a sentence represented by a list of words, find how many times the given sentence can be fitted on the screen.
//Note:
//A word cannot be split into two lines.
//The order of words in the sentence must remain unchanged.
//Two consecutive words in a line must be separated by a single space.
//Total words in the sentence won't exceed 100.
//Length of each word won't exceed 10.
//1 ≤ rows, cols ≤ 20,000.
//Example 1:
//Input:
//rows = 2, cols = 8, sentence = ["hello", "world"]
//Output: 
//1
//Explanation:
//hello---
//world---
//The character '-' signifies an empty space on the screen.
//Example 2:
//Input:
//rows = 3, cols = 6, sentence = ["a", "bcd", "e"]
//Output: 
//2
//Explanation:
//a-bcd- 
//e-a---
//bcd-e-
//The character '-' signifies an empty space on the screen.
//Example 3:
//Input:
//rows = 4, cols = 5, sentence = ["I", "had", "apple", "pie"]
//Output: 
//1
//Explanation:
//I-had
//apple
//pie-I
//had--
//The character '-' signifies an empty space on the screen.
//

#include "../headers/global.hpp"

int wordsTyping(vector<string>& sentence, int rows, int cols) {
        int rowIndex = 1;
        int remainingCols = cols;
        int index= 0;
        int size = sentence.size();
        vector<int> wlen;
        int wc = 0;
        for(int i=0; i<sentence.size(); i++) {
            wlen.push_back(sentence[i].length());
            wc += sentence[i].length();
            wc += 1; //add space
        }
        cout << "wc " << wc << endl;
        int cycle = 0;
        while(rowIndex <= rows) {
            if(index == 0 && wc <= remainingCols) { //case where we can fit all the words in a single line
                cycle += (remainingCols) / wc; 
                remainingCols = remainingCols % wc;
            } else {
                //can accomodate the word
                if(wlen[index] <= remainingCols) {  
                    if(index == size-1) { //all words traversed
                        cycle++;
                    }
                    remainingCols = remainingCols - wlen[index]; //update remainingCols 
                    remainingCols -= 1; //add space 
                    index = (index + 1)%size; //Fetch the next word
                } else { //cannot accomodate the word
                    rowIndex++;  //increase row 
                    remainingCols = cols; //reset the remainingCols count
                }
            }
        }
    cout << "Total cycles = " << cycle << endl;
    return(cycle);
}

int main () {
  //vector<string> strs( {"a","bcd","e"} );
  vector<string> strs( {"abcdef","a","b"} );
  wordsTyping(strs,3,5);
}

// vim: set sw=2 sts=2 tw=120 et nospell : 
