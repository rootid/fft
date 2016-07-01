#include<iostream>
using namespace std;
#include "Stack.h"

int main() {
  Stack<int> A;                      // A = [], size = 0
  A.push(7);                              // A = [7*], size = 1
  A.push(13);                             // A = [7, 13*], size = 2
  cout << A.top() << endl; A.pop();       // A = [7*], outputs: 13
  A.push(9);                              // A = [7, 9*], size = 2
  cout << A.top() << endl;                // A = [7, 9*], outputs: 9
  cout << A.top() << endl; A.pop();       // A = [7*], outputs: 9
  Stack<string> B(10);               // B = [], size = 0
  B.push("Bob");                          // B = [Bob*], size = 1
  B.push("Alice");                        // B = [Bob, Alice*], size = 2
  cout << B.top() << endl; B.pop();       // B = [Bob*], outputs: Alice
  B.push("Eve");                          // B = [Bob, Eve*], size = 2
}
