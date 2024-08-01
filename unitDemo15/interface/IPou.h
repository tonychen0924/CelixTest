#ifndef I_POU_H
#define I_POU_H

#include <iostream>

namespace ACEPHERE_RUNTIME
{

class IPou
{
public:
    virtual int calc(int input) = 0;
};

}

#endif