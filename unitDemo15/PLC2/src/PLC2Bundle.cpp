#include "PLC2Bundle.hpp"

std::shared_ptr<celix::GenericServiceTracker> PLC2Bundle::createTracker(const std::shared_ptr<celix::BundleContext>& ctx)
{
    return ctx->trackServices<ACEPHERE_RUNTIME::IPou>()
            .addSetCallback(std::bind(&PouConsumer::setPou, consumer, std::placeholders::_1))
            .build();
}

PLC2Bundle::PLC2Bundle(const std::shared_ptr<celix::BundleContext>& ctx) :
        consumer{PouConsumer::create()}, tracker{createTracker(ctx)}
{
    // 等待Pou bundle启动服务
    usleep(100);
    for (size_t i = 1; i < 10; i++)
    {
        // sleep(1);
        consumer->calc(i);
        usleep(10);
    }
}






