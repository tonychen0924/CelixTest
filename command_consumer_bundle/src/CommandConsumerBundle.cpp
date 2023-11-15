#include "celix/BundleActivator.h"
#include "CommandImpl.h"
#include "CommandConsumer.h"

class CommandConsumerBundle
{
public:
    std::shared_ptr<CommandConsumer> consumer;

    explicit CommandConsumerBundle(std::shared_ptr<celix::BundleContext> ctx) :
        consumer{CommandConsumer::create()}, tracker{createTracker(ctx)}
    {
        std::cout << "CommandConsumerBundle service bundle start" << std::endl;

        setPCommandConsumer(static_cast<void*>(consumer.get()));
        consumer->commandInstall("test.zip");
    }

    ~CommandConsumerBundle() noexcept {
        std::cout << "CommandConsumerBundle service bundle end" << std::endl;
    }

private:

    std::shared_ptr<celix::GenericServiceTracker> createTracker(const std::shared_ptr<celix::BundleContext>& ctx)
    {
        return ctx->trackServices<ACEPHERE_RUNTIME::IPou>()
                .addSetCallback(std::bind(&CommandConsumer::setPou, consumer, std::placeholders::_1))
                .build();
    }

    const std::shared_ptr<celix::GenericServiceTracker> tracker;
};

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(CommandConsumerBundle)