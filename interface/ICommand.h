#ifndef I_COMMAND_H
#define I_COMMAND_H

#include <iostream>

namespace ACEPHERE_RUNTIME
{

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual void commandInstall(std::string bundleName) = 0;
    virtual void commandUninstall(std::string bundleName) = 0;
    virtual void commandStart(int bundeId) = 0;
    virtual void commandStop(int bundeId) = 0;
    virtual std::string commandLb() = 0;
};

}

#endif //I_CONFIG_POU_H