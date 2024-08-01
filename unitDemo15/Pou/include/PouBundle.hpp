#include "celix/BundleActivator.h"
#include "PouImpl.h"

class PouBundle
{
private:
    const std::shared_ptr<celix::ServiceRegistration> registration;

    static std::shared_ptr<celix::ServiceRegistration> createPlcService(std::shared_ptr<celix::BundleContext>& ctx);

public:
    explicit PouBundle(std::shared_ptr<celix::BundleContext> ctx);
};

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(PouBundle)