#pragma once

#include <iostream>

#include <FGFDMExec.h>

class JSBSimInterface
{
public:
    JSBSimInterface();
    ~JSBSimInterface();

private:
    JSBSim::FGFDMExec _fdm;
};