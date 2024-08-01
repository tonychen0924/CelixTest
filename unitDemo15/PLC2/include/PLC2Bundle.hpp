#include "PouConsumer.h"

class PLC2Bundle
{
private:
    const std::shared_ptr<PouConsumer> consumer;
    const std::shared_ptr<celix::GenericServiceTracker> tracker;

    std::shared_ptr<celix::GenericServiceTracker> createTracker(const std::shared_ptr<celix::BundleContext>& ctx);

public:
    explicit PLC2Bundle(const std::shared_ptr<celix::BundleContext>& ctx);

};

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(PLC2Bundle)