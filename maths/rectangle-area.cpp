//Rectangle Area
//Find the total area covered by two rectilinear rectangles in a 2D plane.
//Each rectangle is defined by its bottom left corner and top right corner as
//shown in the figure.
//Assume that the total area is never beyond the maximum possible value of int.

//x,y,x1,y1,x2,y2,x3,y3


//################################################# Bad  #################################################
int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {

  int area1 = abs( (D-B) * (C-A));
  int area2 = abs((H-F) * (G-E));
  if (A >= G || C <= E || D <= F || B >= H) {
        return area1 + area2 ;
  }
  int overlap_area = (min(C, G) - max(A, E)) * (min(D, H) - max(B, F));
  return area1 + area2 - overlap_area;
}

//################################################# Good #################################################
int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
     return (C-A)*(D-B)+(G-E)*(H-F)-overLap(A, C, E, G) * overLap(B, D, F, H);
}

int overLap(int s1, int t1, int s2, int t2) {
     if (s1 >= t2 || s2 >= t1) return 0;
     return min(t1, t2) - max(s1, s2);
}
