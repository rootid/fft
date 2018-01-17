// Mobile Game Range Module - Inserting Ranges
// A Range Module is a module that tracks ranges of numbers. Range modules are
// used extensively when designing scalable online game maps with millions of
// players. Your task is to write a method - insertRange that takes in an
// ArrayList of sorted, non-overlapping integer Interval s (aka ranges) and a
// new Interval - insert, and returns an ArrayList of sorted Interval s where
// insert has been added to the ArrayList in the correct spot and the required
// overlapping ranges have been merged. The Interval class is available by
// clicking Use Me. Target a time complexity of O(n).
// Note:
// a) [1,3] represents an interval that includes 1, 2 and 3.
// b) Intervals should be sorted based on the value of start
// c) The words Range and Interval are used interchangeably
// Examples:
// Inputs: [ [1,3], [7,10] ] & [2,6], Output: [ [1,6], [7,10] ]

public class InsertRange {
  //##################### In-Place #####################
  public static ArrayList<Interval> insertRange(ArrayList<Interval> intervals,
                                                Interval newInterval) {
    int i = 0;
    while (i < intervals.size() && intervals.get(i).end < newInterval.start)
      i++;
    while (i < intervals.size() && intervals.get(i).start <= newInterval.end) {
      newInterval =
          new Interval(Math.min(intervals.get(i).start, newInterval.start),
                       Math.max(intervals.get(i).end, newInterval.end));
      intervals.remove(i);
    }
    intervals.add(i, newInterval);
    return intervals;
  }
}
