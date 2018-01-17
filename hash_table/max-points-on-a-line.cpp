//Max Points on a Line
//Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
//############### float issue 
//[0,0], [94911151, 94911150], [94911152, 94911151] : failed ip
 int maxPoints(vector<Point>& points) {
     unordered_map<float, int> slopes;
     int maxp = 0, n = points.size();
     for (int i = 0; i < n; i++) {
         slopes.clear();
         int duplicate = 1; 
         for (int j = i + 1; j < n; j++) {
             if (points[j].x == points[i].x && points[j].y == points[i].y) {
                 duplicate++; //same point
                 continue;
             }
             float slope = (points[j].x == points[i].x) ? INT_MAX :  //vertical lines y co-ordinates differ with inf slope
                           (float)(points[j].y - points[i].y) / (points[j].x - points[i].x); // slope y2-y1/x2-x1
             slopes[slope]++;
         }
         //count the duplicates if exists
         maxp = max(maxp, duplicate); //get the max number of co-ordinates
         for (auto slope : slopes) 
             if (slope.second + duplicate > maxp) 
                 maxp = slope.second + duplicate; 
     }
     return maxp; 
 }

//######
//Pair + GCD
public: 
    int maxPoints(vector<Point>& points) {
        map<pair<int, int>, int> slopes;
        int maxp = 0, n = points.size();
        for (int i = 0; i < n; i++) {
            slopes.clear();
            int duplicate = 1;
            for (int j = i + 1; j < n; j++) {
                if (points[j].x == points[i].x && points[j].y == points[i].y) {
                    duplicate++;
                    continue;
                }
                int dx = points[j].x - points[i].x;
                int dy = points[j].y - points[i].y;
                int dvs = gcd(dx, dy);
                slopes[make_pair(dx / dvs, dy / dvs)]++;
            }
            maxp = max(maxp, duplicate); //4,2 duplicates ,in case of all duplicates (0,0),(0,0)
            for (auto slope : slopes)
                if (slope.second + duplicate > maxp) //add duplicate in each slope
                    maxp = slope.second + duplicate;
        } 
        return maxp;
    }
private:
    int gcd(int num1, int num2) {
        while (num2) {
            int temp = num2; 
            num2 = num1 % num2;
            num1 = temp;
        }
        return num1;
    }
