//H-Index II
//Follow up for H-Index: What if the citations array is sorted in ascending
//order? Could you optimize your algorithm?
//Hint:
//Expected runtime complexity is in O(log n) and the input is sorted.
int hIndex(vector<int>& citations) {
  //  citations[index] >= length(citations) - index
    int len = citations.size();
    int start = 0;
    int mid;
    int end = len;
    int step;
    while (end > 0) {
        step = end / 2;
        mid = start + step;
        if (citations[mid] < len - mid) {
            start = mid + 1;
            end -= (step + 1);
        }
        else {
            end = step;
        }
    }
    return len - start;
}
