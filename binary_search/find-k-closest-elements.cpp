//Find K Closest Elements
//Given a sorted array, two integers k and x, find the k closest elements to x in the array. The result should also be sorted in ascending order. If there is a tie, the smaller elements are always preferred.
//Example 1:
//Input: [1,2,3,4,5], k=4, x=3
//Output: [1,2,3,4]
//Example 2:
//Input: [1,2,3,4,5], k=4, x=-1
//Output: [1,2,3,4]
//Note:
//The value k is positive and will always be smaller than the length of the sorted array.
//Length of the given array is positive and will not exceed 104
//Absolute value of elements in the array and x will not exceed 104
//######################################### Deque + binary search ######################################### 
def findClosestElements(self, arr, k, x):
    st,en,i,j,res=0,len(arr)-1,-1,-1,collections.deque()
    while st<=en:
        if x<arr[st]:i=st-1;j=st;break
        if x>arr[en]:i=en;j=en+1;break
        mid=(st+en)>>1
        if arr[mid]==x:k-=1;res.append(arr[mid]);i=mid-1;j=mid+1;break
        if arr[mid]>x:en=mid-1
        else:st=mid+1
    while k>0:
        if i>=0 and (j>=len(arr) or x-arr[i]<=arr[j]-x):res.appendleft(arr[i]);i-=1;k-=1
        elif j<len(arr) and (i<0 or x-arr[i]>arr[j]-x):res.append(arr[j]);j+=1;k-=1
    return list(res)
//######################################### binary search ######################################### 
//It's the first index i so that arr[i] is better than arr[i+k] (with "better" meaning closer to or equally close to x). 
//Then I just return the k elements starting ther
//binary-searching for x and then expanding to the left and to the right like I've seen in other binary search solutions.
//The binary search costs O(log n) (actually also just O(log (n-k)) and the subList call probably only takes O(1). As @sagimann pointed out, subList returns a view, not a separate copy. So it should only take O(1). Can be seen for example in ArrayList's subList and the SubList constructor it calls. I also checked LinkedList, it gets its subList method inherited from AbstractList, where it also takes only O(1). And AbstractList is a basis for most lists.
//Edit: I also implemented it in Go now, to make it O(log n). Edit 2: Ha, didn't have to do that, as the Java version apparently already was O(log n) (I didn't originally know Java returns a view, only added that now). Edit 3: Lol, I had mistakenly written "Python" in the title instead of "Ruby" but apparently nobody noticed (and it's at 1800 views). Fixed that now
public List<Integer> findClosestElements(List<Integer> arr, int k, int x) {
    int lo = 0, hi = arr.size() - k;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (x - arr.get(mid) > arr.get(mid+k) - x)
            lo = mid + 1;
        else
            hi = mid;
    }
    return arr.subList(lo, lo + k);
}
//######################################### binary search ######################################### 
class Solution {
    public List<Integer> findClosestElements(int[] arr, int k, int x) {
    int lo = 0, hi = arr.length - k;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (x - arr[mid] > arr[mid+k] - x)
            lo = mid + 1;
        else hi = mid;
    }
    ArrayList<Integer> result = new ArrayList<>();
    for(int i=lo;i< lo+k;i++) result.add(arr[i]);
    return result;
 }
}
//######################################### binary search ######################################### 
vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    int left = 0;
    int right = arr.size()-k;
    while(left<right){
        int mid = left+(right-left)/2;
        if(x-arr[mid]>arr[mid+k]-x){
            left = mid+1;
        }else{
            right = mid;
        }
    }
    auto S = arr.begin()+left;
    auto E = arr.begin()+left+k;
    
    return vector<int>(S,E);
}
//## In built Binary search ## 
//The idea is to find the first number which is equal to or greater than x in arr. Then, we determine the indices of the start and the end of a subarray in arr, where the subarray is our result. The time complexity is O(logn + k).
//In the following code, arr[index] is the first number which is euqal to or geater than x (if all numbers are less than x, index is arr.size()), and the result is arr[i+1, i+2, ... j]
//######################################### JAVA version: ######################################### 
public List<Integer> findClosestElements(List<Integer> arr, int k, int x) {
    int index = Collections.binarySearch(arr, x);
    if(index < 0) index = -(index + 1);
    int i = index - 1, j = index;                                    
    while(k-- > 0){
        if(i<0 || (j<arr.size() && Math.abs(arr.get(i) - x) > Math.abs(arr.get(j) - x) ))j++;
        else i--;
    }
    return arr.subList(i+1, j);
}
//######################################### C++ version: ######################################### 
vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    int index = std::lower_bound(arr.begin(), arr.end(), x) - arr.begin();
    int i = index - 1, j = index;                                    
    while(k--) (i<0 || (j<arr.size() && abs(arr[i] - x) > abs(arr[j] - x) ))? j++: i--;
    return vector<int>(arr.begin() + i + 1, arr.begin() + j );
}
