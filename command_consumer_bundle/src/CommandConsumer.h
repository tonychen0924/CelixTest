//pou消费类，用于关联PouImpl
#ifndef POU_CONSUMER_H
#define POU_CONSUMER_H

#include "celix/BundleActivator.h"
#include "ICommand.h"
#include <unistd.h>

class CommandConsumer {
public:
    CommandConsumer() = default;

    static std::shared_ptr<CommandConsumer> create()
    {
        std::shared_ptr<CommandConsumer> instance{new CommandConsumer{}, [](CommandConsumer *consumer)
        {
           delete consumer;
        }};
        return instance;
    }

    void setPCommandConsumer(std::shared_ptr<ACEPHERE_RUNTIME::ICommand> pCommandConsumer)
    {
        this->pCommandConsumer = std::move(pCommandConsumer);
    }

    void commandInstall(std::string bundleName)
    {
        std::shared_ptr<ACEPHERE_RUNTIME::ICommand> localCmd = pCommandConsumer;
        if (localCmd) {
            localCmd->commandInstall(bundleName);
        } else {
            std::cout << "WARNING: commandInstall service not available!" << std::endl;
        }
    }

    void commandUninstall(std::string bundleName)
    {
        std::shared_ptr<ACEPHERE_RUNTIME::ICommand> localCmd = pCommandConsumer;
        if (localCmd) {
            localCmd->commandUninstall(bundleName);
        } else {
            std::cout << "WARNING: commandInstall service not available!" << std::endl;
        }
    }

    void commandStart(int bundeId)
    {
        std::shared_ptr<ACEPHERE_RUNTIME::ICommand> localCmd = pCommandConsumer;
        if (localCmd) {
            localCmd->commandStart(bundeId);
        } else {
            std::cout << "WARNING: commandStart service not available!" << std::endl;
        }
    }

    void commandStop(int bundeId)
    {
        std::shared_ptr<ACEPHERE_RUNTIME::ICommand> localCmd = pCommandConsumer;
        if (localCmd) {
            localCmd->commandStop(bundeId);
        } else {
            std::cout << "WARNING: commandStop service not available!" << std::endl;
        }
    }

    std::string commandLb()
    {
        std::shared_ptr<ACEPHERE_RUNTIME::ICommand> localCmd = pCommandConsumer;
        if (localCmd) {
            localCmd->commandLb();
        } else {
            std::cout << "WARNING: commandLb service not available!" << std::endl;
        }
    }

private:
    std::shared_ptr<ACEPHERE_RUNTIME::ICommand> pCommandConsumer;
};


#endif