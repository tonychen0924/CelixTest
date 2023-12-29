//用于ctrl bundle和rte bundle交互数据的接口

#ifndef I_CTRL_H
#define I_CTRL_H

#include <iostream>

namespace ACEPHERE_RUNTIME
{

class ICtrl
{
public:
    virtual ~ICtrl() = default;
    virtual int calc(int input) = 0;
    virtual void StartPLC() = 0;
    virtual void StopPLC() = 0;
};

}  // namespace ACEPHERE_RUNTIME

#endif