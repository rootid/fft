//The Maze II
//There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.
//Given the ball's start position, the destination and the maze, find the shortest distance for the ball to stop at the destination. The distance is defined by the number of empty spaces traveled by the ball from the start position (excluded) to the destination (included). If the ball cannot stop at the destination, return -1.
//The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the borders of the maze are all walls. The start and destination coordinates are represented by row and column indexes.
//Example 1
//Input 1: a maze represented by a 2D array
//0 0 1 0 0
//0 0 0 0 0
//0 0 0 1 0
//1 1 0 1 1
//0 0 0 0 0
//Input 2: start coordinate (rowStart, colStart) = (0, 4)
//Input 3: destination coordinate (rowDest, colDest) = (4, 4)
//Output: 12
//Explanation: One shortest way is : left -> down -> left -> down -> right -> down -> right.
//             The total distance is 1 + 1 + 3 + 1 + 2 + 2 + 2 = 12.
//Example 2
//Input 1: a maze represented by a 2D array
//0 0 1 0 0
//0 0 0 0 0
//0 0 0 1 0
//1 1 0 1 1
//0 0 0 0 0
//Input 2: start coordinate (rowStart, colStart) = (0, 4)
//Input 3: destination coordinate (rowDest, colDest) = (3, 2)
//Output: -1
//Explanation: There is no way for the ball to stop at the destination.
//Note:
//There is only one ball and one destination in the maze.
//Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
//The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
//The maze contains at least 2 empty spaces, and both the width and height of the maze won't exceed 100.
//

//######################################### Pri. Q #########################################
//Solution of The Maze: https://discuss.leetcode.com/topic/77471/easy-understanding-java-bfs-solution
//Solution of The Maze III: https://discuss.leetcode.com/topic/77474/similar-to-the-maze-ii-easy-understanding-java-bfs-solution
//We need to use PriorityQueue instead of standard queue, and record the minimal length of each point.
//
//Why using PriorityQueue?
//We can consider this question as a shortest-route graph problem, that is, each stoppable point is a vertical, where every possible path between two nodes is an edge.
//In this way, we can using Dijkstra algorithm to solve this problem, and that's why we use PriorityQueue.

public class Solution {
    class Point {
        int x,y,l;
        public Point(int _x, int _y, int _l) {x=_x;y=_y;l=_l;}
    }
    public int shortestDistance(int[][] maze, int[] start, int[] destination) {
        int m=maze.length, n=maze[0].length;
        int[][] length=new int[m][n]; // record length
        for (int i=0;i<m*n;i++) length[i/n][i%n]=Integer.MAX_VALUE;
        int[][] dir=new int[][] {{-1,0},{0,1},{1,0},{0,-1}};
        PriorityQueue<Point> list=new PriorityQueue<>((o1,o2)->o1.l-o2.l); // using priority queue
        list.offer(new Point(start[0], start[1], 0));
        while (!list.isEmpty()) {
            Point p=list.poll();
            if (length[p.x][p.y]<=p.l) continue; // if we have already found a route shorter
            length[p.x][p.y]=p.l;
            for (int i=0;i<4;i++) {
                int xx=p.x, yy=p.y, l=p.l;
                while (xx>=0 && xx<m && yy>=0 && yy<n && maze[xx][yy]==0) {
                    xx+=dir[i][0];
                    yy+=dir[i][1];
                    l++;
                }
                xx-=dir[i][0];
                yy-=dir[i][1];
                l--;
                list.offer(new Point(xx, yy, l));
            }
        }
        return length[destination[0]][destination[1]]==Integer.MAX_VALUE?-1:length[destination[0]][destination[1]];
    }
}

//######################################### DFS #########################################
//Time complexity : O(m∗n∗max(m,n)). Complete traversal of maze will be done in the worst case. Here, mmm and nnn refers to the number of rows and columns of the maze. Further, for every current node chosen, we can travel upto a maximum depth of max(m,n)\text{max}(m,n)max(m,n) in any direction.
//Space complexity : O(mn). distancedistancedistance array of size m∗nm*nm∗n is used.
public class Solution {
    public int shortestDistance(int[][] maze, int[] start, int[] dest) {
        int[][] distance = new int[maze.length][maze[0].length];
        for (int[] row: distance)
            Arrays.fill(row, Integer.MAX_VALUE);
        distance[start[0]][start[1]] = 0;
        dfs(maze, start, distance);
        return distance[dest[0]][dest[1]] == Integer.MAX_VALUE ? -1 : distance[dest[0]][dest[1]];
    }

    public void dfs(int[][] maze, int[] start, int[][] distance) {
        int[][] dirs={{0,1}, {0,-1}, {-1,0}, {1,0}};
        for (int[] dir: dirs) {
            int x = start[0] + dir[0];
            int y = start[1] + dir[1];
            int count = 0;
            while (x >= 0 && y >= 0 && x < maze.length && y < maze[0].length && maze[x][y] == 0) {
                x += dir[0];
                y += dir[1];
                count++;
            }
            if (distance[start[0]][start[1]] + count < distance[x - dir[0]][y - dir[1]]) {
                distance[x - dir[0]][y - dir[1]] = distance[start[0]][start[1]] + count;
                dfs(maze, new int[]{x - dir[0],y - dir[1]}, distance);
            }
        }
    }
}

//######################################### BFS #########################################
//Time complexity : O(m∗n∗max(m,n). Time complexity : O(m∗n∗max(m,n))O(m*n*\text{max}(m,n))O(m∗n∗max(m,n)). Complete traversal of maze will be done in the worst case. Here, mmm and nnn refers to the number of rows and columns of the maze. Further, for every current node chosen, we can travel upto a maximum depth of max(m,n)\text{max}(m,n)max(m,n) in any direction.
//Space complexity : O(mn). queuequeuequeue size can grow upto m∗nm*nm∗n in the worst case.
//
public class Solution {
    public int shortestDistance(int[][] maze, int[] start, int[] dest) {
        int[][] distance = new int[maze.length][maze[0].length];
        for (int[] row: distance)
            Arrays.fill(row, Integer.MAX_VALUE);
        distance[start[0]][start[1]] = 0;
         int[][] dirs={{0, 1} ,{0, -1}, {-1, 0}, {1, 0}};
        Queue < int[] > queue = new LinkedList < > ();
        queue.add(start);
        while (!queue.isEmpty()) {
            int[] s = queue.remove();
            for (int[] dir: dirs) {
                int x = s[0] + dir[0];
                int y = s[1] + dir[1];
                int count = 0;
                while (x >= 0 && y >= 0 && x < maze.length && y < maze[0].length && maze[x][y] == 0) {
                    x += dir[0];
                    y += dir[1];
                    count++;
                }
                if (distance[s[0]][s[1]] + count < distance[x - dir[0]][y - dir[1]]) {
                    distance[x - dir[0]][y - dir[1]] = distance[s[0]][s[1]] + count;
                    queue.add(new int[] {x - dir[0], y - dir[1]});
                }
            }
        }
        return distance[dest[0]][dest[1]] == Integer.MAX_VALUE ? -1 : distance[dest[0]][dest[1]];
    }
}
