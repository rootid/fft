#include <iostream>
#include <fstream>
#include <sstream>
#include <string>   
#include <cstdlib> // for exit()

#include "NodeList.h"

using namespace std;

int main() {
  string st = "Hi";
  //NodeList<string> nodeList(st);
  NodeList<string> nodeList;
  nodeList.addFront(st);
}
