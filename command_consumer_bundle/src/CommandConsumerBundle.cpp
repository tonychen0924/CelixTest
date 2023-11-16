#include "celix/BundleActivator.h"
#include "CommandImpl.h"
#include "CommandConsumer.h"

class CommandConsumerBundle
{
public:
    std::shared_ptr<CommandConsumer> consumer;

    explicit CommandConsumerBundle(std::shared_ptr<celix::BundleContext> ctx) :
        consumer{CommandConsumer::create(ctx)}, tracker{createTracker(ctx)}
    {
        std::cout << "CommandConsumerBundle service bundle start" << std::endl;

        // consumer->commandInstall("test.zip");
        // consumer->commandUninstall("test.zip");
        // consumer->commandStart(3);
        // consumer->commandStop(3);
        // consumer->commandLb();

        // consumer->commandInstall("/home/tony/git_pro/CelixTest/build/deploy/MyContainer/bundle/TestBundle.zip");
        consumer->commandInstall("/home/tony/git_pro/CelixTest/build/test_bundle/TestBundle.zip");
    }

    ~CommandConsumerBundle() noexcept {
        std::cout << "CommandConsumerBundle service bundle end" << std::endl;
    }

private:

    std::shared_ptr<celix::GenericServiceTracker> createTracker(const std::shared_ptr<celix::BundleContext>& ctx)
    {
        return ctx->trackServices<ACEPHERE_RUNTIME::ICommand>()
                .addSetCallback(std::bind(&CommandConsumer::setPCommandConsumer, consumer, std::placeholders::_1))
                .build();
    }

    const std::shared_ptr<celix::GenericServiceTracker> tracker;
};

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(CommandConsumerBundle)