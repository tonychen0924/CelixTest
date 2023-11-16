#include "ICommand.h"

namespace ACEPHERE_RUNTIME
{

class CommandImpl : public ACEPHERE_RUNTIME::ICommand
{
public:
    explicit CommandImpl(int _seed) : seed{_seed}
    {

    }

    ~CommandImpl() override = default;

    void commandInstall(std::shared_ptr<celix::BundleContext> ctx, std::string bundleName)
    {
        // TODO
        std::cout << "install " << bundleName << std::endl;
    }

    void commandUninstall(std::shared_ptr<celix::BundleContext> ctx, std::string bundleName)
    {
        // TODO
        std::cout << "uninstall " << bundleName << std::endl;
    }

    void commandStart(std::shared_ptr<celix::BundleContext> ctx, int bundeId)
    {
        // TODO
        std::cout << "start " << bundeId << std::endl;
    }

    void commandStop(std::shared_ptr<celix::BundleContext> ctx, int bundeId)
    {
        // TODO
        std::cout << "stop " << bundeId << std::endl;
    }

    std::string commandLb(std::shared_ptr<celix::BundleContext> ctx)
    {
        std::string res = "";
        // TODO
        ctx->listBundleIds();
        std::cout << "lb return terminal content" << std::endl;
        return res;
    }

private:
    const int seed;
};

}