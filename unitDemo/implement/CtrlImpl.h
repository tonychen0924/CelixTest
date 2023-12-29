//ctrl的服务端接口实现，调用plc_main.h中的接口（往下调用）

#include "ICtrl.h"

extern "C"
{
    #include "plc_main.h"
}

namespace ACEPHERE_RUNTIME
{

// 接口的实现类
class CtrlImpl : public ACEPHERE_RUNTIME::ICtrl
{
public:
    explicit CtrlImpl(int _seed) : seed{_seed}
    {

    }

    ~CtrlImpl() override = default;

    int calc(int input) override
    {
        return seed * input;
    }

    void StartPLC() override
    {
        startPLC(0, 0);
    }

    void StopPLC() override
    {
        stopPLC();
    }

private:
    const int seed;
};

}