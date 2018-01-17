import java.util.*; //Data structures
import java.lang.*; //Exceptions

// A Range Module is a module that tracks ranges of numbers. Range modules are
// used extensively when designing scalable online game maps with millions of
// players. Your task is to write a method - mergeIntervals that takes in an
// ArrayList of integer Interval s (aka ranges), and returns an ArrayList of
// sorted Interval s where all overlapping intervals have been merged. The
// Interval class is available by clicking Use Me.
// Note:
// a) [1,3] represents an interval that includes 1, 2 and 3.
// b) Intervals should be sorted based on the value of start
// Examples:
// Input: [ [1,3], [2,5] ], Output: [ [1,5] ]
// Input: [ [3,5], [1,2] ], Output: [ [1,2], [3,5] ]

public class MergingRanges {
  public static ArrayList<Interval> mergeIntervals(
      ArrayList<Interval> intervalsList) {
    if (intervalsList == null)
      throw new IllegalArgumentException("Please enter valid interval List");
    ArrayList<Interval> resultList = new ArrayList<>();

    Collections.sort(intervalsList,
                     (Interval a, Interval b) -> a.start - b.start);
    // Collections.sort(intervalsList, Comparator.comparingInt(e->e.start));
    for (int i = 0; i < intervalsList.size(); i++) {
      if (resultList.size() == 0 ||
          resultList.get(resultList.size() - 1).end -
                  intervalsList.get(i).start <
              0) {
        resultList.add(
            new Interval(intervalsList.get(i).start, intervalsList.get(i).end));
      } else {
        resultList.get(resultList.size() - 1).end =
            Math.max(intervalsList.get(i).end,
                     resultList.get(resultList.size() - 1).end);
      }
    }
    return resultList;
  }
}
