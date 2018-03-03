//Shortest Word Distance III
//This is a follow up of Shortest Word Distance. The only difference is now
//word1 could be the same as word2.
//Given a list of words and two words word1 and word2, return the shortest
//distance between these two words in the list.
//word1 and word2 may be the same and they represent two individual words in
//the list.
//For example,
//Assume that words = ["practice", "makes", "perfect", "coding", "makes"].
//Given word1 = “makes”, word2 = “coding”, return 1.
//Given word1 = "makes", word2 = "makes", return 3.
//Note:
//You may assume word1 and word2 are both in the list.
int shortestWordDistance(vector<string>& words, string word1, string word2) {
    int len = words.size();
    long long idx1 = len;
    long long idx2 = -len;
    long long min_dist = INT_MAX;
    int idx = 0;
    for(auto& word:words) {
        idx += 1;
        if(word == word1) {
            idx1 = idx;
        }
        if(word == word2) {
            if(word1 == word2) {
                idx1 = idx2;
            }
           idx2 = idx;
        }
        min_dist = min(min_dist, abs(idx1-idx2));
    }
    return min_dist;
}

int main() {

}
