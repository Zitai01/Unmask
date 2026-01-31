// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "Templates/PimplPtr.h"

class FIGIGPT;

// These replicate some of the types defined in nvigi.h
namespace nvigi
{
    using Result = uint32_t;
    struct InferenceInterface;
    struct alignas(8) PluginID;
    struct alignas(8) CudaParameters;
}

class IGI_API FIGIModule : public IModuleInterface
{
public:

    static FIGIModule& Get()
    {
        return FModuleManager::GetModuleChecked<FIGIModule>(FName(UE_MODULE_NAME));
    }

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

    bool LoadIGICore();
    bool UnloadIGICore();

    nvigi::Result LoadIGIFeature(const nvigi::PluginID& Feature, nvigi::InferenceInterface** Interface, const UTF8CHAR* UTF8PathToPlugin = nullptr);
    nvigi::Result UnloadIGIFeature(const nvigi::PluginID& Feature, nvigi::InferenceInterface* Interface);

    const FString GetModelsPath() const;

    FIGIGPT* GetGPT();

    void Test();

private:
    class Impl;
    TPimplPtr<Impl> Pimpl;
};

// Convert nvigi::Result to a readable message
IGI_API FString GetIGIStatusString(nvigi::Result Result);
