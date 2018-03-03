//Judge Route Circle
//Initially, there is a Robot at position (0, 0). Given a sequence of its
//moves, judge if this robot makes a circle, which means it moves back to the
//original place.
//The move sequence is represented by a string. And each move is represent by a
//character. The valid robot moves are R (Right), L (Left), U (Up) and D
//(down). The output should be true or false representing whether the robot
//makes a circle.
//Example 1:
//Input: "UD"
//Output: true
//Example 2:
//Input: "LL"
//Output: false

//######################################### T: O(n) + S : O(k) #########################################
  bool judgeCircle(string moves) {
        int v = 0;
        int h = 0;
        for (char ch : moves) {
            switch (ch) {
                case 'U' : v++; break;
                case 'D' : v--; break;
                case 'R' : h++; break;
                case 'L' : h--; break;
            }
        }
        return v == 0 && h == 0;
    }

//######################################### T: O(n) + S : O(k) #########################################
public boolean judgeCircle(String moves) {
    int x = 0;
    int y = 0;
    for (char ch : moves.toCharArray()) {
        if (ch == 'U') y++;
        else if (ch == 'D') y--;
        else if (ch == 'R') x++;
        else if (ch == 'L') x--;
    }
    return x == 0 && y == 0;
}
//######################################### T: O(n) + S : O(k) #########################################
bool judgeCircle(string moves) {
    int x = 0, y = 0;
    for(char c: moves){
        x += (c == 'R') - (c == 'L'), y += (c == 'U') - (c == 'D');
    }
    return x == 0 && y == 0;
}

//######################################### T: O(n) + S : O(k) #########################################
public boolean judgeCircle(String moves) {
    int x = 0, y = 0;
    for(char c: moves.toCharArray()){
        x += (c=='R'?1:0) + (c=='L'?-1:0); y += (c=='U'?1:0) + (c=='D'?-1:0);
    }
    return x == 0 && y == 0;
}


def judgeCircle(self, moves):
    direct = {'U': 1, 'D': -1, 'L': 1j, 'R': -1j}
    return 0 == sum(direct[m] for m in moves)

def judgeCircle(self, moves):
    c = collections.Counter(moves)
    return c['L'] == c['R'] and c['U'] == c['D']

def judgeCircle(self, moves):
    return not sum(map({'U': 1, 'D': -1, 'L': 1j, 'R': -1j}.get, moves))

//######################################### python 3 #########################################
def judgeCircle(self, moves):
    return not sum(map(1j.__pow__, map('RUL'.find, moves)))

def judgeCircle(self, moves):
    return not sum(1j**'RUL'.find(m) for m in moves)
