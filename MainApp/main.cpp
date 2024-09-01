#include <iostream>
#include "MPointer.h"

int main()
{
    MPointer<int> myPtr = MPointer<int>::New();
    *myPtr = 42;
    std::cout << "Value: " << *myPtr << std::endl;
    return 0;
}
