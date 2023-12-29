//ctrl消费类，用于关联ctrlImpl
#ifndef CTRL_CONSUMER_H
#define CTRL_CONSUMER_H

#include "celix/BundleActivator.h"
#include "ICtrl.h"
#include <unistd.h>

class CtrlConsumer {
public:
    CtrlConsumer() = default;

    //创建CtrlConsumer指针示例
    static std::shared_ptr<CtrlConsumer> create()
    {
        std::shared_ptr<CtrlConsumer> instance{new CtrlConsumer{}, [](CtrlConsumer *consumer)
        {
            consumer->stop();
            delete consumer;
        }};
        instance->start();
        std::cout << "create instance address:" << instance << std::endl ;
        return instance;
    }

    void start() {
        calcThread = std::thread{&CtrlConsumer::run, this};
    }

    void stop() {
        bool wasActive = active.exchange(false);
        if (wasActive) {
            calcThread.join();
        }
    }

    void run()
    {
        while(active)
        {
            StartPLC();
            StopPLC();
            sleep(1);
        }
    }

    void setCtrl(std::shared_ptr<ACEPHERE_RUNTIME::ICtrl> pCtrl)
    {
        std::cout << __func__ << "this address:" << this << " pCtrl address:" << pCtrl << std::endl;
        this->pCtrl = std::move(pCtrl);
    }

    void StartPLC()
    {
        std::shared_ptr<ACEPHERE_RUNTIME::ICtrl> localPCtrl = pCtrl;
        std::cout << __func__ << " localPCtrl address:" << localPCtrl << std::endl;
        if (localPCtrl) {
            localPCtrl->StartPLC();
        } else {
            std::cout << "WARNING: StartPLC Calc service not available!" << std::endl;
        }
    }

    void StopPLC()
    {
        std::shared_ptr<ACEPHERE_RUNTIME::ICtrl> localPCtrl = pCtrl;
        std::cout << __func__ << " localPCtrl address:" << localPCtrl << std::endl;
        if (localPCtrl) {
            localPCtrl->StopPLC();
        } else {
            std::cout << "WARNING: Calc service not available!" << std::endl;
        }
    }

private:
    std::shared_ptr<ACEPHERE_RUNTIME::ICtrl> pCtrl;
    std::thread calcThread{};
    /* 线程状态 */
    std::atomic<bool> active{true};
};


#endif