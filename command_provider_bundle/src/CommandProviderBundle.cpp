#include "celix/BundleActivator.h"
#include "CommandImpl.h"

class CommandProviderBundle
{
public:
    explicit CommandProviderBundle(std::shared_ptr<celix::BundleContext> ctx) :
        registration{createService(ctx)}
    {
        std::cout << "CommandProviderBundle create" << std::endl;
    }

private:
    static std::shared_ptr<celix::ServiceRegistration> createService(std::shared_ptr<celix::BundleContext>& ctx)
    {
        int seed = 42;
        std::cout << "CommandProviderBundle register" << std::endl;
        return ctx->registerService<ACEPHERE_RUNTIME::IPou>(std::make_shared<ACEPHERE_RUNTIME::CommandImpl>(seed))
                .addProperty("seed", seed)
                .build();
    }

    const std::shared_ptr<celix::ServiceRegistration> registration;
};

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(CommandProviderBundle)