#include "../headers/global.hpp"


//First Bad Version
//Search a 2D Matrix （I / II）
//Find Peak Element
//Search Insert Position
int search(int *arr, int n, int key)
{
    int left = 0, right = n-1;
    while(left<=right) {//慎重截止条件，根据指针移动条件来看，这里需要将数组判断到空为止
        int mid = left + ((right - left) >> 1);//防止溢出
        if (arr[mid] == key)//找到了
            return mid; 
        else if(arr[mid] > key) 
            right = mid - 1;//给定值key一定在左边，并且不包括当前这个中间值
        else 
            left = mid + 1;//给定值key一定在右边，并且不包括当前这个中间值
    }
    return -1;
}

int searchFirstEqual(int *arr, int n, int key) {
    int left = 0, right = n-1;
    while(left < right)//根据两指针的意义，如果key存在于数组，left==right相等时已经得到解
    {
        int mid = (left+right)/2;
        if(arr[mid] > key)//一定在mid为止的左边，并且不包含当前位置
            right = mid - 1;
        else if(arr[mid] < key) 
            left = mid + 1;//一定在mid位置的右边，并且不包括当前mid位置
        else
            right=mid;//故意写得和参考博文不一样，下面有证明
    }
    if(arr[left] == key) 
            return left;
    return -1;
}


int searchLastEqual(int *arr, int n, int key)
{
    int left = 0, right = n-1;
    while(left<right-1) {
        int mid = (left+right)/2;
        if(arr[mid] > key) 
            right = mid - 1;//key一定在mid位置的左边，并且不包括当前mid位置
        else if(arr[mid] < key) 
            left = mid + 1; //key一定在mid位置的右边，相等时答案有可能是当前mid位置
        else
            left=mid;//故意写得和参考博客不一样，见下面证明
    }
    if( arr[left]<=key && arr[right] == key) 
        return right;
    if( arr[left] == key && arr[right] > key)
        return left;
    return -1;
}

//lower
int searchFirstEqualOrLarger(int *arr, int n, int key)
{
    int left=0, right=n-1;
    while(left<=right) 
    {
        int mid = (left+right)/2;
        if(arr[mid] >= key) 
            right = mid-1;
        else if (arr[mid] < key) 
            left = mid+1;
    }
    return left;
}


int searchFirstLarger(int *arr, int n, int key)
{
    int left=0, right=n-1;
    while(left<=right)
    {
        int mid = (left+right)/2;
        if(arr[mid] > key) 
            right = mid-1;
        else if (arr[mid] <= key) 
            left = mid+1;
    }
    return left;
}


int searchLastEqualOrSmaller(int *arr, int n, int key)
{
    int left=0, right=n-1;
    while(left<=right) 
    {
        int m = (left+right)/2;
        if(arr[m] > key) 
             right = m-1;
        else if (arr[m] <= key) 
             left = m+1;
    }
    return right;
}

int searchLastSmaller(int *arr, int n, int key)
{
    int left=0, right=n-1;
    while(left<=right) {
        int mid = (left+right)/2;
        if(arr[mid] >= key) 
             right = mid-1;
        else if (arr[mid] < key) 
             left = mid+1;
    }
    return right;
}


int main(void) 
{
    int arr[17] = {1, 
                   2, 2, 5, 5, 5, 
                   5, 5, 5, 5, 5, 
                   5, 5, 6, 6, 7};
    printf("First Equal           : %2d \n", searchFirstEqual(arr, 16, 5));
    printf("Last Equal            : %2d \n", searchLastEqual(arr, 16, 5));
    printf("First Equal or Larger : %2d \n", searchFirstEqualOrLarger(arr, 16, 5));
    printf("First Larger          : %2d \n", searchFirstLarger(arr, 16, 5));
    printf("Last Equal or Smaller : %2d \n", searchLastEqualOrSmaller(arr, 16, 5));
    printf("Last Smaller          : %2d \n", searchLastSmaller(arr, 16, 5));
    system("pause");
    return 0;
}
