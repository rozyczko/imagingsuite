//<LICENSE>
#include "stdafx.h"
#include "../include/ReconFactory.h"
#include "../include/PreprocModuleBase.h"
#include "../include/ReconConfig.h"
#include "../include/ReconException.h"
#include "ModuleException.h"
#include "stdafx.h"
#include <iostream>
#include <memory>

ReconFactory::ReconFactory(void)
    : logger("ReconFactory")
{
}

ReconFactory::~ReconFactory(void)
{
}

ReconEngine* ReconFactory::BuildEngine(ReconConfig& config, kipl::interactors::InteractionBase* interactor)
{
    ReconEngine* engine = new ReconEngine("ReconEngine", interactor);

    try {
        engine->SetConfig(config);
    } catch (ReconException& e) {
        logger(logger.LogError, "Failed to get image size while building recon engine.");
        throw ReconException(e.what());
    } catch (kipl::base::KiplException& e) {
        logger(logger.LogError, "Failed to get image size while building recon engine.");
        throw kipl::base::KiplException(e.what());
    } catch (exception& e) {
        logger(logger.LogError, "Failed to get image size while building recon engine.");
        throw std::runtime_error(e.what());
    }

    std::list<ModuleConfig>::iterator it;

    // Setting up the preprocessing modules
    for (auto const & moduleItem : config.modules)
    {
        if (moduleItem.m_bActive == true)
        {
            ModuleItem* module = nullptr;
            try
            {
                std::cout << "Trying to make new module for " << moduleItem.m_sModule << '\n';
                module = new ModuleItem("muhrec",
                                        moduleItem.m_sSharedObject,
                                        moduleItem.m_sModule, interactor);

                // Setting up the preprocessing modules
                for (auto &module : config.modules)
                {
                    if (module.m_bActive==true)
                    {
                        ModuleItem *moduleItem=nullptr;
                        try
                        {
                            moduleItem=new ModuleItem("muhrec",module.m_sSharedObject,module.m_sModule,interactor);

                            moduleItem->GetModule()->Configure(config,module.parameters);
                            engine->AddPreProcModule(moduleItem);
                        }
                        catch (ReconException &e)
                        {
                            throw ReconException(e.what(),__FILE__,__LINE__);
                        }
                    }
                }

                std::cout << "Configuring "<<moduleItem.m_sModule<<" module with "<<moduleItem.parameters.size()<<" parameters\n";
                module->GetModule()->Configure(config, moduleItem.parameters);
                std::cout << "Adding PreProcModule to the processing chain\n";
                engine->AddPreProcModule(module);
            }
            catch (ReconException& e)
            {
                throw ReconException(e.what(), __FILE__, __LINE__);
            }
        }
    }

    SetBackProjector(config, engine, interactor);
    return engine;
}

void ReconFactory::SetBackProjector(ReconConfig& config, ReconEngine* engine, kipl::interactors::InteractionBase* interactor)
{
    if (config.backprojector.m_bActive == true) {
        BackProjItem* module = nullptr;
        try {
            module = new BackProjItem("muhrecbp", config.backprojector.m_sSharedObject, config.backprojector.m_sModule, interactor);

            module->GetModule()->Configure(config, config.backprojector.parameters);
            engine->SetBackProjector(module);
        } catch (ReconException& e) {
            throw ReconException(e.what(), __FILE__, __LINE__);
        }
    }
}


