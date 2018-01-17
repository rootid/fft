//Line Reflection 
//Given n points on a 2D plane, find if there is such a line parallel to y-axis that reflect the given points.
//Example 1:
//Given points = [[1,1],[-1,1]], return true.
//Example 2:
//Given points = [[1,1],[-1,-1]], return false.
//Follow up:
//Could you do better than O(n^2)?
//
//

//The key point is if there is one line to reflects all the points, it must in the middle of maxX and minX.
//Say its at (minX + maxX)/2 = m
//you can get the reflecting point for any given point x on the given plane
//to be at 2m - x = minX + maxX - x 
//Finding maxX and minX, replacing every point to its reflected point, and comparing whether the two sets are the same, are all linear operations.



//Reflect the points by replacing every x with minX+maxX-x and then check whether you get the same points. 
//Why minX+maxX-x? I actually thought of it as minX+(maxX-x), i.e., first the subtraction (maxX-x). That's how far x is away from the max, so instead go that distance from the min.
//################################################### duplicates + O(n) ################################################### 
def isReflected(self, points):
    if not points: return True
    X = min(points)[0] + max(points)[0]
    return {(x, y) for x, y in points} == {(X - x, y) for x, y in points}

//################################################### duplicates ################################################### 
def isReflected(self, points):
    points.sort()
    return points == sorted([points[0][0] + points[-1][0] - x, y]
                            for x, y in points)

//################################################### No duplicates ################################################### 
def is_reflected(points)
  points.sort!.uniq == points.map { |x, y| [points[0][0] + points[-1][0] - x, y] }.sort.uniq
end

def isReflected(self, points):
    points = sorted(set(map(tuple, points)))
    return points == sorted((points[0][0] + points[-1][0] - x, y)
                            for x, y in points)
