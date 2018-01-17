#ifndef WINDOW_H
#define WINDOW_H

#include<iostream>

class Window
{
public:
    /* ... constructors, destructors, etc. ...*/
    void drawWindow();
    static int getRemainingInstances();
    Window();
private:
    /* ... other data members ... */
    static int sharedPal;
    static int numInstances;
};

#endif /* WINDOW_H */
