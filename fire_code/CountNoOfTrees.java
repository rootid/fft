
public class CountNoOfTrees {
  public int count(int n) {
    if(n <= 0) return 0;
    if(n == 1) return n;
    int result = 0;
    for(int i=n ;i >=0 ;i--) result += count(i-1) + count(n-i);
    return result;
  }
}
