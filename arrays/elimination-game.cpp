//Elimination Game
//There is a list of sorted integers from 1 to n. Starting from left to right, remove the first number and every other number afterward until you reach the end of the list.
//Repeat the previous step again, but this time from right to left, remove the right most number and every other number from the remaining numbers.
//We keep repeating the steps again, alternating left to right and right to left, until a single number remains.
//Find the last number that remains starting with a list of length n.
//Example:
//Input:
//n = 9,
//1 2 3 4 5 6 7 8 9
//2 4 6 8
//2 6
//6
//Output:
//############################ log(N) ###################################
int lastRemaining(int n) {
 bool fwd_pass = true;
 int remaining = n;
 int step = 1;
 int head = 1;
  while (remaining > 1) {
    if (fwd_pass || remaining % 2 == 1) { 
          head = head + step;
        //Our value is eliminated on a forward pass or if there are an odd number of elements.
      }
      remaining = remaining / 2;
      step = step * 2;
      fwd_pass = !fwd_pass;
  }
  return head;
}
//############################ log(N) + recursive ###################################
private :
int helper(bool left_to_right, int n) {
     if (n == 1) return 1;
     if (left_to_right) {
         return helper(false, n / 2) * 2;
     } else {
         if (n % 2) {
             return helper(true, n / 2) * 2;
         } else {
             return helper(true, n / 2) * 2 - 1;
         }
     }
}
public:
    int lastRemaining(int n) {
        return helper(true, n);
    }

//############################ log(N) + recursive ###################################
//left to right, keep odd.
//right to left when total number is odd keep even, else keep odd
int lastRemaining(int n,bool go=true) {
    return n==1?1:2*lastRemaining(n/2,!go)+!go*(n%2-1);
    
}
//When do we eliminate our value?
//Our value is eliminated on a forward pass or if there are an odd number of elements.
//How do we find the next value when our's is eliminated?
//This is probably the trickiest part of the solution. You will probably need to draw this out to see it but turns out if you start with 1 and double each iteration you'll be calculating the number of steps you'll need to take to reach the next available number.
//How do we know when we only have 1 value remaining?
//Each iteration reduces the elements by half and in the case of odd that extra one is removed, so this becomes a simple size/2 integer division
//1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 - > 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
//1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 - > 2 4 6 8 10 12 14 16 18 20 22 24
//2 4 6 8 10 12 14 16 18 20 22 24 - > 2 6 10 14 18 22
//2 6 10 14 18 22 - > 6 14 22
//6 14 22 - > 14
