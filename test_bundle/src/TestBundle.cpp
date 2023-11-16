#include <iostream>
#include "celix/BundleActivator.h"

class TestBundle {
public:
    explicit TestBundle(const std::shared_ptr<celix::BundleContext>& ctx) {
        std::cout << "TestBundle start with id " << ctx->getBundleId() << std::endl;
    }

    ~TestBundle() noexcept {
        std::cout << "TestBundle end" << std::endl;
    }
};

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(TestBundle)