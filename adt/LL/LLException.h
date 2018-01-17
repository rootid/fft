#ifndef LLEXCEPTION_H
#define LLEXCEPTION_H

#include<string>
using namespace std;

template <string EXCEPTION_NAME>
class LLException
{
private:
  

public:
  LLException() {

  }

  virtual string get_name(void) const
  {
      return EXCEPTION_NAME;
  }
  virtual ~LLException();
};

#endif /* LLEXCEPTION_H */
