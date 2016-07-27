#include<iostream>
using namespace std;
class QueueEmpty : public RuntimeException {

  public :
    QueueEmpty(const string &err) : RuntimeException(err) {

    }

}
