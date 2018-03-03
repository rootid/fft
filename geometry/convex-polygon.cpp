//Convex Polygon
//Given a list of points that form a polygon when joined sequentially, find if
//this polygon is convex (Convex polygon definition)
//[https://en.wikipedia.org/wiki/Convex_polygon].
//Note:
//There are at least 3 and at most 10,000 points.
//Coordinates are in the range -10,000 to 10,000.
//You may assume the polygon formed by given points is always a simple polygon
//(Simple polygon definition) [https://en.wikipedia.org/wiki/Simple_polygon] .
//In other words, we ensure that exactly two edges intersect at each vertex,
//and that edges otherwise don't intersect each other.
//Example 1:
//[[0,0],[0,1],[1,1],[1,0]]
//Answer: True
//Explanation:
//Example 2:
//[[0,0],[0,10],[10,10],[10,0],[5,5]]
//Answer: False
//Explanation:
//
//#########################################  #########################################
//Well, I have to say that this problem is beyond my knowledge. @Ipeq1 and
//@zzg_zzm have explained how to solve this problem in their posts
//https://discuss.leetcode.com/topic/70643/i-believe-this-time-it-s-far-beyond-my-ability-to-get-a-good-grade-of-the-contest
//https://discuss.leetcode.com/topic/70664/c-7-line-o-n-solution-to-check-convexity-with-cross-product-of-adajcent-vectors-detailed-explanation
//The algorithm itself is not hard but I have no idea there exists such a way
//to determine if a polygon is convex or not. Laugh at me for my ignorance... I
//believe 90% of programmers can solve this problem if they were given the
//formula.
//Anyway, following is the Java solution with in-line explanation. Accepted,
//32ms. Reference:
//http://csharphelper.com/blog/2014/07/determine-whether-a-polygon-is-convex-in-c/

public class Solution {
    public boolean isConvex(List<List<Integer>> points) {
        // For each set of three adjacent points A, B, C, find the cross product AB · BC. If the sign of
        // all the cross products is the same, the angles are all positive or negative (depending on the
        // order in which we visit them) so the polygon is convex.
        boolean gotNegative = false;
        boolean gotPositive = false;
        int numPoints = points.size();
        int B, C;
        for (int A = 0; A < numPoints; A++) {
            // Trick to calc the last 3 points: n - 1, 0 and 1.
            B = (A + 1) % numPoints;
            C = (B + 1) % numPoints;

            int crossProduct =
                crossProductLength(
                    points.get(A).get(0), points.get(A).get(1),
                    points.get(B).get(0), points.get(B).get(1),
                    points.get(C).get(0), points.get(C).get(1));
            if (crossProduct < 0) {
                gotNegative = true;
            }
            else if (crossProduct > 0) {
                gotPositive = true;
            }
            if (gotNegative && gotPositive) return false;
        }

        // If we got this far, the polygon is convex.
        return true;
    }

    // Return the cross product AB x BC.
    // The cross product is a vector perpendicular to AB and BC having length |AB| * |BC| * Sin(theta) and
    // with direction given by the right-hand rule. For two vectors in the X-Y plane, the result is a
    // vector with X and Y components 0 so the Z component gives the vector's length and direction.
    private int crossProductLength(int Ax, int Ay, int Bx, int By, int Cx, int Cy)
    {
        // Get the vectors' coordinates.
        int BAx = Ax - Bx;
        int BAy = Ay - By;
        int BCx = Cx - Bx;
        int BCy = Cy - By;

        // Calculate the Z coordinate of the cross product.
        return (BAx * BCy - BAy * BCx);
    }
}

//#########################################  #########################################
//ttp://www.geeksforgeeks.org/orientation-3-ordered-points/
public boolean isConvex(List<List<Integer>> points) {
    List<Integer> back1 = points.get(points.size() - 1);
    List<Integer> back2 = points.get(points.size() - 2);
    boolean seenPositive = false, seenNegative = false;

    for (List<Integer> curr : points) {
        int orientation = orientation(back2, back1, curr);

        if (orientation < 0)
            seenNegative = true;
        else if (orientation > 0)
            seenPositive = true;

        if (seenPositive && seenNegative) return false;

        back2 = back1; back1 = curr;
    }

    return true;
}

private int orientation(List<Integer> point1, List<Integer> point2, List<Integer> point3) {
    int orientation = (point2.get(1) - point1.get(1)) * (point3.get(0) - point2.get(0)) -
                      (point2.get(0) - point1.get(0)) * (point3.get(1) - point2.get(1));
    return orientation == 0 ? 0 : orientation / Math.abs(orientation); // 0, 1 or -1
}


//######################################### python2 #########################################
class Solution(object):
    def isConvex(self, points):
        neg, pos = False,False
        N = len(points)
        def cross_product(a,b,c):
            x_ab,y_ab = a[0]-b[0],a[1]-b[1]
            x_bc,y_bc = b[0]-c[0],b[1]-c[1]
            return (x_ab * y_bc - y_ab * x_bc)
        points +=points[0:2]
        for i in xrange(N):
            if cross_product(points[i],points[i+1],points[i+2]) >0: neg=True
            if cross_product(points[i],points[i+1],points[i+2]) <0: pos=True
        return False if neg and pos else True
