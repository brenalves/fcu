#include <iostream>
#include "jsbsiminterface.h"

int main()
{
    std::cout << "Starting FCU application..." << std::endl;

    JSBSimInterface* jsbsim = new JSBSimInterface();
    delete jsbsim;

    std::cout << "FCU application finished." << std::endl;

    return 0;
}