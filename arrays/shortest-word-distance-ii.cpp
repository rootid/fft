//Shortest Word Distance II
//This is a follow up of Shortest Word Distance. The only difference is now you
//are given the list of words and your method will be called repeatedly many
//times with different parameters. How would you optimize it?
//Design a class which receives a list of words in the constructor, and
//implements a method that takes two words word1 and word2 and return the
//shortest distance between these two words in the list.
//For example,
//Assume that words = ["practice", "makes", "perfect", "coding", "makes"].
//Given word1 = “coding”, word2 = “practice”, return 3.
//Given word1 = "makes", word2 = "coding", return 1.
//Note:
//You may assume that word1 does not equal to word2, and word1 and word2 are
//both in the list.

class WordDistance {
private :
    unordered_map<string,vector<int> > word_map;
public:
    WordDistance(vector<string>& words) {
        int idx = 1;
        for(auto& word : words) {
            word_map[word].push_back(idx++);
        }
    }
    int shortest(string word1, string word2) {
        int i = 0;
        int j = 0;
        int min_dist = INT_MAX;
        while(i < word_map[word1].size() && j < word_map[word2].size()) {
            min_dist = min(min_dist,abs(word_map[word1][i] - word_map[word2][j]));
            if(word_map[word1][i] < word_map[word2][j]) { // [ 1,3] [2] , [4,19] [2,22]
                i++;
            } else {
                j++;
            }
        }
        return min_dist;
    }
};
// Your WordDistance object will be instantiated and called as such:
// WordDistance wordDistance(words);
// wordDistance.shortest("word1", "word2");
// wordDistance.shortest("anotherWord1", "anotherWord2");
