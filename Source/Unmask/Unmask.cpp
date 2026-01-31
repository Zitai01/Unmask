// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unmask.h"
#include "Modules/ModuleManager.h"

#include "IGIModule.h"
#include "IGIGPT.h"

DEFINE_LOG_CATEGORY_STATIC(LogIGIUESample, Log, All);

class FIGIUESample : public FDefaultGameModuleImpl
{
    virtual void StartupModule() override
    {
        FCoreDelegates::OnPostEngineInit.AddLambda([]()
            {
                UE_LOG(LogIGIUESample, Log, TEXT("IGI UE sample startup lambda started"));

                FIGIModule* IGIModulePtr{ FModuleManager::GetModulePtr<FIGIModule>(FName("IGI")) };
                if (IGIModulePtr == nullptr)
                {
                    UE_LOG(LogIGIUESample, Error, TEXT("CANNOT FIND IGI MODULE"));
                    return;
                }

                IGIModulePtr->LoadIGICore();

                UE_LOG(LogIGIUESample, Log, TEXT("IGI UE sample startup lambda ended"));
            });

        FCoreDelegates::OnEnginePreExit.AddLambda([]()
            {
                UE_LOG(LogIGIUESample, Log, TEXT("IGI UE sample shutdown lambda started"));

                FIGIModule* IGIModulePtr{ FModuleManager::GetModulePtr<FIGIModule>(FName("IGI")) };
                if (IGIModulePtr == nullptr)
                {
                    UE_LOG(LogIGIUESample, Error, TEXT("CANNOT FIND IGI MODULE"));
                    return;
                }

                IGIModulePtr->UnloadIGICore();

                UE_LOG(LogIGIUESample, Log, TEXT("IGI UE sample shutdown lambda ended"));
            });

        UE_LOG(LogIGIUESample, Log, TEXT("IGI UE sample module started"));
    }

    virtual void ShutdownModule() override
    {
        UE_LOG(LogIGIUESample, Log, TEXT("IGI UE sample module shutdown"));
    }
};

IMPLEMENT_PRIMARY_GAME_MODULE(FIGIUESample, Unmask, "Unmask");

DEFINE_LOG_CATEGORY(LogUnmask)