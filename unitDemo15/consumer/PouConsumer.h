#ifndef POU_CONSUMER_H
#define POU_CONSUMER_H

#include "celix/BundleActivator.h"
#include "IPou.h"
#include <unistd.h>

class PouConsumer
{
private:
    std::shared_ptr<ACEPHERE_RUNTIME::IPou> pPou;
public:
    PouConsumer() = default;

    //创建PouConsumer指针示例
    static std::shared_ptr<PouConsumer> create()
    {
        PouConsumer* ppc = nullptr;
        std::shared_ptr<PouConsumer> instance
        {
            ppc = new PouConsumer{},
            [](PouConsumer *consumer)
            {
                delete consumer;
            }
        };
        std::cout << "ppc address:" << ppc << std::endl;
        return instance;
    }

    void setPou(std::shared_ptr<ACEPHERE_RUNTIME::IPou> pPou)
    {
        this->pPou = std::move(pPou);
    }

    void calc(int input)
    {
        std::shared_ptr<ACEPHERE_RUNTIME::IPou> localPPou = pPou;
        if (localPPou) {
            int res = localPPou->calc(input);
            std::cout << "address:" << this << ", calc:" << res << std::endl;
        } else {
            std::cout << "WARNING: Calc service not available!" << std::endl;
        }
    }
};


#endif