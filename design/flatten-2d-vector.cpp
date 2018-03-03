//Flatten 2D Vector
//Implement an iterator to flatten a 2d vector.
//For example,
//Given 2d vector =
//[
//  [1,2],
//  [3],
//  [4,5,6]
//]
//By calling next repeatedly until hasNext returns false, the order of elements
//returned by next should be: [1,2,3,4,5,6].
//Hint:
//How many variables do you need to keep track?
//Two variables is all you need. Try with x and y.
//Beware of empty rows. It could be the first few rows.
//To write correct code, think about the invariant to maintain. What is it?
//The invariant is x and y must always point to a valid point in the 2d vector.
//Should you maintain your invariant ahead of time or right when you need it?
//Not sure? Think about how you would implement hasNext(). Which is more
//complex?
//Common logic in two different places should be refactored into a common
//method.
//Follow up:
//As an added challenge, try to code it using only iterators in C++ or
//iterators in Java.
class Vector2D {
 private :
      vector<vector<int>>::iterator start, end;
      int idx = 0;
public:
    Vector2D(vector<vector<int>>& vec2d) {
        start = vec2d.begin();
        end = vec2d.end();
    }
    int next() {
           //(*start) : returns 1-d vector
           hasNext();
           //cout << (*start)[idx] << endl;
           return (*start)[idx++];
    }
    bool hasNext() {
            //[[1],[]] : use of whil to check the empty vectors
          while( start != end  && (*start).size() == idx) {
                //reset the idx
                idx = 0;
                start++;
          }
          return start != end;
    }
};
/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */
