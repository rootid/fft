//Flip Game
//You are playing the following Flip Game with your friend: Given a string that
//contains only these two characters: + and -, you and your friend take turns
//to flip two consecutive "++" into "--". The game ends when a person can no
//longer make a move and therefore the other person will be the winner.
//Write a function to compute all possible states of the string after one valid
//move.
//For example, given s = "++++", after one move, it may become one of the
//following states:
//[
//  "--++",
//  "+--+",
//  "++--"
//]
//If there is no valid move, return an empty list [].
vector<string> generatePossibleNextMoves(string s) {
    vector<string> result;
    int len = s.size();
    for(int i=0;i<len - 1;) {
        if(s[i] == s[++i] && s[i] == '+') {
            //cout << i << endl;
            result.push_back(s.substr(0,i-1)+ "--" + s.substr(i+1) );
        }
    }
    return result;
}


List<String> generatePossibleNextMoves(String s) {
    List<String> result = new LinkedList<>();
	if(s == null || s.length() <= 1) return result;
    int len = s.length();
    for(int i=0;i<len - 1;) {
        if(s.charAt(i) == s.charAt(++i) && s.charAt(i) == '+') {
            result.add(s.substring(0,i-1)+ "--" + s.substring(i+1) );
        }
    }
    return result;
}
