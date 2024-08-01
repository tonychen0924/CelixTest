#include "PouBundle.hpp"

std::shared_ptr<celix::ServiceRegistration> PouBundle::createPlcService(std::shared_ptr<celix::BundleContext>& ctx)
{
    std::cout << "PouBundle register" << std::endl;
    //注册服务
    return ctx->registerService<ACEPHERE_RUNTIME::IPou>(std::make_shared<ACEPHERE_RUNTIME::PouImpl>())
            .build();
}

//构造函数，初始化成员变量registration
PouBundle::PouBundle(std::shared_ptr<celix::BundleContext> ctx) :
    registration{createPlcService(ctx)}
{
    std::cout << "PouBundle create" << std::endl;
}
