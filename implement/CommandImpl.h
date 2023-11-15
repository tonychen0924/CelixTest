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

    void commandInstall(std::string bundleName)
    {
        // TODO
        std::cout << "install " << bundleName << std::endl;
    }

    void commandUninstall(std::string bundleName)
    {
        // TODO
        std::cout << "uninstall " << bundleName << std::endl;
    }

    void commandStart(int bundeId)
    {
        // TODO
        std::cout << "start " << bundeId << std::endl;
    }

    void commandStop(int bundeId)
    {
        // TODO
        std::cout << "stop " << bundeId << std::endl;
    }

    std::string commandLb()
    {
        std::string res = "";
        // TODO
        std::cout << "lb return terminal content" << std::endl;
        return res;
    }

private:
    const int seed;
};

}