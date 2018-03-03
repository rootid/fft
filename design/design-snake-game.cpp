//Design Snake Game
//Design a Snake game that is played on a device with screen size = width x
//height. Play the game online if you are not familiar with the game.
//The snake is initially positioned at the top left corner (0,0) with length =
//1 unit.
//You are given a list of food's positions in row-column order. When a snake
//eats the food, its length and the game's score both increase by 1.
//Each food appears one by one on the screen. For example, the second food will
//not appear until the first food was eaten by the snake.
//When a food does appear on the screen, it is guaranteed that it will not
//appear on a block occupied by the snake.
//Example:
//Given width = 3, height = 2, and food = [[1,2],[0,1]].
//Snake snake = new Snake(width, height, food);
//Initially the snake appears at position (0,0) and the food at (1,2).
//|S| | |
//| | |F|
//snake.move("R"); -> Returns 0
//| |S| |
//| | |F|
//snake.move("D"); -> Returns 0
//| | | |
//| |S|F|
//snake.move("R"); -> Returns 1 (Snake eats the first food and right after
//that, the second food appears at (0,1) )
//| |F| |
//| |S|S|
//snake.move("U"); -> Returns 1
//| |F|S|
//| | |S|
//snake.move("L"); -> Returns 2 (Snake eats the second food)
//| |S|S|
//| | |S|
//snake.move("U"); -> Returns -1 (Game over because snake collides with border)

//Deque
//1. snake changes position so need to keep track of head and tail
//Update tail only when snake eats something
//######################################### HashSet + Deque #########################################
public class SnakeGame {

    //2D position info is encoded to 1D and stored as two copies
    Set<Integer> set; // this copy is good for fast loop-up for eating body case
    Deque<Integer> body; // this copy is good for updating tail
    int score; //if game over update the score to avoid repeated move
    int[][] food;
    int foodIndex;
    int width;
    int height;

    public SnakeGame(int width, int height, int[][] food) {
        this.width = width;
        this.height = height;
        this.food = food;
        set = new HashSet<>();
        set.add(0); //intially at [0][0]
        body = new LinkedList<>();
        body.offerLast(0);
    }

    public int move(String direction) {
        //case 0: game already over: do nothing
        if (score == -1) {
            return -1;
        }
        // compute new head
        int rowHead = body.peekFirst() / width;
        int colHead = body.peekFirst() % width;
        switch (direction) {
            case "U" : rowHead--;
                       break;
            case "D" : rowHead++;
                       break;
            case "L" : colHead--;
                       break;
            default :  colHead++;
        }
        int head = rowHead * width + colHead; //new head position

        //case 1: out of boundary or eating body , always need to update the body
        set.remove(body.peekLast()); // new head is legal to be in old tail's position, remove from set temporarily
		//Check boundry + new head is part of snak body
        if (rowHead < 0 || rowHead == height || colHead < 0 || colHead == width || set.contains(head)) {
            return score = -1;
        }

        // add head for case2 and case3
        set.add(head);
        body.offerFirst(head); //update snake body to point to new head

        //case2: eating food, keep tail, add head
        if (foodIndex < food.length && rowHead == food[foodIndex][0] && colHead == food[foodIndex][1]) {
            set.add(body.peekLast()); // old tail does not change, so add it back to set
            foodIndex++;
            return ++score;
        }

        //case3: normal move, remove tail, add head
        body.pollLast();
        return score;

    }
}

//######################################### HashSet + Deque + Hash function #########################################
class Solution {
    int[][] f;
    int w, h, i;
    Deque<Integer> s; //snake

	//The set keeps the hash value of all the index of the body of the snake.
	//So its purpose it to make checking for eating body case easy.
	//All you need to do is to check for if the new position of the head is in the set.
	//If it is in, the snake bites itself, and if not, it is safe.
    Set<Integer> set;
    int p = 199; // prime # to compute hash code

    public SnakeGame(int width, int height, int[][] food) {
        f = food;
        w = width;
        h = height;
        i = 0;
        s = new ArrayDeque();
        set = new HashSet();
        s.offerLast(0);
        set.add(0);
    }
    public int move(String direction) {
        int head = s.peekLast();
        int hr = head % p;
        int hc = head / p;
        switch(direction){
            case "U":
                hr--;
                break;
            case "L":
                hc--;
                break;
            case "R":
                hc++;
                break;
            case "D":
                hr++;
                break;
        }
        if(i < f.length && hr == f[i][0] && hc == f[i][1]){
            i++;
        } else {
            int first = s.pollFirst();
            set.remove(first);
        }
        int newHead = hc * p + hr;
        if(hr < 0 || hr >= h || hc < 0 || hc >= w || set.contains(newHead)){
            return -1;
        }
        s.offerLast(newHead);
        set.add(newHead);
        return set.size() - 1;
    }
}


//######################################### Set + Deque #########################################
class SnakeGame {
public:
/** Initialize your data structure here.
@param width - screen width
@param height - screen height
@param food - A list of food positions
E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */

int w, h, pos;
vector<pair<int, int>> food;
set<pair<int, int>> hist;
deque<pair<int, int>> q;

SnakeGame(int width, int height, vector<pair<int, int>> food) {
	this->food = food;
	w = width, h = height, pos = 0;
	q.push_back(make_pair(0, 0));
}

/** Moves the snake.
@param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
@return The game's score after the move. Return -1 if game over.
Game over when snake crosses the screen boundary or bites its body. */
int move(string direction) {
	int row = q.back().first, col = q.back().second;
	pair<int, int> d = q.front(); q.pop_front();
	hist.erase(d);

	if (direction == "U")
		row--;
	else if (direction == "D")
		row++;
	else if (direction == "L")
		col--;
	else if (direction == "R")
		col++;

	if (row < 0 || col < 0 || col >= w || row >= h || hist.count(make_pair(row, col)))
		return -1;

	hist.insert(make_pair(row, col));
	q.push_back(make_pair(row, col));

	if (pos >= food.size())
		return q.size() - 1;

	if (row == food[pos].first && col == food[pos].second) {
		pos++;
		q.push_front(d);
		hist.insert(d);
	}

	return q.size() - 1;
  }
};


//######################################### Complex Number traversal  #########################################

//use real number to represent row and
//complex number to represent column,
//so we could easily add 1 or 1j to row and col
//without doing something really ugly like pos[0] + direction[0], pos[1] +
//direction[1].
//Complex Number use :
//it makes computing the neighbor coordinate nicer. Even lets me compute what
//to add with 1j ** ... instead of hardcoding something like [1, 1j, -1,
//-1j][...].
//Just came up with an alternative initialization which I think is nicer. Not
//sure why I didn't do that earlier.
//old:    food = [x + y*1j for x, y in food[::-1]]
//new:    food = [complex(*z) for z in food[::-1]]
class SnakeGame(object):
    def __init__(self, width, height, food):
        food = [complex(*z) for z in food[::-1]]
        snake = collections.OrderedDict([(0, True)])
        self.score = 0
        def move(direction):
            head = next(reversed(snake)) + 1j ** 'DRU'.find(direction)
            if head in food[-1:]:
                food.pop()
                self.score += 1
            else:
                snake.popitem(False)
            if head in snake or not (0 <= head.imag < width and 0 <= head.real < height):
                return -1
            snake[head] = True
            return self.score
        self.move = move



//######################################### LL #########################################
//TC ~ O(N)
class SnakeGame {
    class Position{
        int x;
        int y;
        public Position(int x,int y){
            this.x = x;
            this.y = y;
        }
        public boolean isEqual(Position p){
            return this.x==p.x && this.y == p.y ;
        }
    }
    int len;
    int rows ,cols;

    int[][] food;
    LinkedList<Position> snake;

    /** Initialize your data structure here.
        @param width - screen width
        @param height - screen height
        @param food - A list of food positions
        E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
    public SnakeGame(int width, int height, int[][] food) {
        this.rows = height;
        this.cols = width;
        this.food = food;

        snake = new LinkedList<Position>();
        snake.add(new Position(0,0));
        len = 0;
    }

    /** Moves the snake.
        @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
        @return The game's score after the move. Return -1 if game over.
        Game over when snake crosses the screen boundary or bites its body. */
    public int move(String direction) {
    	//if(len>=food.length) return len;

        Position cur = new Position(snake.get(0).x,snake.get(0).y);

        switch(direction){
        case "U":
            cur.x--;  break;
        case "L":
            cur.y--; break;
        case "R":
            cur.y++;   break;
        case "D":
            cur.x++;   break;
        }

        if(cur.x<0 || cur.x>= rows || cur.y<0 || cur.y>=cols) return -1;


        for(int i=1;i<snake.size()-1;i++){
            Position next = snake.get(i);
            if(next.isEqual(cur)) return -1;
        }
        snake.addFirst(cur);
        if(len<food.length){
            Position p = new Position(food[len][0],food[len][1]);
            if(cur.isEqual(p)){
                len++;
            }
        }
        while(snake.size()>len+1) snake.removeLast();

        return len;
    }
}

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame obj = new SnakeGame(width, height, food);
 * int param_1 = obj.move(direction);
 */
