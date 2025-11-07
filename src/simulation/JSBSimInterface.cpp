#include "jsbsiminterface.h"

JSBSimInterface::JSBSimInterface()
{
    std::cout << "JSBSimInterface initialized, version: " << _fdm.GetVersion() << std::endl;
}

JSBSimInterface::~JSBSimInterface()
{
    std::cout << "JSBSimInterface destroyed." << std::endl;
}