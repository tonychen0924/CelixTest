#include <iostream>
#include "celix/BundleActivator.h"

class LiterteDemoBundle {
public:
    explicit LiterteDemoBundle(const std::shared_ptr<celix::BundleContext>& ctx) {
        std::cout << "Hello world from bundle with id " << ctx->getBundleId() << std::endl;
    }

    ~LiterteDemoBundle() noexcept {
        std::cout << "Goodbye world" << std::endl;
    }
};

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(LiterteDemoBundle)