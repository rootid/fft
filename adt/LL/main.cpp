#include <iostream>
#include <fstream>
#include <sstream>
#include <string>   
#include <cstdlib> // for exit()

#include "Node.h"
#include "NodeList.h"

using namespace std;

int main() {
  int st = 2;
  NodeList<int> nodeList(st);
  //NodeList<int> nodeList;
  //NodeList nodeList;
  nodeList.addFront(st);
}
