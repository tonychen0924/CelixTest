//Ctrl bundle服务提供者和使用者

#include "celix/BundleActivator.h"
#include "CtrlImpl.h"
extern "C"
{
    #include "plc_main.h"
}

class PlcCtrlBundle
{
public:

    //构造函数，初始化成员变量registration
    explicit PlcCtrlBundle(std::shared_ptr<celix::BundleContext> ctx) :
        registration{createPlcService(ctx)}
    {
        std::cout << "启动plc service bundle" << std::endl;
    }

private:
    static std::shared_ptr<celix::ServiceRegistration> createPlcService(std::shared_ptr<celix::BundleContext>& ctx)
    {
        //绑定，赋值
        int seed = 42;
        std::cout << "注册plc service bundle" << std::endl;
        //注册服务
        return ctx->registerService<ACEPHERE_RUNTIME::ICtrl>(std::make_shared<ACEPHERE_RUNTIME::CtrlImpl>(seed))
                .addProperty("seed", seed)
                .build();
    }

    //作为服务端
    const std::shared_ptr<celix::ServiceRegistration> registration;
};

CELIX_GEN_CXX_BUNDLE_ACTIVATOR(PlcCtrlBundle)