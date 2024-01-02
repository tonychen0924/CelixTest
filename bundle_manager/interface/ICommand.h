#ifndef I_COMMAND_H
#define I_COMMAND_H

#include <iostream>
#include "celix/BundleActivator.h"

namespace ACEPHERE_RUNTIME
{

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual void commandInstall(std::shared_ptr<celix::BundleContext> ctx, std::string bundleName) = 0;
    virtual void commandUninstall(std::shared_ptr<celix::BundleContext> ctx, std::string bundleName) = 0;
    virtual void commandStart(std::shared_ptr<celix::BundleContext> ctx, int bundeId) = 0;
    virtual void commandStop(std::shared_ptr<celix::BundleContext> ctx, int bundeId) = 0;
    virtual std::string commandLb(std::shared_ptr<celix::BundleContext> ctx) = 0;
};

}

#endif //I_CONFIG_POU_H