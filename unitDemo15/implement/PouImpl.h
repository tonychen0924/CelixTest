#include "IPou.h"

namespace ACEPHERE_RUNTIME
{

// 接口的实现类
class PouImpl : public ACEPHERE_RUNTIME::IPou
{
private:
    int count;
public:
    int calc(int input) override
    {
        this->count += input;
        return this->count;
    }
};

}