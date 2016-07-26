#include "window.h"


int Window::sharedPal;
int Window::numInstances = 0;

Window::Window() {
  numInstances+= 1;
}

void Window::drawWindow() {

}

int Window::getRemainingInstances() {
    return numInstances;
}

int main() {

  Window w;
  int noOfInstances = w.getRemainingInstances();
  std::cout << " # of instances = " << noOfInstances  << std::endl;

  Window w1;
  noOfInstances = w1.getRemainingInstances();
  std::cout << " # of instances = " << noOfInstances  << std::endl;

}

