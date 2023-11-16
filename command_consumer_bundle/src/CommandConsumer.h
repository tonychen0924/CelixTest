//pou消费类，用于关联PouImpl
#ifndef POU_CONSUMER_H
#define POU_CONSUMER_H

#include "celix/BundleActivator.h"
#include "ICommand.h"
#include <unistd.h>

class CommandConsumer {
public:
    CommandConsumer() = default;

    // CommandConsumer(std::shared_ptr<celix::BundleContext> ctx)
    // {
    //     this->ctx = ctx;
    //     std::cout << __func__ << " ctx address:" << ctx << std::endl;
    // }

    static std::shared_ptr<CommandConsumer> create()
    {
        std::shared_ptr<CommandConsumer> instance{new CommandConsumer{}, [](CommandConsumer *consumer)
        {
           delete consumer;
        }};
        return instance;
    }

    static std::shared_ptr<CommandConsumer> create(std::shared_ptr<celix::BundleContext> ctx)
    {
        std::shared_ptr<CommandConsumer> instance{new CommandConsumer{}, [](CommandConsumer *consumer)
        {
           delete consumer;
        }};
        instance->ctx = ctx;
        std::cout << __func__ << " ctx address:" << ctx << std::endl;
        return instance;
    }

    void setPCommandConsumer(std::shared_ptr<ACEPHERE_RUNTIME::ICommand> pCommandConsumer)
    {
        this->pCommandConsumer = std::move(pCommandConsumer);
        std::cout << __func__ << " ctx address:" << ctx << std::endl;
    }

    void commandInstall(std::string bundleName)
    {
        std::shared_ptr<ACEPHERE_RUNTIME::ICommand> localCmd = pCommandConsumer;
        if (localCmd) {
            localCmd->commandInstall(ctx, bundleName);
        } else {
            std::cout << "WARNING: commandInstall service not available!" << std::endl;
        }
    }

    void commandUninstall(std::string bundleName)
    {
        std::shared_ptr<ACEPHERE_RUNTIME::ICommand> localCmd = pCommandConsumer;
        if (localCmd) {
            localCmd->commandUninstall(ctx, bundleName);
        } else {
            std::cout << "WARNING: commandInstall service not available!" << std::endl;
        }
    }

    void commandStart(int bundeId)
    {
        std::shared_ptr<ACEPHERE_RUNTIME::ICommand> localCmd = pCommandConsumer;
        if (localCmd) {
            localCmd->commandStart(ctx, bundeId);
        } else {
            std::cout << "WARNING: commandStart service not available!" << std::endl;
        }
    }

    void commandStop(int bundeId)
    {
        std::shared_ptr<ACEPHERE_RUNTIME::ICommand> localCmd = pCommandConsumer;
        if (localCmd) {
            localCmd->commandStop(ctx, bundeId);
        } else {
            std::cout << "WARNING: commandStop service not available!" << std::endl;
        }
    }

    std::string commandLb()
    {
        std::string res = "";
        std::shared_ptr<ACEPHERE_RUNTIME::ICommand> localCmd = pCommandConsumer;
        if (localCmd) {
            res = localCmd->commandLb(ctx);
        } else {
            std::cout << "WARNING: commandLb service not available!" << std::endl;
        }
        return res;
    }

private:
    std::shared_ptr<ACEPHERE_RUNTIME::ICommand> pCommandConsumer;
    std::shared_ptr<celix::BundleContext> ctx;
};


#endif