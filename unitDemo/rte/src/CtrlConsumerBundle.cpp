#include "CtrlConsumer.h"
#include <thread>

class CtrlConsumerBundle
{
public:
    explicit CtrlConsumerBundle(const std::shared_ptr<celix::BundleContext>& ctx) :
            consumer{CtrlConsumer::create()}, tracker{createTracker(ctx)}
    {
        std::cout << "create CtrlConsumerBundle bundle, consumer address:" << consumer << std::endl ;
    }


private:
    //把consumer通过setCtrl绑定到CtrlConsumer.h中的std::shared_ptr<ACEPHERE_RUNTIME::ICtrl> pCtrl
    std::shared_ptr<celix::GenericServiceTracker> createTracker(const std::shared_ptr<celix::BundleContext>& ctx)
    {
        return ctx->trackServices<ACEPHERE_RUNTIME::ICtrl>()
                .addSetCallback(std::bind(&CtrlConsumer::setCtrl, consumer, std::placeholders::_1))
                .build();
    }

    const std::shared_ptr<CtrlConsumer> consumer;
    const std::shared_ptr<celix::GenericServiceTracker> tracker;
};

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(CtrlConsumerBundle)